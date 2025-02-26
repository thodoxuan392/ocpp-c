#ifndef __OCPP_CHANGE_CONFIGURATION_H
#define __OCPP_CHANGE_CONFIGURATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppCiString50Type key;
	OcppCiString500Type value;
} OcppChangeConfigurationRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppChangeConfigurationResponse;

OcppRetType OcppChangeConfiguration_BuildRequest(void* payload, char* string,
												 uint32_t* stringLength);
OcppRetType OcppChangeConfiguration_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
												 void* payload);
OcppRetType OcppChangeConfiguration_BuildResponse(void* payload, char* string,
												  uint32_t* stringLength);
OcppRetType OcppChangeConfiguration_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
												  void* payload);

#endif // __OCPP_CHANGE_CONFIGURATION_H
