 /******************************************************************
 *
 * @file	HyvePlatformPreserveConf.h
 * @brief	Provide Hyve platform PreserveConf options
 *
 ******************************************************************/

#ifndef HYVEPLATFORMPRESERVECONF_H_
#define HYVEPLATFORMPRESERVECONF_H_


#define HYVEPLATFORM_AMI_PRESERVECONFS \
	/* { Selector, Config_File, Status } */ \
	{0, "SDR", 0}, \
	{1, "FRU", 0}, \
	{2, "SEL", 1}, \
	{3, "IPMI", 1},                 /* have to preserve all INI files and IPMI.conf files */ \
	{4, "Network", 1},              /* to preserve all network related files */ \
	{5, "NTP", 0},                  /* to preserve all NTP related files */ \
	{6, "SNMP", 0},                 /* to preserve all SNMP related files */ \
	{7, "SSH", 0},                  /* to preserve all SSH related files */ \
	{8, "KVM", 0},                  /* to preserve KVM & Vmedia related files */ \
	{9, "Authentication", 1},       /* to preserve Authentication related files */ \
	{10, "Syslog", 0},				/* to preserve Syslog configuration files */ \
	{11, "CMX", 0},					/* to preserve CMX database */ \
	{12, "WEB", 0},            		/* to preserve web configuration files */ \
	{13,"EXTLOG",0},	    		/* to preserve extlog configuration */ \
	{14,"REDFISH",0},				/* RedFish configurations */ \
	{15,"AUTOMATION_ENGINE",0},		/* Automation Engine Configurations */ \
	{16,"RackEvents",0}, 			/*  RMX Events */ \
	{17,"RSD",0} 					/* RSD Configurations */


#endif
