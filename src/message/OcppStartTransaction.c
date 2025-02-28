#include <OcppStartTransaction.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppStartTransaction_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char timestampStr[OCPP_DATE_TIME_MAX_LENGTH];
	memset(timestampStr, 0, sizeof(timestampStr));

	OcppJson_BuildDateTime(&ocppPayload->startTransactionReq.timestamp, timestampStr,
						   &buildStrLength);

	ret =
		sprintf(string,
				"{\"connectorId\": %d,\"idTag\": \"%s\", \"meterStart\": %d,\"reservationId\": "
				"%d,\"timestamp\": \"%s\"}",
				ocppPayload->startTransactionReq.connectorId,
				ocppPayload->startTransactionReq.idTag, ocppPayload->startTransactionReq.meterStart,
				ocppPayload->startTransactionReq.reservationId, timestampStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppStartTransaction_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->startTransactionReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "idTag") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->startTransactionReq.idTag);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "meterStart") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->startTransactionReq.meterStart);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "reservationId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->startTransactionReq.reservationId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "timestamp") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->startTransactionReq.timestamp);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppStartTransaction_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char idTagInfoStr[OCPP_ID_TAG_INFO_MAX_LENGTH];
	memset(idTagInfoStr, 0, sizeof(idTagInfoStr));

	OcppJson_BuildIdTagInfo(&ocppPayload->startTransactionRes.idTagInfo, idTagInfoStr,
							&buildStrLength);

	ret = sprintf(string, "{\"idTagInfo\": %s,\"transactionId\": %d}", idTagInfoStr,
				  ocppPayload->startTransactionRes.transactionId);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppStartTransaction_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "idTagInfo") == 0)
		{
			tokenLen = *tokenSize - i - 1;
			OcppJson_ParseIdTagInfo(json, &token[i + 1], &tokenLen,
									&ocppPayload->startTransactionRes.idTagInfo);
			i += tokenLen;
		}
		else if(OcppJson_Equal(json, &token[i], "transactionId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->startTransactionRes.transactionId);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}