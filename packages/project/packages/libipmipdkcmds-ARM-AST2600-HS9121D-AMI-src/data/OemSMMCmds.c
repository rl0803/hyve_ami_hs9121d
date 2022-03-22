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
 * OemCmdhndlr.c
 * Oem Commands used  by SMM Channel
 *
 * Author: Anurag Bhatia <anuragb@ami.com>
 *         Vinesh Chirstopher <vineshc@ami.com>
 *
 *****************************************************************/
#define ENABLE_DEBUG_MACROS     0
#include "Types.h"
#include "Debug.h"
#include "OemSMMCmds.h"
#include "MsgHndlr.h"
#include "IPMIDefs.h"


const OemSMMCmdHndlr_T	g_OemSMMCmdHndlr [] =
{
	{		NETFN_OEM,     CMD_EXAMPLE_1		,		SMMExample_1,		0x00	},
	{		NETFN_OEM,     CMD_EXAMPLE_2		,		SMMExample_2,		0x1   	},
	{		NETFN_OEM,	 CMD_EXAMPLE_3   	,		SMMExample_3,		0xff	},
	{                  0,                       0,								0,                   0         }
};


/**
*@fn PDKGetOEMMSMMCmdHndlr
*@brief
*@param
*@return Returns 0 on success
*            Returns CC_REQ_INV_LEN on command error
*            Returns -1 on failure
*/
int PDKGetOEMMSMMCmdHndlr (MsgPkt_T *pReq,MsgPkt_T *pRes, int BMCInst)
{
    /*  We have to get the Handle in OEM Cmdhndler */
    int i = 0;
    while(0 != g_OemSMMCmdHndlr[i].pHandler)
    {
        if ((g_OemSMMCmdHndlr [i].NetFnLUN == NET_FN (pReq->NetFnLUN)) &&
            (g_OemSMMCmdHndlr [i].Cmd	   == pReq->Cmd))
        {
            if (0xff == g_OemSMMCmdHndlr [i].Len ||pReq->Size == g_OemSMMCmdHndlr [i].Len)
            {
                pRes->Size = g_OemSMMCmdHndlr [i].pHandler (&pReq->Data [2],
                                                            pReq->Size,
                                                            &pRes->Data [2],BMCInst);

                /* Fill the KCS response bytes */
                pRes->Size += 2;
                return 0;
            }
            else
            {
                /* Command Error. Fill the response bytes*/
                pRes->Data [2] = CC_REQ_INV_LEN;
                return CC_REQ_INV_LEN;
                //goto return_Err;
            }
        }
        i++;
    }

    return -1;
}



 int  SMMExample_1(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
		printf("\n SMM Example 1\n");
        TDBG("\n unused parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
		*pRes= CC_NORMAL;
		 return 	sizeof (*pRes);
}

 int SMMExample_2(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
	printf("\n Example 2\n");
    TDBG("\n unused parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	*pRes= CC_NORMAL;
	return sizeof (*pRes);
}

 int SMMExample_3(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
		printf("\n Example 3\n");
        TDBG("\n unused parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
		*pRes= CC_NORMAL;
		 return sizeof (*pRes);
}

