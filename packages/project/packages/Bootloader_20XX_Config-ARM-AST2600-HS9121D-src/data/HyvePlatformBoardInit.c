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




int HyvePlatformBoardInit(void)
{
    printf("[%s] ...\n",__FUNCTION__);
    return 0;
}
