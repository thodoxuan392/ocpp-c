#include <OcppUpdateFirmware.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppUpdateFirmware_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char retrieveDateStr[OCPP_DATE_TIME_MAX_LENGTH];
	memset(retrieveDateStr, 0, sizeof(retrieveDateStr));

	OcppJson_BuildDateTime(&ocppPayload->updateFirmwareReq.retrieveDate, retrieveDateStr,
						   &buildStrLength);

	ret = sprintf(string,
				  "{\"location\": \"%s\", \"retries\": %d, "
				  "\"retrieveDate\": \"%s\",\"retryInterval\": %d}",
				  ocppPayload->updateFirmwareReq.location, ocppPayload->updateFirmwareReq.retries,
				  retrieveDateStr, ocppPayload->updateFirmwareReq.retryInterval);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppUpdateFirmware_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "location") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->updateFirmwareReq.location);

			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "retries") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->updateFirmwareReq.retries);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "retrieveDate") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->updateFirmwareReq.retrieveDate);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "retryInterval") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->updateFirmwareReq.retryInterval);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppUpdateFirmware_BuildResponse(void* payload, char* string, uint32_t* stringLength)
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
OcppRetType OcppUpdateFirmware_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											 void* payload)
{
	*tokenSize = 0;
	return OCPP_OK;
}