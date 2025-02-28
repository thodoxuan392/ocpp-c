#ifndef __OCPP_SET_CHARGING_PROFILE_H
#define __OCPP_SET_CHARGING_PROFILE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	OcppChargingProfile csChargingProfiles;
} OcppSetChargingProfileRequest;

typedef struct
{
	OcppChargingProfileStatus status;
} OcppSetChargingProfileResponse;

OcppRetType OcppSetChargingProfile_BuildRequest(void* payload, char* string,
												uint32_t* stringLength);
OcppRetType OcppSetChargingProfile_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												void* payload);
OcppRetType OcppSetChargingProfile_BuildResponse(void* payload, char* string,
												 uint32_t* stringLength);
OcppRetType OcppSetChargingProfile_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												 void* payload);
#endif // __OCPP_SET_CHARGING_PROFILE_H