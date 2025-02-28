#ifndef __OCPP_CANCEL_RESERVATION_H
#define __OCPP_CANCEL_RESERVATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int reservationId;
} OcppCancelReservationRequest;

typedef struct
{
	OcppCancelReservationStatus status;
} OcppCancelReservationResponse;

OcppRetType OcppCancelReservation_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppCancelReservation_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											   void* payload);
OcppRetType OcppCancelReservation_BuildResponse(void* payload, char* string,
												uint32_t* stringLength);
OcppRetType OcppCancelReservation_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												void* payload);

#endif // __OCPP_CANCEL_RESERVATION_H