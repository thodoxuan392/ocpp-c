#include <OcppChangeAvailability.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppChangeAvailability_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char availabilityTypeStr[OCPP_AVAILABILITY_TYPE_MAX_LENGTH];
	memset(availabilityTypeStr, 0, sizeof(availabilityTypeStr));

	(void)OcppJson_BuildAvailabilityType(ocppPayload->changeAvailabilityReq.type,
										 availabilityTypeStr, &buildStrLength);

	ret = sprintf(string, "{\"connectorId\": %d, \"type\": \"%s\"}",
				  ocppPayload->changeAvailabilityReq.connectorId, availabilityTypeStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppChangeAvailability_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->changeAvailabilityReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "type") == 0)
		{
			OcppJson_ParseAvailabilityType(json + token[i + 1].start,
										   token[i + 1].end - token[i + 1].start,
										   &ocppPayload->changeAvailabilityReq.type);
			Ocpp_LogError(("[OCPP] Availability Type %.*s %d",
						   token[i + 1].end - token[i + 1].start, json + token[i + 1].start,
						   ocppPayload->changeAvailabilityReq.type));

			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppChangeAvailability_BuildResponse(void* payload, char* string,
												 uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStrLength[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStrLength, 0, sizeof(statusStrLength));

	(void)OcppJson_BuildMessageStatus(ocppPayload->changeAvailabilityRes.status, statusStrLength,
									  &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStrLength);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppChangeAvailability_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
										&ocppPayload->changeAvailabilityRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}