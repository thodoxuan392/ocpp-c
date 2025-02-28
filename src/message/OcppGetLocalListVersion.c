#include <OcppGetLocalListVersion.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppGetLocalListVersion_BuildRequest(void* payload, char* string,
												 uint32_t* stringLength)
{
	int ret;
	ret = sprintf(string, "{}");
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetLocalListVersion_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												 void* payload)
{
	size_t i;
	*tokenSize = 0;
	return OCPP_OK;
}
OcppRetType OcppGetLocalListVersion_BuildResponse(void* payload, char* string,
												  uint32_t* stringLength)
{
	int ret;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{\"listVersion\": %d}", ocppPayload->getLocalListVersionRes.listVersion);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetLocalListVersion_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												  void* payload)
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
		if(OcppJson_Equal(json, &token[i], "listVersion") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->getLocalListVersionRes.listVersion);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}