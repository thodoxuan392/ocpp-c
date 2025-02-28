#include <OcppSendLocalList.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppSendLocalList_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char updateTypeStr[OCPP_UPDATE_TYPE_MAX_LENGTH];
	char localAuthorizationListStr[OCPP_AUTHORIZATION_DATA_MAX_LENGTH];
	char localAuthorizationListArrStr[OCPP_AUTHORIZATION_DATA_MAX_LENGTH *
									  OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH];
	memset(updateTypeStr, 0, sizeof(updateTypeStr));
	memset(localAuthorizationListStr, 0, sizeof(localAuthorizationListStr));
	memset(localAuthorizationListArrStr, 0,
		   OCPP_AUTHORIZATION_DATA_MAX_LENGTH * OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH);

	strcat(localAuthorizationListArrStr, "[");

	for(size_t i = 0; i < ocppPayload->sendLocalListReq.noLocalAuthorizationList; i++)
	{
		OcppJson_BuildAuthorizationData(&ocppPayload->sendLocalListReq.localAuthorizationList[i],
										localAuthorizationListStr, &buildStrLength);
		strncat(localAuthorizationListArrStr, localAuthorizationListStr, buildStrLength);
		if(i != (ocppPayload->sendLocalListReq.noLocalAuthorizationList - 1))
		{
			strcat(localAuthorizationListArrStr, ",");
		}
	}
	strcat(localAuthorizationListArrStr, "]");

	OcppJson_BuildUpdateType(ocppPayload->sendLocalListReq.updateType, updateTypeStr,
							 &buildStrLength);

	ret = sprintf(
		string, "{\"listVersion\": %d,\"localAuthorizationList\": %s, \"updateType\": \"%s\"}",
		ocppPayload->sendLocalListReq.listVersion, localAuthorizationListArrStr, updateTypeStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppSendLocalList_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "listVersion") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->sendLocalListReq.listVersion);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "localAuthorizationList") == 0)
		{
			ocppPayload->sendLocalListReq.noLocalAuthorizationList = token[i + 1].size;

			localListTokenIdx = i + 2;

			for(size_t localListIdx = 0;
				localListIdx < ocppPayload->sendLocalListReq.noLocalAuthorizationList;
				localListIdx++)
			{
				tokenLen = *tokenSize - localListTokenIdx;

				OcppJson_ParseAuthorizationData(
					json, &token[localListTokenIdx], &tokenLen,
					&ocppPayload->sendLocalListReq.localAuthorizationList[localListIdx]);
				localListTokenIdx += tokenLen;
			}
			i = localListTokenIdx - 1;
		}
		else if(OcppJson_Equal(json, &token[i], "updateType") == 0)
		{
			OcppJson_ParseUpdateType(json + token[i + 1].start,
									 token[i + 1].end - token[i + 1].start,
									 &ocppPayload->sendLocalListReq.updateType);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppSendLocalList_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildMessageStatus(ocppPayload->sendLocalListRes.status, statusStr, &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppSendLocalList_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
										&ocppPayload->sendLocalListRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}