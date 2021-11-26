#include <stdlib.h>
#include <string.h>

#include "SMLH_Include.h"
#include "libipmi_session.h"
#include "IPMI_PEF.h"
#include "libipmi_Misc.h"
#include "IPMI_LANConfig.h"
#include "LANConfig.h"
#include "libipmi_AppDevice.h"
#include "libipmi_fru.h"
#include "libipmi_XportDevice.h"
#include "libipmi_IPM.h"
#include "SMLH_IPMI.h"
#include "Debug.h"

#define DISABLE	0x0
#define ENABLE_LOCAL	0x1
#define ENABLE_REMOTE	0x2
#define ENABLE_LOCAL_REMOTE 0x3

#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
#include "libipmi_AMIEXT.h"
#include "IPMI_AMIDevice.h"
#include "ntpserver.h"
#include "libpmb.h"
#include "LANAlert.h"

extern int LogRecordCycle;
//extern char PSUControlMode[10];
extern int getSELRecordData(SELEventRecord_T *ptrToSELRecord,char *propVal);
extern uint16 LIBIPMI_HL_GetFRUData(IPMI20_SESSION_T *pSession,u8 fru_device_id,u32* p_fru_size,FRUData_T* fru_data,int timeout);
extern uint16 IPMICMD_GetLANConfig(IPMI20_SESSION_T *pSession,GetLanConfigReq_T* pSetLANConfigReqData,GetLanConfigRes_T* pSetLANConfigResData,int timeout);
//extern uint16 IPMICMD_OemGetHealthandTemp(IPMI20_SESSION_T *pSession,OemGetHealthandTempReq_T *pOemGetHealthandTempReq ,OemGetHealthandTempRes_T *pOemGetHealthandTempRes,int timeout);
//extern uint16 IPMICMD_GetPowerCycleInterval(IPMI20_SESSION_T *pSession,
//		OemGetPowerCycleIntervalReq_T *pOemGetPwerCycleIntervalReq,
//		OemGetPowerCycleIntervalRes_T *pOemGetPwerCycleIntervalRes,
//				int timeout);
//extern uint16 IPMICMD_OemGetAllTarget(IPMI20_SESSION_T *pSession,
//		OemGetAllTargetReq_T *pOemGetAllTargetCountReq,
//		OemGetAllTargetRes_T *pOemGetAllTargetCountRes,
//				int timeout);
uint16 IPMICMD_AMIGetFWCfg(IPMI20_SESSION_T *pSession,
					   AMIGetFWCfgReq_T* pAMIGetFWCfgReq,
					   AMIGetFWCfgRes_T* pAMIGetFWCfgRes,
                       int timeout);

#endif

extern int ConnectToBMC(IPMI20_SESSION_T *hSession,int sessionNo);
extern unsigned short  IPMICMD_GetPEFConf( IPMI20_SESSION_T *pSession/*in*/,
                                        GetPEFConfigReq_T *pReqGetPEFConf/*in*/,
                                        unsigned char *pResGetPEFConf/*out*/,
                                        int timeout/*in*/);
extern uint16 LIBIPMI_HL_GetSNMPCommunity(IPMI20_SESSION_T *pSession,  uint8* pCommunityStr,uint8 Channel, int timeout);
extern uint16 LIBIPMI_HL_GetLANDestinationAddress(IPMI20_SESSION_T *pSession, uint8 Channel, uint8  index, LANDestAddr_T *LANDestAddrRes, int timeout);


extern int ReadOemSysLog(INT16U num, char *pSyslogs);
extern int GetOemSyslogConf(INT32U *pAmount, INT16U *pNumOfDatRec);

/*
This file contains hooks to fill the properties of a particular target, which 
can be identified by the recID. Here all properties can be overridden with oem 
specific properties, if neccessary.
*/

int FillAdminProperties(uint16 recID, ADMIN_PROP *AdminProp)
{
	int wRet=0,temp=0;
	unsigned int i=0;
	IPMI20_SESSION_T hSession;
	GetSysGUIDRes_T SystemGUID;
	char SysGUID[SMLH_ARR_LEN_32+1] = {0};

	memset(&hSession,0,sizeof(hSession));
	wRet = ConnectToBMC(&hSession, 0);
	if (wRet != SMH_SUCCESS)
	{
		printf("Error in establishing session \n");
		return SMH_FAILURE;
	}
	wRet = snprintf(AdminProp->Name,sizeof(AdminProp->Name),"MAP");
	if(wRet < 0 || wRet >= (signed)sizeof(AdminProp->Name))
	{
	    TCRIT("Buffer Overflow in FillAdminProperties\n");
	    return SMH_FAILURE;
	}
	memset(&SystemGUID,0,sizeof(GetSysGUIDRes_T));
	wRet=IPMICMD_GetSystemGUID(&hSession,&SystemGUID,30);
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
	
	if(wRet == 0)
	{
		char	*pbyRes;
		pbyRes = (char *) &SystemGUID;
		temp= sizeof(SysGUID) - strlen(SysGUID);
		for(i=1;i < sizeof(SystemGUID);i++)
		{
			wRet =snprintf(SysGUID+strlen(SysGUID),temp,"%.2x",pbyRes[i]);
			if(wRet < 0 || wRet >= temp)
			{
				TCRIT("Buffer Overflow is FillAdminProperties\n");
				return SMH_FAILURE;
			}
			temp=temp-wRet;
		}
	}
	wRet = snprintf(AdminProp->GUID,sizeof(AdminProp->GUID),"%s",SysGUID);
	if(wRet < 0 || wRet >= sizeof(AdminProp->GUID))
	{
		TCRIT("Buffer Overflow is FillAdminProperties\n");
		return SMH_FAILURE;
	}
	return SMH_SUCCESS;
}

int FillSPProperties(uint16 recID, SP_PROP *SPProp)
{
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
	snprintf(SPProp->Name,20,"BMC");
	return SMH_SUCCESS;
}

