#ifndef __OCPP_STOP_TRANSACTION_H
#define __OCPP_STOP_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppIdToken idTag;
	int meterStop;
	OcppDateTime timestamp;
	int transactionId;
	OcppReason reason;
	OcppMeterValue transactionData[OCPP_TRANSACTION_DATA_ARRAY_MAX_LENGTH];
} OcppStopTransactionRequest;

typedef struct
{
	OcppIdTagInfo idTagInfo;
} OcppStopTransactionResponse;

OcppRetType OcppStopTransaction_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppStopTransaction_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
											 void* payload);
OcppRetType OcppStopTransaction_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppStopTransaction_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
											  void* payload);

#endif // __OCPP_STOP_TRANSACTION_H