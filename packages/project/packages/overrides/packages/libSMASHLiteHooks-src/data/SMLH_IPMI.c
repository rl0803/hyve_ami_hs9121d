

#include"SMLH_IPMI.h"
#include<stdio.h>
#include "SMLH_Include.h"
#include<time.h>

extern int ConnectToBMC(IPMI20_SESSION_T *hSession,int sessionNo);

uint16 SMASH_GetActiveSessCnt()
{
	IPMI20_SESSION_T hSession;
	int wRet;
	wRet = ConnectToBMC(&hSession, 0);
	if(wRet != 0)
		printf("error in connect to BMC\n");

	GetSmashLiteActiveSessCntRes_T GetActiveSessionCountRes;
	IPMICMD_GetSmashLiteActiveSessCnt(&hSession, &GetActiveSessionCountRes, 2);
	
	SMASH_CloseSession( &hSession );
	return (GetActiveSessionCountRes.SessionCount);
}
uint16 SMASH_SetActiveSessCnt(int a)
{
	IPMI20_SESSION_T hSession;
	int wRet;
	wRet = ConnectToBMC(&hSession, 1);
	if(wRet != 0)
		printf("error in connect to BMC\n");
	SetSmashLiteActiveSessCntReq_T SetActiveSessionCountReq;
	SetSmashLiteActiveSessCntRes_T SetActiveSessionCountRes;
	SetActiveSessionCountReq.SessionCount = a;
	wRet = IPMICMD_SetSmashLiteActiveSessCnt(&hSession, &SetActiveSessionCountReq, &SetActiveSessionCountRes, 2);
	
	SMASH_CloseSession( &hSession );
	
	return wRet;
}


uint16 SMASH_GetOneUserInfo(IPMI20_SESSION_T *hSession,
                            int recordId,
                            GetUserNameRes_T* UserName,
                                                        GetUserAccessRes_T* UserPermsNetwork,
                                                        GetUserAccessRes_T* UserPermsSerial,
                            GetUsrPayldAccRes_T* UserPermsSOL,
                                                        int timeout)
{
	if(hSession == NULL || UserName == NULL || UserPermsNetwork == NULL || UserPermsSerial == NULL || UserPermsSOL == NULL)
		return SMH_FAILURE;
	return (LIBIPMI_HL_GetOneUserInfo(hSession, recordId,
                                        UserName,
                                        UserPermsNetwork,
                                        UserPermsSerial,
                                        UserPermsSOL,
                                        timeout));


}

uint16 SMASH_CloseSession( IPMI20_SESSION_T *hSession )
{
	if(hSession == NULL)
		return SMH_FAILURE;
	return (LIBIPMI_CloseSession(hSession));

}

uint16 SMASH_GetUserAccess(IPMI20_SESSION_T* hSession,
                                                         GetUserAccessReq_T* userAccessReq,
                                                         GetUserAccessRes_T* userAccessNRes,
                                                         int timeout)
{
	if(hSession == NULL || userAccessReq == NULL || userAccessNRes == NULL)
		return SMH_FAILURE;
	return(IPMICMD_GetUserAccess(hSession, userAccessReq, userAccessNRes, timeout));
}

uint16 SMASH_DelUser(IPMI20_SESSION_T *hSession,INT8U recordId,int timeout)
{
	if(hSession == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_DelUser(hSession,recordId,timeout));

}

uint16 SMASH_PowerCycle( IPMI20_SESSION_T *hSession, int timeout )
{
	if(hSession == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_PowerCycle(hSession,timeout));
}

uint16 SMASH_SetSNMPCommunity(IPMI20_SESSION_T *hSession,
                    uint8* CommunityStr,uint8 Channel,
                                        int timeout)
{
	if(hSession == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_SetSNMPCommunity(hSession, CommunityStr, Channel, timeout));

}

uint16 SMASH_SetLANDestinationAddress(IPMI20_SESSION_T *hSession,
                                        uint8 Channel,
                                        uint8  index,
                                        uint8 addrFormat,
                                        uint8* destAddr,
                                        int timeout)
{
	if(hSession == NULL || destAddr == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_SetLANDestinationAddress(hSession, Channel, index, addrFormat, destAddr, timeout));

}

uint16 SMASH_SetLANDestinationv6Address(IPMI20_SESSION_T *hSession,
                                        uint8 Channel,
                                        uint8  index,
                                        uint8 addrFormat,
                                        uint8* destAddr,
                                        int timeout)
{
	if(hSession == NULL || destAddr == NULL)
		return SMH_FAILURE;
        return(LIBIPMI_HL_SetLANDestinationV6Address(hSession, Channel, index, addrFormat, destAddr, timeout));

}


