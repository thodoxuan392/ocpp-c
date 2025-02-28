#include <OcppRemoteStopTransaction.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppRemoteStopTransaction_BuildRequest(void* payload, char* string,
												   uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{\"transactionId\": %d}",
				  ocppPayload->remoteStopTransactionReq.transactionId);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppRemoteStopTransaction_ParseRequest(char* json, jsmntok_t* token,
												   uint32_t* tokenSize, void* payload)
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
		if(OcppJson_Equal(json, &token[i], "transactionId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->remoteStopTransactionReq.transactionId);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppRemoteStopTransaction_BuildResponse(void* payload, char* string,
													uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildMessageStatus(ocppPayload->remoteStopTransactionRes.status, statusStr,
								&buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\"}", statusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppRemoteStopTransaction_ParseResponse(char* json, jsmntok_t* token,
													uint32_t* tokenSize, void* payload)
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
										&ocppPayload->remoteStopTransactionRes.status);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}