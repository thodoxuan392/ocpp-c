#include <OcppChangeConfiguration.h>

#include <OcppMessage.h>
#include <OcppJson.h>
OcppRetType OcppChangeConfiguration_BuildRequest(void* payload, char* string,
												 uint32_t* stringLength)
{
	int ret;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret =
		sprintf(string, "{\"key\": \"%s\", \"value\": \"%s\"}",
				ocppPayload->changeConfigurationReq.key, ocppPayload->changeConfigurationReq.value);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppChangeConfiguration_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "key") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->changeConfigurationReq.key);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "value") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->changeConfigurationReq.value);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppChangeConfiguration_BuildResponse(void* payload, char* string,
												  uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStrLength[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStrLength, 0, sizeof(statusStrLength));

	(void)OcppJson_BuildMessageStatus(ocppPayload->changeConfigurationRes.status, statusStrLength,
									  &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStrLength);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppChangeConfiguration_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 1)
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
										&ocppPayload->changeConfigurationRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}