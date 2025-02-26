#ifndef __OCPP_GET_CONFIGURATION_H
#define __OCPP_GET_CONFIGURATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppCiString50Type key;
	bool readonly;
	OcppCiString500Type value;
} OcppKeyValue;

typedef struct
{
	OcppCiString50Type key[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
} OcppGetConfigurationRequest;

typedef struct
{
	OcppKeyValue configurationKey[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
	OcppCiString50Type unkownKey[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
} OcppGetConfigurationResponse;

OcppRetType OcppGetConfiguration_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppGetConfiguration_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
											  void* payload);
OcppRetType OcppGetConfiguration_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppGetConfiguration_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
											   void* payload);

#endif // __OCPP_GET_CONFIGURATION_H