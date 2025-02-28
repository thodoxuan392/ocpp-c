#ifndef __OCPP_REMOTE_START_TRANSACTION_H
#define __OCPP_REMOTE_START_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	OcppIdToken idTag;
	OcppChargingProfile chargingProfile;
} OcppRemoteStartTransactionRequest;

typedef struct
{
	OcppRemoteStartStopStatus status;
} OcppRemoteStartTransactionResponse;

OcppRetType OcppRemoteStartTransaction_BuildRequest(void* payload, char* string,
													uint32_t* stringLength);
OcppRetType OcppRemoteStartTransaction_ParseRequest(char* json, jsmntok_t* token,
													uint32_t* tokenSize, void* payload);
OcppRetType OcppRemoteStartTransaction_BuildResponse(void* payload, char* string,
													 uint32_t* stringLength);
OcppRetType OcppRemoteStartTransaction_ParseResponse(char* json, jsmntok_t* token,
													 uint32_t* tokenSize, void* payload);

#endif // __OCPP_REMOTE_START_TRANSACTION_H