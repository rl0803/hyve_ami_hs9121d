/*------------------------------------------------------------*
 * wdogcfg.c
 * Warning: This file is generated by PMCP. Any modifications  
 * done on this code will be lost							  
 *------------------------------------------------------------*/
/* *INDENT-OFF* */

/****************************************************************
 ****************************************************************
 **                                                            **
 **    (C)Copyright 2011, American Megatrends Inc.             **
 **                                                            **
 **                 All Rights Reserved.                       **
 **     													   **
 **	    3095 Satellite Boulevard, Building 800, Suite 425,	   **
 **    														   **
 **     Duluth, Georgia 30096, U.S.A Phone-(770)-246-8600.     **
 
 ****************************************************************
 *****************************************************************/

#include <stdio.h>
#include <string.h>
#include "parse-ex.h"
#include "IPMIConf.h"

	/* Watchdog Configuration */
	#include "Types.h"
	#include "PMConfig.h"

int
WDTConfig_LoadFile(char *File, WDTConfig_T *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	data->TmrUse = IniGetUInt(ini, "WatchdogCfg", "TmrUse", (0x1  << 7) | (0x0 << 6) | 0x0);

	data->TmrActions = IniGetUInt(ini, "WatchdogCfg", "TmrActions", (0x0 << 4) | 0x0);

	data->PreTimeOutInterval = IniGetUInt(ini, "WatchdogCfg", "PreTimeOutInterval", 0);

	data->ExpirationFlag = IniGetUInt(ini, "WatchdogCfg", "ExpirationFlag", (0x0 << 5) | (0x0 << 4)  | (0x0 << 3) | \
                      (0x0 << 2) | (0x0 << 1));

	data->InitCountDown = IniGetUInt(ini, "WatchdogCfg", "InitCountDown", 0);

	IniCloseFile(ini);
	return 0;
}

int
WDTConfig_SaveFile(char *File, WDTConfig_T *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetUInt(ini, "WatchdogCfg", "TmrUse", data->TmrUse);

	IniSetUInt(ini, "WatchdogCfg", "TmrActions", data->TmrActions);

	IniSetUInt(ini, "WatchdogCfg", "PreTimeOutInterval", data->PreTimeOutInterval);

	IniSetUInt(ini, "WatchdogCfg", "ExpirationFlag", data->ExpirationFlag);

	IniSetUInt(ini, "WatchdogCfg", "InitCountDown", data->InitCountDown);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}
