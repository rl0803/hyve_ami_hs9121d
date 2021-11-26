 /******************************************************************
 *
 * @file	HyvePlatformCmds.h
 * @brief	The Hyve platform OEM CMD header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMCMDS_H_
#define HYVEPLATFORMCMDS_H_


#define CMD_DUMMY_IRQ					(0xFE)

extern int HyveCmd_DummyIRQ_Cmd(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes, _NEAR_ int BMCInst);

#endif

