 /******************************************************************
 *
 * @file	HyvePlatformFan.h
 * @brief	The Hyve platform Fan header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMFAN_H_
#define HYVEPLATFORMFAN_H_


/* Note: TODO: The fan direction is not determined yet

	Mother Board
    -----------------------------		--> Out?
    |Front|                |Rear|		<-- In?
    |     |                |    |
    |     |                |    |
    |     |                |    |
    -----------------------------                      */
typedef enum {
	PlatformFanDir_Unkonwn = 0,
	PlatformFanDir_In,
	PlatformFanDir_Out
} HyvePlatformFanDirection;




extern INT8U HyvePlatformFan_GetFanDir();


#endif
