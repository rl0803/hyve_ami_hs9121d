 /******************************************************************
 *
 * @file	HyvePlatformTask.c
 * @brief	Provide the platform task functions
 *
 ******************************************************************/

#include <time.h>
#include <sys/select.h>
#include <sys/types.h>

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "IPMI_App.h"
#include "hal_hw.h"
#include "API.h"
#include "PendTask.h"
#include "safesystem.h"
#include "OSPort.h"
#include "EINTR_wrappers.h"
#include "flashlib.h"
#include "Platform.h"
#include "ChassisCtrl.h"
#include "SensorAPI.h"

#include "HyveCommon.h"


#define HYVEPLATFORM_MSG_Q_GENERIC_PATH				"/var/.hyvePlatformMsgQ1"
#define HYVEPLATFORM_MSG_Q_IRQ_PATH					"/var/.hyvePlatformMsgQ2"

#define REG_INTRUSION_CTRL							(0x1E6EF010)

/********************* Global variable definitions *********************/
int g_hyvePlatformMsgQFD = -1;
int g_hyvePlatformMsgQFD_IRQ = -1;

static HyvePlatformPendTask_T g_hyvePlatformPendTasks[HyvePlatformPT_MAX] = {
	// { is_set ,timeout ,jiffy, data, callback }
	{ 0, 1, 0, 0, HyvePlatformPT_BackupFRU },
};


/********************* Functions *********************/
/*-----------------------------------------------------------------
 * @fn HyvePlatform_SetPendTask
 * @brief	To set the platform pending task
 *
 * @param[in]	taskIndex - The platform pending task index
 * @param[in]	timeout - The timeout of the platform pending task
 * @param[in]	data - A INT32U data passed to the task
 *
 * @return  None
 *-----------------------------------------------------------------*/
