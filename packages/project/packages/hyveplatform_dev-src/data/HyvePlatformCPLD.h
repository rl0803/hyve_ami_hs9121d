 /******************************************************************
 *
 * @file	HyvePlatformCPLD.h
 * @brief	The Hyve platform CPLD header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMCPLD_H_
#define HYVEPLATFORMCPLD_H_

typedef enum {
	JTAG_MUX_CPLD = 0,
	JTAG_MUX_RISER
} HyvePlatformJTAGMuxIndex;


extern int HyvePlatformCPLD_Inform_FwAuthComplete(const INT8U op, INT8U* pIs_asserted);

#endif
