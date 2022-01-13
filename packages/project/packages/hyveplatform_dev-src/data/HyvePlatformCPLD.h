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

typedef enum {
	ButtonHostPower = 0,
	ButtonHostReset,
	Button_MAX
} HyvePlatformButtonIndex;





#endif
