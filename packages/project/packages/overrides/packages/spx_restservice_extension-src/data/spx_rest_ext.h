#ifndef __SPXRESTEXT_H__
#define __SPXRESTEXT_H__
/*#include "raphters.h"
#include "rest_types.h"
#include <stdlib.h>
#include <string.h>
#include "fcgiapp.h"
#include "json-c/json.h"
#include "libipmi_struct.h"
#include "libipmi_IPM.h"*/
#include "rest_common.h"
#include "token.h"
#include "EINTR_wrappers.h"

#include "sessioncfg.h"
#include "racsessioninfo.h"


#define TMP_DIR "/tmp/"


CoreFeatures_T g_corefeatures;
CoreMacros_T g_coremacros;


int readStruct(websession_info_t *advisor_token);

int ReadCmdPipeData();

int ReadPipeData();

int getViewerCount(char* SessionCookieString);


int setViewerCount(char* SessionCookieString, int ViewerCount);

int Destroy_session(uint32 racid);

int CreateWebPipe();

int ClearWebSessionEntry();

void map_func(map_handler *m);


extern struct json_object* json_object_object_get_rest(struct json_object* obj, const char *key);

//map_handler *last_map;

//#define RPC_HAPI_SUCCESS	0
int IPMI_lo_Login(char* UserName,char* Password,IPMI20_SESSION_T* IPMISession, uint8 byPrivLevel, uint8 allownulluser, char* uname, char* ipstr, INT8U *ServIPAddr);
void IPMI_lo_Logout(IPMI20_SESSION_T* IPMISession);

typedef enum  REST_EXT_ERROR_CODES {
    COULD_NOT_ESTABLISH_NULL_IPMI_SESSION = 1000,
	INVALID_API_CALL
} REST_EXT_ERROR_CODES_T;

int sample_rest_api();
#endif

