#ifndef __OCPP_REMOTE_START_TRANSACTION_H
#define __OCPP_REMOTE_START_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	char idTag[OCPP_ID_TAG_MAX_LENGTH];
	OcppChargeProfile chargingProfile;
} OcppRemoteStartTransactionRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppRemoteStartTransactionResponse;

#endif // __OCPP_REMOTE_START_TRANSACTION_H