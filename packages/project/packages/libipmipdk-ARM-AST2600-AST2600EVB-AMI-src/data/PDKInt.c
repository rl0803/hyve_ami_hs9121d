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

void PDK_SensorInterruptHandler (IPMI_INTInfo_T *IntInfo);
int gpio_count = 0;

/* Interrupts can be registred manually here or 
     can be done via MDS*/

#define GPIO_INT_SENSOR 0x01

#define GPIO_INT_SENSOR_TYPE    0
#define GPIO_BMC_INT_TEST1      8   //GPIOB0

IPMI_INTInfo_T m_IntInfo [] =
{
 	//{ int_hndlr, int_num, Source, SensorNum, SensorType, TriggerMethod, TriggerType, reading_on_assertion },
    {PDK_SensorInterruptHandler, GPIO_BMC_INT_TEST1, INT_REG_HNDLR, GPIO_INT_SENSOR, GPIO_INT_SENSOR_TYPE, IPMI_INT_TRIGGER_EDGE, IPMI_INT_RISING_EDGE, 0, 0, 0 ,0},
};

int m_IntInfoCount = (sizeof(m_IntInfo)/sizeof(m_IntInfo[0]));

static struct pollfd 	fd_to_watch [IPMI_MAX_INT_FDS];	/* File descriptor to watch for interrupt */
static int	   			m_total_reg_fds = 0;

void PDK_SensorInterruptHandler (IPMI_INTInfo_T *IntInfo)
{
    switch(IntInfo->int_num)
    { 
		case GPIO_BMC_INT_TEST1:
			printf("GPIO_INT_SENSOR\n");
			break;
		default:
			break;
    }
    return;
}

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

    (*pCount) = &m_total_reg_fds;

    void *lib_handle = dlopen(GPIO_LIB, RTLD_NOW);
    if (lib_handle == NULL)
        return -1;
   
    pRegisterInt = dlsym(lib_handle,"register_sensor_interrupts");
    pUnRegisterInt = dlsym(lib_handle,"unregister_sensor_interrupts");
    if (NULL == pRegisterInt || NULL == pUnRegisterInt)
    {
        dlclose(lib_handle);
	lib_handle = NULL;
        return -1;
    }
    if (m_IntInfoCount >= MAX_IPMI_INT)
    {
        /*Not enough space */
        IPMI_WARNING ("Not enough space for INT registration\n");
        dlclose(lib_handle);
	lib_handle = NULL;
        return -1;
    }

	if(0 >= m_IntInfoCount)
	{
	    /*No Interrupts sensor in m_IntInfo table  */
        TDBG("No Interrupts sensor in m_IntInfo table\n");
        dlclose(lib_handle);
	lib_handle = NULL;
	return -1;
	}

    for (i = 0; i < m_IntInfoCount; i++)
    {
	if (INT_SWC_HNDLR != m_IntInfo[i].Source)  /* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */
        {
	       ret = snprintf(commandStrBuf, sizeof(commandStrBuf),SYSFS_GPIO_DIR"/gpio%d/value",(gpio_base+m_IntInfo[i].int_num));/* SCA Fix [Out-of-bounds read]:: False Positive */
           /* Reason for False Positive –  IPMI_INTInfo_T structure array contains one interrupt info only. So i value is always 1 as of now. if any other interruptdetails are added then i value will vary according to no of interrupts in the structure. So there is no issue with existed code. */
            if((ret < 0)||(ret >= (signed int)sizeof(commandStrBuf)))
            {
                IPMI_WARNING ("Buffr Overflow");
                dlclose(lib_handle);
		lib_handle = NULL;
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
                dlclose(lib_handle);
		lib_handle = NULL;
                return -1;
            }
            else
            {
                TDBG("Registering sensor interrupt success\n");
            }

            m_total_reg_fds++;
        }
    }
    dlclose(lib_handle);
    lib_handle = NULL;
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

    int i;

    /* Initialize count */
    (*pfd)              = &fd_to_watch [0];

    /* Initialize all FDs */
    memset (&fd_to_watch[0], 0 , (sizeof (struct pollfd) * IPMI_MAX_INT_FDS));
    //open the gpio driver
    gpio_desc = open( GPIO_CTL_FILE, O_RDWR );
    if(gpio_desc == -1)
    {
        printf("opening gpio device failed\n");
        return -1;
    }

    for(i = 0;i < m_total_reg_fds; i++)
    {
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
