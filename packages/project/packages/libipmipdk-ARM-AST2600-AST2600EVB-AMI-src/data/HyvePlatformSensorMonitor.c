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
#include "PDKHW.h"
#include "SensorAPI.h"
#include "SDRFunc.h"

#include "HyveCommon.h"



#define POLL_INTERVAL_3V3BATTERY					(3600) // seconds
#define POWERON_DELAY_CPU							(30) // seconds
#define POWERON_DELAY_DIMM							(30) // seconds
#define POWERON_DELAY_VR							(30) // seconds
#define SENSOR_READ_RETRY_COUNT						(3)
#define ADC_CH_3V3BATTERY							(7)



typedef struct {
	INT8U	status;
	INT8U	retryCount;
	INT16U	reading;
} HYVE_PACKED HyveSensorReadArrt_T;

typedef enum {
	SensorIndex_3V3Bat = 0,
	SensorIndex_TEMP_MB_1,
	SensorIndex_TEMP_MB_2,
	SensorIndex_TEMP_MB_3_0,
	SensorIndex_TEMP_MB_3_1,
	SensorIndex_TEMP_MB_3_2,
	SensorIndex_TEMP_MB_3_3,
	SensorIndex_TEMP_MB_3_4,
	SensorIndex_TEMP_MB_3_5,
	SensorIndex_TEMP_MB_3_6,
	SensorIndex_TEMP_MB_3_7,
	SensorIndex_TEMP_MB_3_8,
	SensorIndex_TEMP_CPU0,
	SensorIndex_PWR_CPU0,
	SensorIndex_TEMP_DIMMA0,
	SensorIndex_TEMP_DIMMB0,
	SensorIndex_TEMP_DIMMC0,
	SensorIndex_TEMP_DIMMD0,	
	SensorIndex_TEMP_DIMME0,
	SensorIndex_TEMP_DIMMF0,
	SensorIndex_TEMP_DIMMG0,
	SensorIndex_TEMP_DIMMH0,		
	SensorIndex_TEMP_DIMMI0,
	SensorIndex_TEMP_DIMMJ0,
	SensorIndex_TEMP_DIMMK0,
	SensorIndex_TEMP_DIMML0,
	SensorIndex_TEMP_P0SOCVR0,
	SensorIndex_TTEMP_P0V11VR0,
	SensorIndex_TEMP_P0IOVR0,
	SensorIndex_PWR_P0SOCVR0POUT,
	SensorIndex_PWR_P0V11VR0POUT,
	SensorIndex_PWR_P0IOVR0POUT,
	SensorIndex_TEMP_FAN_BOARD,
	SensorIndex_TEMP_FP,
	SensorIndex_TEMP_MP,
	SensorReadArrtIndex_MAX
} HyvePlatformSensorReadArrtIndex;

static const INT16U g_sensorIndexTable[SensorReadArrtIndex_MAX] = {
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_VOLT_BATP3V),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_1),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_2),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_1),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_2),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_3),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_4),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_5),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_6),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_7),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MB_3_8),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_CPU0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_PWR_CPU0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMA0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMB0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMC0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMD0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMME0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMF0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMG0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMH0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMI0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMJ0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMMK0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_DIMML0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_P0SOCVR0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_P0V11VR0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_P0IOVR0),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_PWR_P0SOCVR0POUT),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_PWR_P0V11VR0POUT),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_PWR_P0IOVR0POUT),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_FAN_BOARD),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_FP),
		HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_TEMP_MP),
};

INT8U g_Is_DIMM_Ready = FALSE;
INT8U g_Is_HostIn_S3_State = FALSE;
INT8U g_Is_HostIn_S5_State = FALSE;
INT8U g_Is_CPUPwrGood = FALSE;

static HyveSensorReadArrt_T g_SensorReadArrt[SensorReadArrtIndex_MAX] = {0};
static INT32U g_HostPwrOnCount = 0;



