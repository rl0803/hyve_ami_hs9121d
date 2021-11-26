#include "SMLH_Include.h"
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
#include "SMLH_IPMI.h"
#endif

// this function should give the number of chassis present and also the first record id of the chassis
int GetChassisCount(IPMI20_SESSION_T *session, int * chassisCount, uint16 * firstRecID)
{
	if(0)
	{
		session=session; /* -Wextra, fix for unused parameters */
	}
	*chassisCount = 1;
	*firstRecID = 1;
	return SMH_SUCCESS;
}

// this function should give information of the chassis represented by the currRec,
// the nodeCount gives the number of nodes for the particular chassis
// and nodeRecID give the record ID of the first node
int GetChassisInfo(IPMI20_SESSION_T *session, uint16 currRec, uint16 *nextRec, uint16 *nodeRecID, int * nodeCount)
{
	if(0)
	{
		session=session; /* -Wextra, fix for unused parameters */
		currRec=currRec;
		nextRec=nextRec;
		nodeRecID=nodeRecID;
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	*nodeCount = SMASH_NodeCount();
#else
	*nodeCount = 1;
#endif
	return SMH_SUCCESS;
}

//this function retrieves the next node's record id, current node is represented by currRec
int GetNextNode(IPMI20_SESSION_T *session, uint16 currRec, uint16 *nextRec)
{
	*nextRec = -1;
	if(0)
	{
		session=session; /* -Wextra, fix for unused parameters */
		currRec=currRec;
	}
    return SMH_SUCCESS;
}

void DeleteTarget(int count,logicalDevInfo* Target)
{
    int i = 0;
    phyDevInfo *Device = NULL, *Ptr = NULL;
    
    for(i = 0; i < count; i++)
    {
        Device=Target[i].AssociatedDevices;
        while(Device != NULL)
        {
            Ptr = Device;
            Device = Device->next;
            free(Ptr);
            Ptr= NULL;
        }
    }
    free(Target);
    Target=NULL;
}

//this function fills in the target details of the cooling units
int GetCoolingTargetInfo(IPMI20_SESSION_T *session, logicalDevInfo **CoolingUnitTarget, int *targetCount)
{
	int retVal = SMH_FAILURE;
	if(0)
	{
		session=session; /* -Wextra, fix for unused parameters */
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
    int count = 10, i = 0, j = 0;
#else
        int count = 3, i = 0, j = 0;
#endif
        logicalDevInfo *coolingUnitTarget = (*CoolingUnitTarget);
        phyDevInfo *fanDevice = NULL, *fanPtr = NULL;

        coolingUnitTarget = calloc(count, sizeof(logicalDevInfo));
        if(NULL == coolingUnitTarget)
        {
                return retVal;
        }

        for(i = 0; i < count; i++)
        {
                coolingUnitTarget[i].recID = i + 1;
                coolingUnitTarget[i].AssociatedDeviceCount = 3;
                fanDevice = calloc(1, sizeof(phyDevInfo));
                if(NULL == fanDevice)
                {
			DeleteTarget(i,coolingUnitTarget);
                        return retVal;
                }
                fanDevice->next = NULL;
                fanPtr = fanDevice;
                for(j = 1; j <= coolingUnitTarget[i].AssociatedDeviceCount; j++)
                {
                        fanPtr->recID = (10*i) + j;
                        fanPtr->next = calloc(1, sizeof(phyDevInfo));
                        if(NULL == fanPtr->next)
                        {
				coolingUnitTarget[i].AssociatedDevices = fanDevice;
				DeleteTarget(i,coolingUnitTarget);
                                return retVal;
                        }
                        fanPtr = fanPtr->next;
                        fanPtr->next = NULL;
                }
                coolingUnitTarget[i].AssociatedDevices = fanDevice;
        }

        (*CoolingUnitTarget) = coolingUnitTarget;
        (*targetCount) = count;
	retVal = SMH_SUCCESS;
	return retVal;
}

//this function fills in the target details of the power units
int GetPowerTargetInfo(IPMI20_SESSION_T *session, logicalDevInfo **PowerUnitTarget, int *targetCount)
{
	int retVal = SMH_FAILURE;
	if(0)
	{
		session=session; /* -Wextra, fix for unused parameters */
	}
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
	int count = 1, i = 0, j = 0;
#else
	int count = 2, i = 0, j = 0;
#endif
	logicalDevInfo *pwrUnitTarget = (*PowerUnitTarget);
	phyDevInfo *psuDevice = NULL, *psuPtr = NULL;

	pwrUnitTarget = calloc(count, sizeof(logicalDevInfo));
	if(NULL == pwrUnitTarget)
	{
		return retVal;
	}
		
	for(i = 0; i < count; i++)
	{
		pwrUnitTarget[i].recID = i + 1;
#ifdef CONFIG_SPX_FEATURE_SMASH_LITE_SCORPIO
		pwrUnitTarget[i].AssociatedDeviceCount = 10;
#else
		pwrUnitTarget[i].AssociatedDeviceCount = 3;
#endif
		psuDevice = calloc(1, sizeof(phyDevInfo));
		if(NULL == psuDevice)
		{
			DeleteTarget(i,pwrUnitTarget);
			return retVal;
		}
		psuDevice->next = NULL;
		psuPtr = psuDevice;
		for(j = 1; j <= pwrUnitTarget[i].AssociatedDeviceCount; j++)
		{
			psuPtr->recID = (10*i) + j;
			psuPtr->next = calloc(1, sizeof(phyDevInfo));
                	if(NULL == psuPtr->next)
	                {
				pwrUnitTarget[i].AssociatedDevices = psuDevice;
				DeleteTarget(i,pwrUnitTarget);
        	                return retVal;
               		}
			psuPtr = psuPtr->next;
			psuPtr->next = NULL;
		}
		pwrUnitTarget[i].AssociatedDevices = psuDevice;
	}

	(*PowerUnitTarget) = pwrUnitTarget;
	(*targetCount) = count;
	retVal = SMH_SUCCESS;
        return retVal;
}
