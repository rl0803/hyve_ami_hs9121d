/*****************************************************************
 *****************************************************************
 ***                                                            **
 ***    (C)Copyright 2005-2006, American Megatrends Inc.        **
 ***                                                            **
 ***            All Rights Reserved.                            **
 ***                                                            **
 ***        6145-F, Northbelt Parkway, Norcross,                **
 ***                                                            **
 ***        Georgia - 30071, USA. Phone-(770)-246-8600.         **
 ***                                                            **
 *****************************************************************
 *****************************************************************
 ******************************************************************
 *
 * PDKLED.h
 * Platform specific LED Configuration.
 * Maheswari A <maheswaria@amiindia.co.in>
 * 
 ******************************************************************/
#ifndef _PDKLED_H_
#define _PDKLED_H_

#if defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER8) || defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER9)

/*  LED Numbers as specified in the Specification */
#define FAULT_ROLLUP_LED			0
#define POWER_ON_LED				1
#define HOST_STATUS_LED			2
#define CHASSIS_IDENTIFY_LED			3

#endif
#endif  /* _PDKLED_H_*/
