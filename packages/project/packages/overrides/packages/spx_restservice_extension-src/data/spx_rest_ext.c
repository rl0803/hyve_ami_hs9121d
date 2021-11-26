#include "spx_rest_ext.h"
#include "featuredef.h"

//CoreFeatures_T g_corefeatures;
//CoreMacros_T g_coremacros;

map_handler *last_map=NULL;


int IPMI_lo_Login(char* UserName,char* Password,IPMI20_SESSION_T* IPMISession, uint8 byPrivLevel, uint8 allownulluser, char* uname, char* ipstr,INT8U *ServIPAddr)
{
	uint16 wRet;
#ifdef CFG_PROJ_WEB_BYPASS_LOGIN_YES
	return LIBIPMI_E_SUCCESS;
#endif
	uint8 *ipaddr = NULL;
	uint8 ipbuf[sizeof(struct in6_addr)];
	uint8 IPVersion = 0;

	if(!allownulluser)
	{
		if (strcmp(UserName,"") == 0)
		{
			TCRIT("Null User Not allowed for Web Access\n");
			return LIBIPMI_E_INVALID_USER_NAME;
		}
	}

	/* Conversion of IP address from text to binary form */
	memset(ipbuf, 0, sizeof(struct in6_addr));

	if(NULL != ipstr)
	{
		if ( inet_pton(AF_INET, ipstr, ipbuf) )
		{
			ipaddr = ipbuf;
			IPVersion = IP4_VERSION;
		}
		else if ( inet_pton(AF_INET6, ipstr, ipbuf) )
		{
			ipaddr = ipbuf;
			IPVersion = IP6_VERSION;
		}
		else
		{
			TCRIT("WebSessionIfc_Create: Text to binary conversion of IP Address failed ");
		}
	}

	wRet = LIBIPMI_Create_IPMI_Local_Session_Ext(IPMISession, UserName, Password,
						     &byPrivLevel, uname, ipaddr, IPVersion,ServIPAddr,AUTH_BYPASS_FLAG, 5);


	if (wRet == LIBIPMI_E_SUCCESS)
	{
		TINFO("IPMI Session established successfully\n");
		//always check what privilege level as got finally
		TINFO("Privilege level for this session is %x\n",byPrivLevel);
		return 0;
	}
	else
	{
		TCRIT("Error establishing IPMI Session : %x\n",wRet);
		/* failed with admin priv...may be just an operator */
		printf("byPrivLevel = %d\n",byPrivLevel);
		return wRet;
	}
}

void IPMI_lo_Logout(IPMI20_SESSION_T* IPMISession)
{
	LIBIPMI_CloseSession(IPMISession);
}

struct json_object* json_object_object_get_rest(struct json_object* jso, const char *key)
{
	struct json_object *result = NULL;
	json_object_object_get_ex(jso, key, &result);
	return result;
}


// function to use in scandir call to find session files
int qsession_filter(const struct dirent *entry) {
	if(strstr(entry->d_name, "qsession-") == NULL) {
		return 0;
	} else if(strstr(entry->d_name, ".properties") == NULL) {
		return 0;
	} else {
		return 1;
	}
}

int readStruct(websession_info_t *advisor_token)
{
	int adtFD = -1;
	int readsize;

	//make the path as a definition
	adtFD = sigwrap_open(WEBTOKEN_COMM_PIPE, O_RDONLY|O_NONBLOCK);
	if(adtFD)
	{
		readsize = sigwrap_read(adtFD,advisor_token, sizeof(websession_info_t));
		if(readsize == -1)
		{
			//printf("Couldn't read web tokens from /var/ActiveWebTokens\n");
			sigwrap_close(adtFD);
			return -1;
		}
		if (readsize == 0)
		{
			fprintf(stderr, "There is no data currently in the webtokens file\n");
			sigwrap_close(adtFD);
			return -1;
		}
                advisor_token->websession_token[WEBTOKEN_SIZE-1] = '\0'; // Storing last character as null character
		fprintf(stderr, "Got an Active Web Token from /var/ActiveWebToken\n");

		sigwrap_close(adtFD);
	}else
	{
		return -1;
	}
	return 0;
}

/*
* Read pipe to terminate session if initiated
*/
int ReadCmdPipeData()
{
	int readsize;
	session_disconect_record_t record;
	int WebFD = -1;
	memset(&record,0,sizeof(session_disconect_record_t));

	if(WebFD <0)
	{
		WebFD = sigwrap_open(WEB_SESSION_TERM_PIPE, O_RDONLY|O_NONBLOCK);
	}
	if(WebFD >0)
	{
		readsize = sigwrap_read(WebFD,&record, sizeof(session_disconect_record_t));
		if(readsize == -1)
		{
			//TDBG("Couldn't read rac session id from web pipe::%s\n",WEBTOKEN_COMM_PIPE);
			sigwrap_close(WebFD);
			return -1;
		}
		if (readsize == 0)
		{
			TDBG("There is no data currently in the webserver pipe)\n");
			sigwrap_close(WebFD);
			return 0;
		}
	}
	if((record.session_type !=SESSION_TYPE_WEB_HTTP) && (record.session_type !=SESSION_TYPE_WEB_HTTPS))
	{
		sigwrap_close(WebFD);
		return -1;
	}

	sigwrap_close(WebFD);
	return record.racsession_id;
}