uint16  SMASH_GetChassisStatus( IPMI20_SESSION_T *hSession, int timeout, chassis_status_T *status)
{
	if(hSession == NULL || status == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_GetChassisStatus(hSession,timeout,status));
}

uint16 SMASH_PowerUp( IPMI20_SESSION_T *hSession, int timeout )
{
	if(hSession == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_PowerUp(hSession,timeout));

}
uint16 SMASH_PowerOff( IPMI20_SESSION_T *pSession, int timeout )
{
	if(pSession == NULL)
		return SMH_FAILURE;
	return (LIBIPMI_HL_PowerOff(pSession,timeout ));

}
uint16 SMASH_Create_IPMI_Local_Session(IPMI20_SESSION_T *pSession,
                                                    char *pszUserName, char *pszPassword,
                                                    uint8 *byPrivLevel,INT8U *ServIPAddr,INT8U AuthFlag,int timeout)
{
	if(pSession == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_Create_IPMI_Local_Session(pSession,pszUserName,pszPassword,byPrivLevel,ServIPAddr,AuthFlag,timeout));
}
uint16 SMASH_GetNumOfSELEntries(IPMI20_SESSION_T *pSession,
                                        INT16U* nNumOfSELEntries,
                                        int timeout)
{
	if(pSession == NULL || nNumOfSELEntries == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_GetNumOfSELEntries(pSession,nNumOfSELEntries,timeout));

}

uint16 SMASH_GetAllSELEntries(IPMI20_SESSION_T *pSession,
                                        SELEventRecord_T *pSELEntriesBuffer,
                                        int timeout)
{
	if(pSession == NULL || pSELEntriesBuffer == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_GetAllSELEntries(pSession, pSELEntriesBuffer, timeout));
}

uint16 SMASH_GetMaxSELCount(IPMI20_SESSION_T *pSession, INT16U *MaxSelCount, int timeout)
{
	if(pSession == NULL || MaxSelCount == NULL)
		return SMH_FAILURE;
	return LIBIPMI_HL_GetMaxPossibleSELEntries(pSession, MaxSelCount, timeout);
}

uint16 SMASH_GetMaxNumUsers(IPMI20_SESSION_T* pSession,
                                         INT8U *nNumUsers, int timeout)
{
	if(pSession == NULL || nNumUsers == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_GetMaxNumUsers(pSession, nNumUsers, timeout));
}

LIBIPMI_API uint16    SMASH_GetSDRRepositoryAllocInfo( IPMI20_SESSION_T *pSession,
                                        SDRRepositoryAllocInfo_T *pResGetSDRRepositoryAllocInfo,
                                        int timeout)
{
	if(pSession == NULL || pResGetSDRRepositoryAllocInfo == NULL)
		return SMH_FAILURE;
	return(IPMICMD_GetSDRRepositoryAllocInfo(pSession, pResGetSDRRepositoryAllocInfo, timeout));
}

LIBIPMI_API uint16    SMASH_GetSDRRepositoryInfo( IPMI20_SESSION_T *pSession,
                                        SDRRepositoryInfo_T *pResGetSDRRepositoryInfo,
                                        int timeout)
{
	if(pSession == NULL || pResGetSDRRepositoryInfo == NULL)
		return SMH_FAILURE;
	return(IPMICMD_GetSDRRepositoryInfo(pSession, pResGetSDRRepositoryInfo, timeout));
}

uint16 SMASH_GetAllUserInfo(IPMI20_SESSION_T *pSession,
                                                        INT8U* nNumUsers,
                                                        GetUserNameRes_T* pResGetUserName,
                                                        GetUserAccessRes_T* pResGetUserAccess_Network,
                                                        GetUserAccessRes_T* pResGetUserAccess_Serial,
                            GetUsrPayldAccRes_T* pResGetUserAccessPayload_SOL,
                                                        int timeout)
{
	if(pSession == NULL || nNumUsers == NULL || pResGetUserName == NULL || pResGetUserAccess_Network == NULL || pResGetUserAccess_Serial == NULL || pResGetUserAccessPayload_SOL == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_GetAllUserInfo(pSession, nNumUsers, pResGetUserName,
                            pResGetUserAccess_Network, pResGetUserAccess_Serial,
		    	    pResGetUserAccessPayload_SOL, timeout));

}


