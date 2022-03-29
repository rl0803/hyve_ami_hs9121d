 /******************************************************************
 *
 * @file	HyvePlatformCPLD.c
 * @brief	Provide the platform CPLD related functions
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

/* Note:

Need to know when to pull-H the GPIO 
IO_FM_PWRBRK_BMC_N                  GPIOF7 // GPIO, Output, to request CPLD do power break(PCIe device throttle)

#define IO_BMC_PLD_VR_ALERT_L               GPION2 // GPIO, Output, to inform the CPLD
#define IO_FM_AUTH_COMPLETE_N               GPIOO6 // GPIO, Output, to inform the CPLD that FW auth is done and is good to go next stage


#define IO_FM_BMC_PWRBTN_OUT_N              GPIOP1 // GPIO, Output, pass the button signal to the CPLD
#define IO_RST_SYSRST_BTN_OUT_N             GPIOP3 // GPIO, Output, pass the button signal to the CPLD



*/


/*-----------------------------------------------------------------
 * @fn HyvePlatformCPLD_PCIeDevThrottle
 * @brief	To request the CPLD to do power throttle of PCIe devices
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_enable  - The INT8U pointer to input/output the flag of enable
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformCPLD_PCIeDevThrottle(const INT8U op, INT8U* pIs_enable)
{
	int ret = 0;

	if (!pIs_enable) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (TRUE == *pIs_enable) {
			ret = HyveExt_GPIO_Set_Data_Low(IO_FM_PWRBRK_BMC_N);
		} else {
			ret = HyveExt_GPIO_Set_Data_High(IO_FM_PWRBRK_BMC_N);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently JTAG mux selection
	if ((ret = HyveExt_GPIO_Get_Data(IO_FM_PWRBRK_BMC_N)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_LOW == ret) {
		*pIs_enable = TRUE;
	} else {
		*pIs_enable = FALSE;
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformCPLD_Inform_VRAlert
 * @brief	To inform the CPLD that VR alert asserted/de-asserted
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_asserted  - The INT8U pointer to input/output the flag of assert
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformCPLD_Inform_VRAlert(const INT8U op, INT8U* pIs_asserted)
{
	int ret = 0;

	if (!pIs_asserted) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (TRUE == *pIs_asserted) {
			ret = HyveExt_GPIO_Set_Data_Low(IO_BMC_PLD_VR_ALERT_L);
		} else {
			ret = HyveExt_GPIO_Set_Data_High(IO_BMC_PLD_VR_ALERT_L);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently status
	if ((ret = HyveExt_GPIO_Get_Data(IO_BMC_PLD_VR_ALERT_L)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_LOW == ret) {
		*pIs_asserted = TRUE;
	} else {
		*pIs_asserted = FALSE;
	}
	return 0;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatformCPLD_Inform_FwAuthComplete
 * @brief	To inform the CPLD that FW auth complete asserted/de-asserted
 *
 * @param[in]               op  - The operation: SET, GET
 * @param[in/out]  pIs_asserted  - The INT8U pointer to input/output the flag of assert
 *
 * @return    0 - if success
 *           -1 - otherwise
 *-----------------------------------------------------------------*/
int HyvePlatformCPLD_Inform_FwAuthComplete(const INT8U op, INT8U* pIs_asserted)
{
	int ret = 0;

	if (!pIs_asserted) { return -1; }

	if (Hyve_VALUE_SET == op) {
		if (TRUE == *pIs_asserted) {
			ret = HyveExt_GPIO_Set_Data_Low(IO_FM_AUTH_COMPLETE_N);
		} else {
			ret = HyveExt_GPIO_Set_Data_High(IO_FM_AUTH_COMPLETE_N);
		}
		return ret < 0 ? -1 : 0;
	}
	// Get currently status
	if ((ret = HyveExt_GPIO_Get_Data(IO_FM_AUTH_COMPLETE_N)) < 0) { return ret; }
	if (HYVE_GPIO_DATA_LOW == ret) {
		*pIs_asserted = TRUE;
	} else {
		*pIs_asserted = FALSE;
	}
	return 0;
}








