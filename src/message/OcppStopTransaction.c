#include <OcppStopTransaction.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppStopTransaction_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char timestampStr[OCPP_DATE_TIME_MAX_LENGTH];
	char reasonStr[OCPP_REASON_MAX_LENGTH];
	char meterValueStr[OCPP_METER_VALUE_MAX_LENGTH];
	char meterValueArrStr[OCPP_METER_VALUE_MAX_LENGTH * OCPP_TRANSACTION_DATA_ARRAY_MAX_LENGTH];

	memset(timestampStr, 0, sizeof(timestampStr));
	memset(reasonStr, 0, sizeof(reasonStr));
	memset(meterValueStr, 0, sizeof(meterValueStr));
	memset(meterValueArrStr, 0,
		   OCPP_METER_VALUE_MAX_LENGTH * OCPP_TRANSACTION_DATA_ARRAY_MAX_LENGTH);

	strcat(meterValueArrStr, "[");

	for(size_t i = 0; i < ocppPayload->stopTransactionReq.noTransactionData; i++)
	{
		OcppJson_BuildMeterValue(&ocppPayload->stopTransactionReq.transactionData[i], meterValueStr,
								 &buildStrLength);
		strncat(meterValueArrStr, meterValueStr, buildStrLength);
		if(i != (ocppPayload->stopTransactionReq.noTransactionData - 1))
		{
			strcat(meterValueArrStr, ",");
		}
	}
	strcat(meterValueArrStr, "]");

	OcppJson_BuildDateTime(&ocppPayload->stopTransactionReq.timestamp, timestampStr,
						   &buildStrLength);
	OcppJson_BuildReason(ocppPayload->stopTransactionReq.reason, reasonStr, &buildStrLength);

	ret = sprintf(
		string,
		"{\"idTag\": \"%s\",\"meterStop\": %d, \"timestamp\": \"%s\",\"transactionId\": %d, "
		"\"reason\": \"%s\",\"transactionData\": %s}",
		ocppPayload->stopTransactionReq.idTag, ocppPayload->stopTransactionReq.meterStop,
		timestampStr, ocppPayload->stopTransactionReq.transactionId, reasonStr, meterValueArrStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppStopTransaction_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											 void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t tranDataTokenIdx;
	uint32_t tokenLen;

	if(*tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 2, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "idTag") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->stopTransactionReq.idTag);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "meterStop") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->stopTransactionReq.meterStop);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "timestamp") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->stopTransactionReq.timestamp);

			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "transactionId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->stopTransactionReq.transactionId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "reason") == 0)
		{
			OcppJson_ParseReason(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								 &ocppPayload->stopTransactionReq.reason);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "transactionData") == 0)
		{
			ocppPayload->stopTransactionReq.noTransactionData = token[i + 1].size;

			tranDataTokenIdx = i + 2;

			for(size_t tranDataIdx = 0;
				tranDataIdx < ocppPayload->stopTransactionReq.noTransactionData; tranDataIdx++)
			{
				tokenLen = *tokenSize - tranDataTokenIdx;
				OcppJson_ParseMeterValue(
					json, &token[tranDataTokenIdx], &tokenLen,
					&ocppPayload->stopTransactionReq.transactionData[tranDataIdx]);
				tranDataTokenIdx += tokenLen;
			}
			i = tranDataTokenIdx - 1;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppStopTransaction_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char idTagInfoStr[OCPP_ID_TAG_INFO_MAX_LENGTH];
	memset(idTagInfoStr, 0, sizeof(idTagInfoStr));

	OcppJson_BuildIdTagInfo(&ocppPayload->stopTransactionRes.idTagInfo, idTagInfoStr,
							&buildStrLength);

	ret = sprintf(string, "{\"idTagInfo\": %s}", idTagInfoStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppStopTransaction_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t tranDataTokenIdx;
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
									ocppPayload->stopTransactionReq.idTag);
			i += tokenLen + 1;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}