void HyvePlatform_SetPendTask(const INT16U taskIndex, INT8U timeout, const INT32U data)
{
	if (taskIndex >= HyvePlatformPT_MAX) { return; }

	g_hyvePlatformPendTasks[taskIndex].timeout = timeout;
	g_hyvePlatformPendTasks[taskIndex].jiffy = HYFEPLATFORM_JIFFY;
	g_hyvePlatformPendTasks[taskIndex].data = data;
	g_hyvePlatformPendTasks[taskIndex].is_set = 1;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_Is_PendTaskSet
 * @brief	To check the platform pending task is set or not
 *
 * @param[in]	taskIndex - The platform pending task index
 *
 * @return  the 'is_set' flag
 *-----------------------------------------------------------------*/
INT8U HyvePlatform_Is_PendTaskSet(const INT16U taskIndex)
{
	if (taskIndex >= HyvePlatformPT_MAX) { return 0; }
	return g_hyvePlatformPendTasks[taskIndex].is_set;
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_GenericTask
 * @brief	A platform generic task.
 * 			In this task, we can do
 * 				(1) Timing insensitive routine work.
 * 				(2) Asynchronous and time cost requests.
 *
 * @param[in]	pArg - A pointer of void, but unused
 *
 * @return  0	- if thread exits
 *-----------------------------------------------------------------*/
static void* HyvePlatform_GenericTask(void* pArg)
{
    int nfd = -1;
    fd_set read_set = {0};
    struct timeval timeout = {
		.tv_sec = HyvePlatform_TASK_INTERVAL_GENERIC,
		.tv_usec = 0
    };
    INT16U countUpdateTime = 1; // To trigger it at first time


	if (0) { pArg = pArg;};

	printf("[ INFO ] - Launch %s\n", __func__);

	nfd = HYVEPLATFORM_MSG_Q_GENERIC_FD;
	nfd++;

	while (1) {
        int ret = -1, i = 0;

        FD_ZERO(&read_set);
        FD_SET(HYVEPLATFORM_MSG_Q_GENERIC_FD, &read_set);

        if ((ret = sigwrap_select(nfd, &read_set, NULL, NULL, &timeout)) < 0) {
        	printf("[%s]: Error in select, ret: %d\n", __func__, ret);
            continue;
        }
        if (SELECT_TIMEOUT == ret) {
// Routine Work --
        	// Pending task check
        	for (i = 0; i < HyvePlatformPT_MAX; i++) {
        		if (g_hyvePlatformPendTasks[i].is_set &&
        				(HYFEPLATFORM_JIFFY_DIFF(g_hyvePlatformPendTasks[i].jiffy) >
        										g_hyvePlatformPendTasks[i].timeout)) {
        			// Execute the callback function
        			if (!g_hyvePlatformPendTasks[i].callback(&g_hyvePlatformPendTasks[i])) {
        				// If success, clear the flag
        				g_hyvePlatformPendTasks[i].is_set = 0;
        			}
        		}
        	}
        	// Update the last time stamp and sync the system time to RTC per hour
            if (!(HYFEPLATFORM_JIFFY % countUpdateTime)) {
    			if (HyveExt_SetLastTimeStamp() < 0) {
    				printf("Error in HyveExt_SetLastTimeStamp\n");
    				countUpdateTime = 1; // later retry
    			} else {
    				countUpdateTime = 3600;
    				HyveExt_SetBmcTimeToRTC();
    			}
            }
            // Chassis intrusion check
            // TODO: implement a chassis intrusion driver instead of reading reg directly
            INT32U regVal = 0;
            if (!HyveExt_BMC_Register(Hyve_RegOp_Read, REG_INTRUSION_CTRL, &regVal)) {
            	static INT8U is_intruded = FALSE;

            	if (!is_intruded && !(regVal & HYVE_BIT(4))) {
                	if (!HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_PHYSICAL_SECURITY,
                			SENSOR_NUM_STS_INTRUSION,
            				((is_intruded << 7)| EVENT_TYPE_SENSOR_SPECIFIC_6F),
            				EVENT_GENERAL_CHASSIS_INTRUSION, 0xFF, 0xFF, 1)) {
                		is_intruded = TRUE;
            		}
            	} else if (is_intruded && (regVal & HYVE_BIT(4))) {
                	if (!HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_PHYSICAL_SECURITY,
                			SENSOR_NUM_STS_INTRUSION,
            				((is_intruded << 7)| EVENT_TYPE_SENSOR_SPECIFIC_6F),
            				EVENT_GENERAL_CHASSIS_INTRUSION, 0xFF, 0xFF, 1)) {
                		is_intruded = FALSE;
            		}
            	}
            }

//-- Routine Work
        	timeout.tv_sec = HyvePlatform_TASK_INTERVAL_GENERIC;
            continue;
        }

        if (FD_ISSET(HYVEPLATFORM_MSG_Q_GENERIC_FD, &read_set)) {
        	HyveMsgQ_T msg;
            ssize_t rcount = sigwrap_read(HYVEPLATFORM_MSG_Q_GENERIC_FD, &msg, sizeof(HyveMsgQ_T));
            if (rcount != sizeof(HyveMsgQ_T)) {
                printf("[%s]: Error in reading msg queue\n", __func__);
                continue;
            }
            printf("msg.msgType:%x msg.msgData: %c\n", msg.msgType, msg.msgData);
// Asynchronous Request --
            switch(msg.msgType)
            {
            case HyvePlatformMsgQ_TEST:
            	break;
            default:
            	break;
            }
//-- Asynchronous Request
        }
	} // end while
	sigwrap_close(HYVEPLATFORM_MSG_Q_GENERIC_FD);
	OS_DELETE_THREAD();
}

/*-----------------------------------------------------------------
 * @fn HyvePlatform_IRQDeferHandler
 * @brief	A platform IRQ defer action task.
 * 			In this task, we can do
 * 				(1) Some time cost IRQ actions
 * 				(2) Also can use the Routine Work area to do some special action/check
 *
 * @param[in]	pArg - A pointer of void, passes BMCInst
 *
 * @return  0	- if thread exits
 *-----------------------------------------------------------------*/
