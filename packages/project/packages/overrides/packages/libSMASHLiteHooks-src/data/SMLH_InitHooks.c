#include "SMLH_Include.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void *dl_SMhandle;
func_ptr g_funcHandle[];

sm_func_table func_table [] = {
{GET_CHASSIS_COUNT, "GetChassisCount"},
{GET_ONE_CHASSIS_INFO, "GetChassisInfo"},
{GET_NXT_NODE, "GetNextNode"},
{GET_COOLING_TARGET, "GetCoolingTargetInfo"},
{GET_POWER_TARGET, "GetPowerTargetInfo"},
{FILL_CHASSIS_PROP, "FillChassisProperties"},
{FILL_NODE_PROP, "FillNodeProperties"},
{FILL_SYS_PROP, "FillSystemProperties"},
{FILL_PWR_PROP, "FillPowerProperties"},
{FILL_PSU_PROP, "FillPSUProperties"},
{FILL_COLLING_PROP, "FillCoolingProperties"},
{FILL_FAN_PROP, "FillFanProperties"},
{FILL_LOGS_PROP, "FillLogsProperties"},
{FILL_ACCT_PROP, "FillAccountProperties"},
{FILL_RMC_PROP, "FillRmcupgradeProperties"},
{FILL_RFCB_PROP, "FillRfcbupgradeProperties"},
{FILL_ADMIN_PROP, "FillAdminProperties"},
{FILL_SP_PROP, "FillSPProperties"},
{FILL_SNMP_PROP, "FillSnmpProperties"},
//Add additional function's info here
};

int init_smFuncTable()
{
	int i = 0, fnCount = 0;
	for(i = 0; i < MAX_FUNC_NUMBER; i++)
	{
		g_funcHandle[i] = NULL;
	}

	dl_SMhandle = dlopen(SMH_LIB_PATH, RTLD_NOW);

	if(dl_SMhandle == NULL)
	{
		printf("Error in loading library %s\n", dlerror());
		return SMH_FAILURE;
	}

	fnCount = sizeof(func_table) / sizeof(func_table[0]);
        for(i = 0; i < fnCount; i++ )
        {
                g_funcHandle[func_table[i].funcNum] = dlsym(dl_SMhandle, func_table[i].funcName);
        }

	return SMH_SUCCESS;
}

int uninit_smFuncTable()
{
	if(NULL != dl_SMhandle)
		return dlclose(dl_SMhandle);

	return SMH_SUCCESS;
}


