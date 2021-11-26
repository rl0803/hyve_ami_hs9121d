#include "SMLH_OEM.h"
#include "Debug.h"

#define ROOT_TAR                        30      
#define SYSTEM_TAR                      31              
#define POWER_TAR                       32      
#define PSU_TAR                         33              
#define COOLING_TAR                     34      
#define FAN_TAR                         35              
#define CHASSIS_TAR                     36      
#define NODE_TAR                        37              
#define LOG_TAR                         38      
#define USERS_TAR                       39      
#define ACCOUNT_TAR                     40              
#define RMCUPGRADE_TAR                  41      
#define RFCBUPGRADE_TAR                 42     
#define RECORDLOG_TAR                   43      
#define SUMMARY                         44
#define SNMP_TAR                        47

char** SMASH_AppendOEMVerbs(int TargetID,int *count)
{
	
	static char *SystemVerbs[]={""};
	int syscnt=0;
	static char *PowerVerbs[]={""};
	int pwrcnt=0;
	static char *PsuVerbs[]={""};
	int psucnt=0;
	static char *CoolingVerbs[]={""};
	int coolingcnt=0;
	static char *FanVerbs[]={""};
	int fancnt=0;
	static char *ChassisVerbs[]={""};
	int chassiscnt=0;
	static char *NodeVerbs[]={""};
	int nodecnt=0;
	static char *LogVerbs[]={""};
	int logcnt=0;
	static char *AccountVerbs[]={""};
	int accountcnt=0;
	static char *RmcVerbs[]={""};
	int rmccnt=0;
	static char *RfcbVerbs[]={""};
	int rfcbcnt=0;
	static char *SnmpVerbs[]={""};
	int snmpcnt=0;

	switch(TargetID)
	{
	case SYSTEM_TAR:
		*count=syscnt;
		return SystemVerbs;
		break;

	case POWER_TAR:
		*count=pwrcnt;
		return PowerVerbs;
		break;
	case PSU_TAR:
		*count=psucnt;
		return PsuVerbs;
		break;
	case COOLING_TAR:
		*count=coolingcnt;
		return CoolingVerbs;
		break;
	case FAN_TAR:
		*count=fancnt;
		return FanVerbs;
		break;
	case CHASSIS_TAR:
		*count=chassiscnt;
		return ChassisVerbs;
		break;
	case NODE_TAR:
		*count=nodecnt;
		return NodeVerbs;
		break;
	case LOG_TAR:
		*count=logcnt;
		return LogVerbs;
		break;
	case ACCOUNT_TAR:
		*count=accountcnt;
		return AccountVerbs;
		break;
	case RMCUPGRADE_TAR:
		*count=rmccnt;
		return RmcVerbs;
		break;
	case RFCBUPGRADE_TAR:
		*count=rfcbcnt;
		return RfcbVerbs;
		break;
	case SNMP_TAR:
		*count=snmpcnt;
		return SnmpVerbs;
		break;
    default:
        break;
	
	}
	return NULL;
}

char** SMASH_OEMAdd_PropertyName(int TargetID,int *count)
{
//Example:	static char *SystemProps[]={"length","depth","height"};
//			int syscnt=3;
	static char *SystemProps[]={""};
	int syscnt=0;
	static char *PowerProps[]={""};
	int pwrcnt=0;
	static char *PsuProps[]={""};
	int psucnt=0;
	static char *CoolingProps[]={""};
	int coolcnt=0;
	static char *FanProps[]={""};
	int fancnt=0;
	static char *ChassisProps[]={""};
	int chassiscnt=0;
	static char *NodeProps[]={""};
	int nodecnt=0;
	static char *AccountProps[]={""};
	int accountcnt=0;
	static char *RmcProps[]={""};
	int rmccnt=0;
	static char *RfcbProps[]={""};
	int rfcbcnt=0;
	static char *LogProps[]={""};
	int logcnt=0;
	static char *SnmpProps[]={""};
	int snmpcnt=0;
		
	switch(TargetID)
	{
	case SYSTEM_TAR:
		if(syscnt<=10)
		{
			*count=syscnt;
			return SystemProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		
		break;

	case POWER_TAR:
		if(pwrcnt<=10)
		{
			*count=pwrcnt;
			return PowerProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
		
	case PSU_TAR:
		if(psucnt<=10)
		{
			*count=psucnt;
			return PsuProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case COOLING_TAR:
		if(coolcnt<=10)
		{
			*count=coolcnt;
			return CoolingProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case FAN_TAR:
		if(fancnt <=10)
		{
			*count = fancnt;
			return FanProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case CHASSIS_TAR:
		if(chassiscnt <= 10)
		{
			*count=chassiscnt;
			return ChassisProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case NODE_TAR:
		if(nodecnt <= 10)
		{
			*count=nodecnt;
			return NodeProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case LOG_TAR:
		if(logcnt <= 10)
		{
			*count=logcnt;
			return LogProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case ACCOUNT_TAR:
		if(accountcnt <=10)
		{
			*count=accountcnt;
			return AccountProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case RMCUPGRADE_TAR:
		if(rmccnt <= 10)
		{
			*count = rmccnt;
			return RmcProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case RFCBUPGRADE_TAR:
		if(rfcbcnt <= 10)
		{
			*count=rfcbcnt;
			return RfcbProps;
		}
		else
		{
			printf("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
	case SNMP_TAR:
		if(snmpcnt <= 10)
		{
			*count=snmpcnt;
			return SnmpProps;
		}
		else
		{
			TCRIT("you cant add more than 10 oem properties for each target\n ");
			return NULL;
		}
		break;
    default:
        break;
	}
	return NULL;
}
uint16 SMASH_OEMGet_PropertyValue(int TargetID,char *PropertyName,char *PropVal,int RecID)
{
	if(0)
	{
		PropertyName=PropertyName; /* -Wextra, fix for unused parameters */
		PropVal=PropVal;
		RecID=RecID;
	}
	switch(TargetID)
	{
	case SYSTEM_TAR:
		printf("in system oem target\n");
		break;
	case POWER_TAR:
		printf("in power oem target\n");		
		break;
	case PSU_TAR:
		printf("in PSU oem target\n");		
		break;
	case COOLING_TAR:
		printf("in cooling oem target\n");		
		break;
	case FAN_TAR:
		printf("in fan oem target\n");
		break;
	case CHASSIS_TAR:
		printf("in chassis oem target\n");
		break;
	case NODE_TAR:
		printf("in node oem target\n");
		break;
	case LOG_TAR:
		printf("in log oem target\n");
		break;
	case ACCOUNT_TAR:
		printf("in account oem target\n");
		break;
	case RMCUPGRADE_TAR:
		printf("in an rmc target\n");
		break;
	case RFCBUPGRADE_TAR:
		printf("in rfcb oem target\n");
		break;
	case SNMP_TAR:
		TINFO("in snmp oem target\n");
		break;
    default:
        break;
	}
	return 1;
}
int SMASH_ExecuteOEMCommand(char *path,char *cmd)
{
	printf("in executing OEM command the cmd is and the target is %s %s\n",cmd,path);
/*	if(!strncmp(path,"/system",strlen("/system")))
		printf("COMMAND COMPLETED\n");
	else
		printf("Target not supported\n");*/
	return 1;
}
