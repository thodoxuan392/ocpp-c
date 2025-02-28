#ifndef __OCPP_TRIGGER_MESSAGE_H
#define __OCPP_TRIGGER_MESSAGE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppMessageTrigger requestedMessage;
} OcppTriggerMessageRequest;

typedef struct
{
	OcppTriggerMessageStatus status;
} OcppTriggerMessageResponse;

OcppRetType OcppTriggerMessage_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppTriggerMessage_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											void* payload);
OcppRetType OcppTriggerMessage_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppTriggerMessage_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											 void* payload);

#endif // __OCPP_TRIGGER_MESSAGE_H