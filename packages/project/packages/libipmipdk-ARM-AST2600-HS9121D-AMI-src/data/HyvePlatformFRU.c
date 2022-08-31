 /******************************************************************
 *
 * @file	HyvePlatformFRU.c
 * @brief	Provide the platform FRU functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "PDKEEPROM.h"

#include "HyveCommon.h"


#define EEPROM_24C2				(0x9)	// Page Size 8 bytes
#define EEPROM_24C64			(0xF)	// Page Size 32 bytes


struct _extFRUDevInfo {
	INT8U eepromType;
	INT8U busNum;
	INT8U slave_addr;
	INT16U maxFRUsize;
};
static const struct _extFRUDevInfo  g_FRUDevInfo[HYFEPLATFORM_FRU_ID_MAX] = {
	/* eepromType		busNum							slave_addr							maxFRUsize */
	{ EEPROM_24C64,		EEPROM_I2C_BUS,					EEPROM_I2C_ADDR,					HYVE_FRU_FILE_SIZE },
	{ EEPROM_24C2,		HYFEPLATFORM_SMBUS_PDB,			HYFEPLATFORM_ADDR_PDB_FRU,			HYFEPLATFORM_PDB_FRU_MAXSIZE },
	{ EEPROM_24C64,		HYFEPLATFORM_SMBUS_FAN_BOARD,	HYFEPLATFORM_ADDR_FAN_BOARD_FRU,	HYFEPLATFORM_FANBOARD_FRU_MAXSIZE },
	{0} // FP ???
};
static INT32U g_NeedToSync = 0;

/*-----------------------------------------------------------------
 * @fn HyvePlatform_ReadFRU
 * 
 * @brief	To read the FRU data
 * 
 * @param[in]	fruID - The FRU ID
 * @param[in]	offset - The offset position of the FRU binary file
 * @param[in]	rCount - The read count of the FRU data * 
 * @param[out]	fruData - A INT16U pointer to export the FRU data
 * 
 * @return    countToRead - success.
 *                     -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_ReadFRU(const INT8U fruID, const INT16U offset,
							const INT16U rCount, INT8U* fruData)
{
	int ret = -1;

	if (!fruData) { return ret; }

	switch (fruID) {
	case HYFEPLATFORM_MB_FRU_ID:
	case HYFEPLATFORM_PDB_FRU_ID:
	case HYFEPLATFORM_FANBOARD_FRU_ID:
    	ret = READ_EEPROM(g_FRUDevInfo[fruID].eepromType, g_FRUDevInfo[fruID].busNum,
    			g_FRUDevInfo[fruID].slave_addr, fruData, offset, rCount);
		break;

	case HYFEPLATFORM_FRONTPANEL_FRU_ID:
	default:
		// TODO
		break;
	}
	return ret; 
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_WriteFRU
 * 
 * @brief	To write the FRU data
 * 
 * @param[in]	fruID - The FRU ID
 * @param[in]	offset  - The offset position of the FRU binary file
 * @param[in]	wCount - The write count of the FRU data * 
 * @param[out]	fruData - A INT16U pointer to input the FRU data
 * 
 * @return    countToRead - success.
 *                     -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_WriteFRU(const INT8U fruID, const INT16U offset,
							const INT16U wCount, INT8U* fruData)
{
	int ret = -1, fd = -1;
	char fruFile[128] = {0};

	if (!fruData || fruID >= HYFEPLATFORM_FRU_ID_MAX) { return ret; }

	HYVE_FRU_CACHE_PATH(fruFile, sizeof(fruFile), fruID);

	fd = open(fruFile, O_RDWR | O_CREAT | O_SYNC);	
	if (fd < 0) {
		printf("%s: error in opening %s\n", __func__, fruFile);
		return -1;
	}
	lseek(fd, offset, SEEK_SET);
	ret = write(fd, fruData, wCount);
	close(fd);

	if (wCount != ret) {
		printf("%s: error in writing %s\n", __func__, fruFile);
		return -1;
	}
	HYVE_SetBitVal(g_NeedToSync, fruID, 1);
	HyvePlatform_SetPendTask(HyvePlatformPT_SYNCFRU, 3, fruID);
	
	return ret;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_SyncFRU
 * 
 * @brief	To sync Cache FRUs to EEPROM/flash.
 * 
 * @param[None]
 * 
 * @return 0 - success.
 *        -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_SyncFRU()
{
	INT8U fruID = 0;

	for (fruID = 0; fruID < HYFEPLATFORM_FRU_ID_MAX; fruID++) {
		if (g_NeedToSync & HYVE_BIT(fruID)) {
			INT8U fruData[HYVE_FRU_FILE_SIZE] = {0};

			if ((-1 != HyveFRU_ReadFRU(0, g_FRUDevInfo[fruID].maxFRUsize, fruID,
							HYVE_STORETYPE_CACHE, fruData)) && HyveFRU_Is_ValidFRU(fruData)) {
				int ret = -1;

				// Update to EERPOM
//				printf("%s , Update  FRU%u\n", __func__, fruID);
		    	ret = WRITE_EEPROM(g_FRUDevInfo[fruID].eepromType, g_FRUDevInfo[fruID].busNum,
		    			g_FRUDevInfo[fruID].slave_addr, fruData, 0, g_FRUDevInfo[fruID].maxFRUsize);
				if (HYFEPLATFORM_MB_FRU_ID == fruID) {
					// Update to flash
					HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID,
							HYVE_STORETYPE_FLASH, g_FRUDevInfo[fruID].maxFRUsize);
				}
		    	if (-1 != ret) {
					HYVE_SetBitVal(g_NeedToSync, fruID, 0);
				}
			} else {
//				printf("%s , recover FRU%u cache\n", __func__, fruID);
				// Recover cache
				if (!HyveFRU_FRUBackup(fruID, HYVE_STORETYPE_CACHE, g_FRUDevInfo[fruID].maxFRUsize)) {
					HYVE_SetBitVal(g_NeedToSync, fruID, 0);
				}
			}
		}
	}	
	return g_NeedToSync ? -1 : 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_CreateFRUsCache
 * 
 * @brief	To create FRUs cache
 * 
 * @param[in]	fruIDs - The FRU IDs
 * 
 * @return 0 - success.
 *        -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatform_CreateFRUsCache(INT32U fruIDs)
{
	static INT8U retry = 0;
	INT8U fruID = 0;

	for (; fruID < HYFEPLATFORM_FRU_ID_MAX; fruID++) {
		if ((fruIDs & HYVE_BIT(fruID)) &&
				!HyveFRU_FRUBackup(fruID, HYVE_STORETYPE_CACHE, g_FRUDevInfo[fruID].maxFRUsize)) {
			HYVE_SetBitVal(fruIDs, fruID, 0);
		}
	}
	if (fruIDs && (++retry < 3)) {
		HyvePlatform_SetPendTask(HyvePlatformPT_CREATEFRUCACHE, 1, fruIDs);
		return -1;
	}
	retry = 0;
	return 0;
}
