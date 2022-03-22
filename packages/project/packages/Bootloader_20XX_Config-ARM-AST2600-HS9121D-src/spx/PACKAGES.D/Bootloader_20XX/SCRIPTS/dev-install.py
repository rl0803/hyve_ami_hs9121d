#!/usr/bin/env python

#-----------------------------------------Import Rules Files -------------------------------------------
import PyRules
from   PyRules import PrjVars
from   PyRules import *


#--------------------------------------- Extra Pyhon modules -------------------------------------------
#
#-------------------------------------------------------------------------------------------------------


#-------------------------------------------------------------------------------------------------------
#		  	      Rules for Installing to ImageTree
#-------------------------------------------------------------------------------------------------------
def build_install():

	retval = Py_MkdirClean(PrjVars["BOOT_BIN"])
	if retval != 0:
		return retval

	if "CONFIG_SPX_FEATURE_LAN_AND_DRAM_TEST_CMD_ANY" in PrjVars:
		if PrjVars["CONFIG_SPX_FEATURE_LAN_AND_DRAM_TEST_CMD_ANY"] == "YES":
			Py_CopyFile("./nettest.bin","%s"%(PrjVars["OUTPUT"]))

	# Copy the data to Image
	return Py_CopyFile("./u-boot.bin",PrjVars["BOOT_BIN"])

#-------------------------------------------------------------------------------------------------------
#				Rules for Debug Install
def debug_install():

	return Py_CopyFile("./u-boot.bin",PrjVars["TFTPBOOT"])


#-------------------------------------------------------------------------------------------------------

