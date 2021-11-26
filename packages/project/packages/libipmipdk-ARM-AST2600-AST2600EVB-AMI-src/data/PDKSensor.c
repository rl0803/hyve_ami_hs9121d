/****************************************************************
 ****************************************************************
 **                                                            **
 **    (C)Copyright 2006-2020, American Megatrends Inc.        **
 **                                                            **
 **            All Rights Reserved.                            **
 **                                                            **
 **        5555 Oakbrook Parkway, Norcross,                    **
 **                                                            **
 **        Georgia - 30093, USA. Phone-(770)-246-8600.         **
 **                                                            **
 ****************************************************************
 ****************************************************************
 *
 * pdksensor.c
 * Hooks that are invoked at different points sensor monitoring
 *
 *  Author:Pavithra S (pavithras@amiindia.co.in)
 ******************************************************************/


#include "PDKSensor.h"
#include "IPMIConf.h"


static SensorHooks_T pdk_sensor_hooks []=
	{
		{SENSOR_NUMBER_1, PDK_PreMonitorSensor_1,PDK_PostMonitorSensor_1},
		{SENSOR_NUMBER_2, PDK_PreMonitorSensor_2,PDK_PostMonitorSensor_2},
		{SENSOR_NUMBER_3, PDK_PreMonitorSensor_3,PDK_PostMonitorSensor_3},
	};

int 
PDK_RegisterSensorHooks(int BMCInst)
{
	_FAR_ SensorSharedMem_T*	pSMSharedMem; 
	_FAR_ SensorInfo_T* 		pSensorInfo;
	_FAR_ BMCInfo_t* pBMCInfo = &g_BMCInfo[BMCInst];
	unsigned int i=0;
	
	//pSMSharedMem = (_FAR_ SensorSharedMem_T*)&g_SensorSharedMem;
	pSMSharedMem = (_FAR_ SensorSharedMem_T*)&pBMCInfo->SensorSharedMem;
	if(pSMSharedMem == NULL)
	{
		IPMI_WARNING("Sensor shared mem is null!!\n");
		return -1;
	}
	
	for (i=0; i<sizeof(pdk_sensor_hooks)/sizeof(pdk_sensor_hooks[0]); i++)
	{
		
		pSensorInfo  = (SensorInfo_T*)&pSMSharedMem->SensorInfo[pdk_sensor_hooks[i].SensorNum];
		if (pSensorInfo == NULL ) {  return -1; }
		if(pdk_sensor_hooks[i].pPreMonitor != NULL)
		{
			pSensorInfo->pPreMonitor  = pdk_sensor_hooks[i].pPreMonitor;
		}
		if(pdk_sensor_hooks[i].pPostMonitor != NULL)
		{
			pSensorInfo->pPostMonitor = pdk_sensor_hooks[i].pPostMonitor;
		}
	}
	return 0;
}

/*---------------------------------------------------------------------------
 * @fn PDK_PreMonitorSensor
 *
 * @brief This function is invoked before a sensor is monitored. This
 * function can be used in place of the default sensor monitoring code.
 * This function should return 0 if the default sensor monitoring needs
 * to be run, -1 otherwise.
 *
 * @param	SensorNum		- The sensor number that is being monitored.
 * @param	pSensorReading  - Pointer to the buffer to hold the sensor reading.
 * @param	pReadFlags  	- Pointer to the flag holding the read status.
 *
 * @return  0	- if default sensor monitoring needs to run.
 *			-1	- otherwise
 *---------------------------------------------------------------------------*/
int
PDK_PreMonitorSensor_1 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst)
{
	//SensorInfo_T*  		pSensorInfo = pSenInfo;
	//printf("!!!!!---entering the pre monitor sensor1 for sen[%x]\n",pSensorInfo->SensorNumber);
	if(0)
	{
	    pSenInfo=pSenInfo;  /*  -Wextra, fix for unused parameters  */
	    pReadFlags=pReadFlags;
	    BMCInst=BMCInst;
	}
	return 0;
}

int
PDK_PreMonitorSensor_2 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst)
{
	//SensorInfo_T*  		pSensorInfo = pSenInfo;
	//printf("---entering the pre monitor sensor 2 for sen[%x]---\n",pSensorInfo->SensorNumber);
        if(0)
        {
            pSenInfo=pSenInfo;  /*  -Wextra, fix for unused parameters  */
            pReadFlags=pReadFlags;
            BMCInst=BMCInst;
        }
	return 0;
}

int
PDK_PreMonitorSensor_3 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst)
{
    //SensorInfo_T*  		pSensorInfo = pSenInfo;
	//printf("---entering the pre monitor sensor 3  for sen[%x]---\n",pSensorInfo->SensorNumber);
        if(0)
        {
            pSenInfo=pSenInfo;  /*  -Wextra, fix for unused parameters  */
            pReadFlags=pReadFlags;
            BMCInst=BMCInst;
        }
	return 0;
}

/*---------------------------------------------------------------------------
 * @fn PDK_PostMonitorSensor
 *
 * @brief This function is invoked immediately after the sensor monitoring
 * code is run. This function can be used to override the values returned,
 * or perform certain actions based on the sensor reading etc. This function
 * should return 0 if this sensor reading needs to be considered for this
 * cycle, -1 otherwise.
 *
 * @param	SensorNum		- The sensor number that is being monitored.
 * @param	pSensorReading	- Pointer to the buffer to hold the sensor reading.
 * @param	pReadFlags		- Pointer to the flag holding the read status.
 *
 * @return	0	- if sensor reading is to be considered for this cycle.
 *			-1	- otherwise
 *---------------------------------------------------------------------------*/
int
PDK_PostMonitorSensor_1 ( void*  pSenInfo,INT8U *pReadFlags,int BMCInst)
{
    //SensorInfo_T*  		pSensorInfo = pSenInfo;
	//printf("!!!!!---entering the POST monitor sensor1 for sen[%x]\n",pSensorInfo->SensorNumber);
        if(0)
        {
            pSenInfo=pSenInfo;  /*  -Wextra, fix for unused parameters  */
            pReadFlags=pReadFlags;
            BMCInst=BMCInst;
        }
	return 0;
}

int
PDK_PostMonitorSensor_2 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst)
{
	//SensorInfo_T*		   pSensorInfo = pSenInfo;
	//printf("!!!!!---entering the POST monitor sensor1 for sen[%x]\n",pSensorInfo->SensorNumber);
        if(0)
        {
            pSenInfo=pSenInfo;  /*  -Wextra, fix for unused parameters  */
            pReadFlags=pReadFlags;
            BMCInst=BMCInst;
        }
	return 0;
}
int
PDK_PostMonitorSensor_3 (void*  pSenInfo,INT8U *pReadFlags,int BMCInst)
{
	//SensorInfo_T*		   pSensorInfo = pSenInfo;
	//printf("!!!!!---entering the POST monitor sensor1 for sen[%x]\n",pSensorInfo->SensorNumber);
        if(0)
        {
            pSenInfo=pSenInfo;  /*  -Wextra, fix for unused parameters  */
            pReadFlags=pReadFlags;
            BMCInst=BMCInst;
        }
	return 0;
}
	