/*-----------------------------------------------------------------
 * @fn HyvePlatform_Get_ExtBoardTMP75Sensors
 * @brief	To get the extended board TMP75 sensor list
 *
 * @param [out] pCount - To output the count of the list
 *
 * @return    The pointer of HyvePlatformTMP75Sensor_T
 *-----------------------------------------------------------------*/
static HyvePlatformTMP75Sensor_T* HyvePlatform_Get_ExtBoardTMP75Sensors(INT8U* pCount)
{
	static HyvePlatformTMP75Sensor_T TMP75Sensors[] = {
			// sensorIndex					enable	is_standby	i2cBus                 					i2cAddr
			{ SensorIndex_TEMP_FAN_BOARD,	FALSE,	TRUE, 		HYFEPLATFORM_SMBUS_FAN_BOARD,			HYFEPLATFORM_ADDR_FAN_BOARD_TEMP },
			{ SensorIndex_TEMP_FP,			FALSE,	TRUE,		HYFEPLATFORM_SMBUS_FP_MP_DBGCARD_CPLD,	HYFEPLATFORM_ADDR_FP_TEMP},
			{ SensorIndex_TEMP_MP,			FALSE,	TRUE,		HYFEPLATFORM_SMBUS_FP_MP_DBGCARD_CPLD,	HYFEPLATFORM_ADDR_MP_TEMP},
	};
	*pCount = HYVE_ARRAYSIZE(TMP75Sensors);
	return TMP75Sensors;
}

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
	INT16U target = HYVE_LUN_NUM(sensorLUN, sensorNum);
	INT16U index = 0;
	INT8U is_WordVal = FALSE;

	// Find the mapping index
	for (index = 0; index < HYVE_ARRAYSIZE(g_sensorIndexTable); index++) {
		if (target == g_sensorIndexTable[index]) { break; }
	}
	if (index >= SensorReadArrtIndex_MAX) {
		printf("[%s] Could not find the sensorNum %#02x, LUN:%02x\n", __func__, sensorNum, sensorLUN);
		phal->status_code = HAL_ERR_READ;
		return -1;
	}
	if (SensorIndex_3V3Bat == index) {
		is_WordVal = TRUE;
	}
	if (!is_WordVal) {
		// it's a one-byte reading
		*phal->pbyte = (g_SensorReadArrt[index].reading & 0x00ff);
	} else {
		// it's a two-byte reading
		*phal->pword = g_SensorReadArrt[index].reading;
	}
	phal->status_code = g_SensorReadArrt[index].status;
	return 0;
}

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
	static INT32U preJiffy = (POLL_INTERVAL_3V3BATTERY + 1); /* to trigger reading at first time */
	static INT8U is_ready = FALSE, is_open = FALSE, wait_count = 0;
	int ret = 0;

	if (NULL == g_HALADCHandle[HAL_ADC_READ]) { return -1; }

	if (HYFEPLATFORM_JIFFY_DIFF(preJiffy) > POLL_INTERVAL_3V3BATTERY) {
		unsigned short rData = 0;
		INT8U is_done = FALSE;

		if (FALSE == is_ready) {
			if (FALSE == is_open) {
				if (-1 != (ret = HyvePlatform_3V3BatteryAccess(TRUE))) {
					is_open = TRUE;
					// After enable the ADC access of the 3V3 battery
					// need to wait a while to make sure the reading value is stable
				}
			} else {
				if (++wait_count > 2) {
					is_ready = TRUE;
					wait_count = 0;
				}
			}
		} else {
			ret = ((int(*)(int, unsigned short*))g_HALADCHandle[HAL_ADC_READ])(ADC_CH_3V3BATTERY, &rData);
			if (!ret) {
				 // The ADC reading is a 10-bit value, left shift 2 bit to 8 bit
				g_SensorReadArrt[SensorIndex_3V3Bat].reading = rData >> 2;
				g_SensorReadArrt[SensorIndex_3V3Bat].status = HAL_ERR_NONE;
				g_SensorReadArrt[SensorIndex_3V3Bat].retryCount = 0;
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
				is_open = FALSE;
				preJiffy = HYFEPLATFORM_JIFFY;
			}
		}
	}
	return ret;
}

