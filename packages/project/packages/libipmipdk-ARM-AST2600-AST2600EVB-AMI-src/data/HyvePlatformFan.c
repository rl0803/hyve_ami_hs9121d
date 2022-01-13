 /******************************************************************
 *
 * @file	HyvePlatformFan.c
 * @brief	Provide the platform Fan control or other specific functions
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
#include "EINTR_wrappers.h"

#include "HyveCommon.h"




INT8U HyvePlatformFan_GetFanDir()
{
	int ret = 0;

	if ((ret = HyveExt_GPIO_Get_Data(IO_FAN_DIRECTION)) < 0) {
		return PlatformFanDir_Unkonwn;
	}
	if (HYVE_GPIO_DATA_HIGH == ret) {
		return PlatformFanDir_In;
	}
	return PlatformFanDir_Out;
}
