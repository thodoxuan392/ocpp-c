#include <OcppMeterValue.h>

#include <OcppMessage.h>

#include <OcppJson.h>

OcppRetType OcppMeterValue_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char meterValueArrStr[OCPP_METER_VALUE_ARRAY_MAX_LENGTH * OCPP_METER_VALUE_MAX_LENGTH];
	char meterValueStr[OCPP_METER_VALUE_MAX_LENGTH];

	memset(meterValueArrStr, 0, sizeof(meterValueArrStr));
	memset(meterValueStr, 0, sizeof(meterValueStr));

	strcat(meterValueArrStr, "[");
	for(size_t i = 0; i < ocppPayload->meterValueReq.noMeterValue; i++)
	{
		memset(meterValueStr, 0, OCPP_METER_VALUE_MAX_LENGTH);
		OcppJson_BuildMeterValue(&ocppPayload->meterValueReq.meterValue[i], meterValueStr,
								 &buildLength);
		strcat(meterValueArrStr, meterValueStr);
		if(i != (ocppPayload->meterValueReq.noMeterValue - 1))
		{
			strcat(meterValueArrStr, ",");
		}
	}
	strcat(meterValueArrStr, "]");

	ret = sprintf(string, "{\"connectorId\": %d, \"transactionId\": %d,\"meterValue\": %s }",
				  ocppPayload->meterValueReq.connectorId, ocppPayload->meterValueReq.transactionId,
				  meterValueArrStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppMeterValue_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										void* payload)
{
	/**
	 * @brief Template
	 * {
	 *      "idTagInfo": <Object>
	 * }
	 */
	size_t i, j;
	uint32_t meterValueArrIdx;
	uint32_t tokenRemain;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size expect > 2, got %d\r\n", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->meterValueReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "transactionId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->meterValueReq.transactionId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "meterValue") == 0)
		{
			if(token[i + 1].type != JSMN_ARRAY)
			{
				Ocpp_LogError(("[OCPP] meterValue should be ARRAY\r\n"));
				return OCPP_NOT_OK;
			}
			ocppPayload->meterValueReq.noMeterValue = token[i + 1].size;

			meterValueArrIdx = i + 2;

			for(j = 0; j < ocppPayload->meterValueReq.noMeterValue; j++)
			{
				tokenRemain = *tokenSize - meterValueArrIdx;
				OcppJson_ParseMeterValue(json, &token[meterValueArrIdx], &tokenRemain,
										 &ocppPayload->meterValueReq.meterValue[j]);
				meterValueArrIdx += tokenRemain;
			}
			i = meterValueArrIdx - 1;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppMeterValue_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{}");
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppMeterValue_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
										 void* payload)
{
	*tokenSize = 0;
	return OCPP_OK;
}