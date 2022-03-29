 /******************************************************************
 *
 * @file	HyvePlatformBoardInit.c
 * @brief	Provide a flexible hook function for platform board initialization
 *
 * @author	Alan Wang <alanw@Hyvedesignsolutions.com>
 *  
 ******************************************************************/

#include <common.h>
#include <dm.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <linux/err.h>
#include <dm/uclass.h>



#define REG_HICR5						(0x1E789080)


int HyvePlatformBoardInit(void)
{
    printf("[%s] ...\n",__FUNCTION__);

/* To fix kernel SOC init fail causing by snoop controller not disabled,
	 if previous BMC warm reboot during BIOS POST
	 Disable
		 1. snoop & snoop IRQ
		 2. ACCEPT response code for snoop #0 commands
		 3. port 80 to SGPIO/GPIO                                       */
	*(volatile u32 *)(REG_HICR5) &= (~0xC0004003);

    return 0;
}
