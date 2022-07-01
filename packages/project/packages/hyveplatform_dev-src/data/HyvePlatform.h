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
#include "HyvePlatformFRU.h"
#include "HyvePlatformSKUconfig.h"
#include "HyvePlatformMuxCtrl.h"
#include "HyvePlatformBP_FP.h"

//#define HYVEPSU_DEBUG_ENABLE 1
//#define HYVEFSC_DEBUG_ENABLE 1
//#define HYVETMP_DEBUG_ENABLE 1

/********************* Define platform ID and name string *********************/
/* The naming rule of the platform ID string:
		ProjectID_CutsomerID_SKU
	For example:
		HS9121D_XXXX
		HS9121D_XXXX_1U10                     */
typedef enum {
	PLATFORM_SKU_DEFAULT = 0,
	PLATFORM_SKU_HS9121D,
} HyvePlatformSkuID;

#define PLATFORMID_DEFAULT					"HS9121D"
#define PLATFORMID_HS9121D					"HS9121D"

#define PLARFORMID_TABLE \
		{ PLATFORM_SKU_DEFAULT, PLATFORMID_DEFAULT }, \
		{ PLATFORM_SKU_HS9121D, PLATFORMID_HS9121D },


#define PLATFORM_MANUFACTURE_ID				MANUFACTURE_ID_HYVE
#define PLATFORM_PRODUCT_ID					(9121)


/********************* Define platform configurations *********************/
/*
 * MB EEPROM (AT24CM01) layout

      Offset       Number of bytes
-------------------------------
 0x0000 ~ 0x01FF   ( 512 Bytes): MB FRU
 0x0200 ~ 0x09FF   (2048 Bytes): Reserved for BIOS using
 0x0A00 ~ 0x0A07   (   8 Bytes): last time stamp
 0x0A08 ~ 0x0A27   (  32 Bytes): BMC 4 MAC addresses
 0x0A50 ~                      : FSC config


 * I2C Bus, 0 based, 8-bit address
	I2C-1: APML (May use I3C-3)
	I2C-4: PMBUS
	I2C-5: SMBus for PCIe devices (G-link) access, AIC backplane
	I2C-6: For BMC to access the OCP, Riser, M.2, Clock-Gen IC, and connect to CPU I2C5
	I2C-7: MB FRU, Temp sensor
	I2C-8: CPU VR
	I2C-9: SMBus for PCIe devices (MCIO connector) access

	I2C-11: Fan HW monitor, on-board Fan(4 fans) control
	I2C-12: Fan board, 3 fans, can support up to 8 fans
	I2C-13: FP(front panel), Hyve debug card and CPLD
	I2C-14: CPLD
	I2C-15: ROT

 * I3C Bus, 0 based, 8-bit address
	I3C-0: DIMM A0 ~ F0
	I3C-1: DIMM G0 ~ L0
*/

#define HYFEPLATFORM_SPD_I3CBUS_NUM						(2) // total 2 I3C buses for accessing DIMM SPD
// the total DIMM num of each bus
#define HYFEPLATFORM_BUS_DIMM_NUM						(HYVE_MAX_HOST_DIMM_NUM / HYFEPLATFORM_SPD_I3CBUS_NUM)
#define HYFEPLATFORM_SPD_BUS_DIMM_AF					(0)	// I3C-0
#define HYFEPLATFORM_SPD_BUS_DIMM_GL					(1)	// I3C-1


#define HYFEPLATFORM_APML_BUS							(1) // I2C		or  (3) // I3C
//#define HYVEAMD_APML_BUS_ACCESS						HyveExt_I3C_Access_Retry // TODO
#define HYFEPLATFORM_SBRMI_ADDR   						SBRMI_ADDR_0
#define HYFEPLATFORM_SBTSI_ADDR   						SBTSI_ADDR_0
//#define HYVE_IMX31X2_BUS_ACCESS						HyveExt_I3C_Access_Retry // TODO
#define HYFEPLATFORM_IMX3112_ADDR						(0xE0)

#define HYFEPLATFORM_SMBUS_PDB							HYVE_PSU_I2C_BUS
#define HYFEPLATFORM_ADDR_PDB_TMP75						(0x9A)	// TMP75
#define HYFEPLATFORM_ADDR_PDB_FRU						(0xAC)  // AT24C02C, size 256 Bytes

#define HYFEPLATFORM_SMBUS_G_MCIO						(5)
#define HYFEPLATFORM_ADDR_MUX_PCIE						(0xEC)	// PCA9548A