int FillChassisProperties(uint16 recID, CHASSIS_PROP *chassisProp)
{
	if(0)
	{
		recID = recID; /* -Wextra; Fix for unused parameter*/
	}
	//TODO: Add necessary backend calls to fill real values 
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	chassisProp->ChassisID = recID;
	snprintf(chassisProp->BackplaneStatus,SMLH_ARR_LEN_32,"OK");
#else	
	chassisProp->ChassisID = 0;
	chassisProp->BackplaneStatus = 0;
#endif
	return SMH_SUCCESS;
}

int FillNodeProperties(uint16 recID, NODE_PROP * nodeProp)
{
        if(0)
        {
                recID = recID; /* -Wextra; Fix for unused parameter*/
        }
	//TODO: Add necessary backend calls to fill real values
	snprintf(nodeProp->Status,SMLH_ARR_LEN_32, "Unknown");
	snprintf(nodeProp->Health,SMLH_ARR_LEN_32, "Unknown");
	nodeProp->Power = 0;
	nodeProp->EnTemp = 0;
	nodeProp->ExTemp = 0;
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	snprintf(nodeProp->BMCReset,10, "on");
	nodeProp->CPUAmount = 0;
	nodeProp->MemoryAmount = 0;
	nodeProp->DiskAmount =0;
	
	SMASH_FillNodeProperties(recID, nodeProp);
#endif	
	return SMH_SUCCESS;
}

