#!/usr/bin/env python

#-----------------------------------------Import Rules Files -------------------------------------------
import PyRules
from   PyRules import PrjVars
from   PyRules import *

KernelVersion = "5.4.124-ami"

#--------------------------------------- Extra Pyhon modules -------------------------------------------
#
#-------------------------------------------------------------------------------------------------------


#-------------------------------------------------------------------------------------------------------
#		  	      Rules for Installing to ImageTree
#-------------------------------------------------------------------------------------------------------
def build_install():


#	KenrelVersion = PrjVars["SPX_KERNEL_VERSION"]
	retval=Py_SetValue("SPX_KERNEL_VERSION",KernelVersion)
	if retval != 0:
		return retval


	retval = Py_MkdirClean(PrjVars["KERNEL_BIN"])
	if retval != 0:
		return retval

	# Copy the data to Image
	retval =Py_CopyFile("./boot/kernel/kernel_fit",PrjVars["KERNEL_BIN"])
	if retval != 0:
		return retval

	
	return Py_SoftLink("generic","%s/lib/modules/%s"
						%(PrjVars["IMAGE_TREE"],KernelVersion))



#-------------------------------------------------------------------------------------------------------
#				Rules for Debug Install
def debug_install():

	return Py_CopyFile("./boot/kernel/kernel_fit",PrjVars["TFTPBOOT"])


#-------------------------------------------------------------------------------------------------------

