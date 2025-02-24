#ifndef ___OCPP_STATUS_NOTIFICATION_H
#define ___OCPP_STATUS_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	OcppErrorCode errorCode;
	char info[OCPP_STATUS_NOTIFICATION_INFO_MAX_LENGTH];
	OcppMessageStatus status;
	OcppDateTime timestamp;
	char vendorId[OCPP_VENDOR_ID_MAX_LENGTH];
	char vendorErrorCode[OCPP_VENDOR_ERROR_CODE_MAX_LENGTH];
} OcppStatusNotificationRequest;

typedef struct
{
} OcppStatusNotificationResponse;

#endif // ___OCPP_STATUS_NOTIFICATION_H