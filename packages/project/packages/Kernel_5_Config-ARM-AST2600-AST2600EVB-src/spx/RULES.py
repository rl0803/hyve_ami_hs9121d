#!/usr/bin/env python

#-----------------------------------------Import Rules Files -------------------------------------------
import PyRules
import os
from   PyRules import PrjVars
from   PyRules import *
#-------------------------------------------------------------------------------------------------------

KernelVersion="5.4.124-ami"

CFG_FILE="ast2600evb.config"
DTS_FILE="ast2600evb.dts"
CFG_FILE_A1="ast2600evb_a1.config"
DTS_FILE_A1="ast2600evb_a1.dts"
DTSI_FILE="aspeed-g6.dtsi"
DTB_FILE="ast2600evb.dtb"
#DTB_FILE="aspeed-ast2600-ami.dtb"
LEGACY_FILE="legacy.dtsi"
#-------------------------------------------------------------------------------------------------------
#			Rules for Extracting Source
#-------------------------------------------------------------------------------------------------------
def extract_source():

	return 0

#-------------------------------------------------------------------------------------------------------
#			Rules for Clean Source Directory
#-------------------------------------------------------------------------------------------------------
def clean_source():


	retval = Py_Cwd(PrjVars["KERNEL_SRC"]+"/linux")
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

	
def get_and_copy_dts_files(directory):
	file_paths = ""  # List which will store all of the full filepaths.

	# Walk the tree.
	os.chdir(directory)
	for file in glob.glob("*.dts"):
		filepath = os.path.join(directory, file)
		DtsDestDir="%s/linux/arch/arm/boot/dts/%s"%(PrjVars["KERNEL_SRC"],file)
		retval = Py_CopyFile(filepath,DtsDestDir)
		if retval != 0:
			return retval
		
		base = os.path.splitext(file)[0]
		file_paths+="%s.dtb "%(base)  # Add it to the list
		
	return file_paths
#-------------------------------------------------------------------------------------------------------
#			Rules for Building Source
#-------------------------------------------------------------------------------------------------------

