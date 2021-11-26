/****************************************************************
 ****************************************************************
 **                                                            **
 **    (C)Copyright 2005-2006, American Megatrends Inc.        **
 **                                                            **
 **            All Rights Reserved.                            **
 **                                                            **
 **        6145-F, Northbelt Parkway, Norcross,                **
 **                                                            **
 **        Georgia - 30071, USA. Phone-(770)-246-8600.         **
 **                                                            **
 ****************************************************************
 ****************************************************************/
/******************************************************************
 *
 * PDKInt.c
 * PDK interrupt handling.
 *
 *  Author: Vinothkumar S <vinothkumars@ami.com>
 ******************************************************************/

#ifndef __PDKINT__H 
#define  __PDKINT__H 

#include "Types.h"
#include "OSPort.h"
#include "Debug.h"
#include "API.h"
#include "SharedMem.h"
#include "ipmi_int.h"
#include "featuredef.h"

CoreFeatures_T g_corefeatures;
CoreMacros_T g_coremacros; 

extern int PDK_RegIntFDs ( struct pollfd **pfd, int BMCInst, int ret[IPMI_MAX_INT_FDS], int gpio_desc);
extern int PDK_RegGPIOInts( int fd, int BMCInst, int pinNum[IPMI_MAX_INT_FDS], int **pCount, int gpio_base);

extern IPMI_INTInfo_T* PDK_GetIntInfo (int BMCInst, int FdNum);
extern IPMI_INTInfo_T* PDK_CheckForInt ( int interrupt_num , INT8U reading_on_assertion, int BMCInst);

#if defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER8) || defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER9)
extern int  PDK_RegInt (int fd ,int BMCINst);
#else
extern int  PDK_RegInt ( IPMI_INTInfo_T *pIntInfo ,int BMCINst);
#endif

#endif //__PDKINT__H 
