#ifndef __OCPP_CHANGE_AVAILABILITY_H
#define __OCPP_CHANGE_AVAILABILITY_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_AVAILABILITY_TYPE_INOPERATIVE,
	OCPP_AVAILABILITY_TYPE_OPERATIVE
} OcppAvailabilityType;

typedef struct
{
	int connectorId;
	OcppAvailabilityType type;
} OcppChangeAvailabilityRequest;

typedef struct
{
	OcppAvailabilityStatus status;
} OcppChangeAvailabilityResponse;

#endif // __OCPP_CHANGE_AVAILABILITY_H