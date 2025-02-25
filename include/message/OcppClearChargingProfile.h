#ifndef __OCPP_CLEAR_CHARGING_PROFILE_H
#define __OCPP_CLEAR_CHARGING_PROFILE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_CLEAR_CHARGING_PROFILE_H