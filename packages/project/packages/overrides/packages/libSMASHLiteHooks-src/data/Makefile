#------- Comment/uncomment the following line to enable/disable debugging------
DEBUG = n
LIBRARY_NAME = libSMASHLiteHooks

SRC = SMLH_InitHooks.c 
SRC += SMLH_GetProperties.c 
SRC += SMLH_GetTargetDetails.c
SRC += SMLH_IPMI.c
SRC += SMLH_OEM.c
SRC += SMLH_OEMParser.c

CFLAGS += -I./Includes
CFLAGS += -I$(SPXINC)/global
CFLAGS += -I$(SPXINC)/libipmi
CFLAGS += -I$(SPXINC)/ipmi
CFLAGS += -I${SPXINC}/liboemsystemlog
CFLAGS += -I${SPXINC}/network
CFLAGS += -I${SPXINC}/hostname
CFLAGS += -I${SPXINC}/ntpserver
CFLAGS += -I${SPXINC}/fmh
CFLAGS += -I${SPXINC}/flash
CFLAGS += -I${SPXINC}/pmbus
CFLAGS += -I${SPXINC}/i2c
CFLAGS += -I${SPXINC}/encryption
CFLAGS += -I$(SPXINC)/dbgout

LIBS += -lipmi -L${SPXLIB}/ipmi
LIBS += -loemsystemlog -L${SPXLIB}/oemsystemlog
LIBS += -lntpconf -L${SPXLIB}/ntpconf
LIBS += -lpmbus -L${SPXLIB}/pmbus


include ${TOOLDIR}/rules/Rules.make.libs
