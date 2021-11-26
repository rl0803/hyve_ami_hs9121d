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

#include "Platform.h" //Alan, Test chassis power
#include "ChassisCtrl.h"


#include "HyveCommon.h"


#define HYVEPLATFORM_MSG_Q_GENERIC_PATH				"/var/.hyvePlatformMsgQ1"
#define HYVEPLATFORM_MSG_Q_IRQ_PATH					"/var/.hyvePlatformMsgQ2"

/********************* Global variable definitions *********************/
int g_hyvePlatformMsgQFD = -1;
int g_hyvePlatformMsgQFD_IRQ = -1;

static HyvePlatformPendTask_T g_hyvePlatformPendTasks[HyvePlatformPT_MAX] = {
	// { is_set ,timeout ,jiffy, data, callback }
	{ 0, 1, 0, 0, HyvePlatformPT_BackupFRU },
};


/*
HS1811D tasks
	HyvePlatform_TimerTask
	
	HyveFSC_TimerTask									<--- Fan task
	HyveMonit_SingleOuput_PMBusPollingThreadStart		<--- PSU task (sensor monitor and PSU FW update)
	HyveMonit_TriggerStatusPollingThreadStart			<--- kind of a pending task(Use select + Msg Queue)
	HyveMonit_PlatformSensorMonitor						<--- Sensor monitor(may need one or more depends on platform)
	
	HyveMonit_Early_VGA
	
	Redfish workaround task:
		HyveRedfish_TimerTask
		HyveMonit_SyncAgentHealthMonitorThreadStart
	
	
New task:
	IRQ_deferHandler

For Intel platform:
	PCH and ME task


HS9121D tasks
	PDK_TimerTask					(Use this task to provide one second time-tick count instead using time())
	HyvePlatform_GenericTask		(previous HyvePlatform_TimerTask + HyveMonit_TriggerStatusPollingThreadStart)
									(Use select + Msg Queue to handle platform pending task)
	HyvePlatform_IRQDeferHandler	(Use select + Msg Queue to handle IRQ actions)
	HyvePlatform_FanCtrlTask		(previous HyveFSC_TimerTask)
	HyvePlatform_PSUTask			(previous HyveMonit_SingleOuput_PMBusPollingThreadStart, responsible for sensor monitoring and PSU FW update)
	HyvePlatform_SensorMonitor		(Sensor monitor(may need one or more depends on platform))
	HyvePlatform_SensorMonitor_BP

*/



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
            
            case HyvePlatformIRQMsgQ_PowerButton:
            	printf("IRQMsgQ_Button, data: %u\n", msg.msgData);
            	if (msg.msgData) {
                    OnSetRestartCause(RESTART_CAUSE_POWER_BUTTON, TRUE, BMCInst);
                    Platform_HostPowerOn(BMCInst);
            	} else {
            		Platform_HostPowerOff(BMCInst);
            	}
            	break;
            	
            case HyvePlatformIRQMsgQ_ResetButton:
            	printf("IRQMsgQ_Button, data: %u\n", msg.msgData);
            	if (msg.msgData) {
                    OnSetRestartCause(RESTART_CAUSE_RESET_BUTTON, TRUE, BMCInst);
                    Platform_HostPowerOn(BMCInst);
            	} else {
            		Platform_HostPowerOff(BMCInst);
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
	HYVE_KEYWORDS(ambSensors, "AMB", "Outlet");
	HYVE_KEYWORDSLIST(listKW_amb,
					HYVE_KEYWORDSLIST_PUT(ambSensors));

	HYVE_KEYWORDS(curve0, "CPU");
	HYVE_KEYWORDS(curve1, "DIMM");
	HYVE_KEYWORDS(curve2, "OCP", "CARD");
	HYVE_KEYWORDS(curve3, "NVMe", "SSD");
	HYVE_KEYWORDSLIST(listKW_curves, 
					HYVE_KEYWORDSLIST_PUT(curve0),
					HYVE_KEYWORDSLIST_PUT(curve1),
					HYVE_KEYWORDSLIST_PUT(curve2),
					HYVE_KEYWORDSLIST_PUT(curve3));

	if (HyveFSC_Init(BMCInst, listKW_amb, listKW_curves) < 0) {
		if (HyveFSC_SetAllFanDuty(FULL_FANDUTY) < 0) {
			printf("[%s]: Error in setting all fan full duty\n", __func__);
		}
	}
	// Even if FSC_Init failed, we still can launch the FSC task
	// to allow a user can control fan speed via IPMI OEM cmds
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
	if ((HyveFRU_FRUBackup(HYFEPLATFORM_MB_FRU_ID, HYVE_STORETYPE_CACHE) < 0) && (++retry < 3)) {
		pTask->timeout = 1;
		pTask->jiffy = HYFEPLATFORM_JIFFY;
		return -1;
	}
	retry = 0;

	return 0;
}
