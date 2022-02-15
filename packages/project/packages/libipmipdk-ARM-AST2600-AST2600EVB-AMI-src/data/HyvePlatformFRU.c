 /******************************************************************
 *
 * @file	HyvePlatformFRU.c
 * @brief	Provide the platform FRU functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"

#include "HyveCommon.h"



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
		ret = HyveExt_ReadEEPROM((EEPROM_OFFSET_MB_FRU + offset), fruData, rCount);
		break;
	case HYFEPLATFORM_FANBOARD_FRU_ID:
	case HYFEPLATFORM_FRONTPANEL_FRU_ID:
	case HYFEPLATFORM_MIDPANEL_FRU_ID:
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
	int ret = -1;

	if (!fruData) { return ret; }

	switch (fruID) {
	case HYFEPLATFORM_MB_FRU_ID:
		ret = HyveExt_WriteEEPROM((EEPROM_OFFSET_MB_FRU + offset), fruData, wCount);
		break;
	case HYFEPLATFORM_FANBOARD_FRU_ID:
	case HYFEPLATFORM_FRONTPANEL_FRU_ID:
	case HYFEPLATFORM_MIDPANEL_FRU_ID:
	default:
		// TODO
		break;
	}

	return ret; 
}
