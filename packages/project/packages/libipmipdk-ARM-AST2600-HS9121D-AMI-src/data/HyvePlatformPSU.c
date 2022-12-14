 /******************************************************************
 *
 * @file	HyvePlatformPSU.c
 * @brief	Provide the platform PSU monitor or other specific functions
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


/********************* Global variable definitions *********************/
INT8U g_Is_PSUPwrGood = FALSE; // This variable can only be set by HyvePlatform_Is_PSU_PwrGood or IRQhndlr_PWRGD_PSU_PWROK

const INT8U g_psuLocationTable[] = { HyvePSU_Location_Left, HyvePSU_Location_Right };

void* HyvePlatform_PSUTask(void* pArg)
{
	int BMCInst = (int)pArg;
	INT8U psuNum = 0;
	UINT32 preJiffy = 0;
	INT16U fanSenLUN_NUM[HYVE_PSU_MAX_NUM][1] = {
		// PSU0
		{ HYVE_LUN_NUM(BMC_SENSOR_LUN, SENSOR_NUM_PSU0_FAN)},
		// PSU1
		{ HYVE_LUN_NUM(BMC_SENSOR_LUN, SENSOR_NUM_PSU1_FAN)}
	};
	const HyvePSU_StatusInfo_T *pHyvePSUStatInfo= HyvePSU_GetPSUStatusInfo(0);

	if (0) { BMCInst = BMCInst; }
	
	printf("[ INFO ] - Launch %s\n", __func__);

	// Init Platform PSU config
	HyvePSU_Init();
	for (psuNum = 0; psuNum < HYVE_PSU_MAX_NUM; psuNum++) {
		HyvePSU_SetFanSensorTable(psuNum, fanSenLUN_NUM[psuNum],
				sizeof(fanSenLUN_NUM[psuNum]) / sizeof(fanSenLUN_NUM[psuNum][0]));
	}

	while (1) {
		if (IsCardInFlashMode()) {
			OS_TIME_DELAY_HMSM(0, 0, 5, 0);
			continue;
		}
		for (psuNum = 0; psuNum < HYVE_PSU_MAX_NUM; psuNum++) {			
			if (HyvePSU_IsInFWupdate(psuNum)) {
				break; // If one of PSUs is in FW update, just stop accessing the I2C Bus to avoid FW update fail
				// TODO: implement PSU FW update
			} else { // Normal routine
				INT8U is_PSUlost = 0;
				// char *errMsg = "AC lost";

				// Read PSU status
				HyvePSU_Read_PSU_Info(psuNum, HYVE_PSU_PEC_OFF);
				// Check PSU presence
				if ((!pHyvePSUStatInfo[psuNum].isPresent)) {
					is_PSUlost = 1;
					// errMsg = "Removed";
				}
				// Check AC lost or PSU removed
				if (HYVE_PSU_AC_LOST == pHyvePSUStatInfo[psuNum].isAcLost) {
					is_PSUlost = 1;
				}
				// per 10 second print the msg
				if (is_PSUlost && HYFEPLATFORM_JIFFY_DIFF(preJiffy) > 10) {
					//TODO: Do something, if PSU removed or AC lost occurs
					// printf("[INFO] %s: Detect the PSU(%d) %s\n", __func__, psuNum, errMsg);
					preJiffy = HYFEPLATFORM_JIFFY;
				}
			}
		}
		OS_TIME_DELAY_HMSM(0, 0, 1, 0);
	} // end while
	OS_DELETE_THREAD();
}

/*-----------------------------------------------------------------
 * @fn	HyvePlatform_Is_PSU_PwrGood
 * @brief	To check GPIO pin - power good of the PSU
 *
 * @param None
 *
 * @return    1 - power good asserted
 *            0 - otherwise
 *-----------------------------------------------------------------*/
INT8U HyvePlatform_Is_PSU_PwrGood()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_PWRGD_PS_PWROK_BMC)) < 0) { ret = 0; }
	g_Is_PSUPwrGood = (ret & 0x01);
	return HYVEPLATFORM_IS_PSU_PWRGOOD;
}


