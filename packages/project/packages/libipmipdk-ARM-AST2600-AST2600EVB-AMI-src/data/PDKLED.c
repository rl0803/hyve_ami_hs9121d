/****************************************************************
 ****************************************************************
 **                                                            **
 **    (C)Copyright 2006-2020, American Megatrends Inc.        **
 **                                                            **
 **            All Rights Reserved.                            **
 **                                                            **
 **        5555 Oakbrook Parkway, Norcross,                    **
 **                                                            **
 **        Georgia - 30093, USA. Phone-(770)-246-8600.         **
 **                                                            **
 ****************************************************************
 ****************************************************************
 *
 * PDKLED.c
 * LED Access Functions.
 *
 *  Author: Gowtham Shanmukham <gowthams@ami.com>
 ******************************************************************/
#define ENABLE_DEBUG_MACROS     0

#include "Types.h"
#include "OSPort.h"
#include "Debug.h"
#include "PDKHooks.h"
#include "API.h"
#include "gpioifc.h"
#include "SharedMem.h"
#include "Indicators.h"
#include "LEDMap.h"
#include "NVRAccess.h"
#include "Platform.h"
#include "IPMIConf.h"
#include "hal_hw.h"

/*--------------------------------------------------------------------------
 * @fn  PDK_SetupLEDMap
 * @brief Setup pointers to correct LED Map for given chassis/board
 * @return 0 if success
 *         -1 if failure
 *--------------------------------------------------------------------------*/
int
PDK_PlatformSetupLED (int BMCInst)
{
	int ret = 0;
	IndicatorInfo_T PlatformLEDMap[MAX_LED_NUM] = {
		{
			TRUE, // Enable;
			PLATFORM_LED_BMC_HEARTBEAT, // LEDNum;
			LED_PATTERN_SLOW_BLINK, // Pattern;
			0, // NumSec;
			0, // CurBit;
			0, // Count;
		},
		{
			FALSE,
			PLATFORM_LED_IDENTIFY,
			LED_PATTERN_OFF,
			0,
			0,
			0,
		},
	};

	LOCK_BMC_SHARED_MEM_RET(BMCInst, ret);
	if (ret < 0) {
		printf("[Error] %s: Unable to get the mutex\n", __func__);
		return ret;
	}
	_fmemcpy ((BMC_GET_SHARED_MEM (BMCInst)->LEDInfo), &PlatformLEDMap, (MAX_LED_NUM * sizeof(IndicatorInfo_T)));
	UNLOCK_BMC_SHARED_MEM(BMCInst);   
    return 0;
}


/*--------------------------------------------------------------------------
 * @fn  PDK_GlowLED
 * @brief Glow or turn of an LED.
 * @param LEDNum        LED number to turn on or turn off.
 * @param IsOn          TRUE to turn ON. FALSE to turn off.
 *--------------------------------------------------------------------------*/
void
PDK_GlowLED (INT8U LEDNum, INT8U n, int BMCInst)
{
	if (0) { BMCInst = BMCInst; }
	if (HyvePlatform_LED_Control(LEDNum, Hyve_VALUE_SET, &n) < 0) {
		printf("[Error] %s: failed to turn %s the LED(%u)\n", __func__, (n ? "on" : "off"), LEDNum);
	}
}

/*--------------------------------------------------------------------
 * @fn PDK_GlowFaultLED
 * @brief This function is invoked to manage the front fan failure led
 * @param Fault - Indicates desired fault type to take action on:
 *                LED_FAULT_TEMP   LED_FAULT_FAN     LED_FAULT_PS
 *                LED_FAULT_CPU    LED_FAULT_HDD
 *                LED_FAULT_ECC_CE LED_FAULT_ECC_UE
 * @param State - Caller indicates desired state
 *                LED_STATE_RESET - all off and reset
 *                LED_STATE_OFF   - off from one source
 *                LED_STATE_ON    - on from one source
 *--------------------------------------------------------------------*/
void
PDK_GlowFaultLED (int Fault, int State, INT8U Data, int BMCInst)
{
    if(0)
    {
        BMCInst=BMCInst;  /*  -Wextra, fix for unused parameters  */
	Fault=Fault;
	State=State;
	Data=Data;
    }
}

/*-----------------------------------------------------------------
 * @fn PDK_UpdatePowerLEDStatus
 * @brief This is provided to implement the platform specific
 *        update Power LED status procedure according to Operational
 *        State Machine.
 *
 * @param pFruObj  - Pointer of Operational State FRU object. 
 *
 * @return None.
 *-----------------------------------------------------------------*/
void
PDK_UpdatePowerLEDStatus (OpStateFruObj_T *pFruObj, int BMCInst)
{
    if(0)
    {
        BMCInst=BMCInst;  /*  -Wextra, fix for unused parameters  */
	pFruObj=pFruObj;
    }
    return;
}

/*-----------------------------------------------------------------
 * @fn PDK_UpdateFaultLEDStatus
 * @brief This is provided to implement the platform specific
 *        update Fault LED status procedure according to Aggregated
 *        Fault Sensor.
 *
 * @param FaultState - State according to Aggregated Fault Sensor.
 *
 * @return None.
 *-----------------------------------------------------------------*/
void
PDK_UpdateFaultLEDStatus (INT8U FaultState, int BMCInst)
{
    if(0)
    {
        BMCInst=BMCInst;  /*  -Wextra, fix for unused parameters  */
	FaultState=FaultState;
    }
    return;
}

