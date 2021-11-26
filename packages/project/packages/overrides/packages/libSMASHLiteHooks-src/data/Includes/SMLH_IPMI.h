#ifndef _SMHL_IPMI_H_
#define _SMHL_IPMI_H_
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "libipmi_session.h"
#include "libipmi_errorcodes.h"
#include "libipmi_AppDevice.h"
#include "libipmi_ChassisDevice.h"
#include "libipmi_StorDevice.h"
#include "libipmi_sensor.h"
#include "libipmi_XportDevice.h"
#include "libipmi_PEF.h"
#include "libipmi_Misc.h"
#include "IPMI_AMIDevice.h"
#include "AMIServiceConf.h"
#include "libipmi_AMIEXT.h"

uint16 SMASH_GetActiveSessCnt();
uint16 SMASH_SetActiveSessCnt(int a);

uint16 SMASH_GetOneUserInfo(IPMI20_SESSION_T*, int, GetUserNameRes_T*, GetUserAccessRes_T*, 
			GetUserAccessRes_T*, GetUsrPayldAccRes_T*, int);

uint16 SMASH_CloseSession( IPMI20_SESSION_T *hSession );

uint16 SMASH_GetUserAccess(IPMI20_SESSION_T* pSession,
                                                         GetUserAccessReq_T* pReqGetUserAccess,
                                                         GetUserAccessRes_T* pResGetUserAccess,
                                                         int timeout);
uint16 SMASH_DelUser(IPMI20_SESSION_T *pSession,INT8U UserID,int timeout);

uint16 SMASH_PowerCycle( IPMI20_SESSION_T *pSession, int timeout );

uint16 SMASH_SetSNMPCommunity(IPMI20_SESSION_T *pSession,
                    uint8* CommunityStr,uint8 Channel,
                                        int timeout);
uint16 SMASH_SetLANDestinationAddress(IPMI20_SESSION_T *pSession,
                                        uint8 Channel,
                                        uint8  index,
                                        uint8 addrFormat,
                                        uint8* destAddr,
                                        int timeout);
uint16 SMASH_SetLANDestinationv6Address(IPMI20_SESSION_T *pSession,
                                        uint8 Channel,
                                        uint8  index,
                                        uint8 addrFormat,
                                        uint8* destAddr,
                                        int timeout);

uint16  SMASH_GetChassisStatus( IPMI20_SESSION_T *hSession, int timeout, chassis_status_T *status);

uint16 SMASH_PowerUp( IPMI20_SESSION_T *pSession, int timeout );

uint16 SMASH_PowerOff( IPMI20_SESSION_T *pSession, int timeout );

uint16 SMASH_Create_IPMI_Local_Session(IPMI20_SESSION_T *pSession,
                                                    char *pszUserName, char *pszPassword,
                                                    uint8 *byPrivLevel,INT8U *ServIPAddr,INT8U AuthFlag,int timeout);

uint16 SMASH_GetNumOfSELEntries(IPMI20_SESSION_T *pSession,
                                        INT16U* nNumOfSELEntries,
                                        int timeout);
uint16 SMASH_GetAllSELEntries(IPMI20_SESSION_T *pSession,
                                        SELEventRecord_T *pSELEntriesBuffer,
                                        int timeout);

uint16 SMASH_GetMaxSELCount(IPMI20_SESSION_T *pSession,
        INT16U *MaxSelCount,
        int timeout);

uint16 SMASH_GetMaxNumUsers(IPMI20_SESSION_T* pSession,
                                         INT8U *nNumUsers, int timeout);

LIBIPMI_API uint16    SMASH_GetSDRRepositoryAllocInfo( IPMI20_SESSION_T *pSession,
                                        SDRRepositoryAllocInfo_T *pResGetSDRRepositoryAllocInfo,
                                        int timeout);

LIBIPMI_API uint16    SMASH_GetSDRRepositoryInfo( IPMI20_SESSION_T *pSession,
                                        SDRRepositoryInfo_T *pResGetSDRRepositoryInfo,
                                        int timeout);
uint16 SMASH_GetAllUserInfo(IPMI20_SESSION_T *pSession,
                                                        INT8U* nNumUsers,
                                                        GetUserNameRes_T* pResGetUserName,
                                                        GetUserAccessRes_T* pResGetUserAccess_Network,
                                                        GetUserAccessRes_T* pResGetUserAccess_Serial,
                            GetUsrPayldAccRes_T* pResGetUserAccessPayload_SOL,
                                                        int timeout);
uint16 SMASH_ModUser(IPMI20_SESSION_T *pSession,
                        INT8U UserID,INT8U IsPwdChange,
                        char* UserName,char* ClearPswd,
                        INT8U NetworkPriv,INT8U channel_type,INT8U channel_no,INT8U EnableUser,
                        INT8U ModifyUserName, INT8U EnableSOL,
                        int timeout);

uint16 SMASH_ClearSEL(IPMI20_SESSION_T *pSession,
                                int timeout);


