#ifndef __OCPP_RESERVE_NOW_H
#define __OCPP_RESERVE_NOW_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	OcppDateTime expiryDate;
	char idTag[OCPP_ID_TAG_MAX_LENGTH];
	char parentIdTag[OCPP_ID_TAG_MAX_LENGTH];
	int reservationId;
} OcppReserveNowRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppReserveNowResponse;

#endif // __OCPP_RESERVE_NOW_H