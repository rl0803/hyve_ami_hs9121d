 /******************************************************************
 *
 * @file	HyvePlatformHooks.c
 * @brief	To provide platform hook functions
 * 			
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "IPMI_App.h"
#include "hal_hw.h"
#include "API.h"
#include "PendTask.h"
#include "safesystem.h"
#include "PDKAccess.h"

#include "HyveCommon.h"



/*----------------------------------------------------------------------------
 * @fn HyvePlatform_GetHostStatus
 *
 * @brief To init the pHostStatus
 * @param[in] ptr - A void pointer which must point to the HYVE_HOST_Status type
 *
 *---------------------------------------------------------------------------*/
void HyvePlatform_GetHostStatus(void* ptr)
{
	HYVE_HOST_Status* pHostStatus = (HYVE_HOST_Status*)ptr;

	if (pHostStatus) {
		if (HYVEPLATFORM_IS_SYS_PWRGOOD) {
		/* Currently use the GPIO pin SPD_HOST_CTRL_L as the BIOS POST status pin.
		   Because during POST the DIMM ownership belongs to the Host until POST end */
		pHostStatus->biosPOSTStatus = HYVEPLATFORM_IS_DIMM_READY ?
										Hyve_BIOS_POST_END : Hyve_BIOS_POST_START;
		} else {
			pHostStatus->biosPOSTStatus = Hyve_BIOS_NO_ACTIVE;
		}
	}
}

/*----------------------------------------------------------------------------
 * @fn HyvePlatform_BIOS_Status_Callback
 *
 * @brief This function provides platform actions for BIOS status
 * @param[in]   status - The BIOS status
 *
 *---------------------------------------------------------------------------*/
void HyvePlatform_BIOS_Status_Callback(const INT8U status)
{
	switch(status)
	{
	case Hyve_BIOS_POST_START:
		printf("\n========== BIOS PSOT Start ==========\n");
		break;
	case Hyve_BIOS_POST_END:
		printf("\n========== BIOS PSOT End   ==========\n");
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
 * @fn HyvePlatform_PrepareBIOSFlash
 *
 * @brief This function provides platform actions for preparing BIOS FW update
 * 
 * @param[in]   targetBIOS - The target flash index of the BIOS flash
 * 
 * @return	 0	- success
 *			-1	- otherwise.
 *---------------------------------------------------------------------------*/
int HyvePlatform_PrepareBIOSFlash(INT8U targetBIOS)
{
	INT8U enable = TRUE;

	// Change the ownership to BMC
	if (HyvePlatform_BIOS_FlashAccessControl(Hyve_VALUE_SET, &enable) < 0) {
		return -1;
	}
	// Switch the flash to the target one
	return HyveBIOS_FlashSelect(Hyve_VALUE_SET, &targetBIOS);
}

/*----------------------------------------------------------------------------
 * @fn HyvePlatform_AfterBIOSFlash
 *
 * @brief This function provides platform actions after BIOS FW update
 * 
 * @param[in] updateRes - The update result code, 1, if success; otherwise
 * 
 * @return	 0	- success
 *			-1	- otherwise.
 *---------------------------------------------------------------------------*/
int HyvePlatform_AfterBIOSFlash(INT8U updateRes)
{
	INT8U enable = FALSE;

	// If the update result is fail and the target flash is the boot one
	// then switch to another one to avoid Host cannot boot
	if (TRUE != updateRes) {
		INT8U targetBIOS = 0, bootBIOS = 0;
		HyveBIOS_BootSelect(Hyve_VALUE_GET, &bootBIOS);
		HyveBIOS_UpdateTarget(Hyve_VALUE_GET, &targetBIOS);
		if (bootBIOS == targetBIOS) {
			bootBIOS = ((bootBIOS + 1) & 0x1);
			HyveBIOS_BootSelect(Hyve_VALUE_SET, &bootBIOS);
			printf("%s: Failover BIOS flash to %u\n", __func__, bootBIOS);
		}
	}
	// Restore the BIOS flash to the boot one
	HyveBIOS_RestoreFlashSelect();
	// Change the ownership to BIOS 
	return HyvePlatform_BIOS_FlashAccessControl(Hyve_VALUE_SET, &enable);
}

int HyvePlatform_BeforeUpdateCPLD(INT8U targetCPLD)
{
	if (0) { targetCPLD = targetCPLD; }
	return HyvePlatform_JTagAccessSelect(Enable_CPLD_JTagAccess);
}

int HyvePlatform_AfterUpdateCPLD(int updateResult)
{
	if (0) { updateResult = updateResult; }
	return HyvePlatform_JTagAccessSelect(Disable_All_JTagAccess);
}

int Hyveplatform_PEFOemAction(void *_pEvtRecord, int BMCInst)
{
	if (0) {
		_pEvtRecord = _pEvtRecord;
		BMCInst = BMCInst;
	}
}

void Hyveplatform_PostClearSEL(int BMCInst)
{
	if (0) { BMCInst = BMCInst; }
}
