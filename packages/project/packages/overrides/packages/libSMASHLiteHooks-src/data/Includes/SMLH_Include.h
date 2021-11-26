#ifndef __SMLH_INCLUDE_H__
#define __SMLH_INCLUDE_H__

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "libipmi_struct.h"
#include "coreTypes.h" 

#define SMH_LIB_PATH "/usr/local/lib/libSMASHLiteHooks.so"

#define SMLH_ARR_LEN_8   8
#define SMLH_ARR_LEN_32   32
#define SMLH_ARR_LEN_64   64
#define SMLH_ARR_LEN_128  128
#define SMLH_ARR_LEN_100  100
#define SMLH_ARR_LEN_256 256
#define PROP_SIZE_320K 327680
#define FAN_SENSOR 0x04

#define SMH_SUCCESS 0
#define SMH_FAILURE 1

// Property structure declarations
//Admin
typedef struct{
	char Name[20];
	char GUID[SMLH_ARR_LEN_32+1];
}ADMIN_PROP;
typedef struct{
	char Name[20];
}SP_PROP;
//System
typedef struct {
	char Location[SMLH_ARR_LEN_32];
	char Manufacturer[SMLH_ARR_LEN_32];
	char PartNumber[SMLH_ARR_LEN_32];
	char SN[SMLH_ARR_LEN_32];
	char Firmware[SMLH_ARR_LEN_32];
	char Health[10];
	char HostName[SMLH_ARR_LEN_64];
	char OperatorPassword[SMLH_ARR_LEN_32];
	char AdminPassword[SMLH_ARR_LEN_32];
	char IPMode[SMLH_ARR_LEN_32];
	char IP[SMLH_ARR_LEN_32];
	char NetMask[SMLH_ARR_LEN_32];
	char GateWay[SMLH_ARR_LEN_32];
	unsigned int NodePowerGap;
	char Time[SMLH_ARR_LEN_32];
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_CORE	
	char Summary[SMLH_ARR_LEN_64];
#endif
	char SnmpTrapEnable[SMLH_ARR_LEN_32];
	char SnmpTrapServerIP[SMLH_ARR_LEN_64];
	char SnmpTrapCommunity[SMLH_ARR_LEN_32];
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char ProductName[SMLH_ARR_LEN_32];
	char MAC[SMLH_ARR_LEN_32];
	unsigned char EnTemp;
	char NTPEnable[SMLH_ARR_LEN_32];
	char NTPServerIP[SMLH_ARR_LEN_128];
	char SyslogEnable[SMLH_ARR_LEN_32];
	char SyslogServerIP[SMLH_ARR_LEN_64];
	unsigned int SyslogUDPPort;
	unsigned int SnmpTrapPort;
#endif	
} SYSTEM_PROP;

typedef struct {
	char SnmpTrapEnable[SMLH_ARR_LEN_32];
	char SnmpTrapServerIP[SMLH_ARR_LEN_64];
	char SnmpTrapCommunity[SMLH_ARR_LEN_32];
	unsigned int SnmpTrapPort;
} SNMP_PROP;

//Power
typedef struct {
	char Firmware[SMLH_ARR_LEN_32];
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char Status[SMLH_ARR_LEN_32];
	char Health[SMLH_ARR_LEN_32];
#else
	unsigned char Status;
	unsigned char Health;
#endif
	unsigned int PSUAmount;
	unsigned long MaxPower;
	unsigned long Input;
	unsigned long Output;
	unsigned long Efficiency;
	unsigned long PhaseAVoltage;
	unsigned long PhaseACurrent;
	unsigned long PhaseBVoltage;
	unsigned long PhaseBCurrent;
	unsigned long PhaseCVoltage;
	unsigned long PhaseCCurrent;
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char PSUControlMode[SMLH_ARR_LEN_32];
#endif
} POWER_PROP;

//PSU
typedef struct {
	char Manufacturer[SMLH_ARR_LEN_32];
	char SN[SMLH_ARR_LEN_32];
	unsigned char ID;
	char Firmware[SMLH_ARR_LEN_32];
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char Status[SMLH_ARR_LEN_32];
	char Health[SMLH_ARR_LEN_32];
#else	
	unsigned char Status;
	unsigned char Health;
#endif
	unsigned long AC_InputVoltage;
	unsigned long AC_InputCurrent;
	unsigned long OutputVoltage;
	unsigned long OutputCurrent;
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	unsigned long DC_InputVoltage;
	unsigned long DC_InputCurrent;
	int Temp;
#endif
} PSU_PROP;

