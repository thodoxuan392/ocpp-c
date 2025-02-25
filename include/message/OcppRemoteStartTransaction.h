#ifndef __OCPP_REMOTE_START_TRANSACTION_H
#define __OCPP_REMOTE_START_TRANSACTION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_REMOTE_START_TRANSACTION_H