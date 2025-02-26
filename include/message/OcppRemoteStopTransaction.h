#ifndef __OCPP_REMOTE_STOP_TRANSACTION_H
#define __OCPP_REMOTE_STOP_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int transactionId;
} OcppRemoteStopTransactionRequest;

typedef struct
{
	OcppRemoteStartStopStatus status;
} OcppRemoteStopTransactionResponse;

OcppRetType OcppRemoteStopTransaction_BuildRequest(void* payload, char* string,
												   uint32_t* stringLength);
OcppRetType OcppRemoteStopTransaction_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
												   void* payload);
OcppRetType OcppRemoteStopTransaction_BuildResponse(void* payload, char* string,
													uint32_t* stringLength);
OcppRetType OcppRemoteStopTransaction_ParseResponse(char* json, jsmntok_t* token,
													uint32_t tokenSize, void* payload);

#endif // __OCPP_REMOTE_STOP_TRANSACTION_H