 /******************************************************************
 *
 * @file	HyvePlatformMuxCtrl.h
 * @brief	The Hyve platform Mux Control header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMMUXCTRL_H_
#define HYVEPLATFORMMUXCTRL_H_

extern int HyvePlatform_LockMux(const INT8U muxIndex, const INT16U retryInterval);
extern int HyvePlatform_UnlockMux(const INT8U muxIndex);
extern int HyvePlatform_MuxCtrl(const INT8U muxIndex, const INT8U channel, const INT16U retryInterval);

#endif