//Cooling
typedef struct {
	char Firmware[SMLH_ARR_LEN_32];
	unsigned int ID;
	char Health[10];
	unsigned int Power;
	unsigned int ExTemp;
	char FanControlMode[SMLH_ARR_LEN_32];
	unsigned int Duty;
} COOLING_PROP;

//Fan
typedef struct {
	unsigned int ID;
	char Health[10];
	unsigned long Speed;
} FAN_PROP;

//Chassis
typedef struct {
	unsigned int ChassisID;
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char BackplaneStatus[SMLH_ARR_LEN_32];
#else
	unsigned int BackplaneStatus;
#endif
} CHASSIS_PROP;

//Node
typedef struct {
	char ID[SMLH_ARR_LEN_32];
	char SN[SMLH_ARR_LEN_32];
	char Status[SMLH_ARR_LEN_32];
	char Health[SMLH_ARR_LEN_32];
	unsigned int Power;
	char MAC1[SMLH_ARR_LEN_32];
	char MAC2[SMLH_ARR_LEN_32];
	char Ethernet[SMLH_ARR_LEN_32];
	char IPMode[SMLH_ARR_LEN_32];
	char IP[SMLH_ARR_LEN_32];
	char Netmask[SMLH_ARR_LEN_32];
	char Gateway[SMLH_ARR_LEN_32];
	unsigned int EnTemp;
	unsigned int ExTemp;
	char CPU[SMLH_ARR_LEN_32];
	char MemoryCapacity[SMLH_ARR_LEN_32];
	char DiskCapacity[SMLH_ARR_LEN_32];
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	char ProductName[SMLH_ARR_LEN_32];
	char BMCReset[10];
	unsigned int CPUAmount;
	unsigned int MemoryAmount;
	unsigned int DiskAmount;
#endif
} NODE_PROP;

//logs
typedef struct {
	unsigned int LogAmount;
	unsigned int LogRecordCycle;
	char Log[PROP_SIZE_320K];
} LOGS_PROP;

//Accounts
typedef struct {
	char username[SMLH_ARR_LEN_32];
	unsigned int status;
	unsigned char permission;
} ACCOUNTS_PROP;

//rmcupgrade
typedef struct {
	char Path[SMLH_ARR_LEN_64];
	char Image[SMLH_ARR_LEN_256];
} RMCUPGRADE_PROP;

//rfcbupgrade
typedef struct {
	char Path[SMLH_ARR_LEN_64];
	char Image[SMLH_ARR_LEN_256];
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	int FcbTarget;
#endif
} RFCBUPGRADE_PROP;


typedef struct phy_device_info {
	uint16  recID;
	uint8   EntityID;
	uint8   EntityIns;
	struct	phy_device_info * next;
} phyDevInfo;

typedef struct logical_device_info {
	uint16  recID;
	uint8   EntityID;
	uint8   EntityIns;
	int	AssociatedDeviceCount;
	phyDevInfo *AssociatedDevices;
} logicalDevInfo;

// 
// declaring the void function pointer
typedef void (*func_ptr) (void );

// enum for hook functions
enum g_SMHookFunctions {
GET_CHASSIS_COUNT = 0,
GET_ONE_CHASSIS_INFO,
GET_NXT_NODE,
GET_COOLING_TARGET,
GET_POWER_TARGET,
FILL_CHASSIS_PROP,
FILL_NODE_PROP,
FILL_SYS_PROP,
FILL_PWR_PROP,
FILL_PSU_PROP,
FILL_COLLING_PROP,
FILL_FAN_PROP,
FILL_LOGS_PROP,
FILL_ACCT_PROP,
FILL_RMC_PROP,
FILL_RFCB_PROP,
FILL_ADMIN_PROP,
FILL_SP_PROP,
FILL_SNMP_PROP,
//Add additional function numbers here
MAX_FUNC_NUMBER
};

typedef struct{
	int funcNum;
	char funcName[SMLH_ARR_LEN_256];
}sm_func_table;

extern func_ptr g_funcHandle[MAX_FUNC_NUMBER];

extern void *dl_SMhandle;

extern int init_smFuncTable();
extern int uninit_smFuncTable();


#endif
