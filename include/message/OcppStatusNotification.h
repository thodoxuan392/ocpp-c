#ifndef ___OCPP_STATUS_NOTIFICATION_H
#define ___OCPP_STATUS_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	OcppChargePointErrorCode errorCode;
	OcppCiString50Type info;
	OcppMessageStatus status;
	OcppDateTime timestamp;
	OcppCiString255Type vendorId;
	OcppCiString50Type vendorErrorCode;
} OcppStatusNotificationRequest;

typedef struct
{
} OcppStatusNotificationResponse;

#endif // ___OCPP_STATUS_NOTIFICATION_H