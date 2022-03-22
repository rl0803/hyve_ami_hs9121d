 /******************************************************************
 *
 * @file	HyvePlatformCmds.c
 * @brief	Provide Hyve Platform IPMI OEM commands
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"
#include "hal_hw.h"


#include "HyveCommon.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>

/*-----------------------------------------------------------------
 * @fn HyveCmd_DummyIRQ_Cmd		[Test code]
 * 
 * @brief	CMD_DUMMY_IRQ, NetFn 0x30 Command 0xFE
 * 
 * @return  Numbers of Response
 *-----------------------------------------------------------------*/
int HyveCmd_DummyIRQ_Cmd(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes, _NEAR_ int BMCInst)
{
	HyveMsgQ_T msg = {0};
	int resLen = 1;

    if (0) {
    	BMCInst = BMCInst;
    	ReqLen = ReqLen;
    }
	
    switch (pReq[0]) {
    case 0:
    	msg.msgType = HyvePlatformIRQMsgQ_PowerButton;
    	msg.msgData = pReq[1];
    	break;

    case 1:
    	msg.msgType = HyvePlatformIRQMsgQ_ResetButton;
    	msg.msgData = pReq[1];
    	break;

    case 3:
    	printf("%s: Alan Test...BIOS flash\n", __func__);
    	{
//    		HyveBIOS_PrepareUpdate();
    		

#define HYVE_MTD_DETECT		_IOW('M', 31, int)		// The mtd ioctl cmd to detect flash chip

	{
	char MTD_Device[32] = {0};
	int data = 0, fd , retval = 0;
		
	snprintf(MTD_Device, sizeof(MTD_Device),"/dev/mtd%d", pReq[1]);
	fd = sigwrap_open(MTD_Device, O_RDWR);
		
		if (fd < 0) {
			printf("%s: open %s failed (%s)\n", __func__, MTD_Device, strerror(errno));
			return -1;
		}
		retval = ioctl(fd, HYVE_MTD_DETECT, &data);
		sigwrap_close(fd);
		if (retval < 0) {
			printf("%s: Unable to IOCTL(HYVE_MTD_DETECT), error (%s)\n", __func__, strerror(errno));
		}
	}
//	HyvePlatform_AfterBIOSFlash(1);
    		
    	}
    	
    	
    	break;    	

    case 4: // read POST code

    {
    	u8 PostCodeBuf[512] = {0};
    	hal_t phal;
    	int	rd_len=0, i;

    	INT8U *resdata = &pRes[1];
    	
    	printf ("Starting to Read Current PostCode buffer...\n");
    	phal.read_len = sizeof (PostCodeBuf);
    	phal.pread_buf = PostCodeBuf;
    	rd_len=snoop_read_current_bios_code (&phal);
    	if (-1 == rd_len) {
    		printf ("Error Reading Current PostCode buffer...\n");
    	} else if (rd_len)
    	{
    		printf ("Current Post Codes are ...\n");
    		for (i = 0; i < rd_len; i++)
    		{
    			printf ("0x%02x ", phal.pread_buf[i]);
    			resdata[i] = phal.pread_buf[i];
    		}
    		printf ("\n");
    		resLen = 1 + rd_len;
    	}
    	else
    		printf ("No Post Codes ...\n");
    }
    	break;  
    case 5:
    {
    	INT8U BiosSelect = 0;
    	HyveBIOS_UpdateTarget(Hyve_VALUE_GET, &BiosSelect);
    	printf("Current BIOS flash %s\n", BiosSelect ? "2nd" : "1st");
    	BiosSelect = pReq[1];
    	HyveBIOS_UpdateTarget(Hyve_VALUE_SET, &BiosSelect);
    	HyveBIOS_UpdateTarget(Hyve_VALUE_GET, &BiosSelect);
    	printf("Current BIOS flash %s\n", BiosSelect ? "2nd" : "1st");
    }
    break;
    default:
    	pRes[0] = CC_PARAM_OUT_OF_RANGE;
		return 1;
    	break;
    }
	pRes[0] = CC_NORMAL;
	if (HyveExt_PostMsg(HYVEPLATFORM_MSG_Q_IRQ_FD, &msg) < 0) {
		pRes[0] = CC_UNSPECIFIED_ERR;
	}

	return resLen;
}

