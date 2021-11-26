/*------------------------------------------------------------*
 * ssicfg.c
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

	/* SSI Configuration */
	#include "Types.h"
	#include "PMConfig.h"
	
int
SSIConfig_LoadFile(char *File, SSIConfig_T *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	data->CurrentState = IniGetUInt(ini, "SSICfg", "CurrentState", 0);

	data->CurrentConditions = IniGetUInt(ini, "SSICfg", "CurrentConditions", 2);

	data->CurrentPowerLevel = IniGetUInt(ini, "SSICfg", "CurrentPowerLevel", 0);

	data->CMMIPAddr[0] = IniGetUInt(ini, "SSICfg", "CMMIPAddr/0", 0);
	data->CMMIPAddr[1] = IniGetUInt(ini, "SSICfg", "CMMIPAddr/1", 0);
	data->CMMIPAddr[2] = IniGetUInt(ini, "SSICfg", "CMMIPAddr/2", 0);
	data->CMMIPAddr[3] = IniGetUInt(ini, "SSICfg", "CMMIPAddr/3", 0);

	IniCloseFile(ini);
	return 0;
}

int
SSIConfig_SaveFile(char *File, SSIConfig_T *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetUInt(ini, "SSICfg", "CurrentState", data->CurrentState);

	IniSetUInt(ini, "SSICfg", "CurrentConditions", data->CurrentConditions);

	IniSetUInt(ini, "SSICfg", "CurrentPowerLevel", data->CurrentPowerLevel);

	IniSetUInt(ini, "SSICfg", "CMMIPAddr/0", data->CMMIPAddr[0]);
	IniSetUInt(ini, "SSICfg", "CMMIPAddr/1", data->CMMIPAddr[1]);
	IniSetUInt(ini, "SSICfg", "CMMIPAddr/2", data->CMMIPAddr[2]);
	IniSetUInt(ini, "SSICfg", "CMMIPAddr/3", data->CMMIPAddr[3]);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}

