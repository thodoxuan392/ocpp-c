#ifndef __OCPP_STOP_TRANSACTION_H
#define __OCPP_STOP_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_STOP_TRANSACTION_H