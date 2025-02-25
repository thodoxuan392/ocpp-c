#ifndef __OCPP_RESERVE_NOW_H
#define __OCPP_RESERVE_NOW_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	OcppDateTime expiryDate;
	OcppIdToken idTag;
	OcppIdToken parentIdTag;
	int reservationId;
} OcppReserveNowRequest;

typedef struct
{
	OcppReservationStatus status;
} OcppReserveNowResponse;

#endif // __OCPP_RESERVE_NOW_H