#----------------------------------------------------------------------
#                         Makefile to build libipmipdkcmds
#                 Copyright (c) 2020 American Megatrends Inc 
#-----------------------------------------------------------------------

#------- Comment/uncomment the following line to enable/disable debugging------
DEBUG 		= n
#------------------------------------------------------------------------------

#---------------------- Change according to your files ------------------------
LIBRARY_NAME	= libipmipdkcmds
SRC		=  OemSMMCmds.c PDKCmds.c cmdselect.c PDKPend.c


CFLAGS += -I${SPXINC}/global
CFLAGS += -I${SPXINC}/ipmi
CFLAGS += -I${SPXINC}/smtp
CFLAGS += -I${SPXINC}/unix
CFLAGS += -I${SPXINC}/dbgout
CFLAGS += -I${SPXINC}/pdk
CFLAGS += -I${SPXINC}/ipmihalapi
CFLAGS += -I${SPXINC}/featuredefine
CFLAGS += -I${SPXINC}/network
CFLAGS += -I${SPXINC}/hostname
CFLAGS += -I${SPXINC}/oempdk
CFLAGS += -I${TARGETDIR}/usr/include 

include ${TOOLDIR}/rules/Rules.make.libs
#------------------------------------------------------------------------------
