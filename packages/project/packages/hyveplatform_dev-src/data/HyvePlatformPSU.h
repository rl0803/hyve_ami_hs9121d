 /******************************************************************
 *
 * @file	HyvePlatformPSU.h
 * @brief	The Hyve platform PSU header file
 *
 ******************************************************************/

#ifndef HYVEPLATFORMPSU_H_
#define HYVEPLATFORMPSU_H_


extern void* HyvePlatform_PSUTask(void* pArg);
extern INT8U HyvePlatform_Is_PSU_PwrGood();
extern const INT8U g_psuLocationTable[];
 
#define HYVEPLATFORM_PSU_LOCATION(psuNum)	g_psuLocationTable[psuNum]

#endif
