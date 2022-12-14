 /******************************************************************
 *
 * @file	HyvePlatformFan.h
 * @brief	The Hyve platform Fan header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMFAN_H_
#define HYVEPLATFORMFAN_H_


/* Note: TODO: The fan direction is not determined yet

	Mother Board
	----------------------------------		--> Out?
	|Fan |Rear|                |Front|		<-- In?
	|	 |    |                |     |
	|	 |    |                |     |
	|	 |    |                |     |
	----------------------------------                     

	HS9121D supports 7 Fans (MB 4 + FanBoard 3), the software fan index from 0 to 6
		MB fan index: from 0 ~ 3
		FanBoard index: from 4 ~ 6
*/
typedef enum {
	PlatformFanDir_Unkonwn = 0,
	PlatformFanDir_In,
	PlatformFanDir_Out
} HyvePlatformFanDirection;


extern INT8U HyvePlatform_FSC_GetConfigBankID();
extern void HyvePlatform_FSC_Init(int BMCInst);
extern INT8U HyvePlatformFan_GetFanDir();
extern int HyvePlatformFan_NCT7362Y_Init();
extern void HyvePlatformFan_PresentDetect();

extern const INT8U g_FSCI2CBusTable[];
extern const INT8U g_FSCI2CAddrTable[];
extern const INT8U g_tachIndexTable[];
extern const INT8U g_pwmIndexTable[];

/***************** Platform override functions *****************/
#define HYVEPLATFORM_FSC_I2C_BUS(index)					(g_FSCI2CBusTable[((index) / 4)])
#define HYVEPLATFORM_FSC_I2C_ADDR(index)				(g_FSCI2CAddrTable[((index) / 4)])
#define HYVEPLATFORM_FSC_MONITOR_I2C_BUS(index)			(g_FSCI2CBusTable[((index) / 8)])
#define HYVEPLATFORM_FSC_MONITOR_I2C_ADDR(index)		(g_FSCI2CAddrTable[((index) / 8)])
#define HYVEPLATFORM_FSC_PWM_INDEX(index)  				(g_pwmIndexTable[((index) % 4)])
#define HYVEPLATFORM_FSC_TACH_INDEX(index)				(g_tachIndexTable[((index) % 8)])

#define HYVEPLATFORM_FSC_INIT							HyvePlatform_FSC_Init
#define HYVEPLATFORM_FANCTRL_NCT_INIT					HyvePlatformFan_NCT7362Y_Init
#define HYVEPLATFORM_FAN_PRESENT_DETECT					HyvePlatformFan_PresentDetect
#define HYVEPLATFORM_FSC_GET_CONFIGBANKID				HyvePlatform_FSC_GetConfigBankID

#endif
