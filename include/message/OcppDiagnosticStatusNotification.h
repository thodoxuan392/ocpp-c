#ifndef ___OCPP_DIAGNOSTIC_STATUS_NOTIFICATION_H
#define ___OCPP_DIAGNOSTIC_STATUS_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_DIAGNOSTIC_STATUS_IDLE,
	OCPP_DIAGNOSTIC_STATUS_UPLOADED,
	OCPP_DIAGNOSTIC_STATUS_UPLOAD_FAILED,
	OCPP_DIAGNOSTIC_STATUS_UPLOADING
} OcppDiagnosticStatus;

typedef struct
{
	OcppDiagnosticStatus status;
} OcppDiagnosticStatusNotificationRequest;

typedef struct
{
} OcppDiagnosticStatusNotificationResponse;

#endif // ___OCPP_DIAGNOSTIC_STATUS_NOTIFICATION_H