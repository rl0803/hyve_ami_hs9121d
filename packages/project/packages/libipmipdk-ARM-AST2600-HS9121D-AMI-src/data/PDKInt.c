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
 * PDKInt.c
 *
 * @brief Handles the OEM defined Interrupts.
 *
 *****************************************************************/
#define ENABLE_DEBUG_MACROS 0


#include "PDKInt.h"
#include "PDKHW.h"
#include "hal_hw.h"
#include "API.h"
#include <dlfcn.h>
#include "gpio.h"
#include "gpioifc.h"

#define SYSFS_GPIO_DIR          "/sys/class/gpio"
#define MAX_BUF                 40


/*-----------------------------------------------------------------
 * @fn HyvePlatform_BeforeIRQhndlrInit
 * @brief	To do specific init process before the platform IRQ handler init
 *          to avoid racing condition while GPIO irq handler registering
 *
 * @param None
 *
 * @return    None
 *-----------------------------------------------------------------*/
static void HyvePlatform_BeforeIRQhndlrInit()
{
	printf("%s\n", __func__);
	// Init global flags
	PDK_GetPSGood(1);
	HyvePlatform_Is_CPU_PwrGood();
	HyvePlatform_Is_PSU_PwrGood();
	HyvePlatform_has_DIMMOwership();
	HyvePlatform_Is_HostInS3();
	HyvePlatform_Is_HostInS5();
}


/* Platform Interrupt Handler */
void IRQhndlr_PCIE_P2_MCIO1_ALERT_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_PCIE_P3_MCIO2_ALERT_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_XGMI_G2_AIC1_ALERT_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_XGMI_G3_AIC2_ALERT_N(IPMI_INTInfo_T *IntInfo);

void IRQhndlr_FP_ID_BTN_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_CLK_100M_9DML0455_CLKIN_LOS_N(IPMI_INTInfo_T *IntInfo);

