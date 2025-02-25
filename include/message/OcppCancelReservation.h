#ifndef __OCPP_CANCEL_RESERVATION_H
#define __OCPP_CANCEL_RESERVATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int reservationId;
} OcppCancelReservationRequest;

typedef struct
{
	OcppCancelReservationStatus status;
} OcppCancelReservationResponse;

#endif // __OCPP_CANCEL_RESERVATION_H