int FillSystemProperties(uint16 recID, SYSTEM_PROP * sysProp)
{
	IPMI20_SESSION_T hSession;
	int wRet = 0,retval = 0;
	unsigned char CommunityStr[20] = { 0 };
	char ipmode = 0;
	u8 fru_device_id = 0;
	u32 p_fru_size = 0;
	FRUData_T fru_data;

	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char status[20]={0};
    char PrimServer[128]={0};
    char SecServer[128]={0};
#endif	
    
	GetHostName(sysProp->HostName);
	snprintf(sysProp->OperatorPassword,SMLH_ARR_LEN_32, "xxxxxxxx");
	snprintf(sysProp->AdminPassword,SMLH_ARR_LEN_32, "xxxxxxxx");
	sysProp->NodePowerGap = 0;
	snprintf(sysProp->SnmpTrapEnable,SMLH_ARR_LEN_32, "Disable");

    
	wRet = ConnectToBMC(&hSession, 0);
	if (wRet != SMH_SUCCESS) {
		printf("Error in establishing session \n");
		return SMH_FAILURE;
		}
	GetPEFConfigReq_T GetPEFConfigReq;
	GetPEFConfigReq.ParamSel = 0x01;
	GetPEFConfigReq.SetSel = 0x00;
	GetPEFConfigReq.BlockSel = 0x00;
	uint8  PEFConf[MAX_RESPONSE_SIZE];
	memset(PEFConf, 0, MAX_RESPONSE_SIZE);
	IPMICMD_GetPEFConf(&hSession, &GetPEFConfigReq, PEFConf, 30);

#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	GetSyslogPortRes_T GetSyslogPortRes;
	IPMICMD_GetSyslogPort(&hSession, &GetSyslogPortRes, 30);

	GetSyslogHostnameRes_T GetSyslogHostnameRes;
	IPMICMD_GetSyslogHostname(&hSession, &GetSyslogHostnameRes, 30);

	GetSyslogEnableRes_T GetSyslogEnableRes;
	IPMICMD_GetSyslogEnable(&hSession, &GetSyslogEnableRes, 30);
#endif	
	/** TODO:
	 *    Channel number hard code to 0x01.
	 */
	LIBIPMI_HL_GetSNMPCommunity(&hSession, &CommunityStr[0], 0x01, 30);
	LANDestAddr_T LANDestAddrRes;
	LANDestv6Addr_T LANDestv6AddrRes;
	memset(&LANDestAddrRes, 0x0, sizeof(LANDestAddr_T));
	memset(&LANDestv6AddrRes, 0x0, sizeof(LANDestv6Addr_T));
	LIBIPMI_HL_GetLANDestinationAddress(&hSession, 0x01, 1, &LANDestAddrRes, 30);
	LIBIPMI_HL_GetLANDestinationV6Address(&hSession,0x01,1, &LANDestv6AddrRes, 30);
	GetSysHealthFirmwareANDPowerCycleRes_T GetSysHealthFirmwareANDPowerCycleRes;
	IPMICMD_GetSysHealthFirmwareANDPowerCycle( &hSession,&GetSysHealthFirmwareANDPowerCycleRes,30);
	
	GetDevIDRes_T		GetDevIDRes;
	wRet = IPMICMD_GetDeviceID( &hSession, &GetDevIDRes, 30);
    if(wRet != 0)
    {
        printf("Could not communicate with BMC via IPMB when creating session error code %d!!\n",wRet);
        return wRet;
    }
    retval = snprintf(sysProp->Firmware,sizeof(sysProp->Firmware), "%d.%02d.%d",GetDevIDRes.FirmwareRevision1,GetDevIDRes.FirmwareRevision2,GetDevIDRes.AuxFirmwareRevision);
    if(retval < 0 || retval >= (signed)sizeof(sysProp->Firmware))
    {
	    TCRIT("Buffer Overflow in FillSystemProperties function\n");
	    return SMH_FAILURE;
    }
    if(GetSysHealthFirmwareANDPowerCycleRes.OverallHealth == 0)
    {
	retval = snprintf(sysProp->Health,sizeof(sysProp->Health),"OK");
	if(retval < 0 || retval >= (signed)sizeof(sysProp->Health))
	{
		TCRIT("Buffer Overflow in FillSystemProperties function\n");
		return SMH_FAILURE;
	}
    }
    else
    {
	retval = snprintf(sysProp->Health,sizeof(sysProp->Health),"Fail");
	if(retval < 0 || retval >= (signed)sizeof(sysProp->Health))
	{
		TCRIT("Buffer Overflow in FillSystemProperties function\n");
		return SMH_FAILURE;
	}
    }
    
	sysProp->NodePowerGap = GetSysHealthFirmwareANDPowerCycleRes.PowerCycleInterval;
	
	GetLanConfigReq_T  pGetLANConfigReqData;
	GetLanConfigRes_T  pGetLANConfigResData;
	pGetLANConfigReqData.ChannelNum = 0x01;
	pGetLANConfigReqData.BlockSelect = 0x00;
	pGetLANConfigReqData.SetSelect = 0x00;
	pGetLANConfigReqData.ParameterSelect = 03;
	IPMICMD_GetLANConfig(&hSession,&pGetLANConfigReqData,&pGetLANConfigResData,30);
	snprintf(sysProp->IP,SMLH_ARR_LEN_32, "%d.%d.%d.%d",pGetLANConfigResData.ConfigData.IPAddr[0],pGetLANConfigResData.ConfigData.IPAddr[1],pGetLANConfigResData.ConfigData.IPAddr[2],pGetLANConfigResData.ConfigData.IPAddr[3]);

	pGetLANConfigReqData.ParameterSelect = 6;
	IPMICMD_GetLANConfig(&hSession,&pGetLANConfigReqData,&pGetLANConfigResData,30);
	snprintf(sysProp->NetMask,SMLH_ARR_LEN_32, "%d.%d.%d.%d",pGetLANConfigResData.ConfigData.SubNetMask[0],pGetLANConfigResData.ConfigData.SubNetMask[1],pGetLANConfigResData.ConfigData.SubNetMask[2],pGetLANConfigResData.ConfigData.SubNetMask[3]);

	pGetLANConfigReqData.ParameterSelect = 12;
	IPMICMD_GetLANConfig(&hSession,&pGetLANConfigReqData,&pGetLANConfigResData,30);
	snprintf(sysProp->GateWay,SMLH_ARR_LEN_32, "%d.%d.%d.%d",pGetLANConfigResData.ConfigData.DefaultGatewayIPAddr[0],pGetLANConfigResData.ConfigData.DefaultGatewayIPAddr[1],pGetLANConfigResData.ConfigData.DefaultGatewayIPAddr[2],pGetLANConfigResData.ConfigData.DefaultGatewayIPAddr[3]);

	pGetLANConfigReqData.ParameterSelect = 4;
	IPMICMD_GetLANConfig(&hSession,&pGetLANConfigReqData,&pGetLANConfigResData,30);

	ipmode = pGetLANConfigResData.ConfigData.IPAddrSrc;

	if(ipmode == 0x01)
		snprintf(sysProp->IPMode,SMLH_ARR_LEN_32, "static");
	if(ipmode == 0x02)
		snprintf(sysProp->IPMode,SMLH_ARR_LEN_32, "DHCP");
	
	fru_device_id = 0; //hard coded
	
	wRet=LIBIPMI_HL_GetFRUData(&hSession,fru_device_id,&p_fru_size,&fru_data,30);
	if(wRet == 0)
	{
		
		snprintf(sysProp->Location,SMLH_ARR_LEN_32,"%s",fru_data.ChassisInfo.ChassisPartNum);
		snprintf(sysProp->Manufacturer,SMLH_ARR_LEN_32,"%s",fru_data.ProductInfo.MfrName);
		snprintf(sysProp->PartNumber,SMLH_ARR_LEN_32,"%s",fru_data.ProductInfo.ProductPartNum);
		snprintf(sysProp->SN,SMLH_ARR_LEN_32,"%s",fru_data.ProductInfo.ProductSerialNum);
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO

	GetSysTempRes_T GetSysTempRes;
	IPMICMD_GetSysTemp( &hSession, &GetSysTempRes,30);

	fru_device_id = 0; //hard coded
	wRet=LIBIPMI_HL_GetFRUData(&hSession,fru_device_id,&p_fru_size,&fru_data,30);

	if(wRet == 0)
		snprintf(sysProp->ProductName,SMLH_ARR_LEN_32,"%s",fru_data.BoardInfo.BoardProductName);

	pGetLANConfigReqData.ParameterSelect = 5;
	IPMICMD_GetLANConfig(&hSession,&pGetLANConfigReqData,&pGetLANConfigResData,30);
	snprintf(sysProp->MAC,SMLH_ARR_LEN_32,"%02x:%02x:%02x:%02x:%02x:%02x",pGetLANConfigResData.ConfigData.MACAddr[0],pGetLANConfigResData.ConfigData.MACAddr[1],pGetLANConfigResData.ConfigData.MACAddr[2],pGetLANConfigResData.ConfigData.MACAddr[3],pGetLANConfigResData.ConfigData.MACAddr[4],pGetLANConfigResData.ConfigData.MACAddr[5]);

	wRet=libami_getntpStatus(&status[0]);
	wRet=libami_getntpServer(&PrimServer[0],&SecServer[0],128);

	sysProp->EnTemp=GetSysTempRes.TemperatureSys;//pOemGetHealthandTempRes.TemperatureSys;

	if(!strncasecmp(status,"Auto",strlen("Auto")))
		snprintf(sysProp->NTPEnable,SMLH_ARR_LEN_32,"Enable");
	else if(!strncasecmp(status,"Manual",strlen("Manual")))
		snprintf(sysProp->NTPEnable,SMLH_ARR_LEN_32,"Disable");
	else
	{
		if(!strncasecmp(status,"Failure",strlen("Failure")))
			snprintf(sysProp->NTPEnable,SMLH_ARR_LEN_32,"%s","Disable");
	}

	wRet = snprintf(sysProp->NTPServerIP,sizeof(sysProp->NTPServerIP),PrimServer);
	if(wRet < 0 || (wRet >= (signed)sizeof(sysProp->NTPServerIP)))
	{
		printf("Buffer Overflow\n");
		return SMH_FAILURE;
	}

	if(GetSyslogEnableRes.Enable & ENABLE_REMOTE)
		snprintf(sysProp->SyslogEnable,SMLH_ARR_LEN_32,"Enable");
	else
		snprintf(sysProp->SyslogEnable,SMLH_ARR_LEN_32,"Disable");
	
	if(GetSyslogEnableRes.Enable & ENABLE_REMOTE)
	{
		snprintf(sysProp->SyslogServerIP,SMLH_ARR_LEN_64, "%s", &GetSyslogHostnameRes.Hostname[0]);
		sysProp->SyslogUDPPort = GetSyslogPortRes.Port;
	}
	else
	{
		snprintf(sysProp->SyslogServerIP,SMLH_ARR_LEN_64, "0.0.0.0");
		sysProp->SyslogUDPPort = 0;
	}


#endif

	LIBIPMI_CloseSession(&hSession);
        return SMH_SUCCESS;
}

int FillPowerProperties(uint16 recID, POWER_PROP * pwrProp)
{
        if(0)
        {
                recID = recID; /* -Wextra; Fix for unused parameter*/
        }
	//TODO: Add necessary backend calls to fill real values
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char i2c_dev[100];
	unsigned char read_buf[1024],slave=0x0;//write_buf[1024];
	int PIN=0,POUT=0,efficiency=0,wRet=0,i=0,VIN=0,IIN=0;
	char check[2];
	
	
	memset(read_buf,0,sizeof(read_buf));
	memset(i2c_dev,0,sizeof(i2c_dev));
	memset(check,0,sizeof(check));
	
	
	snprintf(pwrProp->Status,SMLH_ARR_LEN_32,"Unknown");
	snprintf(pwrProp->Health,SMLH_ARR_LEN_32,"Fail");
	pwrProp->PSUAmount = 10;
	snprintf(pwrProp->PSUControlMode,SMLH_ARR_LEN_32,"Manual");
	pwrProp->MaxPower = 0;
	pwrProp->Input = PIN;
	pwrProp->Output = POUT;
	pwrProp->Efficiency = efficiency;
	pwrProp->PhaseAVoltage = 0;
	pwrProp->PhaseACurrent = 0;
	pwrProp->PhaseBVoltage = 0;
	pwrProp->PhaseBCurrent = 0;
	pwrProp->PhaseCVoltage = 0;
	pwrProp->PhaseCCurrent = 0;
	
	
	
	wRet = SMASH_GetPowerTargetAddress(recID,i2c_dev,&slave);
	if(wRet == 1)
	{
	//call to get the firmware version of the psu
	wRet=PMBus_ReadRevision(i2c_dev,slave,&read_buf[0]);
//	printf("retun value for revision..%d\n",wRet);
//	printf("the return values are..%d %d..\n",read_buf[0],read_buf[1]);
	if(wRet>0 && (wRet <= (signed)sizeof(pwrProp->Firmware)))
	{
		memcpy(pwrProp->Firmware,read_buf,sizeof(pwrProp->Firmware));
	}
	else
	{
		printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
		return SMH_FAILURE;
	}

	//call to get the both status and health
	wRet=PMBus_ReadStatusWord(i2c_dev, slave,&read_buf[0]);
//	printf("return va1lue for statusword..%d..\n",wRet);
	if(wRet > 0)
	{
	for(i=0;i<2;i++)
		check[i]=read_buf[i];
	if(check[1]>>5 & 1)
		snprintf(pwrProp->Status,SMLH_ARR_LEN_32,"OFF");
	else
		snprintf(pwrProp->Status,SMLH_ARR_LEN_32,"ON");
	
	if((check[0]>>6 & 1) | (check[0]>>5 & 1) | (check[0]>>4 & 1) | (check[0]>>3 & 1) | (check[1]>>4 & 1) | (check[1]>>3 & 1) | (check[1]>>2 & 1))
		snprintf(pwrProp->Health,SMLH_ARR_LEN_32,"Fault");
	else
		snprintf(pwrProp->Health,SMLH_ARR_LEN_32,"Ok");
	}
	else
	{
		
	}
	
	
	wRet=PMBus_ReadPOUT_MAX(i2c_dev, slave,&read_buf[0]);
	if(wRet > 0)
		pwrProp->MaxPower = atoi((char*)read_buf);
			

	//here i= 1,2,3,4,5 are for group A ..i=6,7,8,9,0 are for group B
	
	for(i=0;i<10;i++)
	{
		SMASH_FillI2cDevandSlave(i, i2c_dev,&slave);
		if (i==4)
		{
			wRet=PMBus_ReadVIN(i2c_dev, slave,&read_buf[0]);
			if(wRet > 0)
			{
				VIN = atoi((char *)read_buf);
				pwrProp->PhaseAVoltage = VIN;
			}
			wRet=PMBus_ReadIIN(i2c_dev, slave,&read_buf[0]);
			if(wRet > 0)
			{
				IIN = atoi((char *)read_buf);
				pwrProp->PhaseACurrent = IIN;
			}
		}
		if(i==8)
		{
			wRet=PMBus_ReadVIN(i2c_dev, slave,&read_buf[0]);
			if(wRet > 0)
			{
				VIN = atoi((char *)read_buf);
				pwrProp->PhaseBVoltage = VIN;
			}
			wRet=PMBus_ReadIIN(i2c_dev, slave,&read_buf[0]);
			if(wRet > 0)
			{
				IIN = atoi((char*)read_buf);
				pwrProp->PhaseBCurrent = IIN;
			}
			wRet = PMBus_ReadON_OFF_CONFIG(i2c_dev, slave,&read_buf[0]);
			if(wRet > 0)
			{
				if(read_buf[0] == 0x07)
					snprintf(pwrProp->PSUControlMode,SMLH_ARR_LEN_32,"Auto");
				if(read_buf[0] == 0x17)
					snprintf(pwrProp->PSUControlMode,SMLH_ARR_LEN_32,"Manual");					
			}
		}
		
		wRet=PMBus_ReadPIN(i2c_dev, slave,&read_buf[0]);
		if(wRet > 0)
		{
			PIN = atoi((char*)read_buf);
			pwrProp->Input = PIN;
		}
		wRet=PMBus_ReadPOUT(i2c_dev, slave,&read_buf[0]);
		if(wRet > 0)
		{
			POUT = atoi((char *)read_buf);
			pwrProp->Output = POUT;
		}
		
		PIN +=PIN;
		POUT+=POUT;
	}
	if(PIN)
		efficiency = (POUT/PIN)*100;
	pwrProp->Efficiency = efficiency;
	}
#else	
	pwrProp->Status = 0;
	pwrProp->Health = 0;
	pwrProp->PSUAmount = 0;
	pwrProp->MaxPower = 0;
	pwrProp->Input = 0;
	pwrProp->Output = 0;
	pwrProp->Efficiency = 0;
	pwrProp->PhaseAVoltage = 0;
	pwrProp->PhaseACurrent = 0;
	pwrProp->PhaseBVoltage = 0;
	pwrProp->PhaseBCurrent = 0;
	pwrProp->PhaseCVoltage = 0;
	pwrProp->PhaseCCurrent = 0;
#endif
        return SMH_SUCCESS;
}

int FillPSUProperties(uint16 recID, PSU_PROP * psuProp)
{
	//TODO: Add necessary backend calls to fill real values
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char i2c_dev[100];
	unsigned char slave=0x0,read_buf[1024]={0},check[2]={0};
	int i=0,PwrSrc=0,wRet=0;
	wRet = SMASH_FillI2cDevandSlave(recID, i2c_dev,&slave);
	
	psuProp->ID = recID;
	if(recID == 0)
		psuProp->ID = 10;
	switch(psuProp->ID)
	{
	case 1:psuProp->ID = 0xA1;
			break;
	case 2:psuProp->ID = 0xA2;
			break;
	case 3:psuProp->ID = 0xA3;
			break;
	case 4:psuProp->ID = 0xA4;
			break;
	case 5:psuProp->ID = 0xA5;
			break;
	case 6:psuProp->ID = 0xB1;
			break;
	case 7:psuProp->ID = 0xB2;
			break;
	case 8:psuProp->ID = 0xB3;
			break;
	case 9:psuProp->ID = 0xB4;
			break;
	case 10:psuProp->ID = 0xB5;
			break;
	default:
		break;
	}
	snprintf(psuProp->Status,SMLH_ARR_LEN_32,"Unknown");
	snprintf(psuProp->Health,SMLH_ARR_LEN_32,"Fail");
	psuProp->AC_InputVoltage = 0;
	psuProp->AC_InputCurrent = 0;
	psuProp->DC_InputVoltage = 0;
	psuProp->DC_InputCurrent = 0;
	psuProp->OutputVoltage = 0;
	psuProp->OutputCurrent = 0;
	psuProp->Temp = 0;
	if(wRet == 1)
	{

	wRet=PMBus_I2CRead( i2c_dev, slave, MFR_ID,&read_buf[0]);
	if(wRet > 0 && (wRet <= (signed)sizeof(psuProp->Manufacturer)))
	{
		memcpy(psuProp->Manufacturer,read_buf,sizeof(psuProp->Manufacturer));
	}
	else
	{
		printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
		return SMH_FAILURE;
	}
	
	wRet=PMBus_I2CRead( i2c_dev, slave, MFR_SERIAL,&read_buf[0]);
	if(wRet > 0 && (wRet <= (signed)sizeof(psuProp->SN)))
	{
		memcpy(psuProp->SN,read_buf,sizeof(psuProp->SN));
	}
	else
	{
		printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
		return SMH_FAILURE;
	}
	
	wRet=PMBus_I2CRead( i2c_dev, slave, MFR_REVISION,&read_buf[0]);
	if(wRet > 0 && (wRet <= (signed)sizeof(psuProp->Firmware)))
	{
		memcpy(psuProp->Firmware,read_buf,sizeof(psuProp->Firmware));
	}
	else
	{
		printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
		return SMH_FAILURE;
	}	
	wRet=PMBus_I2CRead(i2c_dev,slave,STATUS_WORD,&read_buf[0]);
	if(wRet > 0)
	{
	for(i=0;i<2;i++)
		check[i]=read_buf[i];
	if(check[1]>>5 & 1)
		snprintf(psuProp->Status,SMLH_ARR_LEN_32,"OFF");
	else
		snprintf(psuProp->Status,SMLH_ARR_LEN_32,"ON");
	
	if((check[0]>>6 & 1) | (check[0]>>5 & 1) | (check[0]>>4 & 1) | (check[0]>>3 & 1) | (check[1]>>4 & 1) | (check[1]>>3 & 1) | (check[1]>>2 & 1))
		snprintf(psuProp->Health,SMLH_ARR_LEN_32,"Fault");
	else
		snprintf(psuProp->Health,SMLH_ARR_LEN_32,"Ok");
	}
	
	PwrSrc=SMASH_GetPowerSourceType();
	
	wRet=PMBus_I2CRead(i2c_dev,slave,READ_VIN,&read_buf[0]);
	if(wRet > 0)
	{
	if(PwrSrc == 1)
		psuProp->AC_InputVoltage = atoi((char *)read_buf);
	else
		psuProp->DC_InputVoltage = atoi((char *)read_buf);
	}
	
	wRet=PMBus_I2CRead(i2c_dev,slave,READ_IIN,&read_buf[0]);
	if(wRet > 0)
	{
	if(PwrSrc == 1)
		psuProp->AC_InputCurrent = atoi((char *)read_buf);
	else
		psuProp->DC_InputCurrent = atoi((char *)read_buf);
	}
	wRet=PMBus_I2CRead(i2c_dev,slave,READ_VOUT,&read_buf[0]);
	if(wRet > 0)
	psuProp->OutputVoltage = atoi((char *)read_buf);
	wRet=PMBus_I2CRead(i2c_dev,slave,READ_IOUT,&read_buf[0]);
	if(wRet > 0)
	psuProp->OutputCurrent = atoi((char *)read_buf);
	wRet=PMBus_I2CRead(i2c_dev,slave,READ_TEMPERATURE_1,read_buf);
	if(wRet > 0)
		psuProp->Temp = atoi((char *)read_buf);
	}
#else	
	psuProp->ID = recID;
	psuProp->Status = 0;
	psuProp->Health = 0;
	psuProp->AC_InputVoltage = 0;
	psuProp->AC_InputCurrent = 0;
	psuProp->OutputVoltage = 0;
	psuProp->OutputCurrent = 0;
#endif
        return SMH_SUCCESS;
}

int FillCoolingProperties(uint16 recID, COOLING_PROP * coolingProp)
{
	//TODO: Add necessary backend calls to fill real values
	coolingProp->ID = recID;
	snprintf(coolingProp->Health,10, "OK");
	coolingProp->Power = 0;
	coolingProp->ExTemp = 0;
	snprintf(coolingProp->FanControlMode,SMLH_ARR_LEN_32, "Manual");
	coolingProp->Duty = 0;
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	SMASH_FillCoolingProperties(recID,coolingProp);
#endif
        return SMH_SUCCESS;
}

int FillFanProperties(uint16 recID, FAN_PROP * fanProp)
{
	int i,wRet=0,nSensors=0,fan_count=0;	
	IPMI20_SESSION_T hSession;
	struct sensor_data *pSensorBuff = NULL;
	uint32 nNumSensor = 0;
	fanProp->ID = recID;
	memset(&hSession,0,sizeof(hSession));
	wRet = ConnectToBMC(&hSession, 0);
	if(wRet != 0) {
		printf("error in connecting BMC\n");
		return SMH_FAILURE;
		}

	wRet = LIBIPMI_HL_GetSensorCount(&hSession,&nSensors,30);
	if( wRet != 0 ) {
		printf("Error getting num of sensors\n");
		SMASH_CloseSession( &hSession );
		return SMH_FAILURE;
		}

	else {
		pSensorBuff = (struct sensor_data *) calloc(nSensors,sizeof(struct sensor_data));	
		if(pSensorBuff == NULL) {
			SMASH_CloseSession( &hSession );	
			return SMH_FAILURE;
			}
		memset(pSensorBuff, 0, nSensors * sizeof(struct sensor_data));
		nNumSensor = nSensors;
		wRet = LIBIPMI_HL_GetAllSensorReadings(&hSession,pSensorBuff, &nNumSensor,30);
		if(wRet != 0) {
			printf("Error reading All Sensors\n");			
			SMASH_CloseSession( &hSession );
			return SMH_FAILURE;
			}
		else if(pSensorBuff != NULL) {
			for(i=0;i<nSensors;i++ ) {
				if((pSensorBuff[i].sensor_type == FAN_SENSOR)) {
				if(fan_count == (recID -1)) {
					fanProp->Speed = pSensorBuff[i].sensor_reading;
					if(fanProp->Speed == 0)
					snprintf(fanProp->Health,10, "Fail");
					else 
					snprintf(fanProp->Health,10, "Ok");
					}
				++fan_count;
				}
			}	
		}
	}

#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	SMASH_FillFanProperties(recID,fanProp);
#endif
	SMASH_CloseSession( &hSession );
	return SMH_SUCCESS;
}

int FillLogsProperties(uint16 recID, LOGS_PROP * logsProp)
{
	uint32 Amount=0;
	uint16 Index=0;
	char cur_syslogs[ 300+1 ][ 512 ];
	int i = 0;
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	uint16 Selcnt=0;
	IPMI20_SESSION_T hSession;
	char time[25];
	int wRet=0;
	uint16 MaxSelCount = 0;
#endif
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	GetOemSyslogConf (&Amount, &Index);
	wRet = ConnectToBMC(&hSession, 0);
	if(wRet != 0) {
		printf("error in connecting BMC\n");
		return SMH_FAILURE;
		}
	SMASH_GetNumOfSELEntries(&hSession,&Selcnt,30);
	SMASH_GetMaxSELCount(&hSession, &MaxSelCount, 30);
	SELEventRecord_T *ParseSelEvtRecord = NULL;
	SELEventRecord_T *SelRecord=NULL;
	char EvntMsg[100]={0},LogMsg[512]={0} , Syslogs[Index][512];
	SELEventRecord_T *selEvtRecord = (SELEventRecord_T *)calloc(Selcnt,sizeof(SELEventRecord_T));
	if(selEvtRecord == NULL)
	{
		printf("error in allocating memory for selEvtRecord..\n");
		return SMH_FAILURE;
	}
	SelRecord = malloc(sizeof(SELEventRecord_T));
	if(SelRecord == NULL)
	{
		printf("error in allocating memory for SelRecord..\n");
		free(selEvtRecord);
		selEvtRecord = NULL;
		return SMH_FAILURE;
	}
	
	logsProp->LogRecordCycle = 0;
	//snprintf(logsProp->LogAmount,SMLH_ARR_LEN_32, "%d", Amount+Selcnt);
//	logsProp->LogAmount = Amount+Selcnt;
	logsProp->LogAmount = MaxSelCount;
	ReadOemSysLog (Index, (char *)cur_syslogs);
	for(i=0;i<Index;i++) {
		snprintf(Syslogs[i],512,"%d %s",Index-i, cur_syslogs[i]); /*Fortify[Buffer Overflow] :: false positive*/
	}
	for(i=Index-1;i>=0;i--)
	{
		strcat(logsProp->Log, Syslogs[i]);
	}
	memset(SelRecord,0,sizeof(SELEventRecord_T));
	if(Selcnt)
	{
	wRet = SMASH_GetAllSELEntries(&hSession,selEvtRecord,30);
	if(wRet != 0) {
		printf("error in getting all sel entries..\n");
		SMASH_CloseSession( &hSession );
		return SMH_FAILURE;
		}
	else
	{
//		if(Selcnt)
//		{
		ParseSelEvtRecord = selEvtRecord;
			while(Selcnt)
			{
				memcpy(SelRecord,ParseSelEvtRecord,sizeof(SELEventRecord_T));
				getSELRecordData(SelRecord,EvntMsg);
				if(SelRecord != NULL)
				{
					SMASH_GetSelTimeStamp(SelRecord->hdr.TimeStamp,time);
					snprintf(LogMsg,512,"%s  %s \n",time,EvntMsg);
					strcat(logsProp->Log,LogMsg);
					Selcnt--;
					ParseSelEvtRecord++;
				}
			}
//		}
	
	}
	}
	if(selEvtRecord != NULL)
	{
		free(selEvtRecord);
		selEvtRecord = NULL;
	}
	if(SelRecord != NULL)
	{
		free(SelRecord);
		SelRecord = NULL;
	}
#else
	int temp=0,retVal=0;
	GetOemSyslogConf (&Amount, &Index);
	//snprintf(logsProp->LogAmount,SMLH_ARR_LEN_32, "%d", Amount);
	logsProp->LogAmount = 3640;
	ReadOemSysLog (Index, (char *)cur_syslogs);
	for(i=0;i<Index;i++) {
		temp = sizeof(logsProp->Log) - strlen(logsProp->Log);
		retVal=snprintf(logsProp->Log + strlen(logsProp->Log), sizeof(logsProp->Log) - strlen(logsProp->Log), " %3d %s", i+1, cur_syslogs[i]);
        if((retVal<0)||(retVal>=temp))
        {
        	printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
        	return SMH_FAILURE;
        }

	}
#endif
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
    SMASH_CloseSession( &hSession );
#endif
    return SMH_SUCCESS;
}

int FillAccountProperties(uint16 recID, ACCOUNTS_PROP * acctProp)
{
	// no need to any prop here, all props are filled in core
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
		acctProp=acctProp;
	}
    return SMH_SUCCESS;
}

int FillRmcupgradeProperties(uint16 recID, RMCUPGRADE_PROP * rmcProp)
{
	//TODO: Add necessary backend calls to fill the properties
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	AMIGetFWCfgReq_T AMIGetFWCfgReq;
	AMIGetFWCfgRes_T AMIGetFWCfgRes;
	IPMI20_SESSION_T hSession;
	int wRet=0;
	wRet = ConnectToBMC(&hSession, 0);
	
	snprintf(rmcProp->Path,SMLH_ARR_LEN_64,"<path>");
	snprintf(rmcProp->Image,SMLH_ARR_LEN_256,"<Image>");
	
	AMIGetFWCfgReq.Parameter=0x01;
	wRet=IPMICMD_AMIGetFWCfg(&hSession, &AMIGetFWCfgReq,&AMIGetFWCfgRes,30);
	if(wRet == 0)
	{
		memcpy(rmcProp->Path,AMIGetFWCfgRes.Data,sizeof(rmcProp->Path));
	}
	AMIGetFWCfgReq.Parameter=0x02;
	wRet=IPMICMD_AMIGetFWCfg(&hSession, &AMIGetFWCfgReq,&AMIGetFWCfgRes,30);
	if(wRet==0)
	{
		wRet=snprintf(rmcProp->Image,sizeof(rmcProp->Image),"%s",AMIGetFWCfgRes.Data);
	    if((wRet<0)||(wRet>=(signed)sizeof(rmcProp->Image)))
	    {
	      	printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
	       	return SMH_FAILURE;
	    }
	}
	
#else	
	snprintf(rmcProp->Path,SMLH_ARR_LEN_64, "<path>");
	snprintf(rmcProp->Image,SMLH_ARR_LEN_64, "<image>");
#endif
        return SMH_SUCCESS;
}

int FillRfcbupgradeProperties(uint8 recID, RFCBUPGRADE_PROP * rfcbProp)
{
	//TODO: Add necessary backend calls to fill the properties
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	AMIGetFWCfgReq_T AMIGetFWCfgReq;
	AMIGetFWCfgRes_T AMIGetFWCfgRes;
	IPMI20_SESSION_T hSession;
	int wRet=0;
	wRet = ConnectToBMC(&hSession, 0);
	
	snprintf(rfcbProp->Path,SMLH_ARR_LEN_64,"<path>");
	snprintf(rfcbProp->Image,SMLH_ARR_LEN_256,"<Image>");
	
	AMIGetFWCfgReq.Parameter=0x01;
	wRet=IPMICMD_AMIGetFWCfg(&hSession, &AMIGetFWCfgReq,&AMIGetFWCfgRes,30);
	if(wRet == 0)
	{
		memcpy(rfcbProp->Path,AMIGetFWCfgRes.Data,sizeof(rfcbProp->Path));
	}
	AMIGetFWCfgReq.Parameter=0x02;
	wRet=IPMICMD_AMIGetFWCfg(&hSession, &AMIGetFWCfgReq,&AMIGetFWCfgRes,30);
	if(wRet==0)
	{
		wRet=snprintf(rfcbProp->Image,sizeof(rfcbProp->Image),"%s",AMIGetFWCfgRes.Data);
        if((wRet<0)||(wRet>=(signed)sizeof(rfcbProp->Image)))
        {
        	printf("In function %s, Line %d : Buffer Overflow\n",__FUNCTION__, __LINE__);
        	return SMH_FAILURE;
        }

	}
#else	
	snprintf(rfcbProp->Path,SMLH_ARR_LEN_64, "<path>");
        snprintf(rfcbProp->Image,SMLH_ARR_LEN_256, "<image>");
#endif
        return SMH_SUCCESS;
}

int FillSnmpProperties(uint16 recID, SNMP_PROP * sysProp)
{
	IPMI20_SESSION_T hSession;
	memset(&hSession,0,sizeof(hSession));
	int wRet = 0;
	unsigned char CommunityStr[20] = { 0 };
	wRet = snprintf(sysProp->SnmpTrapEnable,sizeof(sysProp->SnmpTrapEnable), "Disable");
	if (wRet >=(signed)sizeof(sysProp->SnmpTrapEnable)||(wRet<0)){
		TCRIT("Buffer overflow \n");
		    return SMH_FAILURE;
	}
	wRet = ConnectToBMC(&hSession, 0);
	if (wRet != SMH_SUCCESS){
		TCRIT("Error in establishing session \n");
		    return SMH_FAILURE;
	}
	/** TODO:
	 *    Channel number hard code to 0x01.
	 */
	LIBIPMI_HL_GetSNMPCommunity(&hSession, &CommunityStr[0], 0x01, 30);
	LANDestAddr_T LANDestAddrRes;
	LANDestv6Addr_T LANDestv6AddrRes;
	
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO	
	GetSnmpPortRes_T GetSnmpPortRes;
	IPMICMD_GetSnmpPort(&hSession, &GetSnmpPortRes, 30);
#endif	
	GetSysHealthFirmwareANDPowerCycleRes_T GetSysHealthFirmwareANDPowerCycleRes;
	IPMICMD_GetSysHealthFirmwareANDPowerCycle( &hSession,&GetSysHealthFirmwareANDPowerCycleRes,30);
	
	GetDevIDRes_T		GetDevIDRes;
	wRet = IPMICMD_GetDeviceID( &hSession, &GetDevIDRes, 30);
    if(wRet != 0)
    {
    	TCRIT("Could not communicate with BMC via IPMB when creating session error code %d!!\n",wRet);
        return wRet;
    }
	GetLanConfigReq_T  pGetLANConfigReqData;
	GetLanConfigRes_T  pGetLANConfigResData;
	pGetLANConfigReqData.ChannelNum = 0x01;
	pGetLANConfigReqData.BlockSelect = 0x00;
	pGetLANConfigReqData.SetSelect = 0x00;
	
	pGetLANConfigReqData.SetSelect = recID ;
	pGetLANConfigReqData.ParameterSelect = 18;
	IPMICMD_GetLANConfig(&hSession,&pGetLANConfigReqData,&pGetLANConfigResData,30);

	memset(&LANDestAddrRes, 0x0, sizeof(LANDestAddr_T));
	memset(&LANDestv6AddrRes, 0x0, sizeof(LANDestv6Addr_T));
	LIBIPMI_HL_GetLANDestinationAddress(&hSession, 0x01, recID, &LANDestAddrRes, 30);
	LIBIPMI_HL_GetLANDestinationV6Address(&hSession,0x01,recID, &LANDestv6AddrRes, 30);
	
	if(pGetLANConfigResData.ConfigData.DestType.DestType==0)
	{
		wRet =snprintf(sysProp->SnmpTrapEnable,sizeof(sysProp->SnmpTrapEnable), "Enable");
		if (wRet >=(signed)sizeof(sysProp->SnmpTrapEnable)||(wRet<0)) {
			TCRIT("Buffer overflow \n");
			    return SMH_FAILURE;
		}
	}
	else
	{
		wRet =snprintf(sysProp->SnmpTrapEnable,sizeof(sysProp->SnmpTrapEnable), "Disable");
	    if (wRet >=(signed)sizeof(sysProp->SnmpTrapEnable)||(wRet<0)) {
	    	TCRIT("Buffer overflow \n");
				return SMH_FAILURE;
		}
	}
	if(pGetLANConfigResData.ConfigData.DestType.DestType==0)
	{	
	if(LANDestAddrRes.IPAddr[0] != 0)
	{
		wRet =snprintf(sysProp->SnmpTrapServerIP,sizeof(sysProp->SnmpTrapServerIP), "%d.%d.%d.%d", LANDestAddrRes.IPAddr[0], LANDestAddrRes.IPAddr[1], LANDestAddrRes.IPAddr[2], LANDestAddrRes.IPAddr[3]);
		if (wRet >=(signed)sizeof(sysProp->SnmpTrapServerIP)||(wRet<0)){
			TCRIT("Buffer overflow \n");
			    return SMH_FAILURE;
		}
	}
	else if(((LANDestv6AddrRes.IPAddr[0]) ||( LANDestv6AddrRes.IPAddr[1]))!= 0)
	{
		wRet =snprintf(sysProp->SnmpTrapServerIP,sizeof(sysProp->SnmpTrapServerIP), "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",LANDestv6AddrRes.IPAddr[0],LANDestv6AddrRes.IPAddr[1],LANDestv6AddrRes.IPAddr[2], LANDestv6AddrRes.IPAddr[3],LANDestv6AddrRes.IPAddr[4],LANDestv6AddrRes.IPAddr[5],LANDestv6AddrRes.IPAddr[6],LANDestv6AddrRes.IPAddr[7],LANDestv6AddrRes.IPAddr[8],LANDestv6AddrRes.IPAddr[9],LANDestv6AddrRes.IPAddr[10],LANDestv6AddrRes.IPAddr[11],LANDestv6AddrRes.IPAddr[12],LANDestv6AddrRes.IPAddr[13],LANDestv6AddrRes.IPAddr[14],LANDestv6AddrRes.IPAddr[15]);
		if (wRet >=(signed)sizeof(sysProp->SnmpTrapServerIP)||(wRet<0)){
			TCRIT("Buffer overflow \n");
			    return SMH_FAILURE ;
		}
	}
	else
		{
			wRet=snprintf(sysProp->SnmpTrapServerIP,sizeof(sysProp->SnmpTrapServerIP), "0.0.0.0");
			if (wRet >=(signed)sizeof(sysProp->SnmpTrapServerIP)||(wRet<0)){
				    TCRIT("Buffer overflow \n");
				        return SMH_FAILURE;
			}
		}
	}
	else
	{
		wRet=snprintf(sysProp->SnmpTrapServerIP,sizeof(sysProp->SnmpTrapServerIP), "0.0.0.0");
		if (wRet >=(signed)sizeof(sysProp->SnmpTrapServerIP)||(wRet<0)){
			TCRIT("Buffer overflow \n");
			    return SMH_FAILURE;
		}
	}
	wRet=snprintf(sysProp->SnmpTrapCommunity,sizeof(sysProp->SnmpTrapCommunity), "%s", CommunityStr);
	if (wRet >=(signed)sizeof(sysProp->SnmpTrapCommunity)||(wRet<0)){
		TCRIT("Buffer overflow \n");
			return SMH_FAILURE;
	}

	if(pGetLANConfigResData.ConfigData.DestType.DestType==0)
	{
		wRet=snprintf(sysProp->SnmpTrapEnable,sizeof(sysProp->SnmpTrapEnable), "Enable");
		if (wRet >=(signed)sizeof(sysProp->SnmpTrapEnable)||(wRet<0)){
			TCRIT("Buffer overflow \n");
				return SMH_FAILURE;
		}
	}
	else
	{
		wRet=snprintf(sysProp->SnmpTrapEnable,sizeof(sysProp->SnmpTrapEnable), "Disable");
		if (wRet >=(signed)sizeof(sysProp->SnmpTrapEnable)||(wRet<0)){
			TCRIT("Buffer overflow \n");
				return SMH_FAILURE;
		}
		
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	if(pGetLANConfigResData.ConfigData.DestType.DestType==0)
	{
		if(GetSnmpPortRes.Port)
			sysProp->SnmpTrapPort = GetSnmpPortRes.Port;
		else
			sysProp->SnmpTrapPort = SNMP_UDP_PORT;
	}
	else
	{
		sysProp->SnmpTrapPort = 0;
	}
#endif
	LIBIPMI_CloseSession(&hSession);
        return SMH_SUCCESS;
}
