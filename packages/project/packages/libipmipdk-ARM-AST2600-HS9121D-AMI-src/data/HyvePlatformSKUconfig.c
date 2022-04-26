 /******************************************************************
 *
 * @file	HyvePlatformSKUconfig.c
 * @brief	Provide the platform SKU config related functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"

#include "HyveCommon.h"



typedef struct HyvePlatform_SKU_sensors {
	INT8U 			is_supported;
	Hyve_Sensor_T 	sensors[MAX_SKU_SENSOR_LIST_COUNT];
} HyvePlatform_SKU_sensors_T;



static INT8U *g_sensor_del_list = NULL;
INT8U g_is_FP_supported = 0;
INT8U g_is_BP_supported = 0;



void HyvePlatform_InitSKUFeature()
{
	switch (HYVEPLATFORM_SKU) {
	case PLATFORM_SKU_DEFAULT:
	case PLATFORM_SKU_HS9121D:
		g_is_FP_supported = 1;
		g_is_BP_supported = 1;
		break;

	default:
		break;
	}
}

const INT8U *HyvePlatform_GetSensorDelList()
{
	if (!g_sensor_del_list) {
		g_sensor_del_list = malloc(MAX_SKU_SENSOR_DEL_LIST_COUNT);
		if (g_sensor_del_list)
			memset(g_sensor_del_list, 0, MAX_SKU_SENSOR_DEL_LIST_COUNT);
	}
	return g_sensor_del_list;
}

const INT8U *HyvePlatform_CreateSensorDelList()
{
	INT8U *sensor_del_list = (INT8U *)HyvePlatform_GetSensorDelList();

	if (sensor_del_list) {
		DECL_SKU_SENSOR_LIST(skuSensorList);
		INT8U index_list = 0;

		for (index_list = 0; index_list < HYVE_ARRAYSIZE(skuSensorList); index_list++) {
			if (!skuSensorList[index_list].is_supported) {
				INT8U index = 0;
				INT8U sensorCount = 0;
				
				printf("Remove sensor: ");
				for (index = 0; skuSensorList[index_list].sensors[index].sensorNum != END_SKU_SENSOR_LIST; index++) {
					// currently BMC only uses LUN01, so just need to consider sensorNum 0 ~ 255
//					INT16U index_map = HYVE_LUN_NUM(skuSensorList[index_list].sensors[index].senorLUN,
//													skuSensorList[index_list].sensors[index].sensorNum);
					INT16U index_map = skuSensorList[index_list].sensors[index].sensorNum;
					
					g_sensor_del_list[index_map] = 1;
					printf("0x%x ", index_map); sensorCount++;
				}
				printf("\nRemove sensor count %u\n", sensorCount);
			}
		}
	}
	return sensor_del_list;
}

void HyvePlatform_DestroySensorDelList()
{
	if (g_sensor_del_list) {
		free(g_sensor_del_list);
		g_sensor_del_list = NULL;
	}
}