static void* HyvePlatform_IRQDeferHandler(void* pArg)
{
	int BMCInst = (int)pArg;
    int nfd = -1;
    fd_set read_set = {0};
    struct timeval timeout = {
		.tv_sec = HyvePlatform_TASK_INTERVAL_GENERIC,
		.tv_usec = 0
    };

	if (0) { BMCInst = BMCInst; }

	printf("[ INFO ] - Launch %s\n", __func__);

	nfd = HYVEPLATFORM_MSG_Q_IRQ_FD;
	nfd++;
	
	while (1) {
        int ret = -1;

        FD_ZERO(&read_set);
        FD_SET(HYVEPLATFORM_MSG_Q_IRQ_FD, &read_set);

        if ((ret = sigwrap_select(nfd, &read_set, NULL, NULL, &timeout)) < 0) {
        	printf("[%s]: Error in select, ret: %d\n", __func__, ret);
            continue;
        }
        if (SELECT_TIMEOUT == ret) {
// Routine Work --

//-- Routine Work
        	timeout.tv_sec = HyvePlatform_TASK_INTERVAL_GENERIC;
            continue;
        }

        if (FD_ISSET(HYVEPLATFORM_MSG_Q_IRQ_FD, &read_set)) {
        	HyveMsgQ_T msg;
            ssize_t rcount = sigwrap_read(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg, sizeof(HyveMsgQ_T));
            if (rcount != sizeof(HyveMsgQ_T)) {
                printf("[%s]: Error in reading msg queue\n", __func__);
                continue;
            }
            printf("msg.msgType:%x msg.msgData: %x\n", msg.msgType, msg.msgData);
// IRQ Defer Action --
            switch(msg.msgType)
            {
            case HyvePlatformMsgQ_TEST:
            	break;

            case HyvePlatformIRQMsgQ_SysPwrGood:
            	API_InitPowerOnTick(BMCInst);
            	if (!msg.msgData) { // Power Off
        			// Clear & stop FRB2 WDT while Host DC off
            		HyveExt_ClrAndStopFRB2WDT(BMCInst);
            		HyveExt_BIOS_Status(Hyve_VALUE_CLEAN, Hyve_BIOS_NO_ACTIVE);
            		HyvePlatform_Sensor_RstStatAfterPwrOff();
            	}
            	break;

            case HyvePlatformIRQMsgQ_BIOS_POST:
            	if (HYVEPLATFORM_IS_SYS_PWRGOOD) {
					HyveExt_BIOS_Status(Hyve_VALUE_SET,
							(msg.msgData ? Hyve_BIOS_POST_START : Hyve_BIOS_POST_END));
					// TODO: currently, BIOS both trigger the GPIO and send the OEM cmd to set the POST status
					// to void redundant SEL, put the action here, it will be moved to HyvePlatform_BIOS_Status_Callback
					if (!msg.msgData) {
						// Record POST complete SEL
						HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_SYSTEMEVENT,
										SENSOR_NUM_STS_BIOSPOSTCMPT	,
										EVENT_TYPE_SENSOR_SPECIFIC_6F,
										EVENT_OEM_SYSTEM_BOOT_EVENT, 0xFF, 0xFF, BMCInst);
					}
            	}
        		break;

            case HyvePlatformIRQMsgQ_CPU_ThermalTrip:
            {
            	printf("IRQMsgQ_CPU_ThermalTrip, data: %u\n", msg.msgData);
				// Check the CPU temp
				_FAR_ SensorInfo_T *pSensorInfo = API_GetSensorInfo(SENSOR_NUM_TEMP_CPU0, BMC_SENSOR_LUN01, BMCInst);
				if (pSensorInfo && (pSensorInfo-> SensorReading > pSensorInfo->UpperCritical)) {
					// Record SEL
					HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_PROCESSOR,
									SENSOR_NUM_ERR_CPU0THRMTRIP,
									(((!msg.msgData) << 7) | EVENT_TYPE_SENSOR_SPECIFIC_6F),
									EVENT_PROCESSOR_THERMALTRIP, 0xFF, 0xFF, BMCInst);
				}
            }
            	break;

            case HyvePlatformIRQMsgQ_CPU_PROCHOT:
            	printf("IRQMsgQ_CPU_PROCHOT, data: %u\n", msg.msgData);
            	if (msg.msgData) {
            		// TODO
            		// Check the CPU temp

            	} else {
            		// De-asset??
            	}
            	break;

            case HyvePlatformIRQMsgQ_FP_ID_Button:
            	printf("IRQMsgQ_Button, data: %u\n", msg.msgData);
            	if (msg.msgData) {
            		// Turn On
            	} else {
            		// Turn Off
            	}
            	break;

            case HyvePlatformIRQMsgQ_PowerButton:
            	printf("HyvePlatformIRQMsgQ_PowerButton, data: %u\n", msg.msgData);

            	if ((!msg.msgData) ||
            			(msg.msgData && !HYVEPLATFORM_IS_SYS_PWRGOOD)) {
                	// Record button event
            		HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_BUTTON,
									SENSOR_NUM_INFO_BTN, EVENT_TYPE_SENSOR_SPECIFIC_6F,
									EVENT_POWERBUTTON_PRESSED, 0xFF, 0xFF, BMCInst);
                    if (!msg.msgData) {
						// For power off by Button, just record ACPI SEL 
						API_SetACPIState(IPMI_ACPI_S5,BMCInst);
                    } else {
						// In order to sync the state and record SEL
						g_Is_PowerButtonOn = TRUE;
						OnSetRestartCause(RESTART_CAUSE_POWER_BUTTON, TRUE, BMCInst);
						Platform_HostPowerOn(BMCInst);
                    }
            	}
            	break;

            case HyvePlatformIRQMsgQ_ResetButton:
            	printf("HyvePlatformIRQMsgQ_ResetButton, data: %u\n", msg.msgData);
            	if (HYVEPLATFORM_IS_SYS_PWRGOOD) {
            		// In order to sync the state and record SEL
            		OnSetRestartCause(RESTART_CAUSE_RESET_BUTTON, TRUE, BMCInst);
                    Platform_HostColdReset(BMCInst);
                	// Record button event
                    HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_BUTTON,
									SENSOR_NUM_INFO_BTN, EVENT_TYPE_SENSOR_SPECIFIC_6F,
									EVENT_RESETBUTTON_PRESSED, 0xFF, 0xFF, BMCInst);
            	}
            	break;
 
            case HyvePlatformIRQMsgQ_PMBus_ALERT:
            {
            	static INT8U is_asserted = FALSE;

            	if (msg.msgData) { is_asserted = TRUE; }

            	if (is_asserted) {
                	HyveExt_LogEvent(0, BMC_GEN_ID, BMC_SENSOR_LUN01, SENSOR_TYPE_PSU,
    								SENSOR_NUM_PMBUS_ALERT,
    								((msg.msgData << 7) | EVENT_TYPE_SENSOR_SPECIFIC_6F),
    								EVENT_POWER_SUPPLY_FAILURE_DETECTED, 0xFF, 0xFF, BMCInst);
                	// Because the PSU status sensor will record more detail SEL, here just record a very general one
                	is_asserted = FALSE;
            	}
            }
        		break;

            default:
            	break;
            }
