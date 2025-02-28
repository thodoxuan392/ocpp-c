#ifndef __OCPP_HEARTBEAT_H
#define __OCPP_HEARTBEAT_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
} OcppHeartBeatRequest;

typedef struct
{
	OcppDateTime currentTime;
} OcppHeartBeatResponse;

OcppRetType OcppHeartBeat_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppHeartBeat_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
									   void* payload);
OcppRetType OcppHeartBeat_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppHeartBeat_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
										void* payload);

#endif // __OCPP_HEARTBEAT_H