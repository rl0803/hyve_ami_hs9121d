#!/usr/bin/env python
#-----------------------------------------Import Rules Files -------------------------------------------
import PyRules
from   PyRules import PrjVars
from   PyRules import *
#--------------------------------------- Extra Python modules -------------------------------------------
#-------------------------------------------------------------------------------------------------------


#-------------------------------------------------------------------------------------------------------
#		  	      Rules for Installing to ImageTree
#-------------------------------------------------------------------------------------------------------

hyvePlatformID = "HS9121D"

def build_install():
    IMAGETREE=PrjVars["IMAGE_TREE"]

    retval = Py_Mkdir(IMAGETREE+"/usr/local/lib/ipmi/" + hyvePlatformID)
    if retval != 0:
        return retval
    
    retval = Py_Mkdir(IMAGETREE+"/conf/BMC1/" + hyvePlatformID)
    if retval != 0:
        return retval
    
    retval = Py_Mkdir(IMAGETREE+"/etc/defconfig/BMC1/" + hyvePlatformID)
    if retval != 0:
        return retval
    
    retval = Py_MkdirClean(IMAGETREE+"/conf/BMC1/" + hyvePlatformID + "/fscConfig")
    if retval != 0:
        return retval
    
    retval = Py_MkdirClean(IMAGETREE+"/etc/defconfig/BMC1/" + hyvePlatformID + "/fscConfig")
    if retval != 0:
        return retval
    
    retval = Py_CopyFile("SDR.dat", IMAGETREE+"/conf/BMC1/" + hyvePlatformID + "/")
    if retval != 0:
        return retval
       
    retval = Py_CopyFile("IPMI.conf", IMAGETREE+"/conf/BMC1/" + hyvePlatformID + "/")
    if retval != 0:
        return retval
       
    retval = Py_CopyFile("SDR.dat", IMAGETREE+"/etc/defconfig/BMC1/" + hyvePlatformID + "/")
    if retval != 0:
        return retval
       
    retval = Py_CopyFile("IPMI.conf", IMAGETREE+"/etc/defconfig/BMC1/" + hyvePlatformID + "/")
    if retval != 0:
        return retval

    retval = Py_CopyFile("libipmipar.so."+PrjVars["PKG_MAJOR"]+"."+PrjVars["PKG_MINOR"]+"."+PrjVars["PKG_AUX"], IMAGETREE+"/usr/local/lib/ipmi/" + hyvePlatformID)
    if retval != 0:
        return retval

    retval = Py_AddLiblinks(IMAGETREE+"/usr/local/lib/ipmi/" + hyvePlatformID,"libipmipar.so."+PrjVars["PKG_MAJOR"]+"."+PrjVars["PKG_MINOR"]+"."+PrjVars["PKG_AUX"])
    if retval != 0:
        return retval
    
    retval = Py_WriteFile(hyvePlatformID, IMAGETREE+"/usr/local/lib/ipmi/platform.conf")
    if retval != 0:
        return retval

# Hyve Platform FSC Config--
    retval = Py_CopyDir("fscConfig", IMAGETREE+"/conf/BMC1/" + hyvePlatformID + "/fscConfig")
    if retval != 0:
        return retval

    retval = Py_CopyDir("fscConfig", IMAGETREE+"/etc/defconfig/BMC1/" + hyvePlatformID + "/fscConfig")
    if retval != 0:
        return retval
# --Hyve Platform FSC Config

    return 0

#-------------------------------------------------------------------------------------------------------
#				Rules for Debug Install

#-------------------------------------------------------------------------------------------------------
def debug_install():
	return 0

#-------------------------------------------------------------------------------------------------------
