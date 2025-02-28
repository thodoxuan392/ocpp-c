#ifndef __OCPP_CLEAR_CHARGING_PROFILE_H
#define __OCPP_CLEAR_CHARGING_PROFILE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int id;
	int connectorId;
	OcppChargingProfilePurpose chargingProfilePurpose;
	int stackLevel;
} OcppClearChargingProfileRequest;

typedef struct
{
	OcppClearChargingProfileStatus status;
} OcppClearChargingProfileResponse;

OcppRetType OcppClearChargingProfile_BuildRequest(void* payload, char* string,
												  uint32_t* stringLength);
OcppRetType OcppClearChargingProfile_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												  void* payload);
OcppRetType OcppClearChargingProfile_BuildResponse(void* payload, char* string,
												   uint32_t* stringLength);
OcppRetType OcppClearChargingProfile_ParseResponse(char* json, jsmntok_t* token,
												   uint32_t* tokenSize, void* payload);

#endif // __OCPP_CLEAR_CHARGING_PROFILE_H