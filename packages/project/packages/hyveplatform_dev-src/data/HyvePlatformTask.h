 /******************************************************************
 *
 * @file	HyvePlatformTask.h
 * @brief	The Hyve platform task header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMTASK_H_
#define HYVEPLATFORMTASK_H_


/********************* Hyve platform message queue *********************/
typedef enum {
/* Generic Message Type */
	HyvePlatformMsgQ_TEST = 0,
	
/* IRQ Message Type */
	HyvePlatformIRQMsgQ_SysPwrGood,
	HyvePlatformIRQMsgQ_CPU_ThermalTrip,
	HyvePlatformIRQMsgQ_CPU_PROCHOT,
	HyvePlatformIRQMsgQ_FP_ID_Button,
	HyvePlatformIRQMsgQ_APML_ALERT,
	HyvePlatformIRQMsgQ_PowerButton,
	HyvePlatformIRQMsgQ_ResetButton,
	HyvePlatformIRQMsgQ_PMBus_ALERT,
	HyvePlatformIRQMsgQ_SMBus_ALERT,
} HyvePlatformMsgQ_Type;

typedef enum {
	HyvePlatformPT_BACKUPFRU = 0,
	HyvePlatformPT_MAX
} HyvePlatformPendTaskIndex;

typedef struct HyvePlatformPendTask_T HyvePlatformPendTask_T;
typedef int (*HyvePlatformPendTask) (HyvePlatformPendTask_T* pTask);
struct HyvePlatformPendTask_T {
	INT8U is_set;	// the flag to indicate the pending task is set or not
	INT8U timeout;	// the timeout to trigger the pending task, unit: second
	INT32U jiffy;	// the platform jiffy to record 'when' this task is set
	INT32U data;	// Just simply pass a 4-Byte data,
					// if need to pass more, please use other mechanism to do it
	HyvePlatformPendTask callback;	// the callback function
};






#define HyvePlatform_TASK_INTERVAL_GENERIC			(1)	// 1 second

// DO NOT use these variables directly, use the MACROs instead
extern int g_hyvePlatformMsgQFD;
extern int g_hyvePlatformMsgQFD_IRQ;

#define HYVEPLATFORM_MSG_Q_GENERIC_FD       		((const int)g_hyvePlatformMsgQFD)
#define HYVEPLATFORM_MSG_Q_IRQ_FD       			((const int)g_hyvePlatformMsgQFD_IRQ)

extern void HyvePlatform_SetPendTask(const INT16U taskIndex, INT8U timeout, const INT32U data);
extern INT8U HyvePlatform_Is_PendTaskSet(const INT16U taskIndex);

/********************* Hyve platform tasks *********************/
extern void HyvePlatform_GenericTaskStart(void);
extern void HyvePlatform_IRQDeferHandlerStart(int BMCInst);
extern void HyvePlatform_FanCtrlTaskStart(int BMCInst);
extern void HyvePlatform_PSUTaskStart(int BMCInst);
extern void HyvePlatform_SensorMonitorStart(int BMCInst);

/********************* Hyve platform pend task call-back functions *********************/
// Note: All platform pend task call-back functions must return "0", if success.
extern int HyvePlatformPT_BackupFRU(HyvePlatformPendTask_T* pTask);



#endif
