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

	# Copy the data to Image
	return 0
	#return Py_CopyFile("./kernel.dtb",PrjVars["KERNEL_BIN"])



#-------------------------------------------------------------------------------------------------------
#				Rules for Debug Install
def debug_install():

	return 0
	#return Py_CopyFile("./kernel.dtb",PrjVars["TFTPBOOT"])


#-------------------------------------------------------------------------------------------------------

