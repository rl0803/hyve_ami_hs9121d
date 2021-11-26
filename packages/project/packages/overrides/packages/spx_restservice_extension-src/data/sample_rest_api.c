#include "spx_rest_ext.h"
int NOT_IN_FWUPDATE = 1;

START_AUTHORIZED_COLLECTION (spxsampleGetCollection, GET, "/sample/getcollection", 1, matches, true) 
{
	   if(0){
	        matches=matches;
	    }

	   
			COLLECTION_NEW_MODEL();
			
			MODEL_ADD_INTEGER("id",1);
			
			COLLECTION_ADD_MODEL();

			COLLECTION_OUTPUT();

	   
} END_AUTHORIZED_COLLECTION



START_AUTHORIZED_MODEL (spxsampleGetModel,GET, "/sample/getmodel", 1, matches, true) 
{

	 if(0){
        	matches=matches;
	    }

	     MODEL_ADD_INTEGER("id", 1);

              MODEL_OUTPUT();
 
}END_AUTHORIZED_MODEL

 
START_AUTHORIZED_MODEL (spxsampleDelete,DELETE, "/sample/delete", 1, matches, true) 
{

	 if(0){
        	matches=matches;
	    }

	 
    THROW_MODEL_ERROR(STATUS_404, "Invalid API Call", INVALID_API_CALL);
 
}END_AUTHORIZED_MODEL

START_AUTHORIZED_MODEL (spxsamplePut, PUT, "/sample/put", 1, matches, true) 
{
     if(0)	{
	        matches=matches;
	}
	 
 	THROW_MODEL_ERROR(STATUS_404, "Invalid API Call", INVALID_API_CALL);

}END_AUTHORIZED_MODEL


START_AUTHORIZED_MODEL (spxsamplePost, POST, "/sample/post", 1, matches, true) 
{
     if(0){
        matches=matches;
	}
		THROW_MODEL_ERROR(STATUS_404, "Invalid API Call", INVALID_API_CALL);

 
}END_AUTHORIZED_MODEL

//testing purpose added this API.
START_HANDLER_AUTHORIZED_UPLOAD (uploadsample, POST, "/maintenance/firmware", 4, matches, false, "/mnt/fwupdate/testing", 10 * 1024 * 1024, 0) 
{


    if(0){
        matches=matches;
    }
	

}END_HANDLER_AUTHORIZED_UPLOAD





int sample_rest_api()
{
    add_handler(spxsampleGetCollection);
	 add_handler(spxsampleGetModel);
    add_handler(spxsampleDelete);   
    add_handler(spxsamplePut);   
    add_handler(spxsamplePost); 
	
   MAP_UPLOAD_HANDLER(uploadsample);
    return 0;
}
