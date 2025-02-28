#include <OcppSetChargingProfile.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppSetChargingProfile_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char chargingProfileStr[OCPP_CHARGING_PROFILE_MAX_LENGTH];
	memset(chargingProfileStr, 0, sizeof(chargingProfileStr));

	OcppJson_BuildChargingProfile(&ocppPayload->setChargingProfileReq.csChargingProfiles,
								  chargingProfileStr, &buildStrLength);

	ret = sprintf(string, "{\"connectorId\": %d,\"csChargingProfiles\": %s}",
				  ocppPayload->setChargingProfileReq.connectorId, chargingProfileStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppSetChargingProfile_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t localListTokenIdx;
	uint32_t tokenLen;

	if(*tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 2, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->setChargingProfileReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "csChargingProfiles") == 0)
		{
			tokenLen = *tokenSize - i - 1;
			OcppJson_ParseChargingProfile(json, &token[i + 1], &tokenLen,
										  &ocppPayload->setChargingProfileReq.csChargingProfiles);
			i += tokenLen + 1;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppSetChargingProfile_BuildResponse(void* payload, char* string,
												 uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildMessageStatus(ocppPayload->setChargingProfileRes.status, statusStr,
								&buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppSetChargingProfile_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
										&ocppPayload->setChargingProfileRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}