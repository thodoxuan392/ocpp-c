#include <OcppRemoteStartTransaction.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppRemoteStartTransaction_BuildRequest(void* payload, char* string,
													uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char chargingProfileStr[OCPP_CHARGING_PROFILE_MAX_LENGTH];
	memset(chargingProfileStr, 0, sizeof(chargingProfileStr));

	(void)OcppJson_BuildChargingProfile(&ocppPayload->remoteStartTransactionReq.chargingProfile,
										chargingProfileStr, &buildStrLength);

	ret = sprintf(string, "{\"connectorId\": %d, \"idTag\": \"%s\", \"chargingProfile\": %s}",
				  ocppPayload->remoteStartTransactionReq.connectorId,
				  ocppPayload->remoteStartTransactionReq.idTag, chargingProfileStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppRemoteStartTransaction_ParseRequest(char* json, jsmntok_t* token,
													uint32_t* tokenSize, void* payload)
{
	size_t i;
	uint32_t tokenLen;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 3, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->remoteStartTransactionReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "idTag") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->remoteStartTransactionReq.idTag);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargingProfile") == 0)
		{
			tokenLen = *tokenSize - i - 1;
			OcppJson_ParseChargingProfile(json, &token[i + 1], &tokenLen,
										  &ocppPayload->remoteStartTransactionReq.chargingProfile);
			i += tokenLen;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppRemoteStartTransaction_BuildResponse(void* payload, char* string,
													 uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	(void)OcppJson_BuildMessageStatus(ocppPayload->remoteStartTransactionRes.status, statusStr,
									  &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppRemoteStartTransaction_ParseResponse(char* json, jsmntok_t* token,
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
										&ocppPayload->remoteStartTransactionRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}