/*------------------------------------------------------------*
 * ipmiconfigs.h
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

#ifndef _H_IPMICONFIGS_H
#define _H_IPMICONFIGS_H

extern int AMIConfig_LoadFile(char *File, AMIConfig_T *data);
extern int AMIConfig_SaveFile(char *File, AMIConfig_T *data);
extern int BondConfig_LoadFile(char *File, BondIface *data);
extern int BondConfig_SaveFile(char *File, BondIface *data);
extern int BridgeMgmtSHM_LoadFile(char *File, BridgeMgmtSHM_T *data);
extern int BridgeMgmtSHM_SaveFile(char *File, BridgeMgmtSHM_T *data);
extern int ChassisConfig_LoadFile(char *File, ChassisConfig_T *data);
extern int ChassisConfig_SaveFile(char *File, ChassisConfig_T *data);
extern int Dcmicfg_LoadFile(char *File, DCMICfg_T *data);
extern int Dcmicfg_SaveFile(char *File, DCMICfg_T *data);
extern int DualImageCfg_LoadFile(char *File, DualImageCfg_T *data);
extern int DualImageCfg_SaveFile(char *File, DualImageCfg_T *data);
extern int EncUserPswd_LoadFile(char *File, BMCInfo_t *data);
extern int EncUserPswd_SaveFile(char *File, BMCInfo_t *data);
extern int FFCmdConfigTable_LoadFile(char *File, BMCInfo_t *data);
extern int FFCmdConfigTable_SaveFile(char *File, BMCInfo_t *data);
extern int Generic_LoadFile(char *File, GENConfig_T *data);
extern int Generic_SaveFile(char *File, GENConfig_T *data);
extern int ICMBChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int ICMBChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int IPMBChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int IPMBChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int LAN1ChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int LAN1ChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int LAN2ChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int LAN2ChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int LAN3ChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int LAN3ChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int LAN4ChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int LAN4ChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int LANConfig1_LoadFile(char *File, LANConfig_T *data);
extern int LANConfig1_SaveFile(char *File, LANConfig_T *data);
extern int LANConfig2_LoadFile(char *File, LANConfig_T *data);
extern int LANConfig2_SaveFile(char *File, LANConfig_T *data);
extern int LANConfig3_LoadFile(char *File, LANConfig_T *data);
extern int LANConfig3_SaveFile(char *File, LANConfig_T *data);
extern int LANConfig4_LoadFile(char *File, LANConfig_T *data);
extern int LANConfig4_SaveFile(char *File, LANConfig_T *data);
extern int LANIfcConfig_LoadFile(char *File, BMCInfo_t *data);
extern int LANIfcConfig_SaveFile(char *File, BMCInfo_t *data);
extern int LANKCSConfig_LoadFile(char *File, LANKCSConfig_T *data);
extern int LANKCSConfig_SaveFile(char *File, LANKCSConfig_T *data);
extern int LoginAuditConfig_LoadFile(char *File, LoginAuditConfig_T *pLoginAuditCfg);
extern int LoginAuditConfig_SaveFile(char *File, LoginAuditConfig_T *pLoginAuditCfg);
extern int MiscConfig_LoadFile(char *File, MiscConfig_T *data);
extern int MiscConfig_SaveFile(char *File, MiscConfig_T *data);
extern int MultiSolConfig_LoadFile(char *File, MultiSolConfig_T *data);
extern int MultiSolConfig_SaveFile(char *File, MultiSolConfig_T *data);
extern int OPMAConfig_LoadFile(char *File, OPMA_Config_T *data);
extern int OPMAConfig_SaveFile(char *File, OPMA_Config_T *data);
extern int PEFConfig_LoadFile(char *File, PEFConfig_T *data);
extern int PEFConfig_SaveFile(char *File, PEFConfig_T *data);
extern int PEFRecordDetailsConfig_LoadFile(char *File, PEFRecordDetailsConfig_T *data);
extern int PEFRecordDetailsConfig_SaveFile(char *File, PEFRecordDetailsConfig_T *data);
extern int RMCPlus1_LoadFile(char *File, RMCPPlus_T *data);
extern int RMCPlus1_SaveFile(char *File, RMCPPlus_T *data);
extern int RMCPlus2_LoadFile(char *File, RMCPPlus_T *data);
extern int RMCPlus2_SaveFile(char *File, RMCPPlus_T *data);
extern int RMCPlus3_LoadFile(char *File, RMCPPlus_T *data);
extern int RMCPlus3_SaveFile(char *File, RMCPPlus_T *data);
extern int RMCPlus4_LoadFile(char *File, RMCPPlus_T *data);
extern int RMCPlus4_SaveFile(char *File, RMCPPlus_T *data);
extern int SMBusChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int SMBusChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int SMLINKChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int SMLINKChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int SMMChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int SMMChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int SMTPConfig1_LoadFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig1_SaveFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig2_LoadFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig2_SaveFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig3_LoadFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig3_SaveFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig4_LoadFile(char *File, Smtp_Config_T *data);
extern int SMTPConfig4_SaveFile(char *File, Smtp_Config_T *data);
extern int SOLTriggerEvtConfigTable_LoadFile(char *File, SOLTriggerEventCfg_T *Trigger);
extern int SOLTriggerEvtConfigTable_SaveFile(char *File, SOLTriggerEventCfg_T *Trigger);
extern int SOL1Config_LoadFile(char *File, SOLConfig_T *data);
extern int SOL1Config_SaveFile(char *File, SOLConfig_T *data);
extern int SOL2Config_LoadFile(char *File, SOLConfig_T *data);
extern int SOL2Config_SaveFile(char *File, SOLConfig_T *data);
extern int SOL3Config_LoadFile(char *File, SOLConfig_T *data);
extern int SOL3Config_SaveFile(char *File, SOLConfig_T *data);
extern int SOL4Config_LoadFile(char *File, SOLConfig_T *data);
extern int SOL4Config_SaveFile(char *File, SOLConfig_T *data);
extern int SSIConfig_LoadFile(char *File, SSIConfig_T *data);
extern int SSIConfig_SaveFile(char *File, SSIConfig_T *data);
extern int SerialChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int SerialChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int SMConfig_LoadFile(char *File, SMConfig_T *data);
extern int SMConfig_SaveFile(char *File, SMConfig_T *data);
extern int SystemInfo_LoadFile(char *File, SystemInfoConfig_T *data);
extern int SystemInfo_SaveFile(char *File, SystemInfoConfig_T *data);
extern int SysifcChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int SysifcChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int ThirdIPMBChannelInfo_LoadFile(char *File, ChannelInfo_T *data);
extern int ThirdIPMBChannelInfo_SaveFile(char *File, ChannelInfo_T *data);
extern int TriggerEvtConfigTable_LoadFile(char *File, TriggerEventCfg_T *Trigger);
extern int TriggerEvtConfigTable_SaveFile(char *File, TriggerEventCfg_T *Trigger);
extern int UserInfo_LoadFile(char *File, BMCInfo_t *data);
extern int UserInfo_SaveFile(char *File, BMCInfo_t *data);
extern int VersionConfig_LoadFile(char *File, VersionConfig_T *data);
extern int VersionConfig_SaveFile(char *File, VersionConfig_T *data);
extern int WDTConfig_LoadFile(char *File, WDTConfig_T *data);
extern int WDTConfig_SaveFile(char *File, WDTConfig_T *data);

#endif //_H_IPMICONFIGS_H
