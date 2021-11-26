#-----------------------------------------------------------------------------
DEBUG = n
#-----------------------------------------------------------------------------

TARGET	=	spx_restservice_ext
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------

SRC		+=	spx_rest_ext.c
SRC     +=  sample_rest_api.c

CFLAGS 	+= 	-I.
CFLAGS  +=  -I${SPXINC}/
CFLAGS  +=	-I${SPXINC}/fastcgi
CFLAGS  +=	-I${SPXINC}/qdecoder
CFLAGS  +=	-I${SPXINC}/raphters
#CFLAGS  +=	-I${SPXINC}/json-c
CFLAGS 	+= 	-I${SPXINC}/session
CFLAGS  +=  -I${SPXINC}/global
CFLAGS  +=  -I${SPXINC}/spxrest
CFLAGS  +=  -I${SPXINC}/ipmi
CFLAGS  +=  -I${SPXINC}/libipmi
CFLAGS  +=  -I${SPXINC}/adviser
CFLAGS  +=  -I${SPXINC}/advisercfg
CFLAGS  +=  -I${SPXINC}/network
CFLAGS +=   -I${SPXINC}/hostname
CFLAGS  +=  -I${SPXINC}/dbgout
CFLAGS  +=  -I${SPXINC}/token
CFLAGS += -I${SPXINC}/racsessioninfo
CFLAGS  += -I${SPXINC}/syslogconf
CFLAGS  +=  -I${SPXINC}/flash
CFLAGS  +=  -I${SPXINC}/unix
CFLAGS	+=	-I${SPXINC}/featuredefine
CFLAGS	+= -I${SPXINC}/fmh

CFLAGS 	+=	-I${TARGETDIR}/usr/include
CFLAGS	+= 	-DHAVE_SOCKLEN_T

LIBS	+=	-L${SPXLIB}/fastcgi -lfcgi
LIBS	+=	-L${SPXLIB}/qdecoder -lqdecoder
LIBS	+=	-L${SPXLIB}/raphters -lraphters
#LIBS	+=	-L${SPXLIB}/json-c -ljson-c
LIBS    +=  -L${SPXLIB}/featuredefine -lfeaturedefine
LIBS    +=  -L${SPXLIB}/ipmi -lipmi
LIBS    +=  -L${SPXLIB}/advisercfg -ladvisercfg
LIBS    +=  -L${SPXLIB}/network -lnetwork
LIBS    +=  -L${SPXLIB}/hostname -lhostname
LIBS    +=  -L${SPXLIB}/dbgout -ldbgout
LIBS    +=  -L${SPXLIB}/token -ltoken
LIBS    +=  -L${SPXLIB}/racsessioninfo -lracsessioninfo
LIBS    +=  -L${SPXLIB}/syslogconf -lsyslogconf
LIBS    +=  -L${SPXLIB}/ipmiparams -lipmiparams
LIBS    +=  -L${SPXLIB}/flash -lflash
LIBS    +=  -L${SPXLIB}/unix -lunix
LIBS	+=	-lpthread
LIBS	+=	-ldl
LIBS	+=	-rdynamic
LIBS	+=	${TARGETDIR}/usr/lib/${MULTI_ARCH_LIB}/libcrypto.so
LIBS	+=	${TARGETDIR}/usr/lib/${MULTI_ARCH_LIB}/libssl.so
ifeq ($(CONFIG_SPX_FEATURE_TARGET_JESSIE),YES)
LIBS    +=  ${TARGETDIR}/lib/${MULTI_ARCH_LIB}/libjson-c.so.2.0.0
endif
ifeq ($(CONFIG_SPX_FEATURE_TARGET_BUSTER),YES)
LIBS    +=  ${TARGETDIR}/usr/lib/${MULTI_ARCH_LIB}/libjson-c.so
endif
LIBS 	+=	-lm

include ${TOOLDIR}/rules/Rules.make.apps

#------------------------------------------------------------------------------
