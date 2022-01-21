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
INT8U g_Is_DCPowerOn = FALSE; // This variable can only be set by PDK_GetPSGood or IRQhndlr_PWRGD_SYS_PWROK


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
static void HyvePlatform_InitPlatformID()
{
	char tmpPlatformID[MAX_PLATFORMID_SIZE] = {0};
	int ret = 0;

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


static void HyvePlatform_InitChip()
{
	INT32U regValue = 0, i = 0;
	// Usually use the WDT1 ~ WDT3
	INT32U wdts[] = { REG_WDT1_BASE, REG_WDT2_BASE, REG_WDT3_BASE };

	// Disable HW Heart Beat LED
	regValue = HYVE_BIT(31);
	HyveExt_BMC_RegSCU(Hyve_RegOp_ClearBits, 0x69C, &regValue);

	// Disable WDT Reset GPIO controller 1 and 2
	for (i = 0; i < HYVE_ARRAYSIZE(wdts); i++) {
		regValue = HYVE_BIT(24);
		HyveExt_BMC_Register(Hyve_RegOp_ClearBits, (wdts[i] + REG_WDT_OFFSET_RESET_MASK1), &regValue);
		regValue = HYVE_BIT(9);
		HyveExt_BMC_Register(Hyve_RegOp_ClearBits, (wdts[i] + REG_WDT_OFFSET_RESET_MASK2), &regValue);
	}
}

static int HyvePlatform_InitFRU()
{
	char fruFile[128] = {0};
	struct stat statbuf = {0};

	// Check if the MB backup FRU exists
	HYVE_FRU_BKFRU_PATH(fruFile, sizeof(fruFile), HYFEPLATFORM_MB_FRU_ID);
	if (stat(fruFile, &statbuf)) {
		// Create the MB backup FRU
		if (HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_FLASH) < 0) {
			printf("[INFO] Error in creating MB backup FRU\n");
		}
	}
	// Create the MB FRU Cache
	if (HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_CACHE) < 0) {
		INT8U fruData[HYVE_FRU_FILE_SIZE] = {0};
		FILE *fp = NULL;

		// Read the backup one
		if (HyveFRU_ReadFRU(0, HYVE_FRU_FILE_SIZE, HYFEPLATFORM_MB_FRU_ID,
				HYVE_STORETYPE_FLASH, fruData) < 0) { return -1; }
		// Try to recover
		if (HyveExt_WriteEEPROM(0, fruData, HYVE_FRU_FILE_SIZE) < 0) {
			printf("[Error] Unable to recover the MB FRU\n");
		}
		HYVE_FRU_CACHE_PATH(fruFile, sizeof(fruFile), HYFEPLATFORM_MB_FRU_ID);
		fp = fopen(fruFile, "w+");
		if (!fp) { return -1; }
		fwrite(fruData, 1, HYVE_FRU_FILE_SIZE, fp);
		fclose(fp);
	}
	return 0;
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
	printf("[INFO] - Run %s\n", __func__);
	HyvePlatform_InitChip();
	HyveExt_MutexInit();

	if (HyvePlatform_InitFRU() < 0 ) {
		printf("[INFO] Error in creating MB FRU cache\n");
	}
	// Recognize this platform
	HyvePlatform_InitPlatformID();


	
	
	
	
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
	


	INT8U offset = CONFIG_SPX_FEATURE_I2C_EEPROM_MAC2ADDR_OFFSET, readData[6] = {0};
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

