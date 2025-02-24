#ifndef __OCPP_CHANGE_AVAILABILITY_H
#define __OCPP_CHANGE_AVAILABILITY_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_CHANGE_AVAILABILITY_TYPE_INOPERATIVE,
	OCPP_CHANGE_AVAILABILITY_TYPE_OPERATIVE
} OcppChangeAvailabilityType;

typedef struct
{
	int connectorId;
	OcppChangeAvailabilityType type;
} OcppChangeAvailabilityRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppChangeAvailabilityResponse;

#endif // __OCPP_CHANGE_AVAILABILITY_H