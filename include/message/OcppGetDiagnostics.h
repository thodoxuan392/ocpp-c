#ifndef __OCPP_GET_DIAGNOSTIC_H
#define __OCPP_GET_DIAGNOSTIC_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	char location[OCPP_LOCATION_MAX_LENGTH];
	int retries;
	int retryInterval;
	OcppDateTime startTime;
	OcppDateTime stopTime;
} OcppGetDiagnosticRequest;

typedef struct
{
	OcppCiString255Type filename;
} OcppGetDiagnosticResponse;

OcppRetType OcppGetDiagnostic_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppGetDiagnostic_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
										   void* payload);
OcppRetType OcppGetDiagnostic_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppGetDiagnostic_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
											void* payload);

#endif // __OCPP_GET_DIAGNOSTIC_H