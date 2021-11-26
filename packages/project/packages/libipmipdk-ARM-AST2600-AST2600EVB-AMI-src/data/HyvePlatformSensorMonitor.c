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
	INT8U reading;
	INT8U status;
} PACKED HyveSensorReadArrt_T;

HyveSensorReadArrt_T g_SensorAlanTest[2] = {0};


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

	switch (target)
	{
	case HYVE_LUN_NUM(BMC_SENSOR_LUN00, SENSOR_NUM_ALANTEST_LUN00):
			*phal->pbyte = g_SensorAlanTest[0].reading;
			phal->status_code = g_SensorAlanTest[0].status;
			break;
	case HYVE_LUN_NUM(BMC_SENSOR_LUN01, SENSOR_NUM_ALANTEST_LUN01):
			*phal->pbyte = g_SensorAlanTest[1].reading;
			phal->status_code = g_SensorAlanTest[1].status;
			break;
	default:
		printf("[%s] Could not find the sensorNum %#02x, LUN:%02x\n", __func__, sensorNum, sensorLUN);
		phal->status_code = HAL_ERR_READ;
		return -1;
	}
	return 0;
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
	
	if (0) { BMCInst = BMCInst; }
	
	printf("[ INFO ] - Launch %s\n", __func__);

	g_SensorAlanTest[0].status = HAL_ERR_NONE;
	g_SensorAlanTest[1].status = HAL_ERR_NONE;
	while (1) {
		if (IsCardInFlashMode()) {
			OS_TIME_DELAY_HMSM(0, 0, 5, 0);
			continue;
		}

		g_SensorAlanTest[0].reading++;
		g_SensorAlanTest[1].reading++;
		
		OS_TIME_DELAY_HMSM(0, 0, 1, 0);
	} // end while
	OS_DELETE_THREAD();
}