/********************* Platform Peripheral Control Functions *********************/
/*-----------------------------------------------------------------
 * @fn HyvePlatform_BIOS_FlashSelect
 * @brief	To select which BIOS flash to access
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pFlashIndex  - The INT8U pointer to input/output the BIOS flash index
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_BIOS_FlashSelect(const INT8U op, INT8U* pFlashIndex)
{
	int ret = 0;

	if (!pFlashIndex) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (PrimaryFlash == *pFlashIndex) {
			ret = HyveExt_GPIO_Set_Data_High(IO_FM_BACKUP_BIOS_SEL_N);
		} else {
			ret = HyveExt_GPIO_Set_Data_Low(IO_FM_BACKUP_BIOS_SEL_N);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently BIOS flash select
	if ((ret = HyveExt_GPIO_Get_Data(IO_FM_BACKUP_BIOS_SEL_N)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_HIGH == ret) {
		*pFlashIndex = PrimaryFlash;
	} else {
		*pFlashIndex = SecondaryFlash;
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_BIOS_FlashAccessControl
 * @brief	To select which BIOS flash to access
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_enable  - The INT8U pointer to input/output the flag of enable
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_BIOS_FlashAccessControl(const INT8U op, INT8U* pIs_enable)
{
	int ret = 0;

	if (!pIs_enable) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (TRUE == *pIs_enable) {
			ret = HyveExt_GPIO_Set_Data_High(IO_FM_BIOS_BMC_CTRL);
		} else {
			ret = HyveExt_GPIO_Set_Data_Low(IO_FM_BIOS_BMC_CTRL);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently set
	if ((ret = HyveExt_GPIO_Get_Data(IO_FM_BIOS_BMC_CTRL)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_HIGH == ret) {
		*pIs_enable = TRUE;
	} else {
		*pIs_enable = FALSE;
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_Reset_OCP_NIC_SMBus
 * @brief	To reset the SMBus of the OCP NIC card
 *          TODO: Need to check if actually reset the SMBus or whole NIC card
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_Reset_OCP_NIC_SMBus()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_BMC_OCP1_SMRST_L) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_BMC_OCP1_SMRST_L) > -1) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;			
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_DisplayPortPwrControl
 * @brief	To enable/disable the power of the display port
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_enable  - The INT8U pointer to input/output the flag of enable
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_DisplayPortPwrControl(const INT8U op, INT8U* pIs_enable)
{
	int ret = 0;

	if (!pIs_enable) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (TRUE == *pIs_enable) {
			ret = HyveExt_GPIO_Set_Data_High(IO_FM_DP_CONN_PWR_EN_CTL);
		} else {
			ret = HyveExt_GPIO_Set_Data_Low(IO_FM_DP_CONN_PWR_EN_CTL);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently set
	if ((ret = HyveExt_GPIO_Get_Data(IO_FM_DP_CONN_PWR_EN_CTL)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_HIGH == ret) {
		*pIs_enable = TRUE;
	} else {
		*pIs_enable = FALSE;
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_BoardSKUID
 * @brief	To get the board SKU ID which is converted by the GPIO pin value of the board SKU ID
 *
 * @param[out]  pBoardID  - The INT8U pointer to output the board SKU ID
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_BoardSKUID(INT8U *pBoardSKUID)
{

	INT8U i = 0, gpios[] = { IO_FM_BMC_BOARD_SKU_ID0_N, IO_FM_BMC_BOARD_SKU_ID1_N,
						IO_FM_BMC_BOARD_SKU_ID2_N, IO_FM_BMC_BOARD_SKU_ID3_N };

	if (!pBoardSKUID) { return -1; }
	
	for (i = 0; i < HYVE_ARRAYSIZE(gpios); i++) {
		int ret = 0;
		if ((ret = HyveExt_GPIO_Get_Data(gpios[i])) < 0) { return -1; }
		*pBoardSKUID |= ((ret & 0x01) << i);
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_BoardID
 * @brief	To get the board ID which is converted by the GPIO pin value of the board ID
 *
 * @param[out]  pBoardID  - The INT8U pointer to output the board ID
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_BoardID(INT8U *pBoardID)
{

	INT8U i = 0, gpios[] = { IO_FM_REV_BOARD_ID0, IO_FM_REV_BOARD_ID1, IO_FM_REV_BOARD_ID2 };

	if (!pBoardID) { return -1; }
	
	for (i = 0; i < HYVE_ARRAYSIZE(gpios); i++) {
		int ret = 0;
		if ((ret = HyveExt_GPIO_Get_Data(gpios[i])) < 0) { return -1; }
		*pBoardID |= ((ret & 0x01) << i);
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_LED_Control
 * @brief	To control the platform LED
 *
 * @param[in]         ledIndex  - The index of the LED
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_enable   - The INT8U pointer to input/output the flag of enable
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_LED_Control(const INT8U ledIndex, const INT8U op, INT8U* pIs_enable)
{
	static const struct ledGpioMap {
		INT16U gpioPinNum;
		INT8U isActiveLow;
	} ledGPIO[PLATFORM_LED_MAX_Index] = {
			{ IO_BMC_HW_HEARTBEAT_N, TRUE },
			{ IO_FP_ID_LED_N, TRUE },
			{ IO_BMC_SYS_STATUS_LED_CTRL_Y, FALSE },
			{ IO_BMC_SYS_STATUS_LED_CTRL_G, FALSE },
			{ IO_BMC_SYS_STATUS_LED_CTRL_R, FALSE }
	};
	int ret = 0;
	int (*pFuncSetGPIO)(const INT16U ) = HyveExt_GPIO_Set_Data_Low;

	if ((ledIndex >= PLATFORM_LED_MAX_Index) || (!pIs_enable)) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (((TRUE == *pIs_enable) && (FALSE == ledGPIO[ledIndex].isActiveLow)) ||
				((FALSE == *pIs_enable) && (TRUE == ledGPIO[ledIndex].isActiveLow))) {
			pFuncSetGPIO = HyveExt_GPIO_Set_Data_High;
		}
		return pFuncSetGPIO(ledGPIO[ledIndex].gpioPinNum) < 0 ? -1 : 0;
	}
	// Get currently set
	if ((ret = HyveExt_GPIO_Get_Data(ledGPIO[ledIndex].gpioPinNum)) < 0) { return ret; }
	*pIs_enable = ((ret & 0x01) ^ ledGPIO[ledIndex].isActiveLow);
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_CPU_NMI_SYNC_FLOOD
 * @brief	To send the NMI signal to the CPU
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_CPU_NMI_SYNC_FLOOD()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_P0_NMI_SYNC_FLOOD_L) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_P0_NMI_SYNC_FLOOD_L) > -1) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;			
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_Reset_EMMC
 * @brief	To reset the EMMC
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_Reset_EMMC()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_FM_BMC_EMMC_RST_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_FM_BMC_EMMC_RST_N) > -1) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;			
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_Reset_PwrAUX_IC
 * @brief	To reset the power AUX IC
 *
 * @param[in] auxIndex - The index of the AUX IC
 *
 * @return    0 - if success
 *           -1 - otherwise
 *           
 * Note:
 *     The reset IC will delay about 5 seconds then trigger reset action
 *     Please make sure you done all preserve, flush config actions
 *           
 *-----------------------------------------------------------------*/
