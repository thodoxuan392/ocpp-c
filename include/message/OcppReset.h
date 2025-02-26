#ifndef __OCPP_RESET_H
#define __OCPP_RESET_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef enum
{
	OCPP_RESET_TYPE_HARD,
	OCPP_RESET_TYPE_SOFT
} OcppResetType;

typedef struct
{
	OcppResetType type;
} OcppResetRequest;

typedef struct
{
	OcppResetStatus status;
} OcppResetResponse;

OcppRetType OcppReset_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppReset_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize, void* payload);
OcppRetType OcppReset_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppReset_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
									void* payload);

#endif // __OCPP_RESET_H