 /******************************************************************
 *
 * @file	HyvePlatformHooks.c
 * @brief	To provide platform hook functions
 * 			
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "IPMI_App.h"
#include "hal_hw.h"
#include "API.h"
#include "PendTask.h"
#include "safesystem.h"
#include "PDKAccess.h"

#include "HyveCommon.h"


int HyvePlatform_HelloHook(int var)
{
	printf("[%s] Hi...var:%d\n", __func__, var);
	
	return 0;
}


/*----------------------------------------------------------------------------
 * @fn HyvePlatform_BIOS_Status_Callback
 *
 * @brief This function provides platform actions for BIOS status
 * @param[in]   status - The BIOS status
 *
 *---------------------------------------------------------------------------*/
void HyvePlatform_BIOS_Status_Callback(const INT8U status)
{
	switch(status)
	{
	default:
		break;
	}
}
