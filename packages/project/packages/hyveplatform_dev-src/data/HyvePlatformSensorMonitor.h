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
	INT8U channel;
	HyveTMP4xxfunc read;
} HyvePlatformTMP4xxSensor_T;

/********************* Functions *********************/
extern int HyveMonitor_GetReadingValBySensorNum(const INT8U sensorNum, const INT8U sensorLUN, hal_t* phal);
extern void* HyvePlatform_SensorMonitor(void* pArg);
extern void* HyvePlatform_SensorMonitor2(void* pArg);
extern INT8U HyvePlatform_has_DIMMOwership();
extern INT8U HyvePlatform_Is_CPU_PwrGood();
extern INT8U HyvePlatform_Is_HostInS3();
extern INT8U HyvePlatform_Is_HostInS5();
extern void HyvePlatform_Sensor_RstStatAfterPwrOff();

#endif
