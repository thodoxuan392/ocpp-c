#include <OcppAuthorize.h>

#include <OcppJson.h>
#include <OcppMessage.h>

OcppRetType OcppAuthorize_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{\"idTag\": \"%s\"}", ocppPayload->authorizeReq.idTag);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppAuthorize_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
									   void* payload)
{
	/**
	 * @brief Template
	 * {
	 *      "idTag": <string>
	 * }
	 */
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 2, got %d", tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "idTag") == 0)
		{
			strncpy(ocppPayload->authorizeReq.idTag, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppAuthorize_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char idTagInfoStr[OCPP_ID_TAG_INFO_MAX_LENGTH];
	memset(idTagInfoStr, 0, sizeof(idTagInfoStr));

	(void)OcppJson_BuildIdTagInfo(&ocppPayload->authorizeRes.idTagInfo, idTagInfoStr,
								  &buildStrLength);

	ret = sprintf(string, "{\"idTagInfo\": %s}", idTagInfoStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppAuthorize_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
										void* payload)
{
	/**
	 * @brief Template
	 * {
	 *      "idTagInfo": <Object>
	 * }
	 */
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;
	uint32_t idTagInfoNoToken;

	if(tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size expect > 2, got %d\r\n", tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "idTagInfo") == 0)
		{
			if(token[i + 1].type != JSMN_OBJECT)
			{
				Ocpp_LogError(("[OCPP] idTagInfo should be Object\r\n"));
				return OCPP_NOT_OK;
			}
			idTagInfoNoToken = tokenSize - i - 1;
			OcppJson_ParseIdTagInfo(json, &token[i + 1], &idTagInfoNoToken,
									&ocppPayload->authorizeRes.idTagInfo);
			i += idTagInfoNoToken;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}