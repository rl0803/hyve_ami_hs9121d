 /******************************************************************
 *
 * @file	HyvePlatformSensorMonitor.h
 * @brief	The Hyve platform sensor monitor header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMSENSORMONITOR_H_
#define HYVEPLATFORMSENSORMONITOR_H_


extern int HyveMonitor_GetReadingValBySensorNum(const INT8U sensorNum, const INT8U sensorLUN, hal_t* phal);
extern void* HyvePlatform_SensorMonitor(void* pArg);
extern INT8U HyvePlatform_has_DIMMOwership();
extern INT8U HyvePlatform_Is_CPU_PwrGood();
extern INT8U HyvePlatform_Is_HostInS3();
extern INT8U HyvePlatform_Is_HostInS5();

#endif