uint16 SMASH_ModUser(IPMI20_SESSION_T *pSession,
                        INT8U UserID,INT8U IsPwdChange,
                        char* UserName,char* ClearPswd,
                        INT8U NetworkPriv,INT8U channel_type,INT8U channel_no,INT8U EnableUser,
                        INT8U ModifyUserName, INT8U EnableSOL,
                        int timeout)
{
	if(pSession == NULL || UserName == NULL || ClearPswd == NULL)
		return SMH_FAILURE;
	if(strlen((char*) ClearPswd) >= IPMI15_MAX_PASSWORD_LEN)              //20Bytes password
		UserID = UserID | TWENTY_BYTE_PWD;
	return(LIBIPMI_HL_ModUser(pSession, UserID, IsPwdChange, UserName, ClearPswd,
                        NetworkPriv, channel_type,channel_no, EnableUser, ModifyUserName, EnableSOL,
                        timeout));
}

uint16 SMASH_ClearSEL(IPMI20_SESSION_T *pSession,
                                int timeout)
{
	if(pSession == NULL)
		return SMH_FAILURE;
	return(IPMICMD_ClearSEL(pSession, timeout));
}

uint16 SMASH_SetLANConfig(IPMI20_SESSION_T *pSession,
                                SetLanConfigReq_T* pSetLANConfigReqData,
                                unsigned int ReqDataLen,
                                SetLanConfigRes_T* pSetLANConfigResData,
                                int timeout)
{
	if(pSession == NULL || pSetLANConfigReqData == NULL || pSetLANConfigResData == NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetLANConfig(pSession, pSetLANConfigReqData, ReqDataLen,
                                pSetLANConfigResData, timeout));
}

uint16  SMASH_GetUser(IPMI20_SESSION_T *pSession, GetUserNameReq_T    *pReqGetUser,
                                                        GetUserNameRes_T        *pResGetUser, int timeout)
{
	if(pSession == NULL || pReqGetUser == NULL|| pResGetUser == NULL)
		return SMH_FAILURE;
	return(IPMICMD_GetUser(pSession, pReqGetUser, pResGetUser, timeout));
}
#if 0		//SMASH_SetPEFConf() is not using anywhere
uint16  SMASH_SetPEFConf( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout)
{
	if(pSession == NULL || pReqSetPEFConf == NULL || pResSetPEFConf == NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetPEFConf(pSession, pReqSetPEFConf, dwReqBufLen,
                                        pResSetPEFConf, timeout));
}
#endif

uint16  SMASH_SetLogProperties( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout)
{               
	//TODO
	//Add the backend function to set log Property
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		pReqSetPEFConf=pReqSetPEFConf;
		dwReqBufLen=dwReqBufLen;
		pResSetPEFConf=pResSetPEFConf;
		timeout=timeout;
	}
    return 1;
}               

uint16 SMASH_SetSyslogEnable ( IPMI20_SESSION_T *pSession,
                SetSyslogEnableReq_T  *pSetSyslogEnableReq ,
                SetSyslogEnableRes_T  *pSetSyslogEnableRes,
                                     int timeout )
{
	if(pSession == NULL || pSetSyslogEnableReq == NULL|| pSetSyslogEnableRes == NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetSyslogEnable (pSession, pSetSyslogEnableReq ,
                		pSetSyslogEnableRes, timeout ));
}

uint16 SMASH_SetSyslogHostname ( IPMI20_SESSION_T *pSession,
                SetSyslogHostnameReq_T  *pSetSyslogHostnameReq ,
                SetSyslogHostnameRes_T  *pSetSyslogHostnameRes,
                                     int timeout )
{
	if(pSession == NULL || pSetSyslogHostnameReq == NULL || pSetSyslogHostnameRes ==NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetSyslogHostname (pSession, pSetSyslogHostnameReq ,
                		pSetSyslogHostnameRes, timeout ));
}

uint16 SMASH_SetSyslogPort ( IPMI20_SESSION_T *pSession,
                SetSyslogPortReq_T  *pSetSyslogPortReq ,
                SetSyslogPortRes_T  *pSetSyslogPortRes,
                                     int timeout )
{
	if(pSession == NULL || pSetSyslogPortReq == NULL || pSetSyslogPortRes == NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetSyslogPort(pSession, pSetSyslogPortReq ,
                	pSetSyslogPortRes, timeout ));
}

