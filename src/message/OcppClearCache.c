#include <OcppClearCache.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppClearCache_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{}");
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppClearCache_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	*tokenSize = 0;
	return OCPP_OK;
}
OcppRetType OcppClearCache_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStrLength[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStrLength, 0, sizeof(statusStrLength));

	(void)OcppJson_BuildMessageStatus(ocppPayload->clearCacheRes.status, statusStrLength,
									  &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStrLength);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppClearCache_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
										 void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 2, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(json + token[i + 1].start,
										token[i + 1].end - token[i + 1].start,
										&ocppPayload->clearCacheRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