#define HYFEPLATFORM_SMBUS_CLK_GEN						(6)
#define HYFEPLATFORM_ADDR_MUX_CLK_GEN					(0xE0)	// PCA9548A
#define 	MUX_CHANNEL_OCP0							MUX_CHANNEL_0
#define 	MUX_CHANNEL_P0_P_CLK_BUF					MUX_CHANNEL_1
#define 	MUX_CHANNEL_CPU_I2C5						MUX_CHANNEL_2 // currently not use (unknown bus owner CPU or BMC)
#define 	MUX_CHANNEL_RISER0							MUX_CHANNEL_3
#define 	MUX_CHANNEL_RISER1							MUX_CHANNEL_4
#define 	MUX_CHANNEL_M2								MUX_CHANNEL_5
#define HYFEPLATFORM_ADDR_OCP0							(0xFF) // Mux channel 0, address unknown
#define HYFEPLATFORM_ADDR_P0_P_CLK_BUF					(0xD8) // Mux channel 1, BMC doesn't control it
#define HYFEPLATFORM_ADDR_M2							(0xFF) // Mux channel 5, address unknown

#define HYFEPLATFORM_SMBUS_MB_TEMP_FRU					(7)
#define HYFEPLATFORM_ADDR_MB_TMP468						(0x90)	// TMP468
#define HYFEPLATFORM_ADDR_MB_TMP75_1					(0x92)	// TMP75
#define HYFEPLATFORM_ADDR_MB_TMP75_2					(0x94)	// TMP75

#define HYFEPLATFORM_SMBUS_CPU_VR						(8)
#define HYFEPLATFORM_ADDR_VDD_CORE_0_VDD_SOC			(0xC2)  // CPU SOC VR			// P0_VDD_SOC_RUN
#define HYFEPLATFORM_ADDR_VDD_CORE_1_VDD_11				(0xC4)  // CPU 1.1 Volt VR   	// P0_VDD_11_SUS
#define HYFEPLATFORM_ADDR_VDD_VDDIO						(0xC6)	// CPU VDDIO VR			// P0_VDD_VDDIO_RUN

#define HYFEPLATFORM_SMBUS_OCP_RISER					(9)
#define HYFEPLATFORM_ADDR_MUX_OCP_RISER					(0xE4)	// PCA9548A
#define 	MUX_CHANNEL_P2_MCIO1_1						MUX_CHANNEL_0
#define 	MUX_CHANNEL_P2_MCIO1_2						MUX_CHANNEL_1
#define 	MUX_CHANNEL_P3_MCIO2_1						MUX_CHANNEL_2
#define 	MUX_CHANNEL_P3_MCIO2_2						MUX_CHANNEL_3
#define 	MUX_CHANNEL_P3_MCIO2_3						MUX_CHANNEL_4 // for PCIeX8 device
#define 	MUX_CHANNEL_P3_MCIO2_4						MUX_CHANNEL_5
#define 	MUX_CHANNEL_P0_CLK_GEN						MUX_CHANNEL_6 // for PCIeX8 device
#define 	MUX_CHANNEL_P0_G_CLK_BUF					MUX_CHANNEL_7
#define HYFEPLATFORM_ADDR_E1S0							(0xEE)	// Mux channel 3	E1.S
#define HYFEPLATFORM_ADDR_E1S1							(0xEE)	// Mux channel 5	E1.S

#define HYFEPLATFORM_SMBUS_FAN_HWMONIOTR				(11)
#define HYFEPLATFORM_ADDR_FAN_HWMON						(0x40)	// HW monitor (MB Fan ctrl IC, NCT7362Y)

#define HYFEPLATFORM_SMBUS_FAN_BOARD					(12)
#define HYFEPLATFORM_ADDR_FAN_BOARD_HWMON0				(0x40)	// HW monitor 0
#define HYFEPLATFORM_ADDR_FAN_BOARD_HWMON1				(0x41)	// HW monitor 1
#define HYFEPLATFORM_ADDR_FAN_BOARD_TEMP				(0x90)	// fan board temp sensor
#define HYFEPLATFORM_ADDR_FAN_BOARD_FRU					(0xA0)	// fan board FRU

#define HYFEPLATFORM_SMBUS_FP_MP_DBGCARD_CPLD			(13)	// FP(front panel), MP(Middle panel), Hyve debug card or CPLD
#define HYFEPLATFORM_ADDR_FP_TEMP						(0x92)	// FP temp sensor
#define HYFEPLATFORM_ADDR_FP_FRU						(0xA8)	// FP FRU
#define HYFEPLATFORM_ADDR_DBGCARD						(0x40)	// Hyve debug card
#define HYFEPLATFORM_ADDR_CPLD1

#define HYFEPLATFORM_SMBUS_CPLD							(14)
#define HYFEPLATFORM_ADDR_CPLD0

#define HYFEPLATFORM_SMBUS_ROT							(15)
#define HYFEPLATFORM_ADDR_ROT



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

