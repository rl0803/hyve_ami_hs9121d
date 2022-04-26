 /******************************************************************
 *
 * @file	HyvePlatformSKUconfig.h
 * @brief	The Hyve platform SKU config header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMSKUCONFIG_H_
#define HYVEPLATFORMSKUCONFIG_H_


#define MAX_SKU_SENSOR_DEL_LIST_COUNT				(256)
#define MAX_SKU_SENSOR_LIST_COUNT					(32)
#define END_SKU_SENSOR_LIST							(0XFF)


#define HYVESENSOR_T(sensorNum, LUN)				{(sensorNum), (LUN) }
#define _SENSOR(sensorNum)							HYVESENSOR_T(sensorNum, BMC_SENSOR_LUN)
#define DECL_SENSORS(...)							{__VA_ARGS__}
#define DECL_SKU_SENSORS(flag, sensors)				{(flag), sensors}

extern void HyvePlatform_InitSKUFeature();
extern const INT8U *HyvePlatform_GetSensorDelList();
extern const INT8U *HyvePlatform_CreateSensorDelList();
extern void HyvePlatform_DestroySensorDelList();

extern INT8U g_is_FP_supported;
extern INT8U g_is_BP_supported;


/* Example
#define PLATFORM_FP_SENSORS		DECL_SENSORS(_SENSOR(0xA0), _SENSOR(0xA1), _SENSOR(0xA2), _SENSOR(END_SKU_SENSOR_LIST))
#define PLATFORM_BP_SENSORS		DECL_SENSORS(_SENSOR(0xB0), _SENSOR(0xB1), _SENSOR(END_SKU_SENSOR_LIST))

#define DECL_SKU_SENSOR_LIST HyvePlatform_SKU_sensors_T skuSensorList[] = \
	{ \
		DECL_SKU_SENSORS(g_is_FP_supported, PLATFORM_FP_SENSORS), \
		DECL_SKU_SENSORS(g_is_BP_supported, PLATFORM_BP_SENSORS), \
	}

*/
#define PLATFORM_TMP_UNSUPPORTED_SENSORS	DECL_SENSORS(_SENSOR(SENSOR_NUM_VAUX_P3V3), _SENSOR(END_SKU_SENSOR_LIST))

#define DECL_SKU_SENSOR_LIST(name) HyvePlatform_SKU_sensors_T name[] = \
	{ \
		DECL_SKU_SENSORS(0, PLATFORM_TMP_UNSUPPORTED_SENSORS), \
	}



#endif