void IRQhndlr_CPU_THERMAL_TRIP_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_CPU_PROCHOT_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_CPU_SMERR_L(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_APML_ALERT_L(IPMI_INTInfo_T *IntInfo);

void IRQhndlr_PWRGD_SYS_PWROK(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_PWRGD_PSU_PWROK(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_PWRGD_CPU_PWROK(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_SPD_HOST_CTRL_L(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_CPU_S3_STATE_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_CPU_S5_STATE_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_BIOS_POST_START(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_BIOS_POST_END(IPMI_INTInfo_T *IntInfo);

void IRQhndlr_PCIE_P1_RISER_ALERT_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_TEMP_I2C_ALERT_L(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_PMBusALERT_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_SMBUS_ALERT(IPMI_INTInfo_T *IntInfo);

void IRQhndlr_PWRBTN_IN_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_RST_SYSTEM_BTN_IN_N(IPMI_INTInfo_T *IntInfo);

// From CPLD
void IRQhndlr_RST_RSMRST_BMC_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_PLTRST_BMC_IN_N(IPMI_INTInfo_T *IntInfo);
// From ROT
void IRQhndlr_EC_BMC_AP1_RESET_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_EC_BMC_FATAL_ERROR_N(IPMI_INTInfo_T *IntInfo);
void IRQhndlr_FM_CEC_BIOS_AUTH_COMP(IPMI_INTInfo_T *IntInfo);


IPMI_INTInfo_T m_IntInfo [] =
{
 	//{ int_hndlr, int_num, Source, SensorNum, SensorType, TriggerMethod, TriggerType, reading_on_assertion, gpioValue },
    { IRQhndlr_PCIE_P2_MCIO1_ALERT_N, IO_PCIE_P2_MCIO1_ALERT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_PCIE_P2_MCIO1_ALERT_N, IO_PCIE_P3_MCIO2_ALERT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_XGMI_G2_AIC1_ALERT_N, IO_XGMI_G2_AIC1_ALERT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_XGMI_G3_AIC2_ALERT_N, IO_XGMI_G3_AIC2_ALERT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_FP_ID_BTN_N, IO_FP_ID_BTN_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_CLK_100M_9DML0455_CLKIN_LOS_N, IO_CLK_100M_9DML0455_CLKIN_LOS_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_CPU_THERMAL_TRIP_N, IO_FM_P0_CPLD_THERMTRIP_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, FALLING_EDGE, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_CPU_PROCHOT_N, IO_P0_PROCHOT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_CPU_SMERR_L, IO_P0_SMERR_L, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_APML_ALERT_L, IO_P0_BMC_APML_ALERT_L, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, FALLING_EDGE, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_PWRGD_SYS_PWROK, IO_PWRGD_SYS_PWROK_BMC, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_PWRGD_PSU_PWROK, IO_PWRGD_PS_PWROK_BMC, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_PWRGD_CPU_PWROK, IO_P0_PWRGD, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_SPD_HOST_CTRL_L, IO_P0_SPD_HOST_CTRL_L, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_RST_RSMRST_BMC_N, IO_RST_RSMRST_BMC_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_PLTRST_BMC_IN_N, IO_PLTRST_BMC_IN_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_EC_BMC_AP1_RESET_N, IO_EC_BMC_AP1_RESET_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_EC_BMC_FATAL_ERROR_N, IO_EC_BMC_FATAL_ERROR_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_FM_CEC_BIOS_AUTH_COMP, IO_FM_CEC_BIOS_AUTH_COMP, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_PWRBTN_IN_N, IO_FM_BMC_PWRBTN_IN_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_RST_SYSTEM_BTN_IN_N, IO_RST_SYSTEM_BTN_IN_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, FALLING_EDGE, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_PCIE_P1_RISER_ALERT_N, IO_PCIE_P1_RISER_ALERT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_TEMP_I2C_ALERT_L, IO_TEMP_I2C_ALERT_L, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    
    { IRQhndlr_CPU_S3_STATE_N, IO_PLD_BMC_SLP_S3_L, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_CPU_S5_STATE_N, IO_PLD_BMC_SLP_S5_L, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },

    { IRQhndlr_PMBusALERT_N, IO_PSU_SMB_ALERT_N, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_SMBUS_ALERT, IO_P0_SMBUS_ALERT, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    
    { IRQhndlr_BIOS_POST_START, IO_FM_P0_BMC_START_POST, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },
    { IRQhndlr_BIOS_POST_END, IO_FM_P0_BMC_START_END, INT_REG_HNDLR, 0xFF, NON_THRESHOLD_SENSOR, IPMI_INT_TRIGGER_EDGE, BOTH_EDGES, 0, 0, 0 ,0 ,0 },  
};

int m_IntInfoCount = (sizeof(m_IntInfo)/sizeof(m_IntInfo[0]));

static struct pollfd 	fd_to_watch [IPMI_MAX_INT_FDS];	/* File descriptor to watch for interrupt */
static int	   			m_total_reg_fds = 0;



/*-------------------------------------------------------------------------
 * @fn PDK_RegGPIOInts
 * @brief This function is called by the core Interrupt Task initialization
 *------------------------------------------------------------------------*/
int
PDK_RegGPIOInts(int fd, int BMCInst, int pinNum[IPMI_MAX_INT_FDS], int **pCount, int gpio_base)
{
    UN_USED(BMCInst);

    int i = 0, ret = 0;
    interrupt_sensor_info gpio_intr[MAX_IPMI_INT];
    int (*pRegisterInt) (interrupt_sensor_info *,unsigned int, int);
    int (*pUnRegisterInt) (int, interrupt_sensor_info *);
    char commandStrBuf[MAX_BUF] = {0};
    void *lib_handle = NULL;

    (*pCount) = &m_total_reg_fds;

    HyvePlatform_BeforeIRQhndlrInit();

    // Because the gpiolib has already loaded, no need to load it again 
    pRegisterInt = (int (*) (interrupt_sensor_info *,unsigned int, int))g_HALGPIOHandle[HAL_GPIO_REGISTER_SENSOR_INTERRUPTS];
    pUnRegisterInt = (int (*) (int, interrupt_sensor_info *))g_HALGPIOHandle[HAL_GPIO_UNREGISTER_SENSOR_INTERRUPTS];
    if (NULL == pRegisterInt || NULL == pUnRegisterInt) {
        lib_handle = dlopen(GPIO_LIB, RTLD_NOW);
        if (lib_handle == NULL) {
        	return -1;
        }
        pRegisterInt = dlsym(lib_handle,"register_sensor_interrupts");
        pUnRegisterInt = dlsym(lib_handle,"unregister_sensor_interrupts");
        if (NULL == pRegisterInt || NULL == pUnRegisterInt) {
    		dlclose(lib_handle);
    		lib_handle = NULL;
            return -1;
        }
    }

    if (m_IntInfoCount >= MAX_IPMI_INT)
    {
		/*Not enough space */
		IPMI_WARNING ("Not enough space for INT registration\n");
	    if (lib_handle) {
	        dlclose(lib_handle);
	        lib_handle = NULL;
	    }
		return -1;
    }

	if(0 >= m_IntInfoCount)
	{
		/*No Interrupts sensor in m_IntInfo table  */
		TDBG("No Interrupts sensor in m_IntInfo table\n");
	    if (lib_handle) {
	        dlclose(lib_handle);
	        lib_handle = NULL;
	    }
		return -1;
	}

    for (i = 0; i < m_IntInfoCount; i++)
    {
    	if (INT_SWC_HNDLR != m_IntInfo[i].Source)  /* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */
        {
			// Check the direction
			if (HYVE_GPIO_DIR_IN != HyveExt_GPIO_Get_Dir(m_IntInfo[i].int_num)) {
				if (HyveExt_GPIO_Set_Dir_Input(m_IntInfo[i].int_num) < 0) {
					printf("[Error] %s: Unable to set GPIO(%d) input\n", __func__, m_IntInfo[i].int_num);
					continue;
				}
			}

	       ret = snprintf(commandStrBuf, sizeof(commandStrBuf),SYSFS_GPIO_DIR"/gpio%d/value",(gpio_base+m_IntInfo[i].int_num));/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */
            if((ret < 0)||(ret >= (signed int)sizeof(commandStrBuf)))
            {
				IPMI_WARNING ("Buffer Overflow");
			    if (lib_handle) {
			        dlclose(lib_handle);
			        lib_handle = NULL;
			    }
				return -1;
            }

            if (access(commandStrBuf, F_OK) == 0)
            {
                //Cleanup any previous interrupt registration
                if (0 != pUnRegisterInt(fd, &gpio_intr[m_total_reg_fds]))
                {
                    IPMI_WARNING ("No old interrupts need to be registered to clear\n");
                }
            }

            /* Check if this registration is for GPIO driver */
            /* Registration specific for GPIO */
	                gpio_intr[m_total_reg_fds].int_num            = m_IntInfo[i].int_num;/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */

            gpio_intr[m_total_reg_fds].gpio_number        = m_IntInfo[i].int_num;/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */

            gpio_intr[m_total_reg_fds].sensor_number      = m_IntInfo[i].SensorNum;/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */

            gpio_intr[m_total_reg_fds].trigger_method     = m_IntInfo[i].TriggerMethod;/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */

            gpio_intr[m_total_reg_fds].trigger_type       = m_IntInfo[i].TriggerType;/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */ 

            pinNum[m_total_reg_fds] = m_IntInfo[i].int_num;  /* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */

            /* Register GPIO interrupts */
            if ( -1 == pRegisterInt (&gpio_intr[m_total_reg_fds], m_total_reg_fds, fd) )
            {
				IPMI_WARNING ("GPIO Interrupt registration failed \n");
			    if (lib_handle) {
			        dlclose(lib_handle);
			        lib_handle = NULL;
			    }
				return -1;
            }
            else
            {
                TDBG("Registering sensor interrupt success\n");
            }

            m_total_reg_fds++;
        }
    }
    if (lib_handle) {
        dlclose(lib_handle);
        lib_handle = NULL;
    }

    return 0;
}

/*-------------------------------------------------------------------------
 * @fn PDK_RegIntFDs
 * @brief This function is called by the core Interrupt Task initialization
 *------------------------------------------------------------------------*/
int
PDK_RegIntFDs ( struct pollfd **pfd, int BMCInst, int ret[IPMI_MAX_INT_FDS], int gpio_desc)
{
    UN_USED(BMCInst);
    UN_USED(gpio_desc);

    int i = 0;

    /* Initialize count */
    (*pfd)  = &fd_to_watch [0];

    /* Initialize all FDs */
    memset (&fd_to_watch[0], 0 , (sizeof (struct pollfd) * IPMI_MAX_INT_FDS));

    for (i = 0; i < m_total_reg_fds; i++) {
        fd_to_watch [i].fd        = ret[i];
        fd_to_watch [i].events    = POLLPRI;
    }
    return 0;
}

/*-------------------------------------------------------------------------
 * @fn PDK_CheckForInt
 * @brief This function is called by the porting code for any
 *        interrupt initialization
 *------------------------------------------------------------------------*/
IPMI_INTInfo_T*
PDK_GetIntInfo (int BMCInst, int FdNum)
{
    UN_USED(BMCInst);

    return &m_IntInfo[FdNum];

}

/* Platform Interrupt Handler */
void IRQhndlr_PCIE_P2_MCIO1_ALERT_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_PCIE_P3_MCIO2_ALERT_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_XGMI_G2_AIC1_ALERT_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_XGMI_G3_AIC2_ALERT_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_PWRGD_SYS_PWROK(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }

	g_Is_DCPowerOn = (IntInfo->gpioValue & 0x01);
	msg.msgType = HyvePlatformIRQMsgQ_SysPwrGood;
	msg.msgData = HYVEPLATFORM_IS_SYS_PWRGOOD;
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, IntInfo->gpioValue);
	}
}

void IRQhndlr_PWRGD_PSU_PWROK(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }

	g_Is_PSUPwrGood = (IntInfo->gpioValue & 0x01);
	// TODO: Check if one of the two PSU unplugged this pin will be triggered or not
	// redundant check
}

void IRQhndlr_PWRGD_CPU_PWROK(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }

	g_Is_CPUPwrGood = (IntInfo->gpioValue & 0x01);
}

void IRQhndlr_CPU_THERMAL_TRIP_N(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }

	msg.msgType = HyvePlatformIRQMsgQ_CPU_ThermalTrip;
	msg.msgData = ((~IntInfo->gpioValue) & 0x01); // convert the alert value
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	}
}

/*
The AMD CPU PROHOT is input pin fed by CPLD,
But CPLD determines this pin by BMC VR alert pin,
So, in other words, BMC control PROHOT ...

And BMC can "Read PROCHOT Status" from APML, that's pretty weird

*/
void IRQhndlr_CPU_PROCHOT_N(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }

	msg.msgType = HyvePlatformIRQMsgQ_CPU_PROCHOT;
	msg.msgData = ((~IntInfo->gpioValue) & 0x01); // convert the alert value
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	}
}

