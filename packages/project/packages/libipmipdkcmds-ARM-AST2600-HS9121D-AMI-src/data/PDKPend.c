/****************************************************************
 ****************************************************************
 **                                                            **
 **    (C)Copyright 2006-2020, American Megatrends Inc.        **
 **                                                            **
 **            All Rights Reserved.                            **
 **                                                            **
 **        5555 Oakbrook Parkway, Norcross,                    **
 **                                                            **
 **        Georgia - 30093, USA. Phone-(770)-246-8600.         **
 **                                                            **
 ****************************************************************
 ****************************************************************
****************************************************************/
/*!
 * \file PDKPend.c
 * \author valantina
 * \date Sep 23, 2015
 * \brief Template for Pendtask 
 *
 * This file provides a template for OEM commands(which requires more
 * response time ) to add their task to pendtask
 */

#include <dlfcn.h>
#include "Types.h"
#include "PDKPend.h"
#include "Debug.h"
#include "IPMI_AMIConf.h"
#include "IPMIConf.h"
#include "PDKAccess.h"

// Function handler for OEM pend task
OEMPendCmdHndlrTbl_T m_OEMPendCmdHndlr [ PEND_OP_MAX_HANDLE ] =
{
        //* operaion, callback function
        {NONE, 0}
};

// Status handler for OEM pend task
OEMPendCmdStatus_T  m_OEMPendCmdStatus [ PEND_OP_MAX_HANDLE ] =
{
        //* operation  , status 
        {NONE, 0}
};


// Register OEM pend task handle
int InitOEMPendTaskTbl(void)
{
    unsigned int i;

    //* NO oem task defined
    if((m_OEMPendCmdHndlr[0].Operation == NONE ) || (m_OEMPendCmdStatus[0].Operation == NONE ) ){
       return 0;
    }

    for(i = 0; i < sizeof(m_OEMPendCmdHndlr) / sizeof(m_OEMPendCmdHndlr[0]); i++)
    {
        UpdateOEMCmdHndlr(m_OEMPendCmdHndlr[i].Operation,m_OEMPendCmdHndlr[i].PendHndlr);
    }

    for(i = 0; i < sizeof(m_OEMPendCmdStatus) / sizeof(m_OEMPendCmdStatus[0]); i++)
    {
        UpdateOEMPendStatus(m_OEMPendCmdStatus[i].Operation,m_OEMPendCmdStatus[i].PendStatus);
    }

    return 0;
}

