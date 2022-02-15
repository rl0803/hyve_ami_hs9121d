 /******************************************************************
 *
 * @file	HyvePlatformFRU.h
 * @brief	The Hyve platform FRU header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMFRU_H_
#define HYVEPLATFORMFRU_H_


#define HYFEPLATFORM_MB_FRU_ID									(0)
#define HYFEPLATFORM_FANBOARD_FRU_ID							(1)
#define HYFEPLATFORM_FRONTPANEL_FRU_ID							(2)
#define HYFEPLATFORM_MIDPANEL_FRU_ID							(3)



/***************** Platform override functions *****************/
#define HYVEPLATFORM_READ_FRU									HyvePlatform_ReadFRU

extern int HyvePlatform_ReadFRU(const INT8U fruID, const INT16U offset, const INT16U rCount, INT8U* fruData);
extern int HyvePlatform_WriteFRU(const INT8U fruID, const INT16U offset, const INT16U wCount, INT8U* fruData);

#endif