void IRQhndlr_CPU_SMERR_L(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }

	g_Is_PSUPwrGood = (IntInfo->gpioValue & 0x01);
}

void IRQhndlr_FP_ID_BTN_N(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }

	msg.msgType = HyvePlatformIRQMsgQ_FP_ID_Button;
	msg.msgData = ((~IntInfo->gpioValue) & 0x01); // convert the alert value
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	}
}

void IRQhndlr_CLK_100M_9DML0455_CLKIN_LOS_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

// From CPLD, purpose TBD
void IRQhndlr_RST_RSMRST_BMC_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

// From CPLD, purpose TBD
void IRQhndlr_PLTRST_BMC_IN_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_APML_ALERT_L(IPMI_INTInfo_T *IntInfo)
{
	// HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }
	// printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	
	// msg.msgType = HyvePlatformIRQMsgQ_APML_ALERT;
	// if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
	// 	printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	// }
}

void IRQhndlr_SPD_HOST_CTRL_L(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }

	// Low: to inform the BMC the owner-ship of DIMMs is CPU
	g_Is_DIMM_Ready = (IntInfo->gpioValue & 0x01);
	/* Use the GPIO pin SPD_HOST_CTRL_L as the BIOS POST start pin.
		Because during POST the DIMM ownership belongs to the Host until POST end */ 
	if (!g_Is_DIMM_Ready) {
		msg.msgType = HyvePlatformIRQMsgQ_BIOS_POST;
		msg.msgData = Hyve_BIOS_POST_START;
		if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
			printf("%s: Error in posting IRQ signal(%u)\n", __func__, msg.msgData);
		}
	}
	// printf("DIMM SPD ownership is %s\n", HYVEPLATFORM_IS_DIMM_READY ? "BMC" : "Host");
}

