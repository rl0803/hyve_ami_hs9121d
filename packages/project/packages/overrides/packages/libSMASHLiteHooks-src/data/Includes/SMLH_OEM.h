#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include "coreTypes.h" 

//uint16 SMASH_OEMAdd_PropertyName(int TargetID,char (*propertyArray)[30],int *count);
char** SMASH_OEMAdd_PropertyName(int TargetID,int *count);
uint16 SMASH_OEMGet_PropertyValue(int TargetID,char *PropertyName,char *PropVal,int RecID);
char** SMASH_AppendOEMVerbs(int TargetID,int *count);