uint16 SMASH_SetLANConfig(IPMI20_SESSION_T *pSession,
                                SetLanConfigReq_T* pSetLANConfigReqData,
                                unsigned int ReqDataLen,
                                SetLanConfigRes_T* pSetLANConfigResData,
                                int timeout);

uint16  SMASH_GetUser(IPMI20_SESSION_T *pSession, GetUserNameReq_T    *pReqGetUser,
                                GetUserNameRes_T *pResGetUser, int timeout);
#if 0  //SMASH_SetPEFConf() is not using anywhere 
uint16  SMASH_SetPEFConf( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout);
#endif

uint16 IPMICMD_SetSyslogEnable ( IPMI20_SESSION_T *pSession,
                SetSyslogEnableReq_T  *pSetSyslogEnableReq ,
                SetSyslogEnableRes_T  *pSetSyslogEnableRes,
                                     int timeout );

uint16 IPMICMD_SetSyslogHostname ( IPMI20_SESSION_T *pSession,
                SetSyslogHostnameReq_T  *pSetSyslogHostnameReq ,
                SetSyslogHostnameRes_T  *pSetSyslogHostnameRes,
                                     int timeout );
uint16 IPMICMD_SetSyslogPort ( IPMI20_SESSION_T *pSession,
                SetSyslogPortReq_T  *pSetSyslogPortReq ,
                SetSyslogPortRes_T  *pSetSyslogPortRes,
                                     int timeout );
uint16 IPMICMD_SetSnmpPort( IPMI20_SESSION_T *pSession,
                SetSnmpPortReq_T *pSetSnmpPortReq,
                SetSnmpPortRes_T *pSetSnmpPortRes,
                                int timeout );

uint16 SMASH_SetSyslogEnable ( IPMI20_SESSION_T *pSession,
                SetSyslogEnableReq_T  *pSetSyslogEnableReq ,
                SetSyslogEnableRes_T  *pSetSyslogEnableRes,
                                     int timeout );

uint16 SMASH_SetSyslogHostname ( IPMI20_SESSION_T *pSession,
                SetSyslogHostnameReq_T  *pSetSyslogHostnameReq ,
                SetSyslogHostnameRes_T  *pSetSyslogHostnameRes,
                                     int timeout );


uint16 SMASH_SetSyslogPort ( IPMI20_SESSION_T *pSession,
                SetSyslogPortReq_T  *pSetSyslogPortReq ,
                SetSyslogPortRes_T  *pSetSyslogPortRes,
                                     int timeout );

uint16 SMASH_SetSnmpPort( IPMI20_SESSION_T *pSession,
                SetSnmpPortReq_T *pSetSnmpPortReq,
                SetSnmpPortRes_T *pSetSnmpPortRes,
                                int timeout );

uint16 SMASH_HardReset( IPMI20_SESSION_T *pSession, int timeout );

uint16  SMASH_SetLogProperties( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout);
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
uint16  SMASH_SetPath( IPMI20_SESSION_T *pSession,AMISetFWCfgReq_T *pAMISetFWCfgReq,AMISetFWCfgRes_T *pAMISetFWCfgRes,int timeout);
uint16  SMASH_SetImage( IPMI20_SESSION_T *pSession,AMISetFWCfgReq_T *pAMISetFWCfgReq,AMISetFWCfgRes_T *pAMISetFWCfgRes,int timeout);
uint16 SMASH_StartRmcupgrade(IPMI20_SESSION_T *pSession,AMIStartFwUpdateReq_T *pAMIStartFwUpdateReq,AMIStartFwUpdateRes_T *pAMIStartFwUpdateRes,int timeout);

#else
uint16  SMASH_SetPath( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout);

uint16  SMASH_SetImage( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout);
uint16 SMASH_StartRmcupgrade();
#endif
uint16 SMASH_StartRfcbupgrade();

uint16  SMASH_SetFanControlMode( IPMI20_SESSION_T *pSession,char *Mode,int timeout);

uint16  SMASH_SetDuty( IPMI20_SESSION_T *pSession,
                                        uint8 *pReqSetPEFConf,
                                        uint32 dwReqBufLen,
                                        uint8 *pResSetPEFConf,
                                        int timeout);

uint16 SMASH_GetServiceConf(IPMI20_SESSION_T *pSession, int ServiceID,AMIGetServiceConfRes_T *pAMIGetServiceConfRes, int timeout);

#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
#include "libipmi_fru.h"
#include "SMLH_Include.h"
#include "IPMI_AMIDevice.h"
//#include "ntpserver.h"
//#include "libipmi_OEM.h"

/*typedef struct{
	char state[20];
}PACKED SetPSUControlModeReq_T;*/
/*typedef struct{
	char Image[50];
	char Path[200];
}PACKED FirmwareUpdate_T;*/
typedef struct{
	char Target[20];
char OEMVerbs[15][20];	
}OEMVerbs;

