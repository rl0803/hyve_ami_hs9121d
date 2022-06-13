 /******************************************************************
 *
 * @file	HyvePlatformFRU.h
 * @brief	The Hyve platform FRU header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMFRU_H_
#define HYVEPLATFORMFRU_H_


#define HYFEPLATFORM_FRUSIZE_256								(256)
#define HYFEPLATFORM_FANBOARD_FRU_MAXSIZE						HYFEPLATFORM_FRUSIZE_256
#define HYFEPLATFORM_PDB_FRU_MAXSIZE							HYFEPLATFORM_FRUSIZE_256


typedef enum {
	HYFEPLATFORM_MB_FRU_ID = 0,
	HYFEPLATFORM_PDB_FRU_ID,
	HYFEPLATFORM_FANBOARD_FRU_ID,
	HYFEPLATFORM_FRONTPANEL_FRU_ID,
	HYFEPLATFORM_FRU_ID_MAX
} HyvePlatformFRUID_E;


/***************** Platform override functions *****************/
#define HYVEPLATFORM_READ_FRU									HyvePlatform_ReadFRU

/***************** Platform functions *****************/
extern int HyvePlatform_ReadFRU(const INT8U fruID, const INT16U offset, const INT16U rCount, INT8U* fruData);
extern int HyvePlatform_WriteFRU(const INT8U fruID, const INT16U offset, const INT16U wCount, INT8U* fruData);
extern int HyvePlatform_SyncFRU();
extern int HyvePlatform_CreateFRUsCache(INT32U fruIDs);

#endif
