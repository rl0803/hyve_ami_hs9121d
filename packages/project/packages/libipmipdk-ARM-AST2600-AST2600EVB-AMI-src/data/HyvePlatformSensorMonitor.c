 /******************************************************************
 *
 * @file	HyvePlatformSensorMonitor.c
 * @brief	Provide the platform sensor monitor functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "IPMI_App.h"
#include "hal_hw.h"
#include "API.h"
#include "PendTask.h"
#include "safesystem.h"
#include "OSPort.h"
#include "EINTR_wrappers.h"
#include "flashlib.h"

#include "HyveCommon.h"



typedef struct {
	INT8U	status;
	INT8U	retryCount;
	INT16U	reading;
} HYVE_PACKED HyveSensorReadArrt_T;


typedef enum {
	SensorIndex_3V3Bat = 0,
	SensorReadArrtIndex_MAX
} HyvePlatformSensorReadArrtIndex;



INT8U g_Is_DIMM_Ready = FALSE;
INT8U g_Is_HostIn_S3_State = FALSE;
INT8U g_Is_HostIn_S5_State = FALSE;
INT8U g_Is_CPUPwrGood = FALSE;

HyveSensorReadArrt_T g_SensorReadArrt[SensorReadArrtIndex_MAX] = {0};


/* HS9121D Platform Sensors
ADC:
	


#define IO_P12V_STBY_SCALED                 GPIOT0 // ADC-0, Standby 12V
#define IO_P12V_SCALED                      GPIOT1 // ADC-1, power supply 12V
#define IO_P3V3_SCALED                      GPIOT2 // ADC-2, power supply 3.3V
#define IO_P3V3_STBY_SCALED                 GPIOT3 // ADC-3, Standby 3.3V
#define IO_P0_VDD_33_DUAL_SCALED            GPIOT4 // ADC-4, CPU VDD 3.3V
#define IO_P5V_AUX_SCALED                   GPIOT5 // ADC-5, AUX 5V
#define IO_P0_VDD_18_DUAL_SCALED            GPIOT6 // ADC-6, CPU VDD 1.8V
#define IO_A_P3V_BAT_SCALED                 GPIOT7 // ADC-7, 3.3V battery

#define IO_P0_VDD_11_SUS_SCALED             GPIOU0 // ADC-8, CPU VDD 1.1V
#define IO_P0_VDD_VDDIO_RUN_SCALED          GPIOU1 // ADC-9, CPU VDDIO 
#define IO_P0_VDD_SOC_RUN_SCALED            GPIOU2 // ADC-10, CPU VDDCR_SOC
#define IO_P0_VDD_CORE_0_SCALED             GPIOU3 // ADC-11, CPU VDDCR_CPU0
#define IO_P0_VDD_CORE_1_SCALED             GPIOU4 // ADC-12, CPU VDDCR_CPU1

*/


/*-------------------------------------------------------------------------
 * @fn HyveMonitor_GetReadingValBySensorNum
 * @brief A hook function for flexible sensor reading purpose
 * 
 * @param[in]	sensorNum - sensor number
 * @param[in]	senLUN - sensor LUN
 * @param[out]	phal - a pointer of hal_t to retrieve a sensor reading

 * @return  0, if success
 *         -1, otherwise
 *------------------------------------------------------------------------*/
int HyveMonitor_GetReadingValBySensorNum(const INT8U sensorNum, const INT8U sensorLUN, hal_t* phal)
{
	INT16U target = sensorNum | (sensorLUN) << 8;
	INT16U index = SensorReadArrtIndex_MAX;
	
	switch (target)
	{
	case HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_VOLT_BATP3V):
		// it's a two-byte reading
		*phal->pword = g_SensorReadArrt[SensorIndex_3V3Bat].reading;
		phal->status_code = g_SensorReadArrt[SensorIndex_3V3Bat].status;
		return 0;
	default:
		index = SensorReadArrtIndex_MAX;
		break;
	}
	if (SensorReadArrtIndex_MAX == index) {
		printf("[%s] Could not find the sensorNum %#02x, LUN:%02x\n", __func__, sensorNum, sensorLUN);
		phal->status_code = HAL_ERR_READ;
		return -1;
	}
	// it's a one-byte reading
	*phal->pbyte = (g_SensorReadArrt[index].reading & 0x00ff);
	phal->status_code = g_SensorReadArrt[index].status;
	return 0;
}


// TODO: The mechanism for 3.3V battery volt reading
// #define IO_A_P3V_BAT_SCALED                 GPIOT7 // ADC-7, 3.3V battery
// #define IO_A_P3V_BAT_SCALED_EN              GPIOV4 // GPIO, Output, High: to enable the mosfet that ADC 'P3V_BAT' can be available; default should keep Low to avoid the bat drained out

#define ADC_CH_3V3BATTERY				(7)
#define POLL_INTERVAL_3V3BATTERY		(3) //(3600)

#define SENSOR_READ_RETRY_COUNT			(3)


