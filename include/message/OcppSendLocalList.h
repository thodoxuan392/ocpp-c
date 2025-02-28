#ifndef __OCPP_SEND_LOCAL_LIST_H
#define __OCPP_SEND_LOCAL_LIST_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int listVersion;
	OcppAuthorizationData localAuthorizationList[OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH];
	int noLocalAuthorizationList;
	OcppUpdateType updateType;
} OcppSendLocalListRequest;

typedef struct
{
	OcppUpdateStatus status;
} OcppSendLocalListResponse;

OcppRetType OcppSendLocalList_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppSendLocalList_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										   void* payload);
OcppRetType OcppSendLocalList_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppSendLocalList_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											void* payload);

#endif // __OCPP_SEND_LOCAL_LIST_H