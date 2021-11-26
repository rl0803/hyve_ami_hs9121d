 /******************************************************************
 *
 * @file	HyvePlatform.h
 * @brief	The Hyve platform header for each projects
 * 			to define their specific configs, functions, etc...
 *
 ******************************************************************/

#ifndef HYVEPLATFORM_H_
#define HYVEPLATFORM_H_

/********************* Platform include header files *********************/
#include "HyvePlatformGPIO.h"
#include "HyvePlatformSensorNum.h"
#include "HyvePlatformHooks.h"
#include "HyvePlatformFan.h"
#include "HyvePlatformPSU.h"
#include "HyvePlatformSensorMonitor.h"
#include "HyvePlatformTask.h"
#include "HyvePlatformCmds.h"
#include "HyvePlatformPreserveConf.h"

/********************* Define platform ID and name string *********************/
/* The naming rule of the platform ID string:
		ProjectID_CutsomerID_SKU
	For example:
		HS9121D_XXXX
		HS9121D_XXXX_1U10                     */
typedef enum {
	PLATFORM_DEFAULT = 0,
	PLATFORM_HS9121D,
} HyvePlatFormSkuID;

#define PLATFORMID_DEFAULT					"ast2600evb_ami"
#define PLATFORMID_HS9121D					"HS9121D"

#define PLARFORMID_TABLE \
		{ PLATFORM_DEFAULT, PLATFORMID_DEFAULT }, \
		{ PLATFORM_HS9121D, PLATFORMID_HS9121D },

/********************* Define platform configurations *********************/
#define HYFEPLATFORM_MB_FRU_ID		(0)
#define HYVE_FRU_FILE_SIZE			(256)


/********************* Export platform global variables *********************/
extern INT8U g_IsBMC_ACPowerOn;
extern UINT32 g_HyvePlatformJiffy;	// DO NOT use this var directly, use HYFEPLATFORM_JIFFY instead
extern int gHyvePlatformSkuID;	// DO NOT use this var directly, use HYVEPLATFORM_SKU instead
extern INT8U g_Is_DCPowerOn;

/********************* Define platform specific functions *********************/
/* The platform global time-tick per second */
#define HYFEPLATFORM_JIFFY 			((const UINT32)g_HyvePlatformJiffy)
#define HYFEPLATFORM_JIFFY_DIFF(X)	((UINT32)(HYFEPLATFORM_JIFFY - (X)))
#define HYVEPLATFORM_SKU			((const int)gHyvePlatformSkuID)

/********************* Type definitions *********************/
typedef struct {
	int skuID;
	char* platformID;
} HyvePlatformID_T;

/********************* Functions *********************/
extern int HyvePlatform_Init();
extern int HyvePlatform_TaskInit(int BMCInst);

#endif
