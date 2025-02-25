#ifndef ___OCPP_START_TRANSACTION_H
#define ___OCPP_START_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_START_TRANSACTION_H