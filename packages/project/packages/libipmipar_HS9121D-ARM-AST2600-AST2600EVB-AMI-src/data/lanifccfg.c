/*------------------------------------------------------------*
 * lanifccfg.c
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

	#include "Types.h"
	#include "IPMIConf.h"
	
int
LANIfcConfig_LoadFile(char *File, BMCInfo_t *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	len = strncpy((char*)data->LanIfcConfig[0].ifname, IniGetStr(ini, "LANIfcConfig/LanIfcConfig/0", "ifname", "eth0"), 16);
	if (len >= (int)sizeof(data->LanIfcConfig[0].ifname)) {
		printf("Buffer overflow");
	}
	data->LanIfcConfig[0].Chtype = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Chtype", 1);
	data->LanIfcConfig[0].Enabled = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Enabled", 0x0);
	data->LanIfcConfig[0].Chnum = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Chnum", 1);
	data->LanIfcConfig[0].Ethindex = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Ethindex", 0);
	data->LanIfcConfig[0].Up_Status = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Up_Status", 0x0);
	len = strncpy((char*)data->LanIfcConfig[1].ifname, IniGetStr(ini, "LANIfcConfig/LanIfcConfig/1", "ifname", "eth1"), 16);
	if (len >= (int)sizeof(data->LanIfcConfig[1].ifname)) {
		printf("Buffer overflow");
	}
	data->LanIfcConfig[1].Chtype = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Chtype", 2);
	data->LanIfcConfig[1].Enabled = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Enabled", 0x0);
	data->LanIfcConfig[1].Chnum = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Chnum", 8);
	data->LanIfcConfig[1].Ethindex = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Ethindex", 1);
	data->LanIfcConfig[1].Up_Status = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Up_Status", 0x0);
	len = strncpy((char*)data->LanIfcConfig[2].ifname, IniGetStr(ini, "LANIfcConfig/LanIfcConfig/2", "ifname", "bond0"), 16);
	if (len >= (int)sizeof(data->LanIfcConfig[2].ifname)) {
		printf("Buffer overflow");
	}
	data->LanIfcConfig[2].Chtype = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Chtype", 1);
	data->LanIfcConfig[2].Enabled = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Enabled", 0x0);
	data->LanIfcConfig[2].Chnum = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Chnum", 1);
	data->LanIfcConfig[2].Ethindex = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Ethindex", 0);
	data->LanIfcConfig[2].Up_Status = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Up_Status", 0x0);
	len = strncpy((char*)data->LanIfcConfig[3].ifname, IniGetStr(ini, "LANIfcConfig/LanIfcConfig/3", "ifname", "usb0"), 16);
	if (len >= (int)sizeof(data->LanIfcConfig[3].ifname)) {
		printf("Buffer overflow");
	}
	data->LanIfcConfig[3].Chtype = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Chtype", 3);
	data->LanIfcConfig[3].Enabled = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Enabled", 0x0);
	data->LanIfcConfig[3].Chnum = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Chnum", 7);
	data->LanIfcConfig[3].Ethindex = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Ethindex", 2);
	data->LanIfcConfig[3].Up_Status = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Up_Status", 0x0);
	len = strncpy((char*)data->LanIfcConfig[4].ifname, IniGetStr(ini, "LANIfcConfig/LanIfcConfig/4", "ifname", ""), 16);
	if (len >= (int)sizeof(data->LanIfcConfig[4].ifname)) {
		printf("Buffer overflow");
	}
	data->LanIfcConfig[4].Chtype = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Chtype", 0);
	data->LanIfcConfig[4].Enabled = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Enabled", 0);
	data->LanIfcConfig[4].Chnum = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Chnum", 0);
	data->LanIfcConfig[4].Ethindex = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Ethindex", 0);
	data->LanIfcConfig[4].Up_Status = IniGetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Up_Status", 0);

	IniCloseFile(ini);
	return 0;
}

int
LANIfcConfig_SaveFile(char *File, BMCInfo_t *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetStr(ini, "LANIfcConfig/LanIfcConfig/0", "ifname", (char*)data->LanIfcConfig[0].ifname);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Chtype", data->LanIfcConfig[0].Chtype);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Enabled", data->LanIfcConfig[0].Enabled);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Chnum", data->LanIfcConfig[0].Chnum);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Ethindex", data->LanIfcConfig[0].Ethindex);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/0", "Up_Status", data->LanIfcConfig[0].Up_Status);
	IniSetStr(ini, "LANIfcConfig/LanIfcConfig/1", "ifname", (char*)data->LanIfcConfig[1].ifname);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Chtype", data->LanIfcConfig[1].Chtype);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Enabled", data->LanIfcConfig[1].Enabled);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Chnum", data->LanIfcConfig[1].Chnum);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Ethindex", data->LanIfcConfig[1].Ethindex);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/1", "Up_Status", data->LanIfcConfig[1].Up_Status);
	IniSetStr(ini, "LANIfcConfig/LanIfcConfig/2", "ifname", (char*)data->LanIfcConfig[2].ifname);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Chtype", data->LanIfcConfig[2].Chtype);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Enabled", data->LanIfcConfig[2].Enabled);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Chnum", data->LanIfcConfig[2].Chnum);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Ethindex", data->LanIfcConfig[2].Ethindex);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/2", "Up_Status", data->LanIfcConfig[2].Up_Status);
	IniSetStr(ini, "LANIfcConfig/LanIfcConfig/3", "ifname", (char*)data->LanIfcConfig[3].ifname);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Chtype", data->LanIfcConfig[3].Chtype);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Enabled", data->LanIfcConfig[3].Enabled);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Chnum", data->LanIfcConfig[3].Chnum);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Ethindex", data->LanIfcConfig[3].Ethindex);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/3", "Up_Status", data->LanIfcConfig[3].Up_Status);
	IniSetStr(ini, "LANIfcConfig/LanIfcConfig/4", "ifname", (char*)data->LanIfcConfig[4].ifname);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Chtype", data->LanIfcConfig[4].Chtype);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Enabled", data->LanIfcConfig[4].Enabled);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Chnum", data->LanIfcConfig[4].Chnum);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Ethindex", data->LanIfcConfig[4].Ethindex);
	IniSetUInt(ini, "LANIfcConfig/LanIfcConfig/4", "Up_Status", data->LanIfcConfig[4].Up_Status);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}

