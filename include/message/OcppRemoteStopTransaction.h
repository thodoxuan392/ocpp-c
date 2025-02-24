#ifndef __OCPP_REMOTE_STOP_TRANSACTION_H
#define __OCPP_REMOTE_STOP_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int transactionId;
} OcppRemoteStopTransactionRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppRemoteStopTransactionResponse;

#endif // __OCPP_REMOTE_STOP_TRANSACTION_H