 /******************************************************************
 *
 * @file	HyvePlatformMuxCtrl.c
 * @brief	The Hyve platform Mux Control related functions
 *
 ******************************************************************/

#include "IPMIConf.h"
#include "IPMIDefs.h"

#include "HyveCommon.h"



/********************* Type definitions *********************/
typedef struct {
	INT8U busNum;
	INT8U slave_addr;
	int (*pFunc) (const INT8U, const INT8U, const INT8U);
} HyvePlatformMuxObj_T;

/********************* Global variable definitions *********************/
static INT8U g_lock_Mux[I2CMUXIndex_MAX] = {0};

/******************** Functions ************************************/
// Currently just simply use static variable as a lock (If this not work, then use mutex)
int HyvePlatform_LockMux(const INT8U muxIndex, const INT16U retryInterval)
{
	INT8 retryCount = 0;

	if (muxIndex >= I2CMUXIndex_MAX) { return -1; }
	for (retryCount = 0; (1 == g_lock_Mux[muxIndex]) && (retryCount < 3); retryCount++) {
		usleep(retryInterval);
	}
	if (retryCount >= 3) {
		printf("[%s] fail to get lock! Mux Index: %u\n", __func__, muxIndex);
		return -1;
	}
	g_lock_Mux[muxIndex] = 1;
	return 0;
}

int HyvePlatform_UnlockMux(const INT8U muxIndex)
{
	if (muxIndex < I2CMUXIndex_MAX)
		g_lock_Mux[muxIndex] = 0;
	return 0;
}

int HyvePlatform_MuxCtrl(const INT8U muxIndex, const INT8U channel, const INT16U retryInterval)
{
	static const HyvePlatformMuxObj_T muxObjs[I2CMUXIndex_MAX] = {
		{ HYFEPLATFORM_SMBUS_G_MCIO, HYFEPLATFORM_ADDR_MUX_PCIE, HyveMuxCtrl_PAC9548A },
		{ HYFEPLATFORM_SMBUS_CLK_GEN, HYFEPLATFORM_ADDR_MUX_CLK_GEN, HyveMuxCtrl_PAC9548A },
		{ HYFEPLATFORM_SMBUS_OCP_RISER, HYFEPLATFORM_ADDR_MUX_OCP_RISER, HyveMuxCtrl_PAC9548A },
	};

	if (HyvePlatform_LockMux(muxIndex, retryInterval) < 0) { return -1; }

	return muxObjs[muxIndex].pFunc(muxObjs[muxIndex].busNum, muxObjs[muxIndex].slave_addr, channel);
}
