#ifndef __OCPP_AUTHORIZE_H
#define __OCPP_AUTHORIZE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef OcppMessageStatus OcppAuthorizationStatus;
typedef struct
{
	OcppIdToken idTag;
} OcppAuthorizeRequest;

typedef struct
{
	OcppIdTagInfo idTagInfo;
} OcppAuthorizeResponse;

OcppRetType OcppAuthorize_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppAuthorize_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
									   void* payload);
OcppRetType OcppAuthorize_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppAuthorize_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
										void* payload);

#endif // __OCPP_AUTHORIZE_H