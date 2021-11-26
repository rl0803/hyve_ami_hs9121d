#!/usr/bin/env python

#-----------------------------------------Import Rules Files -------------------------------------------
import PyRules
import os
from   PyRules import PrjVars
from   PyRules import *
#-------------------------------------------------------------------------------------------------------

CFG_FILE="ast2600evb.config"
EMMC_CFG_FILE="ast2600evb-emmc.config"
DTS_FILE="ast2600-evb.dts"
DTS_FILE_A1="ast2600-A1evb.dts"
DTS_FILE_A0="ast2600-A0evb.dts"
HYVE_BOARDINIT_FILE="HyvePlatformBoardInit.c"
#-------------------------------------------------------------------------------------------------------
#			Rules for Extracting Source
#-------------------------------------------------------------------------------------------------------
def extract_source():

	return 0

#-------------------------------------------------------------------------------------------------------
#			Rules for Clean Source Directory
#-------------------------------------------------------------------------------------------------------
def clean_source():


	retval = Py_Cwd(PrjVars["BOOT_SRC"]+"/uboot")
	if retval != 0:
		return retval 

	retval=Py_SetEnv("ARCH","arm")			# Change to linux specific ARCH name 
	if retval != 0:
		return retval 

	retval =Py_RunMake("clean");
	if retval != 0:
		return retval 

	retval =Py_RunMake("distclean");
	if retval != 0:
		return retval 

	retval=Py_SetEnv("ARCH","ARM")			# Restore SPX spcecific ARCH name
	if retval != 0:
		return retval 

	return 0

#-------------------------------------------------------------------------------------------------------
#			Rules for Building Source
#-------------------------------------------------------------------------------------------------------
def build_source():

	PatchDir = "%s/%s/data" % (PrjVars["SOURCE"], PrjVars["PACKAGE"])

	# Get files from 000-* to 999-*
	PatchFiles = sorted(glob.glob(PatchDir + "/???-*"))

	for PatchFile in PatchFiles:
		if os.path.isfile(PatchFile) == False:
			continue
		if Py_ApplyPatch("1", PatchFile, PrjVars["BOOT_SRC"] + "/uboot") == 1:
			print("[ERROR]: Failed to patch file %s\n" % PatchFile)
			return -1

	TempDir="%s/%s/temp"%(PrjVars["TEMPDIR"],PrjVars["PACKAGE"])
		
	SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],CFG_FILE)
	if "CONFIG_SPX_FEATURE_HW_EMMC_BOOT" in PrjVars:
		SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],EMMC_CFG_FILE)
	DestFile="%s/uboot/.config"%(PrjVars["BOOT_SRC"])
	retval = Py_CopyFile(SrcFile,DestFile)
	if retval != 0:
		return retval 

	# Copy DTS to Uboot DTS Tree
	SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],DTS_FILE_A0)
	DestFile="%s/uboot/arch/arm/dts/%s"%(PrjVars["BOOT_SRC"],DTS_FILE)
	retval = Py_CopyFile(SrcFile,DestFile)
	if retval != 0:
			return retval

	# Copy A1 DTS to Uboot DTS tree
	if "CONFIG_SPX_FEATURE_NUM_SOL_SERIAL_PORTS" in PrjVars:
		SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],DTS_FILE_A1)
		DestFile="%s/uboot/arch/arm/dts/%s"%(PrjVars["BOOT_SRC"],DTS_FILE)
		retval = Py_CopyFile(SrcFile,DestFile)
		if retval != 0:
			return retval

# Hyve--
	# Copy platform board init hook function source file to Uboot source code folder
	SrcFile = "%s/%s/data/%s"%(PrjVars["BUILD"], PrjVars["PACKAGE"], HYVE_BOARDINIT_FILE)
	DestFile = "%s/uboot/arch/arm/mach-aspeed/ast2600/%s"%(PrjVars["BOOT_SRC"], HYVE_BOARDINIT_FILE)

	if os.path.exists(SrcFile) == True:
		retval = Py_CopyFile(SrcFile, DestFile)
		if retval != 0:
			return retval
# --Hyve

	retval=Py_SetEnv("ARCH","arm")
	if retval != 0:
		return retval 

	retval = Py_Cwd(PrjVars["BOOT_SRC"]+"/uboot")
	if retval != 0:
		return retval 

	retval =Py_RunMake("oldconfig");
	if retval != 0:
		return retval 

	retval =Py_RunMake("");
	#retval =Py_RunSilentMake("");
	if retval != 0:
		return retval 

	retval=Py_SetEnv("ARCH","ARM")
	if retval != 0:
		return retval 

	retval = Py_MkdirClean(TempDir)
	if retval != 0:
		return retval 
	
	if "CONFIG_SPX_FEATURE_LAN_AND_DRAM_TEST_CMD_ANY" in PrjVars:
		if PrjVars["CONFIG_SPX_FEATURE_LAN_AND_DRAM_TEST_CMD_ANY"] == "YES":
			retval = Py_CopyFile("%s/uboot/oem/ami/standalone/nettest/nettest.bin"%(PrjVars["BOOT_SRC"]),TempDir)
			if retval != 0:
				return retval
	
	retval = Py_CopyFile("%s/uboot/simage.bin"%(PrjVars["BOOT_SRC"]),"%s/u-boot.bin"%(TempDir))
	if retval != 0:
		return retval 
	
	return 0



#-------------------------------------------------------------------------------------------------------
#			 Rules for Creating (Packing) Binary Packge
#-------------------------------------------------------------------------------------------------------
def build_package_Bootloader_20XX():
	TempDir="%s/%s/temp"%(PrjVars["TEMPDIR"],PrjVars["PACKAGE"])
	return Py_PackSPX("./",TempDir)


#-------------------------------------------------------------------------------------------------------