static void HyvePlatform_Sensor_MBTemp()
{
	static const INT8U TMP75Addrs[] = { HYFEPLATFORM_ADDR_MB_TMP75_1, HYFEPLATFORM_ADDR_MB_TMP75_2 };
	INT8U i = 0, sensorIndex = SensorIndex_TEMP_MB_1;

	for (i = 0; i < HYVE_ARRAYSIZE(TMP75Addrs); i++) {
		int data = 0;

		if (HyveTMP_75_ReadTemp(HYFEPLATFORM_SMBUS_MB_TEMP_FRU, TMP75Addrs[i], &data) < 0) {
			if (g_SensorReadArrt[sensorIndex].retryCount > SENSOR_READ_RETRY_COUNT) {
				g_SensorReadArrt[sensorIndex].status  = HAL_ERR_READ;
			} else {
				g_SensorReadArrt[sensorIndex].retryCount++;
			}
		} else {
			g_SensorReadArrt[sensorIndex].status = HAL_ERR_NONE;
			g_SensorReadArrt[sensorIndex].retryCount = 0;
			g_SensorReadArrt[sensorIndex].reading = data;
		}
		sensorIndex++;
	}
	sensorIndex = SensorIndex_TEMP_MB_3_0;
	for (i = 0; i < HyveTMP_Channel_9; i++) {
		int data = 0;

		if (HyveTMP_468_ReadTemp(HYFEPLATFORM_SMBUS_MB_TEMP_FRU, HYFEPLATFORM_ADDR_MB_TMP468, i, &data) < 0) {
			if (g_SensorReadArrt[sensorIndex].retryCount > SENSOR_READ_RETRY_COUNT) {
				g_SensorReadArrt[sensorIndex].status  = HAL_ERR_READ;
			} else {
				g_SensorReadArrt[sensorIndex].retryCount++;
			}
		} else {
			g_SensorReadArrt[sensorIndex].status = HAL_ERR_NONE;
			g_SensorReadArrt[sensorIndex].retryCount = 0;
			g_SensorReadArrt[sensorIndex].reading = data;
		}
		sensorIndex++;
	}
}

static inline INT8U is_PwrOnDelayOk(const INT8U delayCount)
{
	return g_HostPwrOnCount > delayCount;
}

static void HyvePlatform_Sensor_CPU(int BMCInst)
{
	static INT8U is_ready = FALSE;

	if (PDK_GetPSGood(BMCInst)) {
		if (is_ready && HYVEPLATFORM_IS_CPU_PWRGOOD) {
			INT8U rBuff[4] = {0};
			INT32U *pU32Data = (INT32U*)rBuff;

			// Read CPU temp
			if (HyveAMD_ReadCPU_Temp_Int(HYFEPLATFORM_APML_BUS, HYFEPLATFORM_SBTSI_ADDR,
										SENSOR_READ_RETRY_COUNT, rBuff) < 0) {
				if (g_SensorReadArrt[SensorIndex_TEMP_CPU0].retryCount > SENSOR_READ_RETRY_COUNT) {
					g_SensorReadArrt[SensorIndex_TEMP_CPU0].status  = HAL_ERR_READ;
				} else {
					g_SensorReadArrt[SensorIndex_TEMP_CPU0].retryCount++;
				}
			} else {
				g_SensorReadArrt[SensorIndex_TEMP_CPU0].status = HAL_ERR_NONE;
				g_SensorReadArrt[SensorIndex_TEMP_CPU0].retryCount = 0;
				g_SensorReadArrt[SensorIndex_TEMP_CPU0].reading = rBuff[0];
			}
			// Read CPU average package power consumption
			if (HyveAMD_ReadCPU_Power(HYFEPLATFORM_APML_BUS, HYFEPLATFORM_SBTSI_ADDR,
										SENSOR_READ_RETRY_COUNT, pU32Data) < 0) {
				if (g_SensorReadArrt[SensorIndex_PWR_CPU0].retryCount > SENSOR_READ_RETRY_COUNT) {
					g_SensorReadArrt[SensorIndex_PWR_CPU0].status  = HAL_ERR_READ;
				} else {
					g_SensorReadArrt[SensorIndex_PWR_CPU0].retryCount++;
				}
			} else {
				g_SensorReadArrt[SensorIndex_PWR_CPU0].status = HAL_ERR_NONE;
				g_SensorReadArrt[SensorIndex_PWR_CPU0].retryCount = 0;
				g_SensorReadArrt[SensorIndex_PWR_CPU0].reading = ((*pU32Data) / 1000);
			}			
		} else if (HyvePlatform_Is_CPU_PwrGood() && is_PwrOnDelayOk(POWERON_DELAY_CPU)) {
			is_ready = TRUE;
		}
	} else {
		is_ready = FALSE;
	}
}