def build_source():

	#KernelVersion=PrjVars["SPX_KERNEL_VERSION"]
	TempDir="%s/%s"%(PrjVars["TEMPDIR"],PrjVars["PACKAGE"])
	DtsDir="%s/%s/data/"%(PrjVars["BUILD"],PrjVars["PACKAGE"])

	# Copy Kenrel Configuration	
	SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],CFG_FILE)
	DestFile="%s/linux/.config"%(PrjVars["KERNEL_SRC"])
	retval = Py_CopyFile(SrcFile,DestFile)
	if retval != 0:
		return retval 
	
	# Fix for A1 board Serial driver Issue
	if "CONFIG_SPX_FEATURE_NUM_SOL_SERIAL_PORTS" in PrjVars:
		SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],CFG_FILE_A1)
		retval = Py_CopyFile(SrcFile,DestFile)
		if retval != 0:
			return retval

	# Copy DTS to Kernel DTS Tree
	#SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],DTS_FILE)
	#DestFile="%s/linux/arch/arm/boot/dts/%s"%(PrjVars["KERNEL_SRC"],DTS_FILE)
	#retval = Py_CopyFile(SrcFile,DestFile)
	#if retval != 0:
	#	return retval 
		
	# Fix for A1 board Serial driver Issue
	#if "CONFIG_SPX_FEATURE_NUM_SOL_SERIAL_PORTS" in PrjVars:
	#	SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],DTS_FILE_A1)
	#	retval = Py_CopyFile(SrcFile,DestFile)
		#if retval != 0:
		#	return retval

	
	dtbfilenames = get_and_copy_dts_files(DtsDir)
	
	# If exists copy device tree mappings for legacy AMI drivers to Kernel DTS Tree
	SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],LEGACY_FILE)
	DestFile="%s/linux/arch/arm/boot/dts/%s"%(PrjVars["KERNEL_SRC"],LEGACY_FILE)
	# Hyve, if the platform has dtsi file then use it
	if os.path.exists(SrcFile) == True:
		retval = Py_CopyFile(SrcFile,DestFile)
		if retval != 0:
			return retval

	#copy its file
	SrcFile="%s/%s/data/kernel.its"%(PrjVars["BUILD"],PrjVars["PACKAGE"])
	DestFile="%s/linux/kernel.its"%(PrjVars["KERNEL_SRC"])
	retval = Py_CopyFile(SrcFile,DestFile)
	if retval != 0:
		return retval 

	# Copy DTSI to Kernel DTS Tree
	SrcFile="%s/%s/data/%s"%(PrjVars["BUILD"],PrjVars["PACKAGE"],DTSI_FILE)
	DestFile="%s/linux/arch/arm/boot/dts/%s"%(PrjVars["KERNEL_SRC"],DTSI_FILE)
	# Hyve, if the platform has dtsi file then use it
	if os.path.exists(SrcFile) == True:
		retval = Py_CopyFile(SrcFile,DestFile)
		if retval != 0:
			return retval

	retval=Py_SetEnv("ARCH","arm")
	if retval != 0:
		return retval 

	retval = Py_Cwd(PrjVars["KERNEL_SRC"]+"/linux")
	if retval != 0:
		return retval 

	# Build kenrel and dtb file	
	retval =Py_RunMake("oldconfig");
	if retval != 0:
		return retval
	#retval =Py_RunMake("uImage %s KALLSYMS_EXTRA_PASS=1 LOADADDR=0x80008000"%(DTB_FILE))
	print(dtbfilenames)
	retval =Py_RunMake("zImage %s "%(dtbfilenames))
	if retval != 0:
		return retval 
	
	retval = Py_Execute(" mkimage -f kernel.its kernel_fit ")
	if retval != 0:
		return retval
	#Install dtb files
	retval = Py_MkdirClean("%s/kernel-dtb"%(TempDir))
	if retval != 0:
		return retval 

	
	# Make modules and Install
	retval =Py_RunMake("modules");
	if retval != 0:
		return retval 
	retval = Py_MkdirClean("%s/modules"%(TempDir))
	if retval != 0:
		return retval 
	retval =Py_RunMake("modules_install INSTALL_MOD_PATH=%s/modules"%(TempDir))
	if retval != 0:
		return retval 

	# Remove unwanted direcotries from modules
	retval = Py_Delete("%s/modules/lib/modules/%s/source"%(TempDir,KernelVersion))
	if retval != 0:
		return retval 
	retval = Py_Delete("%s/modules/lib/modules/%s/build"%(TempDir,KernelVersion))
	if retval != 0:
		return retval 


	# Install kernel header files
	retval = Py_MkdirClean("%s/kernel-dev"%(TempDir))
	if retval != 0:
		return retval 
	retval =Py_RunMake("headers_install INSTALL_HDR_PATH=%s/kernel-dev"%(TempDir))
	if retval != 0:
		return retval 

	retval=Py_SetEnv("ARCH","ARM")
	if retval != 0:
		return retval 

	return 0


#-------------------------------------------------------------------------------------------------------
#			 Rules for Creating (Packing) Binary Packge
#-------------------------------------------------------------------------------------------------------
# Rules to create Kernel_5 package
def build_package_Kernel_5():
	return Py_PackSPX("./boot/kernel","%s/linux/kernel_fit"%(PrjVars["KERNEL_SRC"]))

# Rules to create Kernel_5_dtb package
def build_package_Kernel_5_dtb():
	TempDir="%s/%s"%(PrjVars["TEMPDIR"],PrjVars["PACKAGE"])
	return Py_PackSPX("./","%s/kernel-dtb"%(TempDir))

# Rules to create Kernel_5_dev package
def build_package_Kernel_5_dev():
	TempDir="%s/%s"%(PrjVars["TEMPDIR"],PrjVars["PACKAGE"])
	return Py_PackSPX("./","%s/kernel-dev"%(TempDir))
	
# Rules to create Kernel_5_modules package
def build_package_Kernel_5_modules():
	TempDir="%s/%s"%(PrjVars["TEMPDIR"],PrjVars["PACKAGE"])
	return Py_PackSPX("./","%s/modules"%(TempDir))

#-------------------------------------------------------------------------------------------------------


