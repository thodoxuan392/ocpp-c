#ifndef __OCPP_SET_CHARGING_PROFILE_H
#define __OCPP_SET_CHARGING_PROFILE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	OcppChargeProfile csChargingProfiles;
} OcppSetChargingProfileRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppSetChargingProfileResponse;
#endif // __OCPP_SET_CHARGING_PROFILE_H