void IRQhndlr_EC_BMC_AP1_RESET_N(IPMI_INTInfo_T *IntInfo)
{
	// Can use the FM_CEC_BIOS_AUTH_COMP instead
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_EC_BMC_FATAL_ERROR_N(IPMI_INTInfo_T *IntInfo)
{
	// Can use the FM_CEC_BIOS_AUTH_COMP instead
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_FM_CEC_BIOS_AUTH_COMP(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
}

void IRQhndlr_PWRBTN_IN_N(IPMI_INTInfo_T *IntInfo)
{
	static UINT32 jiffy_BtnOn = 0;
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }
	printf("%s: assert: %u \n", __func__, ((~IntInfo->gpioValue) & 0x01));

	
	// The power button behavior
	// Clicking: Power On
	// Press over 3 ~ 6 seconds: Power Off
	if (!IntInfo->gpioValue) {
		// button pressed, record the current platform jiffy count value 
		jiffy_BtnOn = HYFEPLATFORM_JIFFY;
	} else {
		// button released, calc. the time diff
		if (HYFEPLATFORM_JIFFY_DIFF(jiffy_BtnOn) < 2) {
			msg.msgData = 1; // it's to trigger power on
		}
	msg.msgType = HyvePlatformIRQMsgQ_PowerButton;
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
		}
	}
}

