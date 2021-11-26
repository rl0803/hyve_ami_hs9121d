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
 * PDKCmds.c
 * Hooks that are invoked at different points of the Firmware
 * execution.
 *
 *  Author: Govind Kothandapani <govindk@ami.com>
 ******************************************************************/
#define ENABLE_DEBUG_MACROS     0
#include "Types.h"
#include "Debug.h"
#include "API.h"
#include "IPMIDefs.h"
#include "IPMI_Chassis.h"
#include "IPMI_SEL.h"
#include "IPMI_SDRRecord.h"
#include "IPMI_IPM.h"
#include "SharedMem.h"
#include "LEDMap.h"
#include "Indicators.h"
#include "NVRAccess.h"
#include "Platform.h"
#include "PDKCmds.h"
#include "OemDefs.h"
#include "cmdselect.h"
#include "IPMIConf.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "HyveCommon.h"

int IsRawCmdLogEnabled(int BMCInst);

/*NetFn -Application OEM Command Handler to override generic IPMI cmd 
   Commands can be added to the Handler as explained below 
  { CMD_GET_DEV_ID, PRIV_USER, GETDEV_ID,  0x00,  0xAAAA },
  where CMD_GET_DEV_ID - Command no.
            PRIV_USER            - Privilege level like administrator,user
            GETDEV_ID           -  Function for the command to override
            0x00                     -  Request length for the command
            0xAAAA                -   Firewall settings 
  GETDEV_ID function definition can be as shown below   
  int  GETDEV_ID (_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes)
  {
		*pRes= CC_NORMAL;
		return 	sizeof (*pRes);
  }   
*/ 

