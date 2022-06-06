 /******************************************************************
 *
 * @file	HyvePlatformFan.c
 * @brief	Provide the platform Fan control or other specific functions
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

#include "HyveCommon.h"


/********************* Macro definitions *********************/
#define NUM_FANCTRLIC							(2) // The number of fan control IC

/********************* Global variable definitions *********************/
const INT8U g_FSCI2CBusTable[] = {
		HYFEPLATFORM_SMBUS_FAN_HWMONIOTR, HYFEPLATFORM_SMBUS_FAN_BOARD,
};
//const INT8U g_FSCI2CAddrTable[] = {
//		HYFEPLATFORM_ADDR_FAN_HWMON, HYFEPLATFORM_ADDR_FAN_HWMON,
//};
const INT8U g_tachIndexTable[] = {
		TACH12, TACH13, TACH15, TACH14, TACH0, TACH1, TACH2, TACH3,
};
const INT8U g_pwmIndexTable[] = { PWM0, PWM1, PWM2, PWM3, };


/********************* Functions *********************/

INT8U HyvePlatform_FSC_GetConfigBankID()
{
	INT8U fscBankID = 0;

	switch (HYVEPLATFORM_SKU) {
	case PLATFORM_SKU_DEFAULT:
	case PLATFORM_SKU_HS9121D:
	default:
		break;
	}
	return fscBankID;
}

void HyvePlatform_FSC_Init(int BMCInst)
{
	HYVE_KEYWORDS(ambSensors, "AMB", "Outlet");
	HYVE_KEYWORDSLIST(listKW_amb,
					HYVE_KEYWORDSLIST_PUT(ambSensors));

	HYVE_KEYWORDS(curve0, "CPU");
	HYVE_KEYWORDS(curve1, "DIMM");
	HYVE_KEYWORDS(curve2, "OCP", "CARD");
	HYVE_KEYWORDS(curve3, "NVMe", "SSD");
	HYVE_KEYWORDSLIST(listKW_curves, 
					HYVE_KEYWORDSLIST_PUT(curve0),
					HYVE_KEYWORDSLIST_PUT(curve1),
					HYVE_KEYWORDSLIST_PUT(curve2),
					HYVE_KEYWORDSLIST_PUT(curve3));

	if (HyveFSC_Init(BMCInst, listKW_amb, listKW_curves) < 0) {
		if (HYVEFSC_SETALLFANDUTY(FULL_FANDUTY) < 0) {
			printf("[%s]: Error in setting all fan full duty\n", __func__);
		}
	}
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformFan_GetFanDir
 * 
 * @brief	To get the fan direction by GPIO pin indicator
 * 
 * @return  PlatformFanDir_In / PlatformFanDir_Out / PlatformFanDir_Unkonwn
 *-----------------------------------------------------------------*/
INT8U HyvePlatformFan_GetFanDir()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_FAN_DIRECTION)) < 0) {
		return PlatformFanDir_Unkonwn;
	}
	if (HYVE_GPIO_DATA_HIGH == ret) {
		return PlatformFanDir_In;
	}
	return PlatformFanDir_Out;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformFan_NCT7362Y_Init
 * 
 * @brief	To init the fan control IC NCT7362Y
 * 
 * @param[None]
 * 
 * @return  0	- success.
 *			-1	- otherwise 
 *-----------------------------------------------------------------*/
int HyvePlatformFan_NCT7362Y_Init()
{
	const INT8U pinFunc[NCT7362Y_PIN_NUM] = {
			// GPIO00 ~ GPIO03
			NCT7362Y_FUNC_PWM, NCT7362Y_FUNC_PWM, NCT7362Y_FUNC_PWM, NCT7362Y_FUNC_PWM,
			// GPIO04 ~ GPIO07
			NCT7362Y_FUNC_FANIN, NCT7362Y_FUNC_FANIN, NCT7362Y_FUNC_FANIN, NCT7362Y_FUNC_FANIN,
			// GPIO10 ~ GPIO13
			NCT7362Y_FUNC_FANIN, NCT7362Y_FUNC_FANIN, NCT7362Y_FUNC_FANIN, NCT7362Y_FUNC_FANIN,
			// GPIO14 ~ GPIO17
			NCT7362Y_FUNC_GPIO, NCT7362Y_FUNC_GPIO, NCT7362Y_FUNC_GPIO, NCT7362Y_FUNC_GPIO
	};
	INT8U i = 0;
	int ret = 0;

	for (i = 0; i < NUM_FANCTRLIC; i++) {
		INT8U portVal = 0;

		if (HyveFSC_NCT7362Y_SetAllPinFunc(g_FSCI2CBusTable[i], HYVEFSC_I2C_ADDR, pinFunc) < 0) { ret = -1; }
		// Check fan present pin GPIO dir
		if (!HyveFSC_NCT7362Y_GPIOPortDir(Hyve_VALUE_GET, g_FSCI2CBusTable[i], HYVEFSC_I2C_ADDR, 1, &portVal)) {
			HyveFSCDBG("%s: GPIO Port 1: 0x%x\n", __func__, portVal);
			if (0xF0 != (0xF0 & portVal)) {
				portVal |= 0xF0;
				if (HyveFSC_NCT7362Y_GPIOPortDir(Hyve_VALUE_SET, g_FSCI2CBusTable[i], HYVEFSC_I2C_ADDR, 1, &portVal) < 0) {
					HyveFSCDBG("%s: Unable to set GPIO Port1 Dir\n", __func__);
					ret = -1;
				}
			}
		}
	}

	return ret;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformFan_PresentDetect
 * 
 * @brief	To check fan presence
 * 
 * @param[None]
 * 
 * @return  None
 *-----------------------------------------------------------------*/
void HyvePlatformFan_PresentDetect()
{
	static INT8U is_detectDone = 0;

	/* By HW design,
	 * 1. The fan presence is determined if the fan cable is connected 
	 * 2. Once the cable is connected, all the fan present pins are pull low,
	 *    it doesn't matter if there is actually a fan connected
	 * 3. It doesn't support fan Hot-plug
	 * 
	 * So, there is no need to detect fan presence every time */
	if (is_detectDone) { return; }

	HyveFanTach_T *pFanTach = HyveFSC_GetFanTachList();
	INT8U i = 0, fansPresence = 0, detected = 0;

	for (i = 0; i < NUM_FANCTRLIC; i++) {
		INT8U retryCount = 3, portVal = 0xFF;

		do {
			if (!HyveFSC_NCT7362Y_GPIOPort(Hyve_VALUE_GET, g_FSCI2CBusTable[i],
											HYVEFSC_I2C_ADDR, 1, &portVal)) {
				detected |= 0x0F << (4 * i);
				break;
			}
		} while (retryCount--);
		portVal = ((~(portVal) >> 4) & 0x0F);
		fansPresence |= ((((portVal & 0x04) << 1) | ((portVal & 0x08) >> 1) | (portVal & 0x03)) << (i * 4));
	}
	for (i = 0; i < HYVEFSC_MAX_FAN_NUM; i++) {
		pFanTach[i].is_Present = (fansPresence & 0x01);
		fansPresence >>= 1;
	}
	if (0xFF == detected) { is_detectDone = 1; }
}
