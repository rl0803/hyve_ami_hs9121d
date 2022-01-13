 /******************************************************************
 *
 * @file	HyvePlatformROT.c
 * @brief	Provide the platform ROT related functions
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

#include "HyveCommon.h"



/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_ReqResetBMC
 * @brief	To request the ROT to reset the BMC
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_ReqResetBMC()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_FM_SRST_REQ2_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_FM_SRST_REQ2_N) > -1) { return 0; }
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_ReqFwAuth
 * @brief	To request the ROT to do the FW auth
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_ReqFwAuth()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_FM_BMC_RESET_DET_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_FM_BMC_RESET_DET_N) > -1) { return 0; }
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_ReqBIOSFwAuth
 * @brief	To request the ROT to do the BIOS FW auth
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_ReqBIOSFwAuth()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_High(IO_FM_CEC_BIOS_RESET_IN) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_Low(IO_FM_CEC_BIOS_RESET_IN) > -1) { return 0; }
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_GetBIOSFlashSelect
 * @brief	To know which BIOS the ROT is accessing
 *
 * @param[out]  pFlashIndex  - The INT8U pointer to input/output the BIOS flash index
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_GetBIOSFlashSelect(INT8U* pFlashIndex)
{
	int ret = 0, ret1 = 0;

	if (!pFlashIndex) { return -1; }

	ret = HyveExt_GPIO_Get_Data(IO_FM_BIOS_FLASH_SEL0_N);
	ret1 = HyveExt_GPIO_Get_Data(IO_FM_BIOS_FLASH_SEL1_N);
	// If one of GPIO pin unavailable, return -1
	if (ret  < 0 || ret1 < 0) { return -1; }

	// Check if the ROT is accessing BIOS flash 0
	if (HYVE_GPIO_DATA_LOW == ret) {
		*pFlashIndex = PrimaryFlash;
		return 0;
	}
	// Check if the ROT is accessing BIOS flash 1
	if (HYVE_GPIO_DATA_LOW == ret) {
		*pFlashIndex = SecondaryFlash;
		return 0;
	}
	*pFlashIndex = ROT_YIELD_BIOS_FLASH;
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_InformSMBusErr
 * @brief	To inform the ROT the SMBus error occurs
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_InformSMBusErr()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_IRQ_SMB_ROT_ALRT_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_IRQ_SMB_ROT_ALRT_N) > -1) { return 0; }
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_InformBMCReset
 * @brief	To inform the ROT the BMC reset occurs
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_InformBMCReset()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_FM_SRST_REQ1_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_FM_SRST_REQ1_N) > -1) { return 0; }
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformROT_InformWDT2Timeout
 * @brief	To inform the ROT the BMC watchdog2 timeout occurs
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformROT_InformWDT2Timeout()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_FM_ROT_WDRST2_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_FM_ROT_WDRST2_N) > -1) { return 0; }
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

INT8U HyvePlatformROT_Is_BIOS_FwAuthCompleted()
{
	int ret = 0;
	if ((ret = HyveExt_GPIO_Get_Data(IO_FM_CEC_BIOS_AUTH_COMP)) < 0) { ret = 0; }
	return (ret & 0x01);
}