int PnmOemPlatformPowerCharacNotifiOverride(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes, int BMCInst)
{
	//TODO
	TDBG("\n unused parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	return sizeof(*pRes);
}

CmdHndlrMap_T	g_Oem_App_CmdHndlr [] =
{
    { 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

/*Netfn - Chasiss OEM Command Handler to override generic IPMI cmd */
CmdHndlrMap_T	g_Oem_Chassis_CmdHndlr [] =
{
    { 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

/*Netfn - Bridging OEM Command Handler to override generic  IPMI cmd */
CmdHndlrMap_T	g_Oem_Bridge_CmdHndlr [] =
{
    { 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

/*Netfn - Sensor OEM Command Handler to override generic IPMI cmd */
CmdHndlrMap_T	g_Oem_SensorEvent_CmdHndlr [] =
{
    { 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

/*Netfn - Storage OEM Command Handler to override generic IPMI cmd */
CmdHndlrMap_T	g_Oem_Storage_CmdHndlr [] =
{
    { 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

/*Netfn - Transport OEM Command Handler to override generic IPMI cmd */
CmdHndlrMap_T	g_Oem_Config_CmdHndlr [] =
{
    { 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

/*Netfn - 30 OEM Command Handler to override generic IPMI cmd */
CmdHndlrMap_T	g_Oem_NetFn30_CmdHndlr [] =
{
//	{CMD_PNM_OEM_PLATFORM_POWER_CHARACTERIZATION_NOTIFICATION, PRIV_USER, PnmOemPlatformPowerCharacNotifiOverride, 1, 0XAAAA},
	{ 0x00,                 0x00,           0x00,              0x00,                              0x0000, 0x00 }
};

CmdHndlrMap_T g_HYVE_CmdHndlr [] =
{
		// Hyve common IPMI OEM commands
		HYVECMDS_CMDHANDLER

		// Platform IPMI OEM commands
	//	{ CMD_XXX_Platform_CMD,		Privilege,		CmdHndlr, 	ReqLen, 	FFConfig,		IfcSupport}
		{ CMD_DUMMY_IRQ,			PRIV_ADMIN, HyveCmd_DummyIRQ_Cmd,			0x02, 0xAAAA, 0xFFFF },
		{ 0x00,						0x00,           0x00,		0x00,		0x0000,			0x00 }
};

/*OEM Message Handler table to override generic IPMI cmd
  Any OEM specific Netfn and Command Handler can also be
  added here*/
const MsgHndlrTbl_T oem_MsgHndlrTbl [] =
{
    { NETFN_APP,                     g_Oem_App_CmdHndlr             },
    { NETFN_CHASSIS,                 g_Oem_Chassis_CmdHndlr         },
    { NETFN_BRIDGE,                  g_Oem_Bridge_CmdHndlr          },
    { NETFN_SENSOR,                  g_Oem_SensorEvent_CmdHndlr     },
    { NETFN_STORAGE,                 g_Oem_Storage_CmdHndlr         },
    { NETFN_TRANSPORT,               g_Oem_Config_CmdHndlr          },
//    { NETFN_30,                   g_Oem_NetFn30_CmdHndlr			}, // Remove NETFN_30
    { NETFN_HYVE,					g_HYVE_CmdHndlr				    }, // Hyve OEM Cmds
};


/* Is there already a way to add an OEM command if the following handler doesn't exist? */
const ExCmdHndlrMap_T g_OEM_CmdHndlr [] =
{
   
};

/*OEM OwnerIdTbl -This table helps to retrieve the IPMB channel in which
    the device is present.This helps in framing the "Send Message" command.
    The entries can be like 
    {0x2c,6}
    where 0x2c - Can be Node Manager Addr
               6      - The channel number for node manager
*/
const   OwnerIDMap_T  oem_OwnerIdTbl [] =
{
    	
};

/**
*@fn PDKGetOEMMsgHndlrMap 
*@brief Helps in getting command handler for specific NetFn
*@parm NetFn -NetFunction
*@param pCmdHndlrMap - Command Handler for the given NetFn
*@return Returns 0 on success and -1 on failure
*/
int
PDKGetOEMMsgHndlrMap (INT8U NetFn, _FAR_ CmdHndlrMap_T ** pCmdHndlrMap,int BMCInst)
{
    unsigned int i;
    TDBG("\n unused parameters %d\n",BMCInst);
    /* Get the command handler corresponding to the net function */
    for (i = 0; i < sizeof (oem_MsgHndlrTbl) / sizeof (oem_MsgHndlrTbl [0]); i++)
    {
        if (oem_MsgHndlrTbl [i].NetFn == NetFn) 
        {
            break; 
        }
    }

    /* Check if we have not found our net function */
    if (i == sizeof (oem_MsgHndlrTbl) / sizeof (oem_MsgHndlrTbl [0]))
    {
        return -1;
    }

    /* Get the handler corresponding to the command */
    *pCmdHndlrMap = (CmdHndlrMap_T*)oem_MsgHndlrTbl [i].CmdHndlrMap;
    return 0;

}


/*-----------------------------------------------------------------
 * @fn PDK_PreProcessCmd
 *
 * @brief This function is invoked before processing an incoming IPMI command.
 * Use this function to implement a new IPMI command, override an existing IPMI
 * command or perform a certain action on an incoming IPMI command.
 *
 * @param  NetFnLUN		- Net Function & LUN for which the command is addressed.
 * @param  pChannelInfo - Pointer to the channel information.
 * @param  pRequest     - Request IPMI Command Packet.
 * @param  RequestLen   - Length of the Request.
 * @param  pResponse    - Pointer to buffer to hold the response.
 * @param  pResponseLen - Pointer to the variable to hold response length.
 *
 * @return 0		- If the firmware needs to handle this command.
 *         -1		- otherwise
 *-----------------------------------------------------------------*/

//static const INT8U  MfgID[]       = {0xA2, 0x02,0x00};     /**< Contains Manufacturer ID */

int
PDK_PreProcessCmd (INT8U	NetFnLUN,			INT8U Cmd,
					_FAR_	PDK_ChannelInfo_T*	pChannelInfo,
					  	_FAR_ INT8U*				pRequest,
					  		  INT8U					RequestLen,
					  	_FAR_ INT8U*				pResponse,
					  	_FAR_ INT8U*				pResponseLen,
					  	int BMCInst)
{
	//TEXTLOG(LOG_CRIT, "This is a test message for logging\n");
	TDBG("\n unused parameters : %d\t%d\n",pResponse,pResponseLen);
    if((g_corefeatures.log_ipmi_command == ENABLED) && (1 == IsRawCmdLogEnabled(BMCInst)))
		LogIPMICmd(LOG_WARNING, "Request:",(NetFnLUN >> 2), Cmd, pChannelInfo->ChannelNum, RequestLen, pRequest);
	
	return 0;
}


/*-----------------------------------------------------------------
 * @fn PDK_PostProcessCmd
 *
 * @brief This function is invoked after an IPMI command is handled by the
 * core firmware. The response is contained in pResponse and the length of
 * the response is in pResponseLen. Use this function if you would like to
 * modify certain fields of the response or modify the response based on
 * certain conditions.
 *
 * @param  NetFnLUN		- Net Function & LUN for which the command is addressed.
 * @param  pChannelInfo - Pointer to the channel information.
 * @param  pRequest     - Request IPMI Command Packet.
 * @param  RequestLen   - Length of the Request.
 * @param  pResponse    - Pointer to buffer to hold the response.
 * @param  pResponseLen - Pointer to the variable to hold response length.
 *
 * @return 0		- If the firmware needs to handle this command.
 *         -1		- otherwise
 *-----------------------------------------------------------------*/
int
PDK_PostProcessCmd 	(INT8U 	NetFnLUN,			INT8U	Cmd,
					_FAR_	PDK_ChannelInfo_T*	pChannelInfo,
					  	_FAR_ INT8U*				pRequest,
					  		  INT8U					RequestLen,
					  	_FAR_ INT8U*				pResponse,
					  	_FAR_ INT8U*				pResponseLen,
					  	int BMCInst)
{
	INT8U ResponseLen = *pResponseLen;
    TDBG("\n unused parameters : %d\t%d\n",pRequest,RequestLen);
    if((g_corefeatures.log_ipmi_command == ENABLED) && (1 == IsRawCmdLogEnabled(BMCInst)))
		LogIPMICmd(LOG_INFO, "Response:",(NetFnLUN >> 2), Cmd, pChannelInfo->ChannelNum, ResponseLen, pResponse);

	return 0;
}

/**
*@fn PDKAMIGetChNum
*@brief This function helps in getting the corresponding channnel no
             from SensorOwnerID to be used by sendmsg command
*@param SensorOwnerID Sensor Owner ID
*@return Returns ChannelNum on success
                Returns '1', if no match occurs
*/                
int PDKAMIGetChNum(INT8U SensorOwnerID,int BMCInst)
{
    int i; 
    TDBG("\n unused parameters %d\n",BMCInst);
    for(i = 0; i < (signed)(sizeof (oem_OwnerIdTbl) / sizeof (oem_OwnerIdTbl [0])); i++)
    {
        if (oem_OwnerIdTbl [i].OwnerID == SensorOwnerID) 
        {
            break; 
        }
    }

    if (i == sizeof (oem_OwnerIdTbl) / sizeof (oem_OwnerIdTbl [0]))
    {
        return 1;
    }

    return oem_OwnerIdTbl[i].ChannelNum;
}

int IsRawCmdLogEnabled(int BMCInst)
{
    _FAR_ BMCInfo_t* pBMCInfo = &g_BMCInfo[BMCInst];

    return (0x00!=(0x01 & pBMCInfo-> extended_log_conf)) ? 1 : 0;

}


