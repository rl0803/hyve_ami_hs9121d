/****************************************************************
 ****************************************************************
 **                                                            **
 **    (C)Copyright 2010-2011, American Megatrends Inc.        **
 **                                                            **
 **            All Rights Reserved.                            **
 **                                                            **
 **        5555 Oakbrook Pkwy, Building 200, Norcross,         **
 **                                                            **
 **        Georgia 30093, USA. Phone-(770)-246-8600.           **
 **                                                            **
 ****************************************************************
 ****************************************************************/
/*****************************************************************
 *
 * OEMCmds.h
 * Maheswari A<maheswaria@amiindia.co.in>
 *****************************************************************/

#ifndef OEMCMDS_H
#define OEMCMDS_H

#if defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER8) || defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER9)

#include "IPMI_Sensor.h"

#pragma pack(1)

#define NETFN_IBM                                   0x3A

// Commands defined for IBM NetFn (OEM Commands)
#define CMD_AMI_ENABLE_CRONUS_STATE                 (0x01)
#define CMD_AMI_GET_LED_STATE		                (0x02)
#define CMD_AMI_SET_LED_STATE    	                (0x03)
#define CMD_AMI_SET_OEM_SEL			                (0x04)
#define CMD_AMI_WRITE_PNOR_PARTITION                (0x05)
#define CMD_AMI_RDWR_SCR_REGISTERS                  (0x06)
#define CMD_AMI_PNOR_ACCESS_STATUS                  (0x07)
#define CMD_AMI_WRITE_PNOR_PARTITION_STATUS		    (0x08)
#define CMD_ACQUIRE_RELEASE_POST_SMS_SEL            (0x09)
#define CMD_AMI_HAS_BMC_COMPLETED_BOOTING           (0x0A)
#define CMD_AMI_READ_PNOR_PARTITION                 (0x0B)
#define CMD_AMI_GET_PNOR_PARTITION_SIZE             (0x0C)
#define CMD_OCC_BYPASS_COMMAND                      (0x0D)
#define CMD_OCC_RESET                               (0x0E)
#define CMD_BOOT_GOLDEN_SIDE                        (0x0F)
#define CMD_SEL_POWER_RAIL_FAILURE                  (0x10)
#define CMD_SEL_FAN_CTRL_STATE                      (0x11)
#define CMD_FAN_CTRL_COMMAND                        (0x12)
#define CMD_FAN_RUNNING_STATE                       (0x13)
#define CMD_SET_FAN_SPEED                           (0x14)
#define CMD_PNOR_BOOT_FAILURE                       (0x15)
#define CMD_FAN_FAILURE_OEM_SEL                     (0x16)
#define CMD_CHECKSTOP_HOSTREBOOT_CTRL               (0x17)
#define CMD_GET_SET_POWER_REDUNDANT                 (0x18)
#define CMD_SEL_POWER_RAIL_LOG                      (0x19)
#define CMD_BMC_GOLDEN_SIDE_VERSION                 (0x1a)
#define CMD_SWITCH_VGA_ACCESS                       (0x1b)
#define CMD_TRIGGER_REPROVISION                     (0x1c)
#define CMD_REPROVISION_STATUS                      (0x1d)
#define CMD_UPDATE_BMC_GOLDEN                       (0x1e)
#define CMD_FAN_SHUTDOWN_OEM_SEL                    (0x26)

// OEM Error codes for completion code.
#define CC_INVALID_LED_ID 			                0x90
#define CC_LED_BLINK_NOT_SUPPORTED 	                0x91
#define CC_SCRATCH_READ_FAILED		                0x92
#define CC_SCRATCH_WRITE_FAILED		                0x93

#define		MAX_PNAME_LEN			                16
#define		MAX_PREFIX_LEN				32
#define 	MAX_PARTITIONDATA_LEN		            128
#define POWERSEQ_DEV                                "/dev/pow0"
#define MIN_REQLEN_SCRATCH_REGISTERS		        2
#define MAX_REQLEN_SCRATCH_REGISTERS_READ       17
#define MAX_REQLEN_SCRATCH_REGISTERS_WRITE		    17

#define  FIRDATA_PARTITION_STR                       "FIRDATA"
#define  MAX_PARTITION_DATASIZE                       254
typedef struct
{
    INT8U CompletionCode;
    INT8U Reserved[8];
}PACKED CronusModeRes_T;

typedef struct
{
   INT8 PartitionName[MAX_PNAME_LEN + 1];
   off_t Offset;
   INT32U DataLen;
   INT8U *PartitionData;
}PACKED PNORWriteReq_T;

typedef struct
{
   INT8 PartitionName[MAX_PNAME_LEN + 1];
   off_t Offset;
}PACKED PNORReadReq_T;

typedef struct
{
	INT8U CompletionCode;
    INT8U PartitionData[MAX_PARTITION_DATASIZE];
}PACKED PNORReadRes_T;

typedef struct
{
   INT8 PartitionName[MAX_PNAME_LEN+1];
}PACKED PNORPartInfoReq_T;

typedef struct
{
	INT8U CompletionCode;
	INT32U PartitionSize;
}PACKED PNORPartInfoRes_T;

typedef struct
{
  INT8U fan_no;
  INT8U fan_speed[2];
} PACKED SetFanSpeedReq_T;


#pragma pack()

extern int PDK_CronusState(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_GetLedState(_NEAR_ INT8U * pReq,INT8U ReqLen,_NEAR_ INT8U * pRes,int BMCInst);

extern int PDK_SetLedState(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U * pRes, int BMCInst);

extern int PDK_FlashPNORPartition(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U * pRes, int BMCInst);

extern int PDK_RDWRScratchRegisters(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U * pRes, int BMCInst);

extern int PDK_PNORAccessStatus(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U * pRes, int BMCInst);

extern int PDK_PNORWriteStatus(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_AcquireReleasePostSMSandSEL(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_HasBMCCompletedBooting(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_ReadFIRPartition(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_GetPartitionInfo(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_OCCByPassCommand(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_GoldenBootUp(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_FanControlCmd(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_IsFanControlRunning(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_SetFanSpeed_Firestone(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_CKStop_HostReboot_Ctrl(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_sendGPUCommand(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_GPUSetPowerLimit(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_GPUGetPowerLimit(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);

extern int PDK_GetSetPowerRedundant(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_BMCGoldenSide_ver(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst); 

extern int PDK_ReprovisionTriggers(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_ReprovisionStatus(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_UpdateBMCGoldenSide (_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_AMIlockIpmiIfc (_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes, int BMCInst);

extern int PDK_AMIunlockIpmiIfc (_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes, int BMCInst);

extern int PDK_AMIAddExtendSelEntries(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_AMIGETExtendSelData(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_AMIPartialAddExtendSelEntries(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);

extern int PDK_AMIPartialGetExtendSelEntries(_NEAR_ INT8U *pReq, INT8U ReqLen, _NEAR_ INT8U *pRes, int BMCInst);
#endif
#endif /* OEMCMDS_H */