void IRQhndlr_RST_SYSTEM_BTN_IN_N(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }
	printf("%s: assert: %u \n", __func__, ((~IntInfo->gpioValue) & 0x01));

	g_Is_ResetButtonOn = TRUE;

	msg.msgType = HyvePlatformIRQMsgQ_ResetButton;
	msg.msgData = 1;
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	}
}

void IRQhndlr_PCIE_P1_RISER_ALERT_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	// SMBus Alert from the Riser Card
}

void IRQhndlr_TEMP_I2C_ALERT_L(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	// there are 3 Thermal sensors can fire it.
	//  Alert from thermal sensors, need to send I2C cmd to check which one sent
}

void IRQhndlr_CPU_S3_STATE_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	g_Is_HostIn_S3_State = ((~IntInfo->gpioValue) & 0x01);
}

void IRQhndlr_CPU_S5_STATE_N(IPMI_INTInfo_T *IntInfo)
{
	if (!IntInfo) { return; }
	g_Is_HostIn_S5_State = ((~IntInfo->gpioValue) & 0x01);
}

void IRQhndlr_PMBusALERT_N(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }
	
	msg.msgType = HyvePlatformIRQMsgQ_PMBus_ALERT;
	msg.msgData = ((~IntInfo->gpioValue) & 0x01);
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	}
}

void IRQhndlr_SMBUS_ALERT(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }

	printf("%s: assert: %u\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	
	msg.msgType = HyvePlatformIRQMsgQ_SMBus_ALERT;
	msg.msgData = ((~IntInfo->gpioValue) & 0x01);
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		printf("%s: Error in posting IRQ signal(%u)\n", __func__, ((~IntInfo->gpioValue) & 0x01));
	}
}

void IRQhndlr_BIOS_POST_START(IPMI_INTInfo_T *IntInfo)
{
	printf("%s: assert: %u\n", __func__, (IntInfo->gpioValue & 0x01));
	// Note: this POST start is controlled by BIOS FW
}

void IRQhndlr_BIOS_POST_END(IPMI_INTInfo_T *IntInfo)
{
	HyveMsgQ_T msg = {0};

	if (!IntInfo) { return; }
	printf("%s: assert: %u\n", __func__, (IntInfo->gpioValue & 0x01));

	// Low: to inform the BMC the BIOS POST end
	if (!(IntInfo->gpioValue & 0x01)) {
		msg.msgType = HyvePlatformIRQMsgQ_BIOS_POST;
		msg.msgData = Hyve_BIOS_POST_END;
		if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
			printf("%s: Error in posting IRQ signal(%u)\n", __func__, msg.msgData);
		}
	}
}
