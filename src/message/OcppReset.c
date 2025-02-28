#include <OcppReset.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppReset_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char typeStr[OCPP_RESET_TYPE_MAX_LENGTH];
	memset(typeStr, 0, sizeof(typeStr));

	OcppJson_BuildResetType(ocppPayload->resetReq.type, typeStr, &buildStrLength);

	ret = sprintf(string, "{\"type\": \"%s\"}", typeStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppReset_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize, void* payload)
{
	size_t i;
	uint32_t tokenLen;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 1, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "type") == 0)
		{
			OcppJson_ParseResetType(json + token[i + 1].start,
									token[i + 1].end - token[i + 1].start,
									&ocppPayload->resetReq.type);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppReset_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildMessageStatus(ocppPayload->resetRes.status, statusStr, &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppReset_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
									void* payload)
{
	size_t i;
	uint32_t tokenLen;
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
										&ocppPayload->resetRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}