int ReadPipeData()
{
	websession_info_t s;
	char viewer_count = 0;

	while(readStruct(&s)==0)
	{
		viewer_count = getViewerCount(s.websession_token);
		if(s.Status == 1)
			viewer_count++;
		else if (s.Status == 2 && viewer_count > 0)
			viewer_count--;
		setViewerCount(s.websession_token, viewer_count);
	}

	return 0;
}

int getViewerCount(char* SessionCookieString) {
	FILE *fp = NULL;
	char viewer_count_string[128];
	int viewer_count=0;
	int file_size;
	int wret = -1, tempret = 0;
	char session_path[128];

	memset(session_path, 0, 128);
	memset(viewer_count_string, 0, 128);
	
	tempret = snprintf(session_path,sizeof(session_path), "/tmp/%s.viewer_count", SessionCookieString);  
	if( tempret < 0 || tempret >= (signed)sizeof(session_path))
	{
		TCRIT("Buffer Overflow");
		return -1;
	}
	fp = fopen(session_path, "r");
	if(NULL == fp) {
		fprintf(stderr, "viewer count is empty");
	} else {
		fseek(fp, 0L, SEEK_END);
		file_size = ftell(fp);
		rewind(fp);

		wret = fread((void *)viewer_count_string, 1, file_size, fp);
		if(wret) {
			viewer_count = atoi((const char *)viewer_count_string);
		} else {
			TCRIT("Cannot read viewer_count");
		}
		fclose(fp);
	}

	return viewer_count;
}

int setViewerCount(char* SessionCookieString, int ViewerCount) {
	FILE *fp = NULL;
	char session_path[128];

	memset(session_path, 0, 128);
	int path_len = strlen("/tmp/.viewer_count") + strlen(SessionCookieString) + 1;

	snprintf(session_path, path_len, "/tmp/%s.viewer_count", SessionCookieString);

	fp = fopen(session_path, "w");

	if(NULL == fp) {
		fprintf(stderr, "Cannot write viewer session information");
		return -1;
	} else {
		fprintf(fp, "%i", ViewerCount);
		fclose(fp);
	}

	return 0;
}

// Create pipe between webserver and ipmi
int CreateWebPipe()
{
	int pipe=-1;
	unlink(WEB_SESSION_TERM_PIPE); /* Fortify Issues :: False Positive */
	if (-1 == mkfifo(WEB_SESSION_TERM_PIPE, 0777))
	{
		printf("Could not create pipe : %s\n",WEB_SESSION_TERM_PIPE);
	}

	pipe = sigwrap_open(WEB_SESSION_TERM_PIPE, O_RDWR|O_NONBLOCK);
	if (pipe < 0)
	{
		printf("could not open the pipe : %s\n",WEB_SESSION_TERM_PIPE);
		if (unlink(WEB_SESSION_TERM_PIPE) < 0)
            TWARN("Unable to remove pipe");
		pipe = -1;
	}
	return(pipe);
}
int ClearWebSessionEntry()
{
	session_info_record_t *session_info_records;
	session_info_header_t hdr;
	uint32 total_records=0;
	int ret = -1;
	unsigned int i;

	ret=racsessinfo_getallrecords(&session_info_records,&hdr,&total_records);
	if(ret == 0)
	{
		if((hdr.sess_type_logins[SESSION_TYPE_WEB_HTTP] != 0) ||
			(hdr.sess_type_logins[SESSION_TYPE_WEB_HTTPS] != 0))
		{
			for(i=0;i<total_records;i++)
			{
				if((session_info_records[i].session_type == SESSION_TYPE_WEB_HTTP) ||
					(session_info_records[i].session_type == SESSION_TYPE_WEB_HTTPS))
					
				{
					Destroy_session(session_info_records[i].racsession_id);
					racsessinfo_unregister_session(session_info_records[i].racsession_id, 0);
				}
			}
		}
	}
	if (total_records > 0)
	{
		free(session_info_records);
		session_info_records = NULL;
	}
	return 0;
}
int Destroy_session(uint32 racid)
{
	struct dirent ** namelist;
	int n =0, tempret= 0;

	n = scandir(TMP_DIR, &namelist, qsession_filter, alphasort);
	qentry_t *session;
	const char *sessionkey;
	char session_storage_path[PATH_MAX];

	if (n < 0) {
		TCRIT("Error while terminating web session!");
	}
	else {
		while (n--) {
			session = qEntry();
			memset(session_storage_path, 0, sizeof(session_storage_path));
			tempret = snprintf(session_storage_path, sizeof(session_storage_path), "%s%s", TMP_DIR, namelist[n]->d_name);
			if(tempret < 0 || tempret >= (signed)sizeof(session_storage_path) )
			{
				TCRIT("Error in copying session storage path");
				if (session)
				{
					free(session);
					session=NULL;
				}
				free(namelist);
				return -1;
			}
			session->load(session, session_storage_path);	
			sessionkey = session->getstr(session, "_Q_SESSIONID", false);
			if((INT32U)session->getint(session, "racsession_id") == racid) {
				TCRIT("Destroying web session with key: %s", sessionkey);
					qcgisess_destroy(session);
			}
			free(namelist[n]);
		}
		free(namelist);
	}
	return 0;
}


