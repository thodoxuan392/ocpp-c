#ifndef __OCPP_DATA_TRANSFER_H
#define __OCPP_DATA_TRANSFER_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char vendorId[OCPP_VENDOR_ID_MAX_LENGTH];
	char messageId[OCPP_DATA_TRANSFER_MESSAGE_ID_MAX_LENGTH];
	char data[OCPP_DATA_TRANSFER_DATA_MAX_LENGTH];
} OcppDataTransferRequest;

typedef struct
{
	OcppMessageStatus status;
	char data[OCPP_DATA_TRANSFER_DATA_MAX_LENGTH];
} OcppDataTransferResponse;

#endif // __OCPP_DATA_TRANSFER_H