//-- IRQ Defer Action
        }
	} // end while
	sigwrap_close(HYVEPLATFORM_MSG_Q_IRQ_FD);
	OS_DELETE_THREAD();
}

void HyvePlatform_GenericTaskStart(void)
{
	g_hyvePlatformMsgQFD = HyveExt_CreateMsgQ(HYVEPLATFORM_MSG_Q_GENERIC_PATH);
	if (HYVEPLATFORM_MSG_Q_GENERIC_FD > 0) {
		OS_CREATE_THREAD(HyvePlatform_GenericTask, NULL, NULL);
	} else {
		// TODO: Maybe should log event?
	}
}

void HyvePlatform_IRQDeferHandlerStart(int BMCInst)
{
	g_hyvePlatformMsgQFD_IRQ = HyveExt_CreateMsgQ(HYVEPLATFORM_MSG_Q_IRQ_PATH);
	if (HYVEPLATFORM_MSG_Q_IRQ_FD > 0) {
		OS_CREATE_THREAD(HyvePlatform_IRQDeferHandler, (void*)BMCInst, NULL);
	} else {
		// TODO: Maybe should log event?
	}
}

void HyvePlatform_FanCtrlTaskStart(int BMCInst)
{
	OS_CREATE_THREAD(HyveFSC_FanCtrlTask, (void*)BMCInst, NULL);
}

void HyvePlatform_PSUTaskStart(int BMCInst)
{
	OS_CREATE_THREAD(HyvePlatform_PSUTask, (void*)BMCInst, NULL);
}

void HyvePlatform_SensorMonitorStart(int BMCInst)
{
	OS_CREATE_THREAD(HyvePlatform_SensorMonitor, (void*)BMCInst, NULL);
}

int HyvePlatformPT_BackupFRU(HyvePlatformPendTask_T* pTask)
{
	static INT8U retry = 0;

	// Currently only consider MB FRU (FRU ID 0)
	if (((HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_CACHE) < 0) ||
			(HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_FLASH) < 0)) &&
			(++retry < 3)) {
		pTask->timeout = 1;
		pTask->jiffy = HYFEPLATFORM_JIFFY;
		return -1;
	}
	retry = 0;

	return 0;
}
