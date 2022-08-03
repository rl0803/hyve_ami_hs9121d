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


#define REG_HICR9						(0x1E78909C)


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

// Platform test & demo code
typedef enum {
	/* Use positive number as assert; negative number as de-assert  
	   For example,
	   Assert:  HyveSELSeverity_Warning
     Deassert: -HyveSELSeverity_Warning */

	HyveSELSeverity_Normal = 0,	// not an error event, just an information event
	HyveSELSeverity_Warning,
	HyveSELSeverity_Error,
} HyveSELSeverity_E;

int HyveExt_GetSELSeverity(SELEventRecord_T *pEvtRecord)
{
	int severity = HyveSELSeverity_Normal;

	if (!pEvtRecord)
		return HyveSELSeverity_Normal;


	switch (pEvtRecord->SensorType) {
	/* Normal events */
	case SENSOR_TYPE_EVENT_LOGGING_DISABLED:
	case SENSOR_TYPE_SYSTEMEVENT:
	case SENSOR_TYPE_BUTTON:
	case SENSOR_TYPE_SYSTEM_ACPI_POWER_STATE:
	case SENSOR_TYPE_POWERUNIT:
	case SENSOR_TYPE_MANAGEMENT_SUBSYSTEM_HEALTH:
	case SENSOR_TYPE_VERSION_CHANGE:
		break;

	case SENSOR_TYPE_PSU:
		if (!pEvtRecord->EvtData1) {
			// presence event
			if (pEvtRecord->EvtDirType & 0x80) {
				severity = HyveSELSeverity_Warning;
			} else {
				severity = -HyveSELSeverity_Warning;
			}
		} else {
			if (pEvtRecord->EvtDirType & 0x80) {
				severity = -HyveSELSeverity_Error;
			} else {
				severity = HyveSELSeverity_Error;
			}
		}
		break;

	default:
		if (pEvtRecord->EvtDirType & 0x80) {
			severity = -HyveSELSeverity_Error;
		} else {
			severity = HyveSELSeverity_Error;
		}
		break;
	}

	return severity;
}

//static INT16 g_WarningSELCount = 0;
static INT16 g_ErrorSELCount = 0;
static INT8 g_is_allDesserted = 1;

/*----------------------------------------------------------------------------
 * @fn Hyveplatform_ErrorSELstatus
 *
 * @brief This function is called by PDK_PlatformSetupLED
          to know if there is an error SEL created before the "LEDTimer".
 * 
 * @param[in] updateRes - The update result code, 1, if success; otherwise
 * 
 * @return	 0 - normal
 *			 1 - warning, should blink yellow LED
 *			 2 - Error, should blink red LED
 *---------------------------------------------------------------------------*/
INT8 Hyveplatform_ErrorSELstatus()
{
	if (g_ErrorSELCount) {
		return HyveSELSeverity_Error;
	} else if (0xf == g_is_allDesserted) {
		return HyveSELSeverity_Warning;
	}
	return HyveSELSeverity_Normal;
}

int Hyveplatform_PEFOemAction(void *_pEvtRecord, int BMCInst)
{
	SELEventRecord_T *pEvtRecord = (SELEventRecord_T *)_pEvtRecord;
	INT8U off = 0;

	// If it's SEL clear event, just return
	if ((SENSOR_TYPE_EVENT_LOGGING_DISABLED == pEvtRecord->SensorType) &&
			(EVENT_LOG_AREA_CLEARED == pEvtRecord->EvtData1)) {
		return 0;
	}

	switch (HyveExt_GetSELSeverity(pEvtRecord)) {
	case HyveSELSeverity_Warning:
	case HyveSELSeverity_Error:
		g_ErrorSELCount++;
		g_is_allDesserted = 0;
		break;
	case -HyveSELSeverity_Warning:
	case -HyveSELSeverity_Error:
		if (--g_ErrorSELCount < 0)
			g_ErrorSELCount = 0;
		if (!g_is_allDesserted && !g_ErrorSELCount)
			g_is_allDesserted = 0xf;
		break;
	default:
		break;
	}
	// The system status LED is a 3 in one LED, so just light on one color at a time
	if (g_ErrorSELCount) {
		API_GlowLED(PLATFORM_LED_SYS_STATUS_Y, LED_PATTERN_SLOW_BLINK, 0, BMCInst);
		API_GlowLED(PLATFORM_LED_SYS_STATUS_R, LED_PATTERN_SLOW_BLINK, 0, BMCInst);
	} else if (0xf == g_is_allDesserted) {
		API_GlowLED(PLATFORM_LED_SYS_STATUS_Y, LED_PATTERN_ON, 0, BMCInst);
		API_GlowLED(PLATFORM_LED_SYS_STATUS_R, LED_PATTERN_ON, 0, BMCInst);
	}

	return 0;
}

void Hyveplatform_PostClearSEL(int BMCInst)
{
	INT8U on = 1;

	g_ErrorSELCount = 0;
	g_is_allDesserted = 1;

	API_GlowLED(PLATFORM_LED_SYS_STATUS_Y, LED_PATTERN_OFF, 0, BMCInst);
	API_GlowLED(PLATFORM_LED_SYS_STATUS_R, LED_PATTERN_OFF, 0, BMCInst);
}

void HyvePlatform_InitUartRouting(void)
{
	INT32U regValue = 0x08030400; // Default bypass UART1 to COM4

	printf("[HyvePlatform_InitUartRouting]  Default bypass UART1 to COM4 \n");
	
	HyveExt_BMC_Register(Hyve_RegOp_Assign, REG_HICR9, &regValue);
}
