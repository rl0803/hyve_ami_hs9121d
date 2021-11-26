 /******************************************************************
 *
 * @file	HyvePlatform.c
 * @brief	Provide the platform functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "IPMI_App.h"
#include "hal_hw.h"
#include "API.h"
#include "PendTask.h"
#include "safesystem.h"
#include "OSPort.h"

#include "HyveCommon.h"


/********************* Global variable definitions *********************/
int gHyvePlatformSkuID = PLATFORM_DEFAULT;
/* The platform global time-tick per second */
UINT32 g_HyvePlatformJiffy = 0;
INT8U g_IsBMC_ACPowerOn = TRUE; // Alan debug, //FALSE;
INT8U g_Is_DCPowerOn = FALSE; // Alan debug, //FALSE;


/********************* Functions *********************/
static void HyvePlatform_InitSKUID(const char* idStr)
{
	INT8U i = 0;
    HyvePlatformID_T platformIDTable[] = { PLARFORMID_TABLE };

	for (i = 0; i < HYVE_ARRAYSIZE(platformIDTable); i++) {
		if (!strcmp(idStr, platformIDTable[i].platformID)) {
            gHyvePlatformSkuID = platformIDTable[i].skuID;
        }
	}
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_InitPlatformID
 * @brief	To initiate platform ID and SKU ID
 *
 * @param[in]	BMCInst
 *
 * @return  none
 *-----------------------------------------------------------------*/
static void HyvePlatform_InitPlatformID(int BMCInst)
{
	char tmpPlatformID[MAX_PLATFORMID_SIZE] = {0};
	int ret = 0;

	if (0) { BMCInst = BMCInst; }

	/* Get the default built-in platform ID string */
	ret = HyveExt_GetDefaultPlatformID(tmpPlatformID, sizeof(tmpPlatformID));

	/* Search the platform keyword, check if it needs to identify the SKU with
	   1. FRU info
	   2. GPIO pin
	   etc...
	*/
#if 0 // Example code
	if (strstr(tmpPlatformID, "CF") {
		// Get MB FRU Product Name
		char *productName = NULL;
		HyveFRU_AreaData_T productArea = {0};

		if (HyveFRU_GetInfoAreaData(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_CACHE, ProductInfoAreaOffset, &productArea) < 0) {
			printf("%s Unable to get FRU Product Info Area data from cache\n", __func__);
			if (HyveFRU_GetInfoAreaData(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_EEPROM, ProductInfoAreaOffset, &productArea) < 0) {
				printf("%s Unable to get FRU Product Info Area data from EEPROM\n", __func__);
			}
		}
		if (productArea.areaData) {
			INT32U offset = PRODUCT_OFFSET_PRODUCT_NAME(productArea.areaData);
			productName = HyveFRU_GetInfoAreaString(&productArea.areaData[offset]);
			free(productArea.areaData);
		}
	
		// Recognize the platform with Product Name
		if (productName) {
			if (strstr(productName, "CORE-NVME") {
				snprintf(tmpPlatformID, sizeof(tmpPlatformID), "%s", PLATFORMID_HS9121D_CF_1U10);
			}
			free(productName);
		}
	}
#endif

	// Overwrite the PlatformID
	if (1 || !ret) { snprintf(PlatformID, sizeof(PlatformID), "%s", PLATFORMID_HS9121D); }
	HyvePlatform_InitSKUID(PlatformID);
	printf("    [INFO]     ====== Platform: %s    SKU ID: %d ======\n", PlatformID, HYVEPLATFORM_SKU);
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_Init
 * @brief	To do platform specific init procedure,
 * 			this function is supposed to be called in the PDK_PlatformInit() function
 *
 * @param[in]	BMCInst
 *
 * @return  0	- if success
 *			-1	- otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_Init()
{
	int BMCInst = 1;

	printf("[INFO] - Run %s\n", __func__);

	// Create the MB FRU Cache
	if (HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_CACHE) < 0) {
		printf("[INFO] Error in creating MB FRU cache\n");
	}
	// Recognize this platform
	HyvePlatform_InitPlatformID(BMCInst);

	HyveExt_MutexInit();

	// Check BMC AC lost
	if (1 == HyveExt_Is_BMC_ACLost()) {
		time_t timestamp = 0;
		if (HyveExt_GetLastTimeStamp((INT32U*)&timestamp) < 0) {
			printf("[INFO] Error in getting Last Time Stamp\n");
			// If fail getting the last time-stamp
			// then use the current time minus 120 seconds as the last time-stamp
			timestamp = time(NULL) - 120;
		}
		printf("[INFO] BMC AC lost detected, last time stamp: %s\n", ctime(&timestamp));
		// Record AC lost event
		HyveExt_LogEvent(timestamp, BMC_GEN_ID, BMC_SENSOR_LUN00, SENSOR_TYPE_POWERUNIT, SENSOR_NUM_PWRUNIT_STATUS,
				EVENT_TYPE_SENSOR_SPECIFIC_6F, EVENT_POWERUNIT_ACLOST, 0xFF, 0xFF, BMCInst);
		// Set the flag, for PDK_IsACPowerOn using
		g_IsBMC_ACPowerOn = TRUE;
	}




/*--------------Test Code--------------------*/	
	
	
	
//	if (HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, EVENT_TYPE_UNSPECIFIC, 0xBB, EVENT_TYPE_SENSOR_SPECIFIC_6F, 0xFF, 0xFF, 0xFF, BMCInst) < 0) {
//		printf("Error in HyveExt_LogEvent\n");
//	}
//	
//	INT8U pWriteBuff[] = {0x80}, readData[6] = {0};
//	if (HyveExt_I2C_Access_Retry(EEPROM_I2C_NUM, EEPROM_ADDR, pWriteBuff, 1, readData, 6, 3) < 0) {
//		printf("Error in HyveExt_I2C_Access_Retry\n");
//	} else {
//		printf("Get MAC: %x:%x:%x:%x:%x:%x\n", readData[0], readData[1], readData[2], readData[3], readData[4], readData[5]);
//	}

	
//	 HyveMonitor_GetReadingValBySensorNum(const INT8U sensorNum, const INT8U senLUN, hal_t* phal);
	
//	 hal_t *phal = malloc(sizeof(hal_t));
	 
//	UINT8 phal;
//	 
//	 if (!HyveMonitor_GetReadingValBySensorNum(SENSOR_NUM_TEST_LUN00, BMC_SENSOR_LUN00, &phal)) {
//		 printf("Get LUN: %02x, #%02x, %d\n", BMC_SENSOR_LUN00, SENSOR_NUM_TEST_LUN00, phal);
//	 }
//	 if (!HyveMonitor_GetReadingValBySensorNum(SENSOR_NUM_TEST_LUN00, BMC_SENSOR_LUN01, &hal)) {
//		 printf("Get LUN: %02x, #%02x, %d\n", BMC_SENSOR_LUN00, BMC_SENSOR_LUN01, *hal.pbyte);
//	 }	 
	


	INT8U offset = CONFIG_SPX_FEATURE_I2C_EEPROM_MACADDR_OFFSET, readData[6] = {0};
	if (HyveExt_ReadEEPROM(offset, readData, 6) < 0) {
		printf("Error in HyveExt_ReadEEPROM\n");
	} else {
		printf("Get MAC: %x:%x:%x:%x:%x:%x\n", readData[0], readData[1], readData[2], readData[3], readData[4], readData[5]);
	}

//	if (HyveExt_SetLastTimeStamp() < 0) {
//		printf("Error in HyveExt_SetLastTimeStamp\n");
//	}
	
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_TaskInit
 * @brief	To launch platform specific tasks,
 * 			this function is supposed to be called in the PDK_AfterCreatingTasks() function
 *
 * @param[in]	BMCInst
 *
 * @return  0	- if success
 *			-1	- otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_TaskInit(int BMCInst)
{
	if (0) {
		BMCInst = BMCInst;
	}
	
	printf("[ INFO ] - Run %s\n", __func__);
	
	HyvePlatform_GenericTaskStart();
	HyvePlatform_IRQDeferHandlerStart(BMCInst);
	HyvePlatform_FanCtrlTaskStart(BMCInst);
	HyvePlatform_PSUTaskStart(BMCInst);
	HyvePlatform_SensorMonitorStart(BMCInst);
	
	return 0;
}




