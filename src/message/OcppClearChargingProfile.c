#include <OcppClearChargingProfile.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppClearChargingProfile_BuildRequest(void* payload, char* string,
												  uint32_t* stringLength)
{
	int ret;
	uint32_t buildLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char chargingProfilePurposeStr[OCPP_CHARGING_PROFILE_PURPOSE_MAX_LENGTH];
	memset(chargingProfilePurposeStr, 0, sizeof(chargingProfilePurposeStr));

	if(OcppJson_BuildChargingProfilePurpose(
		   ocppPayload->clearChargingProfileReq.chargingProfilePurpose, chargingProfilePurposeStr,
		   &buildLength) != OCPP_OK)
	{
		return OCPP_NOT_OK;
	}

	ret = sprintf(
		string,
		"{\"id\": %d,\"connectorId\": %d,\"chargingProfilePurpose\": \"%s\",\"stackLevel\": %d}",
		ocppPayload->clearChargingProfileReq.id, ocppPayload->clearChargingProfileReq.connectorId,
		chargingProfilePurposeStr, ocppPayload->clearChargingProfileReq.stackLevel);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppClearChargingProfile_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 4)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 4, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "id") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->clearChargingProfileReq.id);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->clearChargingProfileReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargingProfilePurpose") == 0)
		{
			OcppJson_ParseChargingProfilePurpose(
				json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
				&ocppPayload->clearChargingProfileReq.chargingProfilePurpose);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "stackLevel") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->clearChargingProfileReq.stackLevel);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppClearChargingProfile_BuildResponse(void* payload, char* string,
												   uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStrLength[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStrLength, 0, sizeof(statusStrLength));

	(void)OcppJson_BuildMessageStatus(ocppPayload->clearChargingProfileRes.status, statusStrLength,
									  &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStrLength);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppClearChargingProfile_ParseResponse(char* json, jsmntok_t* token,
												   uint32_t* tokenSize, void* payload)
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
										&ocppPayload->clearChargingProfileRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}