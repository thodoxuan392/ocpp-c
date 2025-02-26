#ifndef __OCPP_RESERVE_NOW_H
#define __OCPP_RESERVE_NOW_H

#include <OcppConfig.h>
#include <OcppTypes.h>

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

OcppRetType OcppReserveNow_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppReserveNow_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
										void* payload);
OcppRetType OcppReserveNow_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppReserveNow_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
										 void* payload);

#endif // __OCPP_RESERVE_NOW_H