uint16 SMASH_SetSnmpPort( IPMI20_SESSION_T *pSession,
                SetSnmpPortReq_T *pSetSnmpPortReq,
                SetSnmpPortRes_T *pSetSnmpPortRes,
                                int timeout )
{
	if(pSession == NULL || pSetSnmpPortReq == NULL || pSetSnmpPortRes == NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetSnmpPort(pSession, pSetSnmpPortReq,
                pSetSnmpPortRes, timeout ));
}

uint16 SMASH_HardReset( IPMI20_SESSION_T *pSession, int timeout )
{
	if(pSession == NULL)
		return SMH_FAILURE;
	return(LIBIPMI_HL_HardReset(pSession,timeout ));
}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
uint16  SMASH_SetPath( IPMI20_SESSION_T *pSession,
        AMISetFWCfgReq_T* pAMISetFWCfgReq,
        AMISetFWCfgRes_T* pAMISetFWCfgRes,
        int timeout)
{      
	if(pSession == NULL || pAMISetFWCfgReq == NULL|| pAMISetFWCfgRes == NULL)
		return SMH_FAILURE;                 
        //TODO  
        //Add the backend function to set Path
	return(IPMICMD_AMISetFWHostCfg(pSession,pAMISetFWCfgReq,pAMISetFWCfgRes,timeout));

        
}       
uint16  SMASH_SetImage( IPMI20_SESSION_T *pSession,
        AMISetFWCfgReq_T* pAMISetFWCfgReq,
        AMISetFWCfgRes_T* pAMISetFWCfgRes,
        int timeout)
{      
	if(pSession == NULL || pAMISetFWCfgReq == NULL|| pAMISetFWCfgRes == NULL)
		return SMH_FAILURE;                 
        //TODO  
        //Add the backend function to set Image
	return(IPMICMD_AMISetFWFilePathCfg(pSession,pAMISetFWCfgReq,pAMISetFWCfgRes,timeout));

      
}                               

uint16 SMASH_SetFWProtocol(IPMI20_SESSION_T *pSession,
        AMISetFWProtocolReq_T* pAMISetFWProtocolReq,
        AMISetFWProtocolRes_T* pAMISetFWProtocolRes,
        int timeout)
{
	if(pSession == NULL || pAMISetFWProtocolReq == NULL || pAMISetFWProtocolRes ==NULL)
		return SMH_FAILURE;
	return(IPMICMD_AMISetFWProtocol(pSession,pAMISetFWProtocolReq,pAMISetFWProtocolRes,timeout));
}
uint16 SMASH_StartRmcupgrade(IPMI20_SESSION_T *pSession,
		AMIStartFwUpdateReq_T *pAMIStartFwUpdateReq,
		AMIStartFwUpdateRes_T *pAMIStartFwUpdateRes,
                       int timeout)
{
	if(pSession == NULL || pAMIStartFwUpdateReq == NULL || pAMIStartFwUpdateRes == NULL)
		return SMH_FAILURE;
	//TODO AMIStartTFTPFwUpdate
	//Add the backend call for start Rmcupgrade
	return(IPMICMD_AMIStartTFTPFwupdate(pSession,pAMIStartFwUpdateReq,pAMIStartFwUpdateRes,timeout));

}

uint16 SMASH_StartRfcbupgrade(char *server,char *FilePath,int fcbno)
{
	//TODO 
	//Add the backend call for start Rfcbupgrade
	if(0)
	{
		server=server; /* -Wextra, fix for unused parameters */
		FilePath=FilePath;
		fcbno=fcbno;
	}
	return 1;
}

uint16 SMASH_SetUserPassword(IPMI20_SESSION_T *pSession, SetUserPswdReq_T	*pReqSetUserPswd,
							SetUserPswdRes_T	*pResSetUserPswd, int timeout)
{
	if(pSession == NULL || pReqSetUserPswd == NULL || pResSetUserPswd == NULL)
		return SMH_FAILURE;
	return(IPMICMD_SetUserPassword(pSession,pReqSetUserPswd,pResSetUserPswd, timeout));
}

#else
uint16  SMASH_SetPath( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout)
{                       
        //TODO  
        //Add the backend function to set Path
		if(0)
		{
			pSession=pSession; /* -Wextra, fix for unused parameters */
			pReqSetPEFConf=pReqSetPEFConf;
			dwReqBufLen=dwReqBufLen;
			pResSetPEFConf=pResSetPEFConf;
			timeout=timeout;
		}
        return 1;
}                               

