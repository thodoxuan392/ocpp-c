#include <OcppTriggerMessage.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppTriggerMessage_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char requestedMessageStr[OCPP_TRIGGER_MESSAGE_MAX_LENGTH];
	memset(requestedMessageStr, 0, sizeof(requestedMessageStr));

	OcppJson_BuildMessageTrigger(ocppPayload->triggerMessageReq.requestedMessage,
								 requestedMessageStr, &buildStrLength);

	ret = sprintf(string, "{\"requestedMessage\": \"%s\"}", requestedMessageStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppTriggerMessage_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t tranDataTokenIdx;
	uint32_t tokenLen;

	if(*tokenSize < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 1, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "requestedMessage") == 0)
		{
			OcppJson_ParseMessageTrigger(json + token[i + 1].start,
										 token[i + 1].end - token[i + 1].start,
										 &ocppPayload->triggerMessageReq.requestedMessage);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppTriggerMessage_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildMessageStatus(ocppPayload->triggerMessageRes.status, statusStr, &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppTriggerMessage_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											 void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 1, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(json + token[i + 1].start,
										token[i + 1].end - token[i + 1].start,
										&ocppPayload->triggerMessageRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}