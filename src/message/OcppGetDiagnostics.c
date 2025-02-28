#include <OcppGetDiagnostics.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppGetDiagnostic_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char startTimeStr[OCPP_DATE_TIME_MAX_LENGTH];
	char stopTimeStr[OCPP_DATE_TIME_MAX_LENGTH];

	memset(startTimeStr, 0, sizeof(startTimeStr));
	memset(stopTimeStr, 0, sizeof(stopTimeStr));

	(void)OcppJson_BuildDateTime(&ocppPayload->getDiagnosticReq.startTime, startTimeStr,
								 &buildStrLength);
	(void)OcppJson_BuildDateTime(&ocppPayload->getDiagnosticReq.stopTime, stopTimeStr,
								 &buildStrLength);

	ret = sprintf(string,
				  "{\"location\": \"%s\", \"retries\": %d,\"retryInterval\": %d, "
				  "\"startTime\": \"%s\",\"stopTime\": \"%s\"}",
				  ocppPayload->getDiagnosticReq.location, ocppPayload->getDiagnosticReq.retries,
				  ocppPayload->getDiagnosticReq.retryInterval, startTimeStr, stopTimeStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetDiagnostic_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										   void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 5)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 5, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "location") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->getDiagnosticReq.location);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "retries") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->getDiagnosticReq.retries);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "retryInterval") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->getDiagnosticReq.retryInterval);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "startTime") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->getDiagnosticReq.startTime);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "stopTime") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->getDiagnosticReq.stopTime);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppGetDiagnostic_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{\"filename\": \"%s\"}", ocppPayload->getDiagnosticRes.fileName);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetDiagnostic_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "fileName") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->getDiagnosticRes.fileName);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}