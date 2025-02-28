#ifndef ___OCPP_CLEAR_CACHE_H
#define ___OCPP_CLEAR_CACHE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
} OcppClearCacheRequest;

typedef struct
{
	OcppClearCacheStatus status;
} OcppClearCacheResponse;

OcppRetType OcppClearCache_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppClearCache_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										void* payload);
OcppRetType OcppClearCache_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppClearCache_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
										 void* payload);

#endif // __OCPP_CLEAR_CACHE_H