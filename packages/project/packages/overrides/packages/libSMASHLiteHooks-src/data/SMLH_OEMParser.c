/*
 * File Name: SMLH_OEMParser.c
 *
 *  Created on: Jul 6, 2016
 *  Author: B Sreedhar
 *  OEM Parser is defined to edit the parser rules
 */

#include "SMLH_OEMParser.h"

/*************************************************************
 * Function Name: parse_oem_target_ufct
 * In			: string -> value of the string given by the
 * 				  user, which is remaining
 * 				  min_range, max_range defined in bnf.h
 * Out			: num_chars_found number of characters found 
 * 				  and should be parsed successfully.
 * retVal 		: return value is if the hook is implemented
 * 				  it must be '1' or else it is '0'
 **************************************************************/

int SMASH_OEMParseTargetUfct(char *string, int min_range, int max_range, int *num_chars_found) 
{	
	/* fix for unused variable */
	if( string && min_range && max_range && num_chars_found )
		return 0;
	
	return 0;
}