static void HyvePlatform_Sensor_DIMM(int BMCInst)
{
	static INT8U is_ready = FALSE;

	if (PDK_GetPSGood(BMCInst)) {
		if (is_ready && HYVEPLATFORM_IS_DIMM_READY) {
			INT8U enableMux = TRUE, index = 0;
			INT8U sensorIndex = SensorIndex_TEMP_DIMMA0;
			INT8U busNum = HYFEPLATFORM_SPD_BUS_DIMM_AF;
			const INT8U busDIMMNum = HYVE_MAX_HOST_DIMM_NUM / 2;

			// Switch Mux ownership to BMC
			if (HyvePlatform_DIMM_MuxControl(Hyve_VALUE_SET, &enableMux) < 0) {
				for (index = 0; index < HYVE_MAX_HOST_DIMM_NUM; index++) {
					if (g_SensorReadArrt[sensorIndex].retryCount > SENSOR_READ_RETRY_COUNT) {
						g_SensorReadArrt[sensorIndex].status  = HAL_ERR_READ;
					} else {
						g_SensorReadArrt[sensorIndex].retryCount++;
					}
					sensorIndex++;
				}
				printf("%s: Unable to enable SPD Mux access\n", __func__);
				return;
			}
			// Read DIMM temp
			for (index = 0; index < HYVE_MAX_HOST_DIMM_NUM; index++) {
//				INT16U rData = 0;

				if (busDIMMNum == index) {
					// Change to another bus
					busNum = HYFEPLATFORM_SPD_BUS_DIMM_GL;
				}
#if 0 // TODO: wait 9121D MB
				if (HyveSPD_ReadTemp(busNum, SPD_ADDR_HIDXXX((index % busDIMMNum)),
									SENSOR_READ_RETRY_COUNT, &rData) < 0) {
					if (g_SensorReadArrt[sensorIndex].retryCount > SENSOR_READ_RETRY_COUNT) {
						g_SensorReadArrt[sensorIndex].status  = HAL_ERR_READ;
					} else {
						g_SensorReadArrt[sensorIndex].retryCount++;
					}
				} else {
					g_SensorReadArrt[sensorIndex].status = HAL_ERR_NONE;
					g_SensorReadArrt[sensorIndex].retryCount = 0;
					g_SensorReadArrt[sensorIndex].reading = rData;
				}
#endif
				sensorIndex++;
			}
		} else if (HyvePlatform_has_DIMMOwership() &&
					(Hyve_BIOS_POST_END == HyveExt_BIOS_Status(Hyve_VALUE_GET, 0)) &&
					is_PwrOnDelayOk(POWERON_DELAY_DIMM)) {
			is_ready = TRUE;
		}
	} else {
		is_ready = FALSE;
	}
}

