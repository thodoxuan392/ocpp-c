#include <OcppReserveNow.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppReserveNow_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char expiryDateStr[OCPP_DATE_TIME_MAX_LENGTH];
	memset(expiryDateStr, 0, sizeof(expiryDateStr));

	OcppJson_BuildDateTime(&ocppPayload->reserveNowReq.expiryDate, expiryDateStr, &buildStrLength);

	ret = sprintf(string,
				  "{\"connectorId\": %d,\"expiryDate\": \"%s\",\"idTag\": \"%s\",\"parentIdTag\": "
				  "\"%s\",\"reservationId\": %d}",
				  ocppPayload->reserveNowReq.connectorId, expiryDateStr,
				  ocppPayload->reserveNowReq.idTag, ocppPayload->reserveNowReq.parentIdTag,
				  ocppPayload->reserveNowReq.reservationId);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppReserveNow_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->reserveNowReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "expiryDate") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->reserveNowReq.expiryDate);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "idTag") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->reserveNowReq.idTag);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "parentIdTag") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->reserveNowReq.parentIdTag);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "reservationId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->reserveNowReq.reservationId);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppReserveNow_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildMessageStatus(ocppPayload->reserveNowRes.status, statusStr, &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppReserveNow_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
										&ocppPayload->reserveNowRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}