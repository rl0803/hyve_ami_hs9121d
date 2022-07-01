 /******************************************************************
 *
 * @file	HyvePlatformBP_FP.c
 * @brief	The Hyve platform BP FP related functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"

#include "HyveCommon.h"


// HYVE_MAX_HOST_HDD_NUM

INT8U HyvePlatform_BP_IsValidHDDIndex(INT8U hddIndex)
{
	return hddIndex > 2 ? 0 : 1;
}

INT8U HyvePlatform_BP_HDDSlotIndex(INT8U hddIndex)
{
	return hddIndex;
}

INT8U HyvePlatform_BP_I2CBus(INT8U hddIndex)
{
	if (0) { hddIndex = hddIndex; }
	return HYFEPLATFORM_SMBUS_OCP_RISER;
}

INT8U HyvePlatform_BP_I2CAddr(INT8U hddIndex)
{
	if (0) { hddIndex = hddIndex; }
	return MG9100_ADDR_C0;
}