static void HyvePlatform_Sensor_VR(int BMCInst)
{
	static INT8U is_ready = FALSE;
	static const INT8U VRAddrs[] = {
			HYFEPLATFORM_ADDR_VDD_CORE_0_VDD_SOC,
			HYFEPLATFORM_ADDR_VDD_CORE_1_VDD_11,
			HYFEPLATFORM_ADDR_VDD_VDDIO
	};

	if (PDK_GetPSGood(BMCInst)) {
		if (is_ready) {
			INT8U index = 0, sensorIndex = SensorIndex_TEMP_P0SOCVR0,
					sensorIndex2 = SensorIndex_PWR_P0SOCVR0POUT;

			for (index = 0; index < HYVE_ARRAYSIZE(VRAddrs); index++) {
				INT32U dataBuff = 0;

				// Read VR Temperature
				if (HyveExt_Send_PMBus_CMD(HYFEPLATFORM_SMBUS_CPU_VR, VRAddrs[index], CMD_READ_TEMPERATURE_1,
											HYVE_PSU_CMD_R, SENSOR_READ_RETRY_COUNT, (INT8U*)&dataBuff) < 0) {
					if (g_SensorReadArrt[sensorIndex].retryCount > SENSOR_READ_RETRY_COUNT) {
						g_SensorReadArrt[sensorIndex].status  = HAL_ERR_READ;
					} else {
						g_SensorReadArrt[sensorIndex].retryCount++;
					}
				} else {
					g_SensorReadArrt[sensorIndex].status = HAL_ERR_NONE;
					g_SensorReadArrt[sensorIndex].retryCount = 0;
					g_SensorReadArrt[sensorIndex].reading = HyvePSU_Convert_Linear11(TO_16U(&dataBuff));
				}
				dataBuff = 0;
				// Read VR Power Out
				if (HyveExt_Send_PMBus_CMD(HYFEPLATFORM_SMBUS_CPU_VR, VRAddrs[index], CMD_PSU_READ_POUT,
											HYVE_PSU_CMD_R, SENSOR_READ_RETRY_COUNT, (INT8U*)&dataBuff) < 0) {
					if (g_SensorReadArrt[sensorIndex2].retryCount > SENSOR_READ_RETRY_COUNT) {
						g_SensorReadArrt[sensorIndex2].status  = HAL_ERR_READ;
					} else {
						g_SensorReadArrt[sensorIndex2].retryCount++;
					}
				} else {
					g_SensorReadArrt[sensorIndex2].status = HAL_ERR_NONE;
					g_SensorReadArrt[sensorIndex2].retryCount = 0;
					g_SensorReadArrt[sensorIndex2].reading = HyvePSU_Convert_Linear11(TO_16U(&dataBuff));
				}
				sensorIndex++;
				sensorIndex2++;
			}
		} else {
			is_ready = is_PwrOnDelayOk(POWERON_DELAY_VR);
		}
	} else {
		is_ready = FALSE;
	}
}

static void HyvePlatform_Sensor_ExtBoard_Temp()
{
	static HyvePlatformTMP75Sensor_T *ExtBdTMP75Sensors = NULL;
	static INT8U sensorCount = 0;
	INT8U i = 0;

	if (!ExtBdTMP75Sensors) {
		ExtBdTMP75Sensors = HyvePlatform_Get_ExtBoardTMP75Sensors(&sensorCount);
		if (!ExtBdTMP75Sensors) { return; }
	}
	// Read TMP75 temp sensor of the extended boards
	for (i = 0; i < sensorCount; i++) {
		if (ExtBdTMP75Sensors[i].enable) {
			int data = 0;

			// Check if need Host power on
			if (!ExtBdTMP75Sensors[i].is_standby &&
					!HYVEPLATFORM_IS_SYS_PWRGOOD) {
				continue;
			}
			if (HyveTMP_75_ReadTemp(ExtBdTMP75Sensors[i].i2cBus, ExtBdTMP75Sensors[i].i2cAddr, &data) < 0) {
				if (g_SensorReadArrt[ExtBdTMP75Sensors[i].sensorIndex].retryCount > SENSOR_READ_RETRY_COUNT) {
					g_SensorReadArrt[ExtBdTMP75Sensors[i].sensorIndex].status  = HAL_ERR_READ;
				} else {
					g_SensorReadArrt[ExtBdTMP75Sensors[i].sensorIndex].retryCount++;
				}
			} else {
				g_SensorReadArrt[ExtBdTMP75Sensors[i].sensorIndex].status = HAL_ERR_NONE;
				g_SensorReadArrt[ExtBdTMP75Sensors[i].sensorIndex].retryCount = 0;
				g_SensorReadArrt[ExtBdTMP75Sensors[i].sensorIndex].reading = data;
			}
		}
	}
}

