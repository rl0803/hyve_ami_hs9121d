/*------------------------------------------------------------*
 * smtpcfg4.c
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
	#include "IPMI_AMISmtp.h"
	
int
SMTPConfig4_LoadFile(char *File, Smtp_Config_T *data)
{
        int len = 0;
        UN_USED(len);
	INI_HANDLE ini;
	ini=IniLoadFile(File);
	if (ini == NULL)
		return -1;

	data->EnableDisableSMTP = IniGetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSMTP", 1);

	data->EnableDisableSmtpAuth = IniGetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSmtpAuth", 0);

	data->ServerAddr[0] = IniGetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/0", 0);
	data->ServerAddr[1] = IniGetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/1", 0);
	data->ServerAddr[2] = IniGetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/2", 0);
	data->ServerAddr[3] = IniGetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/3", 0);

	data->IP6_ServerAddr[0] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/0", 0x0);
	data->IP6_ServerAddr[1] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/1", 0x0);
	data->IP6_ServerAddr[2] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/2", 0x0);
	data->IP6_ServerAddr[3] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/3", 0x0);
	data->IP6_ServerAddr[4] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/4", 0x0);
	data->IP6_ServerAddr[5] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/5", 0x0);
	data->IP6_ServerAddr[6] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/6", 0x0);
	data->IP6_ServerAddr[7] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/7", 0x0);
	data->IP6_ServerAddr[8] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/8", 0x0);
	data->IP6_ServerAddr[9] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/9", 0x0);
	data->IP6_ServerAddr[10] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/10", 0x0);
	data->IP6_ServerAddr[11] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/11", 0x0);
	data->IP6_ServerAddr[12] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/12", 0x0);
	data->IP6_ServerAddr[13] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/13", 0x0);
	data->IP6_ServerAddr[14] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/14", 0x0);
	data->IP6_ServerAddr[15] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/15", 0x0);

	len = strncpy((char*)data->UserName, IniGetStr(ini, "SMTPLAN4Configuration", "UserName", ""), 65);
	if (len >= (int)sizeof(data->UserName)) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->Passwd, IniGetStr(ini, "SMTPLAN4Configuration", "Passwd", ""), 256);
	if (len >= (int)sizeof(data->Passwd)) {
		printf("Buffer overflow");
	}

	data->NoofDestinations = IniGetUInt(ini, "SMTPLAN4Configuration", "NoofDestinations", 15);

	len = strncpy((char*)data->Subject[0], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/0", ""), 32);
	if (len >= (int)sizeof(data->Subject[0])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[1], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/1", ""), 32);
	if (len >= (int)sizeof(data->Subject[1])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[2], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/2", ""), 32);
	if (len >= (int)sizeof(data->Subject[2])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[3], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/3", ""), 32);
	if (len >= (int)sizeof(data->Subject[3])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[4], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/4", ""), 32);
	if (len >= (int)sizeof(data->Subject[4])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[5], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/5", ""), 32);
	if (len >= (int)sizeof(data->Subject[5])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[6], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/6", ""), 32);
	if (len >= (int)sizeof(data->Subject[6])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[7], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/7", ""), 32);
	if (len >= (int)sizeof(data->Subject[7])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[8], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/8", ""), 32);
	if (len >= (int)sizeof(data->Subject[8])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[9], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/9", ""), 32);
	if (len >= (int)sizeof(data->Subject[9])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[10], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/10", ""), 32);
	if (len >= (int)sizeof(data->Subject[10])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[11], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/11", ""), 32);
	if (len >= (int)sizeof(data->Subject[11])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[12], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/12", ""), 32);
	if (len >= (int)sizeof(data->Subject[12])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[13], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/13", ""), 32);
	if (len >= (int)sizeof(data->Subject[13])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[14], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/14", ""), 32);
	if (len >= (int)sizeof(data->Subject[14])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Subject[15], IniGetStr(ini, "SMTPLAN4Configuration", "Subject/15", ""), 32);
	if (len >= (int)sizeof(data->Subject[15])) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->Msg[0], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/0", ""), 64);
	if (len >= (int)sizeof(data->Msg[0])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[1], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/1", ""), 64);
	if (len >= (int)sizeof(data->Msg[1])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[2], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/2", ""), 64);
	if (len >= (int)sizeof(data->Msg[2])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[3], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/3", ""), 64);
	if (len >= (int)sizeof(data->Msg[3])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[4], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/4", ""), 64);
	if (len >= (int)sizeof(data->Msg[4])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[5], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/5", ""), 64);
	if (len >= (int)sizeof(data->Msg[5])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[6], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/6", ""), 64);
	if (len >= (int)sizeof(data->Msg[6])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[7], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/7", ""), 64);
	if (len >= (int)sizeof(data->Msg[7])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[8], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/8", ""), 64);
	if (len >= (int)sizeof(data->Msg[8])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[9], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/9", ""), 64);
	if (len >= (int)sizeof(data->Msg[9])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[10], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/10", ""), 64);
	if (len >= (int)sizeof(data->Msg[10])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[11], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/11", ""), 64);
	if (len >= (int)sizeof(data->Msg[11])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[12], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/12", ""), 64);
	if (len >= (int)sizeof(data->Msg[12])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[13], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/13", ""), 64);
	if (len >= (int)sizeof(data->Msg[13])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[14], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/14", ""), 64);
	if (len >= (int)sizeof(data->Msg[14])) {
		printf("Buffer overflow");
	}
	len = strncpy((char*)data->Msg[15], IniGetStr(ini, "SMTPLAN4Configuration", "Msg/15", ""), 64);
	if (len >= (int)sizeof(data->Msg[15])) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->SenderAddr, IniGetStr(ini, "SMTPLAN4Configuration", "SenderAddr", ""), 64);
	if (len >= (int)sizeof(data->SenderAddr)) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->Servername, IniGetStr(ini, "SMTPLAN4Configuration", "Servername", ""), 32);
	if (len >= (int)sizeof(data->Servername)) {
		printf("Buffer overflow");
	}

	data->SmtpPort = IniGetUInt(ini, "SMTPLAN4Configuration", "SmtpPort", 25);

	data->SmtpSecurePort = IniGetUInt(ini, "SMTPLAN4Configuration", "SmtpSecurePort", 465);

	data->UserID[0] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/0", 0);
	data->UserID[1] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/1", 0);
	data->UserID[2] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/2", 0);
	data->UserID[3] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/3", 0);
	data->UserID[4] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/4", 0);
	data->UserID[5] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/5", 0);
	data->UserID[6] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/6", 0);
	data->UserID[7] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/7", 0);
	data->UserID[8] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/8", 0);
	data->UserID[9] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/9", 0);
	data->UserID[10] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/10", 0);
	data->UserID[11] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/11", 0);
	data->UserID[12] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/12", 0);
	data->UserID[13] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/13", 0);
	data->UserID[14] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/14", 0);
	data->UserID[15] = IniGetUInt(ini, "SMTPLAN4Configuration", "UserID/15", 0);

	data->EnableDisableSMTP2 = IniGetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSMTP2", 0);

	data->EnableDisableSmtp2Auth = IniGetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSmtp2Auth", 0);

	data->Server2Addr[0] = IniGetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/0", 0);
	data->Server2Addr[1] = IniGetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/1", 0);
	data->Server2Addr[2] = IniGetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/2", 0);
	data->Server2Addr[3] = IniGetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/3", 0);

	data->IP6_Server2Addr[0] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/0", 0x0);
	data->IP6_Server2Addr[1] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/1", 0x0);
	data->IP6_Server2Addr[2] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/2", 0x0);
	data->IP6_Server2Addr[3] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/3", 0x0);
	data->IP6_Server2Addr[4] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/4", 0x0);
	data->IP6_Server2Addr[5] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/5", 0x0);
	data->IP6_Server2Addr[6] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/6", 0x0);
	data->IP6_Server2Addr[7] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/7", 0x0);
	data->IP6_Server2Addr[8] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/8", 0x0);
	data->IP6_Server2Addr[9] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/9", 0x0);
	data->IP6_Server2Addr[10] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/10", 0x0);
	data->IP6_Server2Addr[11] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/11", 0x0);
	data->IP6_Server2Addr[12] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/12", 0x0);
	data->IP6_Server2Addr[13] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/13", 0x0);
	data->IP6_Server2Addr[14] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/14", 0x0);
	data->IP6_Server2Addr[15] = IniGetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/15", 0x0);

	len = strncpy((char*)data->UserName2, IniGetStr(ini, "SMTPLAN4Configuration", "UserName2", ""), 65);
	if (len >= (int)sizeof(data->UserName2)) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->Passwd2, IniGetStr(ini, "SMTPLAN4Configuration", "Passwd2", ""), 256);
	if (len >= (int)sizeof(data->Passwd2)) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->Sender2Addr, IniGetStr(ini, "SMTPLAN4Configuration", "Sender2Addr", ""), 64);
	if (len >= (int)sizeof(data->Sender2Addr)) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->Server2name, IniGetStr(ini, "SMTPLAN4Configuration", "Server2name", ""), 32);
	if (len >= (int)sizeof(data->Server2name)) {
		printf("Buffer overflow");
	}

	data->Smtp2Port = IniGetUInt(ini, "SMTPLAN4Configuration", "Smtp2Port", 25);

	data->Smtp2SecurePort = IniGetUInt(ini, "SMTPLAN4Configuration", "Smtp2SecurePort", 465);

	len = strncpy((char*)data->EncryptedHexPswd, IniGetStr(ini, "SMTPLAN4Configuration", "EncryptedHexPswd", ""), 512);
	if (len >= (int)sizeof(data->EncryptedHexPswd)) {
		printf("Buffer overflow");
	}

	len = strncpy((char*)data->EncryptedHexPswd2, IniGetStr(ini, "SMTPLAN4Configuration", "EncryptedHexPswd2", ""), 512);
	if (len >= (int)sizeof(data->EncryptedHexPswd2)) {
		printf("Buffer overflow");
	}

	data->EnableSTARTTLSSupport = IniGetUInt(ini, "SMTPLAN4Configuration", "EnableSTARTTLSSupport", 0x0);

	data->EnableSSLTLSSupport = IniGetUInt(ini, "SMTPLAN4Configuration", "EnableSSLTLSSupport", 0x0);

	data->Smtp2EnableSTARTTLSSupport = IniGetUInt(ini, "SMTPLAN4Configuration", "Smtp2EnableSTARTTLSSupport", 0x0);

	data->Smtp2EnableSSLTLSSupport = IniGetUInt(ini, "SMTPLAN4Configuration", "Smtp2EnableSSLTLSSupport", 0x0);

	data->passwd_len = IniGetUInt(ini, "SMTPLAN4Configuration", "passwd_len", 0);

	data->passwd2_len = IniGetUInt(ini, "SMTPLAN4Configuration", "passwd2_len", 0);

	IniCloseFile(ini);
	return 0;
}

int
SMTPConfig4_SaveFile(char *File, Smtp_Config_T *data)
{
	static INI_HANDLE ini = NULL;
	if(ini == NULL)
	{
		ini=IniLoadFile(File);
		if (ini == NULL)
			return -1;
	}

	IniSetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSMTP", data->EnableDisableSMTP);

	IniSetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSmtpAuth", data->EnableDisableSmtpAuth);

	IniSetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/0", data->ServerAddr[0]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/1", data->ServerAddr[1]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/2", data->ServerAddr[2]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "ServerAddr/3", data->ServerAddr[3]);

	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/0", data->IP6_ServerAddr[0]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/1", data->IP6_ServerAddr[1]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/2", data->IP6_ServerAddr[2]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/3", data->IP6_ServerAddr[3]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/4", data->IP6_ServerAddr[4]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/5", data->IP6_ServerAddr[5]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/6", data->IP6_ServerAddr[6]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/7", data->IP6_ServerAddr[7]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/8", data->IP6_ServerAddr[8]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/9", data->IP6_ServerAddr[9]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/10", data->IP6_ServerAddr[10]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/11", data->IP6_ServerAddr[11]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/12", data->IP6_ServerAddr[12]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/13", data->IP6_ServerAddr[13]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/14", data->IP6_ServerAddr[14]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_ServerAddr/15", data->IP6_ServerAddr[15]);

	IniSetStr(ini, "SMTPLAN4Configuration", "UserName", (char*)data->UserName);

	IniSetStr(ini, "SMTPLAN4Configuration", "Passwd", (char*)data->Passwd);

	IniSetUInt(ini, "SMTPLAN4Configuration", "NoofDestinations", data->NoofDestinations);

	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/0", (char*)data->Subject[0]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/1", (char*)data->Subject[1]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/2", (char*)data->Subject[2]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/3", (char*)data->Subject[3]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/4", (char*)data->Subject[4]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/5", (char*)data->Subject[5]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/6", (char*)data->Subject[6]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/7", (char*)data->Subject[7]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/8", (char*)data->Subject[8]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/9", (char*)data->Subject[9]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/10", (char*)data->Subject[10]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/11", (char*)data->Subject[11]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/12", (char*)data->Subject[12]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/13", (char*)data->Subject[13]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/14", (char*)data->Subject[14]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Subject/15", (char*)data->Subject[15]);

	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/0", (char*)data->Msg[0]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/1", (char*)data->Msg[1]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/2", (char*)data->Msg[2]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/3", (char*)data->Msg[3]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/4", (char*)data->Msg[4]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/5", (char*)data->Msg[5]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/6", (char*)data->Msg[6]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/7", (char*)data->Msg[7]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/8", (char*)data->Msg[8]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/9", (char*)data->Msg[9]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/10", (char*)data->Msg[10]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/11", (char*)data->Msg[11]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/12", (char*)data->Msg[12]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/13", (char*)data->Msg[13]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/14", (char*)data->Msg[14]);
	IniSetStr(ini, "SMTPLAN4Configuration", "Msg/15", (char*)data->Msg[15]);

	IniSetStr(ini, "SMTPLAN4Configuration", "SenderAddr", (char*)data->SenderAddr);

	IniSetStr(ini, "SMTPLAN4Configuration", "Servername", (char*)data->Servername);

	IniSetUInt(ini, "SMTPLAN4Configuration", "SmtpPort", data->SmtpPort);

	IniSetUInt(ini, "SMTPLAN4Configuration", "SmtpSecurePort", data->SmtpSecurePort);

	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/0", data->UserID[0]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/1", data->UserID[1]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/2", data->UserID[2]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/3", data->UserID[3]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/4", data->UserID[4]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/5", data->UserID[5]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/6", data->UserID[6]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/7", data->UserID[7]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/8", data->UserID[8]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/9", data->UserID[9]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/10", data->UserID[10]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/11", data->UserID[11]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/12", data->UserID[12]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/13", data->UserID[13]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/14", data->UserID[14]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "UserID/15", data->UserID[15]);

	IniSetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSMTP2", data->EnableDisableSMTP2);

	IniSetUInt(ini, "SMTPLAN4Configuration", "EnableDisableSmtp2Auth", data->EnableDisableSmtp2Auth);

	IniSetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/0", data->Server2Addr[0]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/1", data->Server2Addr[1]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/2", data->Server2Addr[2]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "Server2Addr/3", data->Server2Addr[3]);

	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/0", data->IP6_Server2Addr[0]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/1", data->IP6_Server2Addr[1]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/2", data->IP6_Server2Addr[2]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/3", data->IP6_Server2Addr[3]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/4", data->IP6_Server2Addr[4]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/5", data->IP6_Server2Addr[5]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/6", data->IP6_Server2Addr[6]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/7", data->IP6_Server2Addr[7]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/8", data->IP6_Server2Addr[8]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/9", data->IP6_Server2Addr[9]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/10", data->IP6_Server2Addr[10]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/11", data->IP6_Server2Addr[11]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/12", data->IP6_Server2Addr[12]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/13", data->IP6_Server2Addr[13]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/14", data->IP6_Server2Addr[14]);
	IniSetUInt(ini, "SMTPLAN4Configuration", "IP6_Server2Addr/15", data->IP6_Server2Addr[15]);

	IniSetStr(ini, "SMTPLAN4Configuration", "UserName2", (char*)data->UserName2);

	IniSetStr(ini, "SMTPLAN4Configuration", "Passwd2", (char*)data->Passwd2);

	IniSetStr(ini, "SMTPLAN4Configuration", "Sender2Addr", (char*)data->Sender2Addr);

	IniSetStr(ini, "SMTPLAN4Configuration", "Server2name", (char*)data->Server2name);

	IniSetUInt(ini, "SMTPLAN4Configuration", "Smtp2Port", data->Smtp2Port);

	IniSetUInt(ini, "SMTPLAN4Configuration", "Smtp2SecurePort", data->Smtp2SecurePort);

	IniSetStr(ini, "SMTPLAN4Configuration", "EncryptedHexPswd", (char*)data->EncryptedHexPswd);

	IniSetStr(ini, "SMTPLAN4Configuration", "EncryptedHexPswd2", (char*)data->EncryptedHexPswd2);

	IniSetUInt(ini, "SMTPLAN4Configuration", "EnableSTARTTLSSupport", data->EnableSTARTTLSSupport);

	IniSetUInt(ini, "SMTPLAN4Configuration", "EnableSSLTLSSupport", data->EnableSSLTLSSupport);

	IniSetUInt(ini, "SMTPLAN4Configuration", "Smtp2EnableSTARTTLSSupport", data->Smtp2EnableSTARTTLSSupport);

	IniSetUInt(ini, "SMTPLAN4Configuration", "Smtp2EnableSSLTLSSupport", data->Smtp2EnableSSLTLSSupport);

	IniSetUInt(ini, "SMTPLAN4Configuration", "passwd_len", data->passwd_len);

	IniSetUInt(ini, "SMTPLAN4Configuration", "passwd2_len", data->passwd2_len);

	IniSaveFile(ini,File);
	if(g_corefeatures.dual_image_support != ENABLED)
	{
		IniCloseFile(ini);
		ini = NULL;
	}
	return 0;
}