uint16  SMASH_SetImage( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout)
{                       
        //TODO  
        //Add the backend function to set Image
		if(0)
		{
			pSession=pSession; /* -Wextra, fix for unused parameters */
			pReqSetPEFConf=pReqSetPEFConf;
			dwReqBufLen=dwReqBufLen;
			pResSetPEFConf=pResSetPEFConf;
			timeout=timeout;
		}
        return 1;
}                               
 
uint16 SMASH_StartRmcupgrade()
{
	//TODO
	//Add the backend call for start Rmcupgrade
	
	return 1;

}

uint16 SMASH_StartRfcbupgrade()
{
	//TODO 
	//Add the backend call for start Rfcbupgrade
	return 1;
}
#endif
uint16  SMASH_SetFanControlMode( IPMI20_SESSION_T *pSession,char *Mode,int timeout)
{                       
        //TODO  
        //Add the backend function to set Image
		if(0)
		{
			pSession=pSession; /* -Wextra, fix for unused parameters */
			Mode=Mode;
			timeout=timeout;
		}
        return 1;
}


uint16  SMASH_SetDuty( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout)
{                       
    //TODO  
    //Add the backend function to set Image
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		pReqSetPEFConf=pReqSetPEFConf;
		dwReqBufLen=dwReqBufLen;
		pResSetPEFConf=pResSetPEFConf;
		timeout=timeout;
	}
    return 1;
}

uint16 SMASH_GetServiceConf(IPMI20_SESSION_T *pSession, int ServiceID,AMIGetServiceConfRes_T *pAMIGetServiceConfRes, int timeout)
{
	int wRet = 0;
	if(pSession == NULL || pAMIGetServiceConfRes == NULL)
		return SMH_FAILURE;
	wRet =  LIBIPMI_HL_AMIGetServiceConf(pSession, ServiceID,
                             pAMIGetServiceConfRes, timeout);
    
	if( wRet !=0 )
	{
	printf("Failed in IPMICMD_AMIGetServiceConf with error code = %d\n", wRet);
	return wRet;
	}
	return 0;
}

#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
uint16 SMASH_SetNodeEth(IPMI20_SESSION_T *pSession, char *ethval, int timeout)
{
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		ethval=ethval;
		timeout=timeout;
	}
	return 1;
}

uint16 SMASH_SetNodeIPMode(IPMI20_SESSION_T *pSession, char *IPMode, int timeout)
{
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		IPMode=IPMode;
		timeout=timeout;
	}
	return 1;
}
uint16 SMASH_SetNodeIP(IPMI20_SESSION_T *pSession, char *IP, int timeout)
{
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		IP=IP;
		timeout=timeout;
	}
	return 1;
}

uint16 SMASH_SetNodeReset(IPMI20_SESSION_T *pSession, char *Reset, int timeout)
{
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		Reset=Reset;
		timeout=timeout;
	}
	return 1;
}

uint16 SMASH_StartNode()
{
	return 0;
}
uint16 SMASH_StopNode()
{
	return 0;
}
uint16 SMASH_ResetNode()
{
	return 0;
}


uint16 SMASH_SetPSUControlMode(IPMI20_SESSION_T *pSession, char *PSUControlMode,uint16 recordID,int timeout)
{
	char i2c_dev[50]={0};
	unsigned char slave=0x0,write_buf[1024]={0};
	int i=0,wRet=0;
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		recordID=recordID;
		timeout=timeout;
	}
	if((strncasecmp(PSUControlMode,"Auto",strlen("Auto")) == 0))
	{
		write_buf[0] = 0x07;
	}
	if((strncasecmp(PSUControlMode,"Manual",strlen("Manual")) == 0))
	{
		write_buf[0] = 0x17;
	}
	if(write_buf[0])
	{
		for(i=0;i<10;i++)
		{
			wRet =  SMASH_FillI2cDevandSlave(i, i2c_dev,&slave);
			if(wRet ==1)
			PMBus_WriteON_OFF_CONFIG(i2c_dev, slave,&write_buf[0]);
		}
	}
	
	return 1;
}

uint16 SMASH_SetMaxPower(IPMI20_SESSION_T *pSession, int *MaxPower,uint16 recordID,int timeout)
{
	char i2c_dev[50]={0};
	unsigned char slave=0x0,write_buffer[1024]={0};
	int wRet=0;
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		timeout=timeout;
	}
	snprintf((char *)write_buffer,1024,"%d",*MaxPower);
	wRet=SMASH_GetPowerTargetAddress(recordID,i2c_dev,&slave);
	if(wRet == 1)
		PMBus_WritePIN_OP_WARN_LIMIT(i2c_dev,slave,&write_buffer[0]);

	return 1;
}