/*-----------------------------------------------------------------
 * @fn HyvePlatform_3V3BatteryAccess
 * @brief	To enable/disable the access of the 3V3 Battery that ADC 'P3V_BAT' can be available
 *
 * @param[in]  enable  - True, if enable; False, if disable
 *
 * @return    0 - if success
 *           -1 - otherwise
 * 
 * Note:
 *     Default should keep Low to avoid the battery drained out
 *-----------------------------------------------------------------*/
static inline int HyvePlatform_3V3BatteryAccess(const INT8U enable)
{
	if (TRUE == enable) {
		return HyveExt_GPIO_Set_Data_High(IO_A_P3V_BAT_SCALED_EN) < 0 ? -1 : 0;
	}
	return HyveExt_GPIO_Set_Data_Low(IO_A_P3V_BAT_SCALED_EN) < 0 ? -1 : 0;
}

static int HyvePlatform_Sensor_3V3Bat()
{
	static INT32U preJiffy = - 1; /* to trigger reading at first time */
	static INT8U is_ready = FALSE;
	int ret = 0;

	if (NULL == g_HALADCHandle[HAL_ADC_READ]) { return -1; }

	if (HYFEPLATFORM_JIFFY_DIFF(preJiffy) > POLL_INTERVAL_3V3BATTERY) {
		unsigned short rData = 0;
		INT8U is_done = FALSE;

		if (FALSE == is_ready) {
			ret = HyvePlatform_3V3BatteryAccess(TRUE);
			if (-1 != ret) {
				is_ready = TRUE;
				// After enable the ADC access of the 3V3 battery
				// need to wait a while to make sure the reading value is stable
			}
		} else {				
			ret = ((int(*)(int, unsigned short*))g_HALADCHandle[HAL_ADC_READ])(ADC_CH_3V3BATTERY, &rData);
			if (!ret) {
				g_SensorReadArrt[SensorIndex_3V3Bat].status = HAL_ERR_NONE;
				g_SensorReadArrt[SensorIndex_3V3Bat].retryCount = 0;
				 // The ADC reading is a 10-bit value, left shift 2 bit to 8 bit
				g_SensorReadArrt[SensorIndex_3V3Bat].reading = rData >> 2;
				is_done = TRUE;
			} else {
				if (g_SensorReadArrt[SensorIndex_3V3Bat].retryCount > SENSOR_READ_RETRY_COUNT) {
					g_SensorReadArrt[SensorIndex_3V3Bat].status = HAL_ERR_READ;
					is_done = TRUE;
				} else {
					g_SensorReadArrt[SensorIndex_3V3Bat].retryCount++;
				}
			}
			if (TRUE == is_done) {
				HyvePlatform_3V3BatteryAccess(FALSE);
				is_ready = FALSE;
				preJiffy = HYFEPLATFORM_JIFFY;
			}
		}
	}
	return ret;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_SensorMonitor
 * @brief	The platform sensor monitor.
 *
 * @param[in]	pArg - A pointer of void, passes BMCInst
 *
 * @return  0	- if thread exits
 *-----------------------------------------------------------------*/
void* HyvePlatform_SensorMonitor(void* pArg)
{
	int BMCInst = (int)pArg;
	INT16U i = 0;
	
	if (0) { BMCInst = BMCInst; }
	
	printf("[ INFO ] - Launch %s\n", __func__);

	// Init the sensor reading status
	for (i = 0; i < HYVE_ARRAYSIZE(g_SensorReadArrt); i++) {
		g_SensorReadArrt[i].status = HAL_ERR_NONE;
	}

	while (1) {
		if (IsCardInFlashMode()) {
			OS_TIME_DELAY_HMSM(0, 0, 5, 0);
			continue;
		}

		if (HyvePlatform_Sensor_3V3Bat() < 0) {
			printf("%s: read 3V3 battery volt failed\n", __func__);
		}

		OS_TIME_DELAY_HMSM(0, 0, 1, 0);
	} // end while
	OS_DELETE_THREAD();
}

/*-----------------------------------------------------------------
 * @fn	HyvePlatform_has_DIMMOwership
 * @brief	To check if has ownership of the SMBus access of DIMM
 *
 * @param None
 *
 * @return    1 - has the ownership
 *            0 - otherwise
 *-----------------------------------------------------------------*/
INT8U HyvePlatform_has_DIMMOwership()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_P0_SPD_HOST_CTRL_L)) < 0) { ret = 0; }
	g_Is_DIMM_Ready = (ret & 0x01);
	return HYVEPLATFORM_IS_DIMM_READY;
}

INT8U HyvePlatform_Is_CPU_PwrGood()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_P0_PWRGD)) < 0) { ret = 0; }
	g_Is_CPUPwrGood = (ret & 0x01);
	return HYVEPLATFORM_CPU_PWRGOOD;
}

INT8U HyvePlatform_Is_HostInS3()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_PLD_BMC_SLP_S3_L)) < 0) { ret = 1; }
	g_Is_HostIn_S3_State = ((~ret) & 0x01);
	return HYVEPLATFORM_IS_HOST_IN_S3;
}

INT8U HyvePlatform_Is_HostInS5()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_PLD_BMC_SLP_S5_L)) < 0) { ret = 1; }
	g_Is_HostIn_S5_State = ((~ret) & 0x01);
	return HYVEPLATFORM_IS_HOST_IN_S5;
}

