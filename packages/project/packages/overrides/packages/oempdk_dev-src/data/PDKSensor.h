
/*****************************************************************
 *****************************************************************
 ***                                                            **
 ***    (C)Copyright 2010-2011, American Megatrends Inc.        **
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
 * PDKsensor.h
 * sensor hook functions.
 *
 *  Author:Pavithra S (pavithras@amiindia.co.in)
 *
 ******************************************************************/
#ifndef PDK_SENSOR_H
#define PDK_SENSOR_H

#include "SharedMem.h"
#include "SensorAPI.h"

#define		FAULTROLLUP_LEDNO		0
#define 	HOST_STATUS_LEDNO		3
#define 	POWERON_LENNO			2
#define 	CHASSIC_LEDNO			4

typedef struct  
{
    INT16U                      SensorNum;         /* SensorNumber for which the pre-monitor and post-monitor 
													  hook is to be replaced by default hook defined in Init_Sensor.
													*/
	pPDK_MonitorHook_T			pPreMonitor;		/* Pre monitor hook   */
	pPDK_MonitorHook_T			pPostMonitor;		/* Post Monitor hook */
	
}SensorHooks_T;

/** The below defined sensor numbers are for testing purpose.
  *   For the below sensors the default pre-monitor and post-monitor hooks
  *   are replaced by the hooks defined in PDK_RegisterSensorHooks
  */
#define SENSOR_NUMBER_1 0x01
#define SENSOR_NUMBER_2 0x02
#define SENSOR_NUMBER_3 0x03

/***
*@brief The pre -monitor hook function for first sensor.
*@	The default pre-monitor hook function is overridden by this for the first sensor.
*@[in]pSensorInfo - The SensorInfo structure
*@[in]pReadFlags - Flags to be used if any as in internal_sensor
*@[in]BMCInst  - The particular BMCInst
**/
int PDK_PreMonitorSensor_1 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);

/***
*@brief The pre -monitor hook function for second sensor.
*@	The default pre-monitor hook function is overridden by this for the second sensor.
*@[in]pSensorInfo - The SensorInfo structure
*@[in]pReadFlags - Flags to be used if any as in internal_sensor
*@[in]BMCInst  - The particular BMCInst
**/
int PDK_PreMonitorSensor_2 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);

/***
*@brief The pre -monitor hook function for third sensor.
*@	The default pre-monitor hook function is overridden by this for the third sensor.
*@[in]pSensorInfo - The SensorInfo structure
*@[in]pReadFlags - Flags to be used if any as in internal_sensor
*@[in]BMCInst  - The particular BMCInst
**/
int PDK_PreMonitorSensor_3 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);

/***
*@brief The post -monitor hook function for first sensor.
*@	The default post-monitor hook function is overridden by this for the first sensor.
*@[in]pSensorInfo - The SensorInfo structure
*@[in]pReadFlags - Flags to be used if any as in internal_sensor
*@[in]BMCInst  - The particular BMCInst
**/
int PDK_PostMonitorSensor_1 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
/***
*@brief The post -monitor hook function for second sensor.
*@	The default post-monitor hook function is overridden by this for the second sensor.
*@[in]pSensorInfo - The SensorInfo structure
*@[in]pReadFlags - Flags to be used if any as in internal_sensor
*@[in]BMCInst  - The particular BMCInst
**/
int PDK_PostMonitorSensor_2 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);

/***
*@brief The post -monitor hook function for third sensor.
*@	The default post-monitor hook function is overridden by this for the third sensor.
*@[in]pSensorInfo - The SensorInfo structure
*@[in]pReadFlags - Flags to be used if any as in internal_sensor
*@[in]BMCInst  - The particular BMCInst
**/
int PDK_PostMonitorSensor_3 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);


/***
* PDK_RegisterSensorHooks
*@brief Pre-Monitor and Post Monitor Sensor Hooks are initialized in this function
*@[in]BMCInst  - The particular BMCInst
**/

int PDK_RegisterSensorHooks(int BMCInst);

/***
* PDK_BeforeValidSensorList
*@brief hook to handle oem actions before building the valid sensor list
*@[in]pseninfo - pointer to the sensor info structure of that particular sensor
*@index - index to the sensor in the sensor info structure
*@bmcinst - the particular bmc instance
*@return - 1 to skip adding the sensor to the valid sensor list
	 - 0 - to proceed further in adding the sensor to the valid sensor list
**/
int PDK_BeforeValidSensorList(void *pSenInfo, int Index, int BMCInst);

/***
* PDK_OverrideDefaultValues
*@brief hook to handle oem actions before building the valid sensor list
*@[in]pseninfo - pointer to the sensor info structure of that particular sensor
*@index - index to the sensor in the sensor info structure
*@bmcinst - the particular bmc instance
*@return - 1 to skip adding the sensor to the valid sensor list
	 - 0 - to proceed further in adding the sensor to the valid sensor list
**/
int PDK_OverrideDefaultValues(void *pSDRRec, void *pSenInfo, int BMCInst);

