/*------------------------------------------------------------*
 * multisolcfg.c
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

	#include "PMConfig.h"
	#include "Types.h"
	
int
MultiSolConfig_LoadFile(char *File, MultiSolConfig_T *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	strncpy((char*)data->MultiSolTblEntry[0].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/0", "sol_ifc_port", "/dev/ttyS0"), 16);
	strncpy((char*)data->MultiSolTblEntry[1].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/1", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[2].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/2", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[3].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/3", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[4].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/4", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[5].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/5", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[6].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/6", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[7].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/7", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[8].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/8", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[9].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/9", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[10].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/10", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[11].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/11", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[12].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/12", "sol_ifc_port", ""), 16);
	strncpy((char*)data->MultiSolTblEntry[13].sol_ifc_port, IniGetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/13", "sol_ifc_port", ""), 16);

	IniCloseFile(ini);
	return 0;
}

int
MultiSolConfig_SaveFile(char *File, MultiSolConfig_T *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/0", "sol_ifc_port", (char*)data->MultiSolTblEntry[0].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/1", "sol_ifc_port", (char*)data->MultiSolTblEntry[1].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/2", "sol_ifc_port", (char*)data->MultiSolTblEntry[2].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/3", "sol_ifc_port", (char*)data->MultiSolTblEntry[3].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/4", "sol_ifc_port", (char*)data->MultiSolTblEntry[4].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/5", "sol_ifc_port", (char*)data->MultiSolTblEntry[5].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/6", "sol_ifc_port", (char*)data->MultiSolTblEntry[6].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/7", "sol_ifc_port", (char*)data->MultiSolTblEntry[7].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/8", "sol_ifc_port", (char*)data->MultiSolTblEntry[8].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/9", "sol_ifc_port", (char*)data->MultiSolTblEntry[9].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/10", "sol_ifc_port", (char*)data->MultiSolTblEntry[10].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/11", "sol_ifc_port", (char*)data->MultiSolTblEntry[11].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/12", "sol_ifc_port", (char*)data->MultiSolTblEntry[12].sol_ifc_port);
	IniSetStr(ini, "MultiSOLConfigurationInformation/MultiSolTblEntry/13", "sol_ifc_port", (char*)data->MultiSolTblEntry[13].sol_ifc_port);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}

