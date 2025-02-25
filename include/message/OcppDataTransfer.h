#ifndef __OCPP_DATA_TRANSFER_H
#define __OCPP_DATA_TRANSFER_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_DATA_TRANSFER_H