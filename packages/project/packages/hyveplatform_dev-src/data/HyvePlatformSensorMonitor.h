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


#endif
