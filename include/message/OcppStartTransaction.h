#ifndef ___OCPP_START_TRANSACTION_H
#define ___OCPP_START_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	OcppIdToken idTag;
	int meterStart;
	int reservationId;
	OcppDateTime timestamp;
} OcppStartTransactionRequest;

typedef struct
{
	OcppIdTagInfo idTagInfo;
	int transactionId;
} OcppStartTransactionResponse;

OcppRetType OcppStartTransaction_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppStartTransaction_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											  void* payload);
OcppRetType OcppStartTransaction_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppStartTransaction_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											   void* payload);

#endif // __OCPP_START_TRANSACTION_H