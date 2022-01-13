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
#include "HyvePlatformCPLD.h"
#include "HyvePlatformROT.h"


/********************* Define platform ID and name string *********************/
/* The naming rule of the platform ID string:
		ProjectID_CutsomerID_SKU
	For example:
		HS9121D_XXXX
		HS9121D_XXXX_1U10                     */
typedef enum {
	PLATFORM_DEFAULT = 0,
	PLATFORM_HS9121D,
} HyvePlatformSkuID;

#define PLATFORMID_DEFAULT					"ast2600evb_ami"
#define PLATFORMID_HS9121D					"HS9121D"

#define PLARFORMID_TABLE \
		{ PLATFORM_DEFAULT, PLATFORMID_DEFAULT }, \
		{ PLATFORM_HS9121D, PLATFORMID_HS9121D },


#define PLATFORM_MANUFACTURE_ID				MANUFACTURE_ID_HYVE
#define PLATFORM_PRODUCT_ID					(9121)


/********************* Define platform configurations *********************/
#define HYFEPLATFORM_MB_FRU_ID		(0)
#define HYVE_FRU_FILE_SIZE			(256)


/********** Platform LED Map Number Definition **********/
/* Note: HS9121D has 5 LEDs */
typedef enum {
	PLATFORM_LED_BMC_HEARTBEAT = 0,
	PLATFORM_LED_IDENTIFY,
	PLATFORM_LED_SYS_STATUS_Y,
	PLATFORM_LED_SYS_STATUS_G,
	PLATFORM_LED_SYS_STATUS_R,
	PLATFORM_LED_MAX_Index
} HyvePlatformLEDIndex;


/* I2C Bus, 0 based
I2C-1: APML (May use I3C-4)
I2C-4: PMBUS
I2C-5: SMBus for PCIe device access
I2C-6: For BMC to access the Clock-Gen IC but BMC doesn't control it.
I2C-7: MB FRU, Temp sensor
I2C-8: CPU VR
I2C-9: OCP, Riser

I2C-11: Fan HW monitor, tach??
I2C-12: Fan board
I2C-13: Hyve Debug Card
I2C-14: CPLD
I2C-15: ROT

*/


/********************* Export platform global variables *********************/
extern INT8U g_IsBMC_ACPowerOn;
extern UINT32 g_HyvePlatformJiffy;		// DO NOT use this var directly, use HYFEPLATFORM_JIFFY instead
extern int gHyvePlatformSkuID;			// DO NOT use this var directly, use HYVEPLATFORM_SKU instead
extern INT8U g_Is_DCPowerOn;			// DO NOT use this var directly, use HYVEPLATFORM_SYS_PWRGOOD instead
extern INT8U g_Is_PSUPwrGood;			// DO NOT use this var directly, use HYVEPLATFORM_PSU_PWRGOOD instead
extern INT8U g_Is_DIMM_Ready;			// DO NOT use this var directly, use HYVEPLATFORM_IS_DIMM_READY instead
extern INT8U g_Is_CPUPwrGood;			// DO NOT use this var directly, use HYVEPLATFORM_CPU_PWRGOOD instead
extern INT8U g_Is_HostIn_S3_State;		// DO NOT use this var directly, use HYVEPLATFORM_IS_HOST_IN_S3 instead
extern INT8U g_Is_HostIn_S5_State;		// DO NOT use this var directly, use HYVEPLATFORM_IS_HOST_IN_S5 instead

/********************* Define platform specific functions *********************/
/* The platform global time-tick per second */
#define HYFEPLATFORM_JIFFY 					((const UINT32)g_HyvePlatformJiffy)
#define HYFEPLATFORM_JIFFY_DIFF(X)			((UINT32)(HYFEPLATFORM_JIFFY - (X)))
#define HYVEPLATFORM_SKU					((const int)gHyvePlatformSkuID)
#define HYVEPLATFORM_SYS_PWRGOOD			((const INT8U)g_Is_DCPowerOn)
#define HYVEPLATFORM_PSU_PWRGOOD			((const INT8U)g_Is_PSUPwrGood)
#define HYVEPLATFORM_IS_DIMM_READY			((const INT8U)g_Is_DIMM_Ready)
#define HYVEPLATFORM_CPU_PWRGOOD			((const INT8U)g_Is_CPUPwrGood)
#define HYVEPLATFORM_IS_HOST_IN_S3			((const INT8U)g_Is_HostIn_S3_State)
#define HYVEPLATFORM_IS_HOST_IN_S5			((const INT8U)g_Is_HostIn_S5_State)

/********************* Type definitions *********************/
typedef struct {
	int skuID;
	char* platformID;
} HyvePlatformID_T;

typedef enum {
	P5V_AUX = 0,
	P3V3_AUX,
	PwrAUXIndex_MAX
} HyvePlatformPwrAUXIndex;

typedef enum {
	I2CMUX_CLKGEN = 0,	// MUX-PCA9546, for BMC SMBus channel to access clock generator
	I2CMUX_PLINK,		// MUX-PCA9548, for BMC SMBus channel to access PCIe devices
	I2CMUX_GLINK,		// MUX-PCA9546, for BMC SMBus channel to access OCP and Riser
	I2CMUXIndex_MAX
} HyvePlatformI2CMuxIndex;

typedef enum {
	HDT_CPLD = 0,
	HDT_BMC
} HyvePlatformHDTIndex;

/********************* Functions *********************/
extern int HyvePlatform_Init();
extern int HyvePlatform_TaskInit(int BMCInst);

/********************* Platform Peripheral Control Functions *********************/
extern int HyvePlatform_BIOS_FlashSelect(const INT8U op, INT8U* pFlashIndex);
extern int HyvePlatform_BIOS_FlashAccessControl(const INT8U op, INT8U* pIs_enable);
extern int HyvePlatform_Reset_OCP_NIC_SMBus();
extern int HyvePlatform_DisplayPortPwrControl(const INT8U op, INT8U* pIs_enable);
extern int HyvePlatform_BoardSKUID(INT8U *pBoardSKUID);
extern int HyvePlatform_BoardID(INT8U *pBoardID);
extern int HyvePlatform_LED_Control(const INT8U ledIndex, const INT8U op, INT8U* pIs_enable);

#endif