int PMBus_WriteON_OFF_CONFIG(char *i2c_dev, u8 slave,u8 *write_buf);
int PMBus_WritePIN_OP_WARN_LIMIT(char *i2c_dev, u8 slave,u8 *write_buf);
//uint16 IPMICMD_OemGetHealthandTemp(IPMI20_SESSION_T *pSession,OemGetHealthandTempReq_T *pOemGetHealthandTempReq ,OemGetHealthandTempRes_T *pOemGetHealthandTempRes,int timeout);
//uint16 SMASH_OemGetHealthandTemp(IPMI20_SESSION_T *pSession,
		//OemGetHealthandTempReq_T *pOemGetHealthandTempReq ,
		//OemGetHealthandTempRes_T *pOemGetHealthandTempRes,
          //                           int timeout);
uint16 SMASH_GetFruData(IPMI20_SESSION_T *pSession,u8 fru_device_id,u32* p_fru_size,FRUData_T* fru_data,int timeout);

uint16 SMASH_GetPowerTargetAddress(uint16 recID,char *i2c_dev,u8 *slave);
uint16 SMASH_FillI2cDevandSlave(uint16 recID,char *i2c_dev,u8 *slave);
uint16 SMASH_NodeCount();
uint16 SMASH_SetNodeEth(IPMI20_SESSION_T *pSession, char *ethval, int timeout);
uint16 SMASH_SetNodeIPMode(IPMI20_SESSION_T *pSession, char *IPMode, int timeout);
uint16 SMASH_SetNodeIP(IPMI20_SESSION_T *pSession, char *IP, int timeout);
uint16 SMASH_SetNodeReset(IPMI20_SESSION_T *pSession, char *Reset, int timeout);
uint16 SMASH_SetPSUControlMode(IPMI20_SESSION_T *pSession, char *PSUControlMode,uint16 recordID,int timeout);
uint16 SMASH_SetMaxPower(IPMI20_SESSION_T *pSession, int *MaxPower,uint16 recordID,int timeout);
uint16 SMASH_GetPowerSourceType();
uint16 SMASH_SetNodePowerGap(IPMI20_SESSION_T *hSession,SetPowerCycleIntervalReq_T *pSetPowerCycleIntervalReq,SetPowerCycleIntervalRes_T *pSetPowerCycleIntervalRes, int timeout);
uint16 SMASH_FillCoolingProperties(uint16 recID, COOLING_PROP * coolingProp);
uint16 SMASH_FillFanProperties(uint16 recID, FAN_PROP * fanProp);
uint16 SMASH_FillCoolProperties(uint16 recID,COOLING_PROP *coolingProp);
uint16 SMASH_FillFanProp(uint16 recID,FAN_PROP *fanProp);
uint16 IPMICMD_AMISetFWHostCfg(IPMI20_SESSION_T *pSession,
		               AMISetFWCfgReq_T* pAMISetFWCfgReq,
		               AMISetFWCfgRes_T* pAMISetFWCfgRes,
                       int timeout);
uint16 IPMICMD_AMISetFWFilePathCfg(IPMI20_SESSION_T *pSession,
		               AMISetFWCfgReq_T* pAMISetFWCfgReq,
		               AMISetFWCfgRes_T* pAMISetFWCfgRes,
                       int timeout);
uint16	IPMICMD_SetUserPassword(IPMI20_SESSION_T *pSession, SetUserPswdReq_T	*pReqSetUserPswd,
							SetUserPswdRes_T	*pResSetUserPswd, int timeout);

uint16 SMASH_SetUserPassword(IPMI20_SESSION_T *pSession, SetUserPswdReq_T	*pReqSetUserPswd,
							SetUserPswdRes_T	*pResSetUserPswd, int timeout);
uint16 SMASH_FillNodeProps(uint16 recID,NODE_PROP * nodeProp);
uint16 SMASH_FillNodeProperties(uint16 recID, NODE_PROP * nodeProp);
uint16 SMASH_GetSelTimeStamp(INT32U timestamp,char *buf);
uint16 SMASH_GetSensorType(INT8U TypeCode,char *TypeString);
uint16 IPMICMD_AMIStartTFTPFwupdate(IPMI20_SESSION_T *pSession,
		AMIStartFwUpdateReq_T *pAMIStartFwUpdateReq,
		AMIStartFwUpdateRes_T *pAMIStartFwUpdateRes,
                       int timeout);
uint16 SMASH_SetFWProtocol(IPMI20_SESSION_T *pSession,
        AMISetFWProtocolReq_T* pAMISetFWProtocolReq,
        AMISetFWProtocolRes_T* pAMISetFWProtocolRes,
        int timeout);
uint16 IPMICMD_AMISetFWProtocol(IPMI20_SESSION_T *pSession,
                       AMISetFWProtocolReq_T* pAMISetFWProtocolReq,
                       AMISetFWProtocolRes_T* pAMISetFWProtocolRes,
                       int timeout);
uint16 SMASH_SetSN(IPMI20_SESSION_T *pSession, char *Location, int timeout);
uint16 SMASH_SetLocation(IPMI20_SESSION_T *pSession, char *Location, int timeout);
uint16 SMASH_StartNode();
uint16 SMASH_StopNode();
uint16 SMASH_ResetNode();
#endif
#endif