/***
* PDK_OverrideCheckEntityPresence
*@brief hook to handle oem actions for Checking the Entity Presence
*@[in]SensorNum = Sensor Number of the sensor
*@[in]OwnerLUN = LUN to which this sensor belongs to
*@[in]EventTypeCode = The code to indicate the type of the Event
*@[in]SensorType = Code to indicate the type of sensor this refers to
*@BMCInst - the particular bmc instance
*@return - 0 to proceed with the core functionality
	 - -1 to override the default core behavior and 
		- This in turn returns NOT_FOUND_SCANNING_ENABLED to the caller function
**/
int PDK_OverrideCheckEntityPresence(INT8U SensorNum, INT8U OwnerLUN, INT8U EventTypeCode, INT8U SensorType, int BMCInst);

#if defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER8) || defined(CONFIG_SPX_FEATURE_GLOBAL_ARCH_POWER9)

#define     FAULTROLLUP_LEDNO       0
#define     HOST_STATUS_LEDNO       3
#define     POWERON_LENNO           2
#define     CHASSIC_LEDNO           4

typedef enum 
{
	FAULTLED_OFF  = 0,
	FAULTLED_ON = 1,
	FAULTLED_BLINK  = 2
} LEDmode;

typedef struct  
{
    char                        SensorName[64];     /* SensorName for getting the corresponding sensor number*/
    pPDK_MonitorHook_T          pPreMonitor;        /* Pre monitor hook   */
    pPDK_MonitorHook_T          pPostMonitor;       /* Post Monitor hook */
    
}OPP8SensorHooks_T;

typedef struct 
{
	char		SensorName[64];
	INT8U       LUN;
	INT8U		OpCode;
	INT16U		EventData;
	INT16U		ActionFlag;
	INT16U		RecoveryActionFlag;
} OemSensorHook_T;

typedef struct
{
    INT32U  offset;
    char    SensorName[64];
    INT16U  SensorReading;
    INT16U  PreviousState;
}PACKED VirtualSensorInfo;

// File to preserve the internal sensors readings. 
#define VIRTUAL_SENSOR_FILE(Instance,filename) \
	sprintf(filename,"%s%d/%s",NV_DIR_PATH,Instance,"Sensor.dat")

#define EXT_VIRTUAL_SENSOR_FILE(Instance,filename) \
	sprintf(filename,"%s%d/%s",NV_EXLOG_DIR_PATH,Instance,"Sensor.dat")

//Oem OpCode 
#define 	SENSOR_ERR		    0x01
#define 	SENSOR_DATA		    0x02
#define 	SENSOR_THRESHOLD	0x03
#define 	SENSOR_DATA_MASK	0x04
#define	SENSOR_DATA_MULTIPLE_MAP	0x08

/* Oem BIT Map */
#define		TURN_ON_FAULT_LED			0x0001
#define 	POWER_ON_HOST		    	0x0002
#define 	POWER_OFF_HOST		    	0x0004
#define		SET_NW_LINK_UP				0x0008
#define 	TURN_ON_IDENTIFY_LED    	0x0010
#define	    BOOT_CRONUS_MODE        	0x0020
#define     BLINK_FAULT_LED         	0x0040
#define     SET_XXX_SENSOR_READING  	0x0080
#define 	TURN_OFF_HOSTSTATUS_LED		0x0100
#define 	TURN_ON_HOSTSTATUS_LED		0x0200
#define		BLINK_HOSTSTATUS_LED		0x0400
#define		FW_BOOT_PROGRESS			0x0800
#define     HOST_POWER_RESET            0x1000
#define     DEFERABLE_HOST_RESET		0x2000
#define 	TURN_OFF_FAULT_LED			0x4000
#define     SET_GPU_POWER_LIMIT         0x8000

/* OEM Event ....... */
#define 	FLT_ROLLUP		    		0x00
#define     CROSS_ANY_THRESH    		0xFF
#define     CROSS_LNC_THRESH    		0x01
#define     CROSS_LC_THRESH     		0x02
#define     CROSS_LNR_THRESH    		0x04
#define     CROSS_UNC_THRESH    		0x08
#define     CROSS_UC_THRESH     		0x10
#define     CROSS_UNR_THRESH    		0x20
#define		FW_BOOT_INCREMENT			0x40
#define 	FLT_ROLLUP_DIMM_FUNC		0x50
#define 	FLT_ROLLUP_CPU_CORE_FUNC	0x0180
#define  	FLT_ROLLUP_CENT_FUNC		0x50

extern char  *SensorMapIndex[];

//POWER8: Oem Actions needs to be implemented
int OemFaultLEDOn(int BMCInst);
int OemPowerOnHost(int BMCInst);

/* POWER8 : PostMonitor Task for all physical Sensors.... */
int PDK_PostMonitorCPUDiode(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorQuickPowerDrop(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorChassisInt(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorPGood(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorFWBootProgress(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorCPUVDDV(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorCPUVDDCur(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorBootCount(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorCheckStop(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorAmbientTemp(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorBoardTemp(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorWatchdog(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorHostStatus(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorOCCActive(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorPCI(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorOSBoot(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorPSDerating(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorBackPlaneFlt(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorSystemEvent(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorActivatePwrLmt(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorRefClk(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorPciclk(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorTodClk(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorAPSSFlt(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorPSUFault(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorGPU(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorDIMMFunc(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorCPUCoreFunc(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorMEMBufFunc(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorCPUFunc(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PostMonitorBIOSGolden(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);

extern int PDK_OemTakeAction(void *pSenInfo, unsigned short actionbitmap, int BMCInst);

#endif
#endif
