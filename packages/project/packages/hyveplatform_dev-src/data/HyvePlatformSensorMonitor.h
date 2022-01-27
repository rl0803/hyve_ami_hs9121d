 /******************************************************************
 *
 * @file	HyvePlatformSensorMonitor.h
 * @brief	The Hyve platform sensor monitor header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMSENSORMONITOR_H_
#define HYVEPLATFORMSENSORMONITOR_H_


/********************* Type definitions *********************/
typedef int (*HyveTMP4xxfunc) (const INT8U, const INT8U, const INT8U, int*);

typedef struct {
	INT8U sensorIndex;
	INT8U enable;
	INT8U is_standby;
	INT8U i2cBus;
	INT8U i2cAddr;
} HyvePlatformTMP75Sensor_T;

typedef struct {
	INT8U sensorIndex;
	INT8U enable;
	INT8U is_standby;
	INT8U i2cBus;
	INT8U i2cAddr;
	HyveTMP4xxfunc read;
} HyvePlatformTMP4xxSensor_T;

typedef enum {
	SensorIndex_3V3Bat = 0,
	SensorIndex_TEMP_MB_1,
	SensorIndex_TEMP_MB_2,
	SensorIndex_TEMP_MB_3_0,
	SensorIndex_TEMP_MB_3_1,
	SensorIndex_TEMP_MB_3_2,
	SensorIndex_TEMP_MB_3_3,
	SensorIndex_TEMP_MB_3_4,
	SensorIndex_TEMP_MB_3_5,
	SensorIndex_TEMP_MB_3_6,
	SensorIndex_TEMP_MB_3_7,
	SensorIndex_TEMP_MB_3_8,
	SensorIndex_TEMP_CPU0,
	SensorIndex_PWR_CPU0,
	SensorIndex_TEMP_DIMMA0,
	SensorIndex_TEMP_DIMMB0,
	SensorIndex_TEMP_DIMMC0,
	SensorIndex_TEMP_DIMMD0,	
	SensorIndex_TEMP_DIMME0,
	SensorIndex_TEMP_DIMMF0,
	SensorIndex_TEMP_DIMMG0,
	SensorIndex_TEMP_DIMMH0,		
	SensorIndex_TEMP_DIMMI0,
	SensorIndex_TEMP_DIMMJ0,
	SensorIndex_TEMP_DIMMK0,
	SensorIndex_TEMP_DIMML0,
	SensorIndex_TEMP_P0SOCVR0,
	SensorIndex_TTEMP_P0V11VR0,
	SensorIndex_TEMP_P0IOVR0,
	SensorIndex_PWR_P0SOCVR0POUT,
	SensorIndex_PWR_P0V11VR0POUT,
	SensorIndex_PWR_P0IOVR0POUT,
	SensorIndex_TEMP_FAN_BOARD,
	SensorIndex_TEMP_FP,
	SensorIndex_TEMP_MP,
	SensorReadArrtIndex_MAX
} HyvePlatformSensorReadArrtIndex;



/********************* Functions *********************/
extern HyvePlatformTMP75Sensor_T* HyvePlatform_Get_ExtBoardTMP75Sensors(INT8U* pCount);
extern int HyveMonitor_GetReadingValBySensorNum(const INT8U sensorNum, const INT8U sensorLUN, hal_t* phal);
extern void* HyvePlatform_SensorMonitor(void* pArg);
extern void* HyvePlatform_SensorMonitor2(void* pArg);
extern INT8U HyvePlatform_has_DIMMOwership();
extern INT8U HyvePlatform_Is_CPU_PwrGood();
extern INT8U HyvePlatform_Is_HostInS3();
extern INT8U HyvePlatform_Is_HostInS5();

#endif
