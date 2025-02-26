#ifndef __OCPP_FIRMWARE_STATUS_NOTIFICATION_H
#define __OCPP_FIRMWARE_STATUS_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppFirmwareStatus status;
} OcppFirmwareStatusNotificationRequest;

typedef struct
{
} OcppFirmwareStatusNotificationResponse;

OcppRetType OcppFirmwareStatusNotification_BuildRequest(void* payload, char* string,
														uint32_t* stringLength);
OcppRetType OcppFirmwareStatusNotification_ParseRequest(char* json, jsmntok_t* token,
														uint32_t tokenSize, void* payload);
OcppRetType OcppFirmwareStatusNotification_BuildResponse(void* payload, char* string,
														 uint32_t* stringLength);
OcppRetType OcppFirmwareStatusNotification_ParseResponse(char* json, jsmntok_t* token,
														 uint32_t tokenSize, void* payload);

#endif // __OCPP_FIRMWARE_STATUS_NOTIFICATION_H