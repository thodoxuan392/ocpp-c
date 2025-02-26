#ifndef ___OCPP_DIAGNOSTIC_STATUS_NOTIFICATION_H
#define ___OCPP_DIAGNOSTIC_STATUS_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>
typedef struct
{
	OcppDiagnosticsStatus status;
} OcppDiagnosticStatusNotificationRequest;

typedef struct
{
} OcppDiagnosticStatusNotificationResponse;

OcppRetType OcppDiagnosticStatusNotification_BuildRequest(void* payload, char* string,
														  uint32_t* stringLength);
OcppRetType OcppDiagnosticStatusNotification_ParseRequest(char* json, jsmntok_t* token,
														  uint32_t tokenSize, void* payload);
OcppRetType OcppDiagnosticStatusNotification_BuildResponse(void* payload, char* string,
														   uint32_t* stringLength);
OcppRetType OcppDiagnosticStatusNotification_ParseResponse(char* json, jsmntok_t* token,
														   uint32_t tokenSize, void* payload);

#endif // ___OCPP_DIAGNOSTIC_STATUS_NOTIFICATION_H