uint16 SMASH_SetLocation(IPMI20_SESSION_T *pSession, char *Location, int timeout)
{
	//add the backend function to set the chassis part location
//	return(IPMICMD_WriteFRUData(pSession,
//					pFRUWriteReqData,
//					ReqDataLen /* Bytes to be written + sizeof(FRUWriteReq_T) */,
//					pFRUWriteResData,
//					timeout));
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		Location=Location;
		timeout=timeout;
	}
	return 1;	
}

uint16 SMASH_SetSN(IPMI20_SESSION_T *pSession, char *Location, int timeout)
{
	//add the backend function to set the serial number
//	return(IPMICMD_WriteFRUData(pSession,
//					pFRUWriteReqData,
//					ReqDataLen /* Bytes to be written + sizeof(FRUWriteReq_T) */,
//					pFRUWriteResData,
//					timeout));
	if(0)
	{
		pSession=pSession; /* -Wextra, fix for unused parameters */
		Location=Location;
		timeout=timeout;
	}
	return 1;
}



uint16 SMASH_SetNodePowerGap(IPMI20_SESSION_T *hSession,SetPowerCycleIntervalReq_T *pSetPowerCycleIntervalReq,SetPowerCycleIntervalRes_T *pSetPowerCycleIntervalRes, int timeout)
{
	if(hSession == NULL || pSetPowerCycleIntervalReq == NULL || pSetPowerCycleIntervalRes == NULL)
		return SMH_FAILURE;
	//add the backend function to set the node poweron time gap
	return(IPMICMD_SetPowerCycleInterval(hSession,pSetPowerCycleIntervalReq,pSetPowerCycleIntervalRes,timeout));
}





/*** POWER TARGET PDKS ***/

uint16 SMASH_FillI2cDevandSlave(uint16 recID,char *i2c_dev,u8 *slave)
{
	//char i2c_dev[20],slave;
	switch(recID)
	{
	case 1:
		strncpy(i2c_dev,"/dev/i2c0",strlen("/dev/i2c0")+1); //here i2cdevice file of PSUA1 unit you need to fill realtime values 
		*slave = 0x58; //ex:PSUA1 slave address ,you have to assign actual slave address of PSUA1 
	case 2://similarly for PSUA2 
	case 3://similarly for PSUA3
	case 4://similarly for PSUA4
	case 5://similarly for PSUA5
	case 6://similarly for PSUB1
	case 7://similarly for PSUB2
	case 8://similarly for PSUB3
	case 9://similarly for PSUB4
	case 0://similarly for PSUB5
		break;
    default:
        break;
	}
	return -1; //returning failure as we are not getting real values otherwise we can return success(return 1) from respective switch case
}

uint16 SMASH_GetPowerTargetAddress(uint16 recID,char *i2c_dev,u8 *slave)
{
	if(i2c_dev == NULL)
		return SMH_FAILURE;
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
	}
	strncpy(i2c_dev,"/dev/i2c0",strlen("/dev/i2c0")+1); //these are example values ....fill the real time values
	*slave = 0x58;
		return -1;    //returning failure as we are not filling the real i2c fila and slave address otherwise we can return 1(success in out case)
	return 1;
}

uint16 SMASH_FillCoolingProperties(uint16 recID, COOLING_PROP * coolingProp)
{
	if(coolingProp == NULL)
		return SMH_FAILURE;
//	int coolingPropID=0;
//	coolingPropID = (recID/10)+1;
	switch(recID)
	{
	case 1://fill cooling target 1 details
		SMASH_FillCoolProperties(recID,coolingProp);
		break;
	case 2://fill cooling target 2 details
		SMASH_FillCoolProperties(recID,coolingProp);
		break;
	case 3://fill cooling target 3 details
	case 4://fill cooling target 4 details
	case 5://fill cooling target 5 details
	case 6://fill cooling target 6 details
	case 7://fill cooling target 7 details
	case 8://fill cooling target 8 details
	case 9://fill cooling target 9 details
	case 10://fill cooling target 10 details
		break;
    default:
        break;
	}
	return 1;
}

uint16 SMASH_FillCoolProperties(uint16 recID,COOLING_PROP *coolingProp)
{
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
		coolingProp=coolingProp;
	}
	return 1;
}

