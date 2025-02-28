#include <OcppGetConfiguration.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppGetConfiguration_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char timestampStr[OCPP_DATE_TIME_MAX_LENGTH];
	char keyArrStr[sizeof(OcppCiString50Type) * OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];

	memset(timestampStr, 0, sizeof(timestampStr));
	memset(keyArrStr, 0, sizeof(keyArrStr));

	strcat(keyArrStr, "[");

	for(size_t i = 0; i < ocppPayload->getConfigurationReq.noKey; i++)
	{
		strcat(keyArrStr, "\"");
		strcat(keyArrStr, ocppPayload->getConfigurationReq.key[i]);
		strcat(keyArrStr, "\"");
		if(i != (ocppPayload->getConfigurationReq.noKey - 1))
		{
			strcat(keyArrStr, ",");
		}
	}
	strcat(keyArrStr, "]");

	ret = sprintf(string, "{\"key\": %s}", keyArrStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetConfiguration_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t keyTokenIdx;
	uint32_t tokenLen;

	if(*tokenSize < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 1, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "key") == 0)
		{
			ocppPayload->getConfigurationReq.noKey = token[i + 1].size;

			keyTokenIdx = i + 2;

			for(size_t keyIdx = 0; keyIdx < ocppPayload->getConfigurationReq.noKey; keyIdx++)
			{
				OcppJson_ToString(json, &token[keyTokenIdx],
								  ocppPayload->getConfigurationReq.key[keyIdx]);
				keyTokenIdx += 1;
			}
			i = keyTokenIdx - 1;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppGetConfiguration_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char tempStr[OCPP_KEY_VALUE_MAX_LENGTH];
	memset(tempStr, 0, sizeof(tempStr));

	memset(string, 0, *stringLength);
	strcat(string, "{\"configurationKey\":[");

	for(size_t i = 0; i < ocppPayload->getConfigurationRes.noConfigurationKey; i++)
	{
		(void)OcppJson_BuildKeyValue(&ocppPayload->getConfigurationRes.configurationKey[i], tempStr,
									 &buildStrLength);
		strncat(string, tempStr, buildStrLength);
		if(i != (ocppPayload->getConfigurationRes.noConfigurationKey - 1))
		{
			strcat(string, ",");
		}
	}
	strcat(string, "],\"unknownKey\":[");
	for(size_t i = 0; i < ocppPayload->getConfigurationRes.noUnknownKey; i++)
	{
		strcat(string, "\"");
		strcat(string, ocppPayload->getConfigurationRes.unknownKey[i]);
		strcat(string, "\"");
		if(i != (ocppPayload->getConfigurationRes.noUnknownKey - 1))
		{
			strcat(string, ",");
		}
	}
	strcat(string, "]}");

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetConfiguration_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											   void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t keyTokenIdx;
	uint32_t tokenLen;

	if(*tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 2, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "configurationKey") == 0)
		{
			ocppPayload->getConfigurationRes.noConfigurationKey = token[i + 1].size;

			keyTokenIdx = i + 2;

			for(size_t keyIdx = 0; keyIdx < ocppPayload->getConfigurationRes.noConfigurationKey;
				keyIdx++)
			{
				tokenLen = *tokenSize - keyTokenIdx;

				OcppJson_ParseKeyValue(json, &token[keyTokenIdx], &tokenLen,
									   &ocppPayload->getConfigurationRes.configurationKey[keyIdx]);
				keyTokenIdx += tokenLen;
			}
			i = keyTokenIdx - 1;
		}
		else if(OcppJson_Equal(json, &token[i], "unknownKey") == 0)
		{
			ocppPayload->getConfigurationRes.noUnknownKey = token[i + 1].size;

			keyTokenIdx = i + 2;

			for(size_t keyIdx = 0; keyIdx < ocppPayload->getConfigurationRes.noUnknownKey; keyIdx++)
			{
				OcppJson_ToString(json, &token[keyTokenIdx],
								  &ocppPayload->getConfigurationRes.unknownKey[keyIdx]);
				keyTokenIdx += 1;
			}
			i = keyTokenIdx - 1;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}