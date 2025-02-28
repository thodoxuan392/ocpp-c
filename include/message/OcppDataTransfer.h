#ifndef __OCPP_DATA_TRANSFER_H
#define __OCPP_DATA_TRANSFER_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppCiString255Type vendorId;
	OcppCiString50Type messageId;
	char data[OCPP_DATA_TRANSFER_DATA_MAX_LENGTH];
} OcppDataTransferRequest;

typedef struct
{
	OcppDataTransferStatus status;
	char data[OCPP_DATA_TRANSFER_DATA_MAX_LENGTH];
} OcppDataTransferResponse;

OcppRetType OcppDataTransfer_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppDataTransfer_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										  void* payload);
OcppRetType OcppDataTransfer_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppDataTransfer_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
										   void* payload);

#endif // __OCPP_DATA_TRANSFER_H