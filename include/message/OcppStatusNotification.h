#ifndef ___OCPP_STATUS_NOTIFICATION_H
#define ___OCPP_STATUS_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	OcppChargePointErrorCode errorCode;
	OcppCiString50Type info;
	OcppChargePointStatus status;
	OcppDateTime timestamp;
	OcppCiString255Type vendorId;
	OcppCiString50Type vendorErrorCode;
} OcppStatusNotificationRequest;

typedef struct
{
} OcppStatusNotificationResponse;

OcppRetType OcppStatusNotification_BuildRequest(void* payload, char* string,
												uint32_t* stringLength);
OcppRetType OcppStatusNotification_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												void* payload);
OcppRetType OcppStatusNotification_BuildResponse(void* payload, char* string,
												 uint32_t* stringLength);
OcppRetType OcppStatusNotification_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												 void* payload);

#endif // ___OCPP_STATUS_NOTIFICATION_H