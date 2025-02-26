#ifndef __OCPP_CHANGE_AVAILABILITY_H
#define __OCPP_CHANGE_AVAILABILITY_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	OcppAvailabilityType type;
} OcppChangeAvailabilityRequest;

typedef struct
{
	OcppAvailabilityStatus status;
} OcppChangeAvailabilityResponse;

OcppRetType OcppChangeAvailability_BuildRequest(void* payload, char* string,
												uint32_t* stringLength);
OcppRetType OcppChangeAvailability_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
												void* payload);
OcppRetType OcppChangeAvailability_BuildResponse(void* payload, char* string,
												 uint32_t* stringLength);
OcppRetType OcppChangeAvailability_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
												 void* payload);

#endif // __OCPP_CHANGE_AVAILABILITY_H