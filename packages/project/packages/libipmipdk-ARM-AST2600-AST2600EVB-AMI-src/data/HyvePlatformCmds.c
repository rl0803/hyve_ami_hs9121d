 /******************************************************************
 *
 * @file	HyvePlatformCmds.c
 * @brief	Provide Hyve Platform IPMI OEM commands
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "hal_hw.h"


#include "HyveCommon.h"


/*-----------------------------------------------------------------
 * @fn HyveCmd_DummyIRQ_Cmd		[Test code]
 * 
 * @brief	CMD_DUMMY_IRQ, NetFn 0x30 Command 0xFE
 * 
 * @return  Numbers of Response
 *-----------------------------------------------------------------*/
int HyveCmd_DummyIRQ_Cmd(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes, _NEAR_ int BMCInst)
{
	HyveMsgQ_T msg = {0};

    if (0) {
    	BMCInst = BMCInst;
    	ReqLen = ReqLen;
    }
	
    switch (pReq[0]) {
    case 0:
    	msg.msgType = HyvePlatformIRQMsgQ_PowerButton;
    	msg.msgData = pReq[1];
    	break;

    case 1:
    	msg.msgType = HyvePlatformIRQMsgQ_ResetButton;
    	msg.msgData = pReq[1];
    	break;

    default:
    	pRes[0] = CC_PARAM_OUT_OF_RANGE;
		return 1;
    	break;
    }
	pRes[0] = CC_NORMAL;
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		pRes[0] = CC_UNSPECIFIED_ERR;
	}

	return 1;
}

