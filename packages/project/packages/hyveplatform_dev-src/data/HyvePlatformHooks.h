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


extern void HyvePlatform_BIOS_Status_Callback(const INT8U status);
extern int HyvePlatform_PrepareBIOSFlash(INT8U targetBIOS);
extern int HyvePlatform_AfterBIOSFlash(INT8U updateRes);

#define HYVEPLATFORM_BIOS_FLASHSELECT								HyvePlatform_BIOS_FlashSelect
#define HYVEPLATFORM_PREPARE_BIOSFLASH								HyvePlatform_PrepareBIOSFlash
#define HYVEPLATFORM_AFTER_BIOSFLASH								HyvePlatform_AfterBIOSFlash


#define HYVEPLATFORM_AFTERCREATINGTASKS								HyvePlatform_TaskInit

#endif
