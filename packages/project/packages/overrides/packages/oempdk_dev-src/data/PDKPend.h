/*******************************************************************
 *******************************************************************
 ***                                                             ***
 ***    (C)Copyright 2014, American Megatrends Inc.              ***
 ***                                                             ***
 ***    All Rights Reserved.                                     ***
 ***                                                             ***
 ***    5555 , Oakbrook Pkwy, Norcross,                          ***
 ***                                                             ***
 ***    Georgia - 30093, USA. Phone-(770)-246-8600.              ***
 ***                                                             ***
 *******************************************************************
 *******************************************************************
 *******************************************************************
 *
 * PDKPend.c
 * OEM Pend task declaration
 * karthik <karthikeyanm@amiindia.co.in>
 *
 * *******************************************************************/

#ifndef _PDKPEND_H_
#define _PDKPEND_H_

#include "PendTask.h"
#include "Types.h"

#if defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER8) || defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER9)

typedef enum
{
/*Make sure that Core and OEM should not conflict*/
    PEND_OP_FLASH_PNOR_PARTITION = 255,
    PEND_OP_REPROVISION_PARTITION = 256,
} OEMPendTaskOperation_E;

#else

typedef enum
{
  /*
    Make sure that Core and OEM should not conflict
    Replace 'NONE' with actual operation name
   */
  
  NONE = 255
} OEMPendTaskOperation_E;

#endif

typedef struct
{
    OEMPendTaskOperation_E Operation;
    pPendCmdHndlr_T     PendHndlr;
}OEMPendCmdHndlrTbl_T;

typedef struct
{
    OEMPendTaskOperation_E Operation;
    int PendStatus;
} OEMPendCmdStatus_T;

extern int InitOEMPendTaskTbl(void);

#if defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER8) || defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER9)
extern int PendFlashPNORPartition(INT8U * pData, INT32U DataLen, INT8U Ethindex, int BMCInst);
extern int PendReprovsionPNORPartition(INT8U * pData, INT32U DataLen, INT8U Ethindex, int BMCInst);
#endif

#endif

