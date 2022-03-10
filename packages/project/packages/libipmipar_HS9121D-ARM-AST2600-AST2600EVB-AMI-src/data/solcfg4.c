/*------------------------------------------------------------*
 * solcfg4.c
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

	/* SOL Configuration */
  #include "PMConfig.h"
  #include "Types.h"

int
SOL4Config_LoadFile(char *File, SOLConfig_T *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	data->SOLEnable = IniGetUInt(ini, "SOL4Configuration", "SOLEnable", 0x1);

	data->SOLAuth = IniGetUInt(ini, "SOL4Configuration", "SOLAuth", (0x0 << 7) | (0x0 << 6) | 0x2);

	data->CharAccThresh = IniGetUInt(ini, "SOL4Configuration", "CharAccThresh", (96 << 8) |  12);

	data->SOLRetryCount = IniGetUInt(ini, "SOL4Configuration", "SOLRetryCount", 7);

	data->SOLRetryInterval = IniGetUInt(ini, "SOL4Configuration", "SOLRetryInterval", 50);

	data->NVBitRate = IniGetUInt(ini, "SOL4Configuration", "NVBitRate", 10);

	data->VBitRate = IniGetUInt(ini, "SOL4Configuration", "VBitRate", 10);

	data->PayldChannel = IniGetUInt(ini, "SOL4Configuration", "PayldChannel", 1);

	data->PayldPortNum = IniGetUInt(ini, "SOL4Configuration", "PayldPortNum", 623);

	IniCloseFile(ini);
	return 0;
}

int
SOL4Config_SaveFile(char *File, SOLConfig_T *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetUInt(ini, "SOL4Configuration", "SOLEnable", data->SOLEnable);

	IniSetUInt(ini, "SOL4Configuration", "SOLAuth", data->SOLAuth);

	IniSetUInt(ini, "SOL4Configuration", "CharAccThresh", data->CharAccThresh);

	IniSetUInt(ini, "SOL4Configuration", "SOLRetryCount", data->SOLRetryCount);

	IniSetUInt(ini, "SOL4Configuration", "SOLRetryInterval", data->SOLRetryInterval);

	IniSetUInt(ini, "SOL4Configuration", "NVBitRate", data->NVBitRate);

	IniSetUInt(ini, "SOL4Configuration", "VBitRate", data->VBitRate);

	IniSetUInt(ini, "SOL4Configuration", "PayldChannel", data->PayldChannel);

	IniSetUInt(ini, "SOL4Configuration", "PayldPortNum", data->PayldPortNum);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}


	/* End SOL Configuration */
	