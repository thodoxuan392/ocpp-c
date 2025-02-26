#ifndef __OCPP_UNLOCK_CONNECTOR_H
#define __OCPP_UNLOCK_CONNECTOR_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
} OcppUnlockConnectorRequest;

typedef struct
{
	OcppUnlockStatus status;
} OcppUnlockConnectorResponse;

OcppRetType OcppUnlockConnector_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppUnlockConnector_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
											 void* payload);
OcppRetType OcppUnlockConnector_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppUnlockConnector_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
											  void* payload);

#endif // __OCPP_UNLOCK_CONNECTOR_H