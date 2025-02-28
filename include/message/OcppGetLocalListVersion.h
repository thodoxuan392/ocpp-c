#ifndef __OCPP_GET_LOCAL_LIST_VERSION_H
#define __OCPP_GET_LOCAL_LIST_VERSION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
} OcppGetLocalListVersionRequest;

typedef struct
{
	int listVersion;
} OcppGetLocalListVersionResponse;

OcppRetType OcppGetLocalListVersion_BuildRequest(void* payload, char* string,
												 uint32_t* stringLength);
OcppRetType OcppGetLocalListVersion_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												 void* payload);
OcppRetType OcppGetLocalListVersion_BuildResponse(void* payload, char* string,
												  uint32_t* stringLength);
OcppRetType OcppGetLocalListVersion_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												  void* payload);
#endif // __OCPP_GET_LOCAL_LIST_VERSION_H