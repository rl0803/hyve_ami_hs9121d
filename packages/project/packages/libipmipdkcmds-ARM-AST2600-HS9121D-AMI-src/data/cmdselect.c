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
 *
 * cmdselect.c
 * OEM can enable or disable IPMI Command accoring to requirements
 *
 *  Author: Winston <winstont@ami.com>
 ******************************************************************/

#include "Types.h"
#include "Debug.h"
#include "IPMI_App.h"
#include "IPMI_Chassis.h"
#include "IPMI_Bridge.h"
#include "IPMI_SensorEvent.h"
#include "IPMI_Storage.h"
#include "IPMI_DeviceConfig.h"
#include "IPMI_AMI.h"
#include "IPMIDefs.h"
#include "IPMI_OPMA.h"
#include "Pnm.h"
#include "IPMI_GroupExtn.h"
#include "cmdselect.h"
#include "IPMIConf.h"
#include "dbgout.h"
#include "PDKCmdselect.h"

#include "HyveCommon.h"

/* Individual command can be Enabled/Disabled using the below tables.
    To Enable/Disable the command "Set BMC GLOBA ENABLES" should be added 
    in table g_app which corresponds to its Net Function (0x6). 
    1) The first entry 'CMD_SET_BMC_GBL_ENABLES' denotes command number. 
    2) The second entry can be ENABLED or DISABLED. 
    3) The third entry should be changed only if logging of 
        "IPMI command support" is enabled. The third entry can be 
        NONE                      - Command will not be logged
        EXT_REQ_LOG         - IPMI command reqest will be logged into extended log (SD Card)
        EXT_RES_LOG         - IPMI command response will be logged into extended log (SD Card)
        VOL_REQ_RES_LOG - Both request and response will be logged into /var/log
*/

const NetFnCmds_T g_App [] = 
{
// { CMD_SET_BMC_GBL_ENABLES                           ,ENABLED, NONE},
    {0                                                                   ,0           , NONE },
};

const NetFnCmds_T g_Chassis [] =
{
    {CMD_GET_CHASSIS_STATUS, ENABLED,VOL_REQ_RES_LOG},
    {0,                                                                            0             , NONE}

};

const NetFnCmds_T g_Bridge [] = 
{
    { 0                                                                           ,0           , NONE}

};

const NetFnCmds_T g_Sensor [] = 
{
    {0,                                                                           0             , NONE}
};

const NetFnCmds_T g_Storage [] = 
{
   
    {CMD_ADD_SEL_ENTRY, ENABLED, EXT_REQ_LOG | EXT_RES_LOG }, 
    { 0,                                                                             0             , NONE}

};

const NetFnCmds_T g_Transport [] = 
{
    { 0                                                                            ,0            , NONE}
};

const NetFnCmds_T g_AMI [] = 
{
    {0                                                                           ,0            , NONE}
};

const NetFnCmds_T g_NetFn30 [] = 
{
    {  0                                                                         ,0             , NONE}

};

const NetFnCmds_T g_opma2 [] =
{
    {  0                                                                          ,0             , NONE}
};

const NetFnCmds_T g_apml [] = 
{
    {0                                                                            ,0           , NONE}

};

const NetFnCmds_T g_dcmi [] = 
{
    { 0                                                                             ,0          , NONE}

};

const NetFnCmds_T g_hpm [] = 
{
    { 0,                                            0      , NONE}

};

const NetFnCmds_T g_pnm [] =
{
    {0                                                                             ,0           , NONE}
};

const NetFnCmds_T g_ssi [] =
{
    { 0,                                        0, NONE}
};

NetFnCmds_T g_Hyve_oem [] =
{
	// Hyve common IPMI OEM commands
	HYVECMDS_NETFNTABLE

	// Platform IPMI OEM commands
//	{ CMD_XXX_Platform_CMD,				ENABLED, NONE },
	{ CMD_DUMMY_IRQ,					ENABLED, NONE },
};

NETFNTable_T Netfntbl [] = 
{
    { NETFN_APP,        GRPEXT_NA,      g_App       },
    { NETFN_CHASSIS,    GRPEXT_NA,      g_Chassis   },
    { NETFN_BRIDGE,     GRPEXT_NA,      g_Bridge    },
    { NETFN_SENSOR,     GRPEXT_NA,      g_Sensor    },
    { NETFN_STORAGE,    GRPEXT_NA,      g_Storage   },
    { NETFN_TRANSPORT,  GRPEXT_NA,      g_Transport },
    { NETFN_AMI,        GRPEXT_NA,      g_AMI       },
//    { NETFN_30,         GRPEXT_NA,      g_NetFn30   }, // Remove NETFN_30
    { NETFN_OPMA2,      GRPEXT_NA,      g_opma2     },
    { NETFN_APML,       GRPEXT_NA,      g_apml      },
    { NETFN_HPM,        GRPEXT_HPM,     g_hpm       },
    { NETFN_DCMI,       GRPEXT_DCMI,    g_dcmi      },
//    { NETFN_PNM,        GRPEXT_NA,      g_pnm       }, // Remove NETFN_30
    { NETFN_SSI,        GRPEXT_SSI,     g_ssi       },
    { NETFN_HYVE,   	GRPEXT_NA,      g_Hyve_oem  }, // Hyve OEM Cmds
    { 0xff, 0, NONE }
};

NETFNTable_T *PDK_GetNetFnHndlr()
{
    return &Netfntbl[0];
}