int HyvePlatform_Reset_PwrAUX_IC(const INT8U auxIndex)
{
	const INT16U resetPins[PwrAUXIndex_MAX] = {
			IO_P5V_AUX_RST_DLY, IO_P3V3_AUX_RST_DLY
	};
	int retryCount = 3;

	if (auxIndex >= PwrAUXIndex_MAX) { return -1; }
	
	do {
		if (HyveExt_GPIO_Set_Data_Low(resetPins[auxIndex]) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(resetPins[auxIndex]) > -1) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;			
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_BMC_Ready
 * @brief	To set the BMC ready
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_BMC_Ready()
{
	int retryCount = 3;

	do {
		// To inform the CPLD that the BMC is ready
		if (HyveExt_GPIO_Set_Data_Low(IO_FM_BMC_ONCTL_N) > -1) {
			if (HYVE_GPIO_DATA_LOW == HyveExt_GPIO_Get_Data(IO_FM_BMC_ONCTL_N)) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_Reset_CMOS
 * @brief	To reset the EMMC
 *
 * @param None
 *
 * @return    0 - if success
 *           -1 - otherwise
 * 
 * Note:
 *     this pin can both reset the CMOS and the BMC RTC
 *-----------------------------------------------------------------*/
int HyvePlatform_Reset_CMOS()
{
	int retryCount = 3;

	do {
		if (HyveExt_GPIO_Set_Data_Low(IO_RST_RTCRST_N) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(IO_RST_RTCRST_N) > -1) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;			
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_HDTSelect
 * @brief	To set the HDT source selection
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pFlashIndex  - The INT8U pointer to input/output the BIOS flash index
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_HDTSelect(const INT8U op, INT8U* pHDTIndex)
{
	int ret = 0;

	if (!pHDTIndex) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (HDT_CPLD == *pHDTIndex) {
			ret = HyveExt_GPIO_Set_Data_High(IO_P0_HDT_SEL_0);
		} else {
			ret = HyveExt_GPIO_Set_Data_Low(IO_P0_HDT_SEL_0);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently HDT selection
	if ((ret = HyveExt_GPIO_Get_Data(IO_P0_HDT_SEL_0)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_HIGH == ret) {
		*pHDTIndex = HDT_CPLD;
	} else {
		*pHDTIndex = HDT_BMC;
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_DIMM_MuxControl
 * @brief	To enable/disable the control of the Mux of the SPD(DIMMs)
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_enable  - The INT8U pointer to input/output the flag of enable
 *
 * @return    0 - if success
 *           -1 - otherwise
 * 
 * Note:
 *     By default, it's controlled by HW circuit.
 *     CPIO Pin High: enable; Low: disable
 *-----------------------------------------------------------------*/
int HyvePlatform_DIMM_MuxControl(const INT8U op, INT8U* pIs_enable)
{
	int ret = 0;

	if (!pIs_enable) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (TRUE == *pIs_enable) {
			ret = HyveExt_GPIO_Set_Data_High(IO_SPD_REMOTE_SEL);
		} else {
			ret = HyveExt_GPIO_Set_Data_Low(IO_SPD_REMOTE_SEL);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently set
	if ((ret = HyveExt_GPIO_Get_Data(IO_SPD_REMOTE_SEL)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_HIGH == ret) {
		*pIs_enable = TRUE;
	} else {
		*pIs_enable = FALSE;
	}
	return 0;
}



/*-----------------------------------------------------------------
 * @fn HyvePlatform_Reset_I2CMux
 * @brief	To reset the I2C Mux IC
 *
 * @param[in] muxIndex - The index of the Mux IC
 *
 * @return    0 - if success
 *           -1 - otherwise
 *          
 *-----------------------------------------------------------------*/
int HyvePlatform_Reset_I2CMux(const INT8U muxIndex)
{
	const INT16U resetPins[I2CMUXIndex_MAX] = {
			IO_BMC_CLKGEN_I2CMUX_RST_N, IO_BMC_PLINK_I2CMUX_RST_N,
			IO_BMC_GLINK_I2CMUX_RST_N
	};
	int retryCount = 3;

	if (muxIndex >= I2CMUXIndex_MAX) { return -1; }
	
	do {
		if (HyveExt_GPIO_Set_Data_Low(resetPins[muxIndex]) > -1) {
			// TODO: Currently the delay time is unknown 
			usleep(1000);
			if (HyveExt_GPIO_Set_Data_High(resetPins[muxIndex]) > -1) {
				return 0;
			}
		}
		usleep(1000);
	} while (retryCount--);

	return -1;			
}

