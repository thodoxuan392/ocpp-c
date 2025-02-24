#ifndef __OCPP_UNLOCK_CONNECTOR_H
#define __OCPP_UNLOCK_CONNECTOR_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
} OcppUnlockConnectorRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppUnlockConnectorResponse;

#endif // __OCPP_UNLOCK_CONNECTOR_H