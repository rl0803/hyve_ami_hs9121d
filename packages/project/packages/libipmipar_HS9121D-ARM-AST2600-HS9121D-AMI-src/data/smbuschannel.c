/*------------------------------------------------------------*
 * smbuschannel.c
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
SMBusChannelInfo_LoadFile(char *File, ChannelInfo_T *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	data->ID = IniGetUInt(ini, "SMBUSChannelInformation", "ID", 0x43484944);

	data->ChannelIndex = IniGetUInt(ini, "SMBUSChannelInformation", "ChannelIndex", 5);

	data->ChannelNumber = IniGetUInt(ini, "SMBUSChannelInformation", "ChannelNumber", 0x4);

	data->ChannelType = IniGetUInt(ini, "SMBUSChannelInformation", "ChannelType", 0x6);

	data->ChannelMedium = IniGetUInt(ini, "SMBUSChannelInformation", "ChannelMedium", 0x9);

	data->ChannelProtocol = IniGetUInt(ini, "SMBUSChannelInformation", "ChannelProtocol", 0x4);

	data->SessionSupport = IniGetUInt(ini, "SMBUSChannelInformation", "SessionSupport", 0x0);

	data->ActiveSession = IniGetUInt(ini, "SMBUSChannelInformation", "ActiveSession", 0x0);

	data->AuthType[0] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/0", 0);
	data->AuthType[1] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/1", 0);
	data->AuthType[2] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/2", 0);
	data->AuthType[3] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/3", 0);
	data->AuthType[4] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/4", 0);
	data->AuthType[5] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/5", 0);
	data->AuthType[6] = IniGetUInt(ini, "SMBUSChannelInformation", "AuthType/6", 0);

	data->ProtocolVendorId[0] = IniGetUInt(ini, "SMBUSChannelInformation", "ProtocolVendorId/0", (0xf21b00 & 0xFF0000) >> 16);
	data->ProtocolVendorId[1] = IniGetUInt(ini, "SMBUSChannelInformation", "ProtocolVendorId/1", \
			(0xf21b00 & 0xFF00) >> 8);
	data->ProtocolVendorId[2] = IniGetUInt(ini, "SMBUSChannelInformation", "ProtocolVendorId/2", (0xf21b00 & 0xFF));

	data->AuxiliaryInfo[0] = IniGetUInt(ini, "SMBUSChannelInformation", "AuxiliaryInfo/0", (0 & 0xFF00) >> 8);
	data->AuxiliaryInfo[1] = IniGetUInt(ini, "SMBUSChannelInformation", "AuxiliaryInfo/1", (0 & 0xFF));

	data->ReceiveMsgQ = IniGetUInt(ini, "SMBUSChannelInformation", "ReceiveMsgQ", 1);

	data->AccessMode = IniGetUInt(ini, "SMBUSChannelInformation", "AccessMode", 0x2);

	data->AccessModeSupported = IniGetUInt(ini, "SMBUSChannelInformation", "AccessModeSupported", 0);

	data->Alerting = IniGetUInt(ini, "SMBUSChannelInformation", "Alerting", 0x0);

	data->PerMessageAuth = IniGetUInt(ini, "SMBUSChannelInformation", "PerMessageAuth", 0x0);

	data->UserLevelAuth = IniGetUInt(ini, "SMBUSChannelInformation", "UserLevelAuth", 0x0);

	data->MaxPrivilege = IniGetUInt(ini, "SMBUSChannelInformation", "MaxPrivilege", 0);

	data->reserved = IniGetUInt(ini, "SMBUSChannelInformation", "reserved", 0);

	data->SetUserAccess = IniGetUInt(ini, "SMBUSChannelInformation", "SetUserAccess", 0x0);

	data->SetChPrivilege = IniGetUInt(ini, "SMBUSChannelInformation", "SetChPrivilege", 0x0);

	data->SessionLimit = IniGetUInt(ini, "SMBUSChannelInformation", "SessionLimit", 0);

	data->LoginStatusNUP = IniGetUInt(ini, "SMBUSChannelInformation", "LoginStatusNUP", 0);

	data->LoginStatusNUNP = IniGetUInt(ini, "SMBUSChannelInformation", "LoginStatusNUNP", 0);

	data->LoginStatusNNU = IniGetUInt(ini, "SMBUSChannelInformation", "LoginStatusNNU", 0);

	data->MaxUser = IniGetUInt(ini, "SMBUSChannelInformation", "MaxUser", 0);

	data->NoCurrentUser = IniGetUInt(ini, "SMBUSChannelInformation", "NoCurrentUser", 0);

	data->NoFixedUser = IniGetUInt(ini, "SMBUSChannelInformation", "NoFixedUser", 0);


	data->ChannelIndexNvRam = IniGetUInt(ini, "SMBUSChannelInformation", "ChannelIndexNvRam", 0);

	data->ChannelUserInfo[0].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "ID", (((INT32U)'U'<<24) | ((INT32U)'S'<<16) | ('E'<<8) | ('R') ));
	data->ChannelUserInfo[0].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserId", 0);
	data->ChannelUserInfo[0].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "AccessLimit", 0xf);
	data->ChannelUserInfo[0].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "LinkAuth", 0x0);
	data->ChannelUserInfo[0].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserAccessCallback", 0x0);
	data->ChannelUserInfo[0].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserAccessCBCPCallback", 0x0);
	data->ChannelUserInfo[0].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[1].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "ID", (((INT32U)'U'<<24) | ((INT32U)'S'<<16) | ('E'<<8) | ('R') ));
	data->ChannelUserInfo[1].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserId", 0);
	data->ChannelUserInfo[1].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "AccessLimit", 0xf);
	data->ChannelUserInfo[1].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "LinkAuth", 0x0);
	data->ChannelUserInfo[1].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserAccessCallback", 0x0);
	data->ChannelUserInfo[1].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserAccessCBCPCallback", 0x0);
	data->ChannelUserInfo[1].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[2].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "ID", 0);
	data->ChannelUserInfo[2].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserId", 0);
	data->ChannelUserInfo[2].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "AccessLimit", 0);
	data->ChannelUserInfo[2].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "LinkAuth", 0);
	data->ChannelUserInfo[2].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserAccessCallback", 0);
	data->ChannelUserInfo[2].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[2].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[3].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "ID", 0);
	data->ChannelUserInfo[3].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserId", 0);
	data->ChannelUserInfo[3].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "AccessLimit", 0);
	data->ChannelUserInfo[3].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "LinkAuth", 0);
	data->ChannelUserInfo[3].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserAccessCallback", 0);
	data->ChannelUserInfo[3].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[3].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[4].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "ID", 0);
	data->ChannelUserInfo[4].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserId", 0);
	data->ChannelUserInfo[4].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "AccessLimit", 0);
	data->ChannelUserInfo[4].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "LinkAuth", 0);
	data->ChannelUserInfo[4].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserAccessCallback", 0);
	data->ChannelUserInfo[4].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[4].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[5].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "ID", 0);
	data->ChannelUserInfo[5].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserId", 0);
	data->ChannelUserInfo[5].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "AccessLimit", 0);
	data->ChannelUserInfo[5].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "LinkAuth", 0);
	data->ChannelUserInfo[5].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserAccessCallback", 0);
	data->ChannelUserInfo[5].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[5].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[6].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "ID", 0);
	data->ChannelUserInfo[6].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserId", 0);
	data->ChannelUserInfo[6].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "AccessLimit", 0);
	data->ChannelUserInfo[6].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "LinkAuth", 0);
	data->ChannelUserInfo[6].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserAccessCallback", 0);
	data->ChannelUserInfo[6].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[6].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[7].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "ID", 0);
	data->ChannelUserInfo[7].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserId", 0);
	data->ChannelUserInfo[7].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "AccessLimit", 0);
	data->ChannelUserInfo[7].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "LinkAuth", 0);
	data->ChannelUserInfo[7].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserAccessCallback", 0);
	data->ChannelUserInfo[7].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[7].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[8].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "ID", 0);
	data->ChannelUserInfo[8].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserId", 0);
	data->ChannelUserInfo[8].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "AccessLimit", 0);
	data->ChannelUserInfo[8].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "LinkAuth", 0);
	data->ChannelUserInfo[8].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserAccessCallback", 0);
	data->ChannelUserInfo[8].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[8].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserCallbackCapabilities", 0);
	data->ChannelUserInfo[9].ID = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "ID", 0);
	data->ChannelUserInfo[9].UserId = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserId", 0);
	data->ChannelUserInfo[9].AccessLimit = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "AccessLimit", 0);
	data->ChannelUserInfo[9].LinkAuth = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "LinkAuth", 0);
	data->ChannelUserInfo[9].UserAccessCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserAccessCallback", 0);
	data->ChannelUserInfo[9].UserAccessCBCPCallback = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserAccessCBCPCallback", 0);
	data->ChannelUserInfo[9].UserCallbackCapabilities = IniGetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserCallbackCapabilities", 0);

	IniCloseFile(ini);
	return 0;
}

int
SMBusChannelInfo_SaveFile(char *File, ChannelInfo_T *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetUInt(ini, "SMBUSChannelInformation", "ID", data->ID);

	IniSetUInt(ini, "SMBUSChannelInformation", "ChannelIndex", data->ChannelIndex);

	IniSetUInt(ini, "SMBUSChannelInformation", "ChannelNumber", data->ChannelNumber);

	IniSetUInt(ini, "SMBUSChannelInformation", "ChannelType", data->ChannelType);

	IniSetUInt(ini, "SMBUSChannelInformation", "ChannelMedium", data->ChannelMedium);

	IniSetUInt(ini, "SMBUSChannelInformation", "ChannelProtocol", data->ChannelProtocol);

	IniSetUInt(ini, "SMBUSChannelInformation", "SessionSupport", data->SessionSupport);

	IniSetUInt(ini, "SMBUSChannelInformation", "ActiveSession", data->ActiveSession);

	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/0", data->AuthType[0]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/1", data->AuthType[1]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/2", data->AuthType[2]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/3", data->AuthType[3]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/4", data->AuthType[4]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/5", data->AuthType[5]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuthType/6", data->AuthType[6]);

	IniSetUInt(ini, "SMBUSChannelInformation", "ProtocolVendorId/0", data->ProtocolVendorId[0]);
	IniSetUInt(ini, "SMBUSChannelInformation", "ProtocolVendorId/1", data->ProtocolVendorId[1]);
	IniSetUInt(ini, "SMBUSChannelInformation", "ProtocolVendorId/2", data->ProtocolVendorId[2]);

	IniSetUInt(ini, "SMBUSChannelInformation", "AuxiliaryInfo/0", data->AuxiliaryInfo[0]);
	IniSetUInt(ini, "SMBUSChannelInformation", "AuxiliaryInfo/1", data->AuxiliaryInfo[1]);

	IniSetUInt(ini, "SMBUSChannelInformation", "ReceiveMsgQ", data->ReceiveMsgQ);

	IniSetUInt(ini, "SMBUSChannelInformation", "AccessMode", data->AccessMode);

	IniSetUInt(ini, "SMBUSChannelInformation", "AccessModeSupported", data->AccessModeSupported);

	IniSetUInt(ini, "SMBUSChannelInformation", "Alerting", data->Alerting);

	IniSetUInt(ini, "SMBUSChannelInformation", "PerMessageAuth", data->PerMessageAuth);

	IniSetUInt(ini, "SMBUSChannelInformation", "UserLevelAuth", data->UserLevelAuth);

	IniSetUInt(ini, "SMBUSChannelInformation", "MaxPrivilege", data->MaxPrivilege);

	IniSetUInt(ini, "SMBUSChannelInformation", "reserved", data->reserved);

	IniSetUInt(ini, "SMBUSChannelInformation", "SetUserAccess", data->SetUserAccess);

	IniSetUInt(ini, "SMBUSChannelInformation", "SetChPrivilege", data->SetChPrivilege);

	IniSetUInt(ini, "SMBUSChannelInformation", "SessionLimit", data->SessionLimit);

	IniSetUInt(ini, "SMBUSChannelInformation", "LoginStatusNUP", data->LoginStatusNUP);

	IniSetUInt(ini, "SMBUSChannelInformation", "LoginStatusNUNP", data->LoginStatusNUNP);

	IniSetUInt(ini, "SMBUSChannelInformation", "LoginStatusNNU", data->LoginStatusNNU);

	IniSetUInt(ini, "SMBUSChannelInformation", "MaxUser", data->MaxUser);

	IniSetUInt(ini, "SMBUSChannelInformation", "NoCurrentUser", data->NoCurrentUser);

	IniSetUInt(ini, "SMBUSChannelInformation", "NoFixedUser", data->NoFixedUser);


	IniSetUInt(ini, "SMBUSChannelInformation", "ChannelIndexNvRam", data->ChannelIndexNvRam);

	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "ID", data->ChannelUserInfo[0].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserId", data->ChannelUserInfo[0].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "AccessLimit", data->ChannelUserInfo[0].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "LinkAuth", data->ChannelUserInfo[0].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserAccessCallback", data->ChannelUserInfo[0].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserAccessCBCPCallback", data->ChannelUserInfo[0].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/0", "UserCallbackCapabilities", data->ChannelUserInfo[0].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "ID", data->ChannelUserInfo[1].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserId", data->ChannelUserInfo[1].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "AccessLimit", data->ChannelUserInfo[1].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "LinkAuth", data->ChannelUserInfo[1].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserAccessCallback", data->ChannelUserInfo[1].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserAccessCBCPCallback", data->ChannelUserInfo[1].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/1", "UserCallbackCapabilities", data->ChannelUserInfo[1].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "ID", data->ChannelUserInfo[2].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserId", data->ChannelUserInfo[2].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "AccessLimit", data->ChannelUserInfo[2].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "LinkAuth", data->ChannelUserInfo[2].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserAccessCallback", data->ChannelUserInfo[2].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserAccessCBCPCallback", data->ChannelUserInfo[2].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/2", "UserCallbackCapabilities", data->ChannelUserInfo[2].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "ID", data->ChannelUserInfo[3].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserId", data->ChannelUserInfo[3].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "AccessLimit", data->ChannelUserInfo[3].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "LinkAuth", data->ChannelUserInfo[3].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserAccessCallback", data->ChannelUserInfo[3].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserAccessCBCPCallback", data->ChannelUserInfo[3].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/3", "UserCallbackCapabilities", data->ChannelUserInfo[3].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "ID", data->ChannelUserInfo[4].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserId", data->ChannelUserInfo[4].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "AccessLimit", data->ChannelUserInfo[4].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "LinkAuth", data->ChannelUserInfo[4].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserAccessCallback", data->ChannelUserInfo[4].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserAccessCBCPCallback", data->ChannelUserInfo[4].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/4", "UserCallbackCapabilities", data->ChannelUserInfo[4].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "ID", data->ChannelUserInfo[5].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserId", data->ChannelUserInfo[5].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "AccessLimit", data->ChannelUserInfo[5].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "LinkAuth", data->ChannelUserInfo[5].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserAccessCallback", data->ChannelUserInfo[5].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserAccessCBCPCallback", data->ChannelUserInfo[5].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/5", "UserCallbackCapabilities", data->ChannelUserInfo[5].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "ID", data->ChannelUserInfo[6].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserId", data->ChannelUserInfo[6].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "AccessLimit", data->ChannelUserInfo[6].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "LinkAuth", data->ChannelUserInfo[6].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserAccessCallback", data->ChannelUserInfo[6].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserAccessCBCPCallback", data->ChannelUserInfo[6].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/6", "UserCallbackCapabilities", data->ChannelUserInfo[6].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "ID", data->ChannelUserInfo[7].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserId", data->ChannelUserInfo[7].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "AccessLimit", data->ChannelUserInfo[7].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "LinkAuth", data->ChannelUserInfo[7].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserAccessCallback", data->ChannelUserInfo[7].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserAccessCBCPCallback", data->ChannelUserInfo[7].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/7", "UserCallbackCapabilities", data->ChannelUserInfo[7].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "ID", data->ChannelUserInfo[8].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserId", data->ChannelUserInfo[8].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "AccessLimit", data->ChannelUserInfo[8].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "LinkAuth", data->ChannelUserInfo[8].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserAccessCallback", data->ChannelUserInfo[8].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserAccessCBCPCallback", data->ChannelUserInfo[8].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/8", "UserCallbackCapabilities", data->ChannelUserInfo[8].UserCallbackCapabilities);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "ID", data->ChannelUserInfo[9].ID);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserId", data->ChannelUserInfo[9].UserId);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "AccessLimit", data->ChannelUserInfo[9].AccessLimit);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "LinkAuth", data->ChannelUserInfo[9].LinkAuth);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserAccessCallback", data->ChannelUserInfo[9].UserAccessCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserAccessCBCPCallback", data->ChannelUserInfo[9].UserAccessCBCPCallback);
	IniSetUInt(ini, "SMBUSChannelInformation/ChannelUserInfo/9", "UserCallbackCapabilities", data->ChannelUserInfo[9].UserCallbackCapabilities);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}


	/* End SMBUS Channel Information */
	