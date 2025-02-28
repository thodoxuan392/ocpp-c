#include <OcppHeartBeat.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppHeartBeat_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	ret = sprintf(string, "{}");
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppHeartBeat_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
									   void* payload)
{
	*tokenSize = 0;
	return OCPP_OK;
}
OcppRetType OcppHeartBeat_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char currentTimeStr[OCPP_DATE_TIME_MAX_LENGTH];
	memset(currentTimeStr, 0, sizeof(currentTimeStr));

	(void)OcppJson_BuildDateTime(&ocppPayload->heartBeatRes.currentTime, currentTimeStr,
								 &buildStrLength);

	ret = sprintf(string, "{\"currentTime\": \"%s\"}", currentTimeStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppHeartBeat_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "currentTime") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->heartBeatRes.currentTime);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}