/********** Platform Button Map Number Definition **********/
typedef enum {
	PLATFORM_BUTTON_POWER = 0,
	PLATFORM_BUTTON_RESET,
	PLATFORM_BUTTON_MAX_Index
} HyvePlatformButtonIndex;


/********************* Export platform global variables *********************/
extern UINT32 g_HyvePlatformJiffy;		// DO NOT use this var directly, use HYFEPLATFORM_JIFFY instead
extern int gHyvePlatformSkuID;			// DO NOT use this var directly, use HYVEPLATFORM_SKU instead
extern INT8U g_Is_DCPowerOn;			// DO NOT use this var directly, use HYVEPLATFORM_SYS_PWRGOOD instead
extern INT8U g_Is_PSUPwrGood;			// DO NOT use this var directly, use HYVEPLATFORM_PSU_PWRGOOD instead
extern INT8U g_Is_DIMM_Ready;			// DO NOT use this var directly, use HYVEPLATFORM_IS_DIMM_READY instead
extern INT8U g_Is_CPUPwrGood;			// DO NOT use this var directly, use HYVEPLATFORM_CPU_PWRGOOD instead
extern INT8U g_Is_HostIn_S3_State;		// DO NOT use this var directly, use HYVEPLATFORM_IS_HOST_IN_S3 instead
extern INT8U g_Is_HostIn_S5_State;		// DO NOT use this var directly, use HYVEPLATFORM_IS_HOST_IN_S5 instead
extern INT8U g_Is_PowerButtonOn;
extern INT8U g_Is_ResetButtonOn;

/********************* Define platform specific functions *********************/
/* The platform global time-tick per second */
#define HYFEPLATFORM_JIFFY 					((const UINT32)g_HyvePlatformJiffy)
#define HYFEPLATFORM_JIFFY_DIFF(X)			((UINT32)(HYFEPLATFORM_JIFFY - (X)))
#define HYVEPLATFORM_SKU					((const int)gHyvePlatformSkuID)
#define HYVEPLATFORM_IS_SYS_PWRGOOD			((const INT8U)g_Is_DCPowerOn)
#define HYVEPLATFORM_IS_PSU_PWRGOOD			((const INT8U)g_Is_PSUPwrGood)
#define HYVEPLATFORM_IS_DIMM_READY			((const INT8U)g_Is_DIMM_Ready)
#define HYVEPLATFORM_IS_CPU_PWRGOOD			((const INT8U)g_Is_CPUPwrGood)
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
	I2CMUX_GLINK = 0, // MUX-PCA9548, for BMC SMBus channel to access PCIe devices
	I2CMUX_CLKGEN,    // MUX-PCA9548, for BMC SMBus channel to access OCP, Riser, and clock generator
	I2CMUX_PLINK,     // MUX-PCA9548, for BMC SMBus channel to access PCIe devices (MCIO connector)
	I2CMUXIndex_MAX
} HyvePlatformI2CMuxIndex;

typedef enum {
	Disable_All_JTagAccess = 0,
	Enable_CPLD_JTagAccess,
	Enable_Riser_JTagAccess,
	Enable_HostCPU_JTagAccess
} HyvePlatformJTagAccessSelect;

/********************* Functions *********************/
extern int HyvePlatform_Init();
extern int HyvePlatform_TaskInit(int BMCInst);

/********************* Platform Peripheral Control Functions *********************/
extern int HyvePlatform_ButtonProxy(const INT8U gpioNum, const INT16U delaySec,
									const INT16U delayMs, INT8U retryCount);
extern int HyvePlatform_BIOS_FlashSelect(const INT8U op, INT8U* pFlashIndex);
extern int HyvePlatform_BIOS_FlashAccessControl(const INT8U op, INT8U* pIs_enable);
extern int HyvePlatform_Reset_OCP_NIC_SMBus();
extern int HyvePlatform_DisplayPortPwrControl(const INT8U op, INT8U* pIs_enable);
extern int HyvePlatform_BoardSKUID(INT8U *pBoardSKUID);
extern int HyvePlatform_BoardID(INT8U *pBoardID);
extern int HyvePlatform_LED_Control(const INT8U ledIndex, const INT8U op, INT8U* pIs_enable);
extern int HyvePlatform_TriggerHostCPU_NMI_SYNC_FLOOD();
extern int HyvePlatform_Reset_EMMC();
extern int HyvePlatform_Reset_PwrAUX_IC();
extern int HyvePlatform_SetBMCReady(const INT8U enable);
extern int HyvePlatform_Reset_CMOS();
extern int HyvePlatform_JTagAccessSelect(const INT8U selection);
extern int HyvePlatform_DIMM_MuxControl(const INT8U op, INT8U* pIs_enable);
extern int HyvePlatform_Reset_I2CMux(const INT8U muxIndex);
extern int HyvePlatform_HostPowerCtrl(const INT8U on_off);

#endif
