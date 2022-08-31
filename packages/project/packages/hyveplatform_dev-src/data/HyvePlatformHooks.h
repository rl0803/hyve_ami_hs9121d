 /******************************************************************
 *
 * @file	HyvePlatformHooks.h
 * @brief	To provide platform hook functions
 * 			
 ******************************************************************/
#ifndef HYVEPLATFORMHOOKS_H_
#define HYVEPLATFORMHOOKS_H_

/*
The Hyve platform hook function mechanism:
	1. Use the "Macro defined" function to provide a flexible, independent hook function.

	For example,
	
	In the "HyvePlatformHooks.h" file, define a function HYVEPLATFORM_HELLO_PLATFORMHOOK

		#define HYVEPLATFORM_HELLO_PLATFORMHOOK		HyvePlatform_HelloHook
	
	In the HyvePDKHooks.c,
	
		#ifdef HYVEPLATFORM_HELLO_PLATFORMHOOK
			HYVEPLATFORM_HELLO_PLATFORMHOOK();
		#endif


Hyve Platform Hook Function Definition Steps:
	Step 1. Declare a platform hook function
	Step 2. Define the function macro which is used in HyvePDKHooks.c

	For example,

	extern int HyvePlatform_HelloHook(int var);
	
	#define HYVEPLATFORM_HELLO_PLATFORMHOOK		HyvePlatform_HelloHook

 */

extern void HyvePlatform_GetHostStatus(void* pHostStatus);
extern void HyvePlatform_BIOS_Status_Callback(const INT8U status);
extern int HyvePlatform_PrepareBIOSFlash(INT8U targetBIOS);
extern int HyvePlatform_AfterBIOSFlash(INT8U updateRes);
extern int HyvePlatform_BeforeUpdateCPLD(INT8U targetCPLD);
extern int HyvePlatform_AfterUpdateCPLD(int updateResult);
extern int Hyveplatform_PEFOemAction(void *_pEvtRecord, int BMCInst);
extern void Hyveplatform_PostClearSEL(int BMCInst);
extern INT8 Hyveplatform_ErrorSELstatus();
extern int HyvePlatform_InitUartRouting(void);

#define HYVEPLATFORM_BIOS_FLASHSELECT								HyvePlatform_BIOS_FlashSelect
#define HYVEPLATFORM_PREPARE_BIOSFLASH								HyvePlatform_PrepareBIOSFlash
#define HYVEPLATFORM_AFTER_BIOSFLASH								HyvePlatform_AfterBIOSFlash
#define HYVEPLATFORM_CLAER_CMOS										HyvePlatform_Reset_CMOS
#define HYVEPLATFORM_LED_CONTROL(ledIndex, enable)					HyvePlatform_LED_Control((ledIndex), Hyve_VALUE_SET, &(enable))
#define HYVEPLATFORM_AFTERCREATINGTASKS								HyvePlatform_TaskInit
#define HYVEPLATFORM_GET_HOST_STATUS								HyvePlatform_GetHostStatus
#define HYVEPLATFORM_BIOS_STATUS_CALLBACK							HyvePlatform_BIOS_Status_Callback
#define HYVEPLATFORM_BEFORE_UPDATE_CPLD								HyvePlatform_BeforeUpdateCPLD
#define HYVEPLATFORM_AFTER_UPDATE_CPLD								HyvePlatform_AfterUpdateCPLD
#define HYVEPLATFORM_PEFOEMACTION									Hyveplatform_PEFOemAction
#define HYVEPLATFORM_POSTCLEARSEL									Hyveplatform_PostClearSEL
#define HYVEPLATFORM_SYS_POWER_RESET								HyvePlatform_Reset_PwrAUX_IC
#define HYVEPLATFORM_IS_BP_SUPPORT()								g_is_BP_supported
#define HYVEPLATFORM_INIT_UARTROUTING								HyvePlatform_InitUartRouting

#endif
