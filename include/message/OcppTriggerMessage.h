#ifndef __OCPP_TRIGGER_MESSAGE_H
#define __OCPP_TRIGGER_MESSAGE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_TRIGGER_MESSAGE_BOOT_NOTIFICATION,
	OCPP_TRIGGER_MESSAGE_DIAGNOSTIC_NOTIFICATION,
	OCPP_TRIGGER_MESSAGE_FIRMWARE_STATUS_NOTIFICATION,
	OCPP_TRIGGER_MESSAGE_HEARTBEAT,
	OCPP_TRIGGER_MESSAGE_METER_VALUE,
	OCPP_TRIGGER_MESSAGE_STATUS_NOTIFICATION
} OcppMessageTrigger;

typedef struct
{
	OcppMessageTrigger requestedMessage;
} OcppTriggerMessageRequest;

typedef struct
{
	OcppTriggerMessageStatus status;
} OcppTriggerMessageResponse;

#endif // __OCPP_TRIGGER_MESSAGE_H