uint16 SMASH_FillFanProperties(uint16 recID, FAN_PROP * fanProp)
{
	if(fanProp == NULL)
		return SMH_FAILURE;
	int FanID =0;
	FanID = recID;//(recID/10)*3 + (recID % 10);
	switch(FanID)
	{
	case 1: //fill the fan1 details of the cooling zone 1
		SMASH_FillFanProp(recID,fanProp);
		break;
	case 2: //fill the fan2 details of the cooling zone 1
		break;
	case 3: //fill the fan3 details of the cooling zone 1
		break;
	case 4: //fill the fan1 details of the cooling zone 2
		break;
	case 5: //fill the fan2 details of the cooling zone 2
		break;
	case 6: //fill the fan3 details of the cooling zone 2
		break;
	case 7: //fill the fan1 details of the cooling zone 3
		break;
	case 8: //fill the fan2 details of the cooling zone 3
		break;
	case 9: //fill the fan3 details of the cooling zone 3
		break;
	case 10: //fill the fan1 details of the cooling zone 4
		break;
	case 11: //fill the fan2 details of the cooling zone 4
		break;
	case 12: //fill the fan3 details of the cooling zone 4
		break;
	case 13: //fill the fan1 details of the cooling zone 5
		break;
	case 14: //fill the fan2 details of the cooling zone 5
		break;
	case 15: //fill the fan3 details of the cooling zone 5
		break;
	case 16: //fill the fan1 details of the cooling zone 6
		break;
	case 17: //fill the fan2 details of the cooling zone 6
		break;
	case 18: //fill the fan3 details of the cooling zone 6
		break;
	case 19: //fill the fan1 details of the cooling zone 7
		break;
	case 20: //fill the fan2 details of the cooling zone 7
		break;
	case 21: //fill the fan3 details of the cooling zone 7
		break;
	case 22: //fill the fan1 details of the cooling zone 8
		break;
	case 23: //fill the fan2 details of the cooling zone 8
		break;
	case 24: //fill the fan3 details of the cooling zone 8
		break;
	case 25: //fill the fan1 details of the cooling zone 9
		break;
	case 26: //fill the fan2 details of the cooling zone 9
		break;
	case 27: //fill the fan3 details of the cooling zone 9
		break;
	case 28: //fill the fan1 details of the cooling zone 10
		break;
	case 29: //fill the fan2 details of the cooling zone 10
		break;
	case 30: //fill the fan3 details of the cooling zone 10
		break;
    default:
        break;
	}
	return 1;
}

uint16 SMASH_FillFanProp(uint16 recID,FAN_PROP *fanProp)
{
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
		fanProp=fanProp;
	}
	return 1;
}

uint16 SMASH_NodeCount()
{
	return 5 ;//this is node count statically i have given here ...you have to add the respective backend call to get the node count
	return 1;
}
uint16  SMASH_FillNodeProperties(uint16 recID, NODE_PROP * nodeProp)
{
	if(nodeProp == NULL)
		return SMH_FAILURE;
	switch(recID)
	{
	case 1: SMASH_FillNodeProps(recID,nodeProp);   //fill the first node properties
			break;
	case 2: //fill the second node properties
	case 3: //fill the third node properties
	case 4: //fill the fourth node properties
	case 5: //fill the fifth node propertis
		break;
    default:
        break;
	}
	return 1;
}
uint16 SMASH_FillNodeProps(uint16 recID,NODE_PROP * nodeProp)
{
	if(0)
	{
		recID=recID; /* -Wextra, fix for unused parameters */
		nodeProp=nodeProp;
	}
	return 1;
}
uint16 SMASH_GetPowerSourceType()
{
	int ac;
	if(1) //if the source is ac ..you have to modify this according to the power source type
		ac=1;
	else  //if the source is dc
		ac=0;
	
	return ac;
}
uint16 SMASH_GetSelTimeStamp(INT32U timestamp,char *buf)
{
	time_t time = (time_t)timestamp;
	strftime(buf,25,"%m/%d/%Y  %H:%M:%S",gmtime(&time));
	return 1;
}
uint16 SMASH_GetSensorType(INT8U TypeCode,char *TypeString)
{
	if(TypeString == NULL)
		return SMH_FAILURE;
	switch(TypeCode)
	{
	case 0x01:
		strncpy(TypeString,"Temperature",strlen("Temperature")+1);
		break;
	case 0x02:
		strncpy(TypeString,"voltage",strlen("voltage")+1);
		break;
	case 0x03:
		strncpy(TypeString,"current",strlen("current")+1);
		break;
	case 0x04:
		strncpy(TypeString,"Fan",strlen("Fan")+1);
		break;
	case 0x05:
		strncpy(TypeString,"Physical Security",strlen("Physical Security")+1);
		break;
	case 0x06:
		strncpy(TypeString,"Platform Security",strlen("Platform Security")+1);
		break;
	case 0x07:
		strncpy(TypeString,"Processor",strlen("Processor")+1);
		break;
	case 0x08:
		strncpy(TypeString,"PowerSupply",strlen("PowerSupply")+1);
		break;
	case 0x09:
		strncpy(TypeString,"PowerUnit",strlen("PowerUnit")+1);
		break;
	case 0x0a:
		strncpy(TypeString,"CoolingDevice",strlen("CoolingDevice")+1);
		break;
	case 0x0b:
		strncpy(TypeString,"OtherUnits",strlen("OtherUnits")+1);
		break;
	case 0x0c:
		strncpy(TypeString,"Memory",strlen("Memory")+1);
		break;
	case 0x0d:
		strncpy(TypeString,"DriveSlot",strlen("DriveSlot")+1);
		break;
	case 0x0e:
		strncpy(TypeString,"POST Memory Resize",strlen("POST Memory Resize")+1);
		break;
	case 0x0f:
		strncpy(TypeString,"System firmware",strlen("System firmware")+1);
		break;
	case 0x10:
		strncpy(TypeString,"EventLoggingDisable",strlen("EventLoggingDisable")+1);
		break;
	case 0x11:
		strncpy(TypeString,"WatchDog1",strlen("WatchDog1")+1);
		break;
	case 0x12:
		strncpy(TypeString,"system event",strlen("system event")+1);
		break;
	case 0x13:
		strncpy(TypeString,"Critical Interrupt",strlen("Critical Interrupt")+1);
		break;
	case 0x14:
		strncpy(TypeString,"Button/Switch",strlen("Button/Switch")+1);
		break;
	case 0x15:
		strncpy(TypeString,"Module/Board",strlen("Module/Board")+1);
		break;
	case 0x16:
		strncpy(TypeString,"MicroController",strlen("MicroController")+1);
		break;
	case 0x17:
		strncpy(TypeString,"Add-In card",strlen("Add-In card")+1);
		break;
	case 0x18:
		strncpy(TypeString,"Chassis",strlen("Chassis")+1);
		break;
	case 0x19:
		strncpy(TypeString,"ChipSet",strlen("ChipSet")+1);
		break;
	case 0x1a:
		strncpy(TypeString,"Other FRU",strlen("Other FRU")+1);
		break;
	case 0x1b:
		strncpy(TypeString,"cable/interconnect",strlen("cable/interconnect")+1);
		break;
	case 0x1c:
		strncpy(TypeString,"Terminator",strlen("Terminator")+1);
		break;
	case 0x1d:
		strncpy(TypeString,"system Boot/restart",strlen("system Boot/restart")+1);
		break;
	case 0x1e:
		strncpy(TypeString,"Boot error",strlen("Boot error")+1);
		break;
	case 0x1f:
		strncpy(TypeString,"OS Boot",strlen("OS Boot")+1);
		break;
	case 0x20:
		strncpy(TypeString,"OS stop",strlen("OS stop")+1);
		break;
	case 0x21:
		strncpy(TypeString,"slot/connector",strlen("slot/connector")+1);
		break;
	case 0x22:
		strncpy(TypeString,"System ACPI Power",strlen("System ACPI Power")+1);
		break;
	case 0x23:
		strncpy(TypeString,"watchdog2",strlen("watchdog2")+1);
		break;
	case 0x24:
		strncpy(TypeString,"Platform Alert",strlen("Platform Alert")+1);
		break;
	case 0x25:
		strncpy(TypeString,"Entity Presence",strlen("Entity Presence")+1);
		break;
	case 0x26:
		strncpy(TypeString,"Monitor ASIC/IC",strlen("Monitor ASIC/IC")+1);
		break;
	case 0x27:
		strncpy(TypeString,"LAN",strlen("LAN")+1);
		break;
	case 0x28:
		strncpy(TypeString,"Management subsystem health",strlen("Management subsystem health")+1);
		break;
	case 0x29:
		strncpy(TypeString,"Battery",strlen("Battery")+1);
		break;
	case 0x2a:
		strncpy(TypeString,"Session Audit",strlen("Session Audit")+1);
		break;
	case 0x2b:
		strncpy(TypeString,"Version Change",strlen("Version Change")+1);
		break;
	case 0x2c:
		strncpy(TypeString,"FRU State",strlen("FRU State")+1);
		break;

		
	default:
		printf("invalid value..\n");
		break;
	
	}
	return 1;
}

#endif

