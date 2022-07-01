 /******************************************************************
 *
 * @file	HyvePlatformBP_FP.h
 * @brief	The Hyve platform BP FP header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMBPFP_H_
#define HYVEPLATFORMBPFP_H_


#define HYVEPLATFORM_IS_VALID_HDD_INDEX							HyvePlatform_BP_IsValidHDDIndex
#define HYVEPLATFORM_BP_HDD_SLOT_INDEX							HyvePlatform_BP_HDDSlotIndex
#define HYVEPLATFORM_BP_I2C_BUS									HyvePlatform_BP_I2CBus
#define HYVEPLATFORM_BP_I2C_ADDR								HyvePlatform_BP_I2CAddr

#define HYVEPLATFORM_BEFORE_ACCESS_BP(hddIndex)					HyvePlatform_MuxCtrl(I2CMUX_PLINK, MUX_CHANNEL_3, 100)
#define HYVEPLATFORM_AFTER_ACCESS_BP(hddIndex)					HyvePlatform_UnlockMux(I2CMUX_PLINK)


extern INT8U HyvePlatform_BP_IsValidHDDIndex(const INT8U hddIndex);
extern INT8U HyvePlatform_BP_HDDSlotIndex(const INT8U hddIndex);
extern INT8U HyvePlatform_BP_I2CBus(const INT8U hddIndex);
extern INT8U HyvePlatform_BP_I2CAddr(const INT8U hddIndex);

#endif
