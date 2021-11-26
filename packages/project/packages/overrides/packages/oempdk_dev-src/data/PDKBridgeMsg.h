/*******************************************************************
********************************************************************
****                                                              **
****    (C)Copyright 2011-2012, American Megatrends Inc.          **
****                                                              **
****    All Rights Reserved.                                      **
****                                                              **
****    5555 , Oakbrook Pkwy, Norcross,                           **
****                                                              **
****    Georgia - 30093, USA. Phone-(770)-246-8600.               **
****                                                              **
********************************************************************
********************************************************************
********************************************************************
**
** PDKBridgeMsg.h
** Bridge Message originator enumerations.
**
** Author: Senathipathy (senathipathyt@ami.com)
*******************************************************************/

#ifndef PDKBRIDGEMSG_H
#define PDKBRIDGEMSG_H

typedef enum
{
  ORIGIN_UNSPECIFIED = 0,
  ORIGIN_SENDMSG,
  ORIGIN_CMDFWD,
  ORIGIN_INT_REQ,
  ORIGIN_NM,
}BridgeOrigin;

#endif
