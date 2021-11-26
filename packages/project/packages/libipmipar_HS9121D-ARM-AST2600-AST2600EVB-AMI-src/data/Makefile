#-----------------------------------------------------------------------------
DEBUG = n
#-----------------------------------------------------------------------------

LIBRARY_NAME=libipmipar
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#SRC    = $(PDK_PLATFORM_DIR).c
SRC    = ast2600evb.c usrinfo.c dcmicfg.c wdogcfg.c pefcfg.c chassiscfg.c
SRC    += serialcfg.c bridgecfg.c systeminfo.c lancfg1.c lancfg2.c lancfg3.c lancfg4.c
SRC    += rmcppluscfg1.c rmcppluscfg2.c rmcppluscfg3.c rmcppluscfg4.c solcfg1.c solcfg2.c
SRC    += solcfg3.c solcfg4.c ffirewallcfg.c opmacfg.c smtpcfg1.c smtpcfg2.c smtpcfg3.c smtpcfg4.c
SRC    += genericcfg.c smbuschannel.c lanchannel1.c lanchannel2.c lanchannel3.c lanchannel4.c
SRC    += ipmbchannel.c smlinkipmbchannel.c thirdipmbchannel.c icmbchannel.c smmchannel.c
SRC    += serialchannel.c sysifchannel.c triggerevtcfg.c soltriggereventcfg.c loginadtcfg.c amicfg.c
SRC    += version.c ssicfg.c encusrpswd.c lanifccfg.c bondcfg.c lankcscfg.c
SRC    += pefrecorddetailscfg.c dualimagecfg.c misccfg.c multisolcfg.c

CFLAGS += -fPIC
CFLAGS += -I${SPXINC}/ipmi
CFLAGS += -I${SPXINC}/global
CFLAGS += -I${SPXINC}/unix
CFLAGS += -I${SPXINC}/dbgout
CFLAGS += -I${SPXINC}/iniparser
CFLAGS += -I${SPXINC}/pdk
CFLAGS += -I${SPXINC}/ipmihalapi
CFLAGS += -I${SPXINC}/network
CFLAGS += -I${SPXINC}/hostname
CFLAGS += -I${SPXINC}/mmap

CFLAGS += -I${SPXINC}/featuredefine
LIBS   += -L${SPXLIB}/featuredefine -lfeaturedefine

include ${TOOLDIR}/rules/Rules.make.libs

#------------------------------------------------------------------------------