static void HyvePlatform_SensorInit(int BMCInst)
{
	_FAR_ BMCInfo_t *pBMCInfo = &g_BMCInfo[BMCInst];
	_FAR_ SDRRecHdr_T *pSDRRecHdr = NULL;
	INT8U sensorCount_TMP75 = 0, i = 0;
	HyvePlatformTMP75Sensor_T *ExtBdTMP75Sensors = HyvePlatform_Get_ExtBoardTMP75Sensors(&sensorCount_TMP75);

	pSDRRecHdr = SDR_GetFirstSDRRec(BMCInst);

	while (pSDRRecHdr) {
		if (FULL_SDR_REC == pSDRRecHdr->Type) {
			_FAR_ FullSensorRec_T *pFullRec = (_FAR_ FullSensorRec_T*)pSDRRecHdr;
			// Check the OwnerID
			if (pFullRec->OwnerID == pBMCInfo->IpmiConfig.BMCSlaveAddr) {
				// Find the Temp sensor
				if (IPMI_SENSOR_TEMP_TYPE == pFullRec->SensorType) {
					// Check if the platform SDR has the supported sensors
					if (ExtBdTMP75Sensors) {
						for (i = 0; i < sensorCount_TMP75; i++) {
							if ((!ExtBdTMP75Sensors[i].enable) &&
									(HYVE_LUN_NUM(pFullRec->OwnerLUN, pFullRec->SensorNum) ==
										g_sensorIndexTable[ExtBdTMP75Sensors[i].sensorIndex])) {
								ExtBdTMP75Sensors[i].enable = TRUE;
								printf("[%s] Find the %s sensor (0x%x), LUN: 0x%x  \n",
										__func__, pFullRec->IDStr, pFullRec->SensorNum, pFullRec->OwnerLUN);
								break;
							}
						}
					}
				}
			}
		}
		pSDRRecHdr = SDR_GetNextSDRRec(pSDRRecHdr, BMCInst);
	} // end of while
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
		g_SensorReadArrt[i].status = HAL_ERR_FUNC_NOT_SUPPORTED;
	}

	HyvePlatform_SensorInit(BMCInst);

	while (1) {
		if (IsCardInFlashMode()) {
			OS_TIME_DELAY_HMSM(0, 0, 5, 0);
			continue;
		}
		// Tick the g_HostPwrOnCount
		if (PDK_GetPSGood(BMCInst)) {
			g_HostPwrOnCount++;
		} else {
			g_HostPwrOnCount = 0;
		}
		if (HyvePlatform_Sensor_3V3Bat() < 0) {
			printf("%s: read 3V3 battery volt failed\n", __func__);
		}

		HyvePlatform_Sensor_MBTemp();
		HyvePlatform_Sensor_CPU(BMCInst);
		HyvePlatform_Sensor_DIMM(BMCInst);
		HyvePlatform_Sensor_VR(BMCInst);
		HyvePlatform_Sensor_ExtBoard_Temp();

		OS_TIME_DELAY_HMSM(0, 0, 1, 0);
	} // end while
	OS_DELETE_THREAD();
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_SensorMonitor2
 * @brief	The platform sensor monitor2 for PCIe devices or add-on cards.
 *
 * @param[in]	pArg - A pointer of void, passes BMCInst
 *
 * @return  0	- if thread exits
 *-----------------------------------------------------------------*/
void* HyvePlatform_SensorMonitor2(void* pArg)
{
	int BMCInst = (int)pArg;

	if (0) { BMCInst = BMCInst; }
	
	printf("[ INFO ] - Launch %s\n", __func__);

	while (1) {
		if (IsCardInFlashMode()) {
			OS_TIME_DELAY_HMSM(0, 0, 5, 0);
			continue;
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
	return HYVEPLATFORM_IS_CPU_PWRGOOD;
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