// function to erase any web session containing the given racsession_id
int WebSession_Terminate(uint32 racid) {
	struct dirent ** namelist;
	int n;

	n = scandir(TMP_DIR, &namelist, qsession_filter, alphasort);
    qentry_t *session;
    const char *sessionkey;
	char session_storage_path[PATH_MAX];

    if (n < 0) {
		TCRIT("Error while terminating web session!");
    }
	else {
		while (n--) {
	    	session = qEntry();

    		snprintf(session_storage_path, sizeof(session_storage_path), "%s%s", TMP_DIR, namelist[n]->d_name);
	    	session->load(session, session_storage_path);	
	    	sessionkey = session->getstr(session, "_Q_SESSIONID", false);
			if((INT32U)session->getint(session, "racsession_id") == racid) {
				TCRIT("Destroying web session with key: %s", sessionkey);
	    		qcgisess_destroy(session);
			}
	    	free(namelist[n]);
	    }
	    // web session is deleted, terminate racsession as well
		if(g_corefeatures.session_management == ENABLED)
		{
			if(racsessinfo_unregister_session(racid, SESSION_UNREGISTER_REASON_LOGOUT)!=0)
			{
				TWARN("Error while unregistering WEB session with session manager");
			}
		}   
	    free(namelist);
    }
	return 0;
}

void map_func(map_handler *m) {
    if(last_map != NULL) {
        last_map->next = m;
        m->prev = last_map;
    }
    last_map = m;
}

void pre_call_hook(qentry_t *req) {
	int racid = -1;
	
	//On every incoming call before authorization, check the pipe of KVM Viewer to see if any new sessions are opened
    if(0){
        req=req;     /*-Wextra, Fix for comparison error*/
    }
	if(ReadPipeData()<0)
	{
		fprintf(stderr, "Cannot update active JViewer sessions");
	}
	if(g_corefeatures.session_management == ENABLED)
	{
		//Check any active websesion termination is initiated.
		racid = ReadCmdPipeData();
		if( racid> 0)
		{
			fprintf(stderr, "Active Web sessions Termination Initiated.\n");
			WebSession_Terminate(racid);
		}
	}
}

void post_call_hook(qentry_t *req) 
{
	if(0)
	{
		req=req;     /*-Wextra, Fix for comparison error*/
	}
}

void pre_authorized_call_hook(qentry_t *req, qentry_t *session) {
	//On every incoming call, after authorization, check if the session associated with it has any viewer_count.
	//If there is a viewer_count on this session, then it should not be destroyed unless manually done.
	//Set DO_NOT_DESTROY to extend session
    if(0){
        req=req;     /*-Wextra, Fix for comparison error*/
    }
	if(getViewerCount((char *)qcgisess_getid(session)) > 0) {
		session->putint(session, DO_NOT_DESTROY, 1, true);
	} else {
		session->putint(session, DO_NOT_DESTROY, 0, true);
	}
}

void post_authorized_call_hook(qentry_t *req, qentry_t *session) 
{
	if(0)
	{
		req=req;     /*-Wextra, Fix for comparison error*/
		session=session;
	}
}


int main()
{
	/* Retrieves the Enabled features */
	RetrieveCoreFeatures(&g_corefeatures);
	RetrieveCoreMacros(&g_coremacros,&g_corefeatures);


	FILE *mfile = fopen("/tmp/map", "ab");
	sigwrap_flock(fileno(mfile), LOCK_EX); /* Fortify Issues :: False Positive */

	for(; last_map != NULL; last_map = last_map->prev) {
		//fwrite(&last_map, sizeof(map_handler), 1, mfile);
		fprintf(mfile, "%s %lu\n", last_map->url, last_map->size);
	}

    if ( sigwrap_flock(fileno(mfile), LOCK_UN) < 0)
        TWARN("FLOCK failure");

    fclose(mfile);

	// Create pipe between webserver and ipmi 
       if(g_corefeatures.session_management == ENABLED)
	{
		CreateWebPipe();
		ClearWebSessionEntry();
	}

	sample_rest_api();
	serve_forever();
	return 0;
}
