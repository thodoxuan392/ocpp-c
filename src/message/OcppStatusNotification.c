#include <OcppStatusNotification.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppStatusNotification_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char errorCodeStr[OCPP_ERROR_CODE_MAX_LENGTH];
	char timestampStr[OCPP_DATE_TIME_MAX_LENGTH];
	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];

	memset(errorCodeStr, 0, sizeof(errorCodeStr));
	memset(timestampStr, 0, sizeof(timestampStr));
	memset(statusStr, 0, sizeof(statusStr));

	OcppJson_BuildChargePointErrorCode(ocppPayload->statusNotificationReq.errorCode, errorCodeStr,
									   &buildStrLength);
	OcppJson_BuildDateTime(&ocppPayload->statusNotificationReq.timestamp, timestampStr,
						   &buildStrLength);
	OcppJson_BuildMessageStatus(ocppPayload->statusNotificationReq.status, statusStr,
								&buildStrLength);

	ret = sprintf(string,
				  "{\"connectorId\": %d,\"errorCode\": \"%s\",\"info\": \"%s\",\"status\": "
				  "\"%s\",\"timestamp\": \"%s\",\"vendorId\": \"%s\",\"vendorErrorCode\": \"%s\"}",
				  ocppPayload->statusNotificationReq.connectorId, errorCodeStr,
				  ocppPayload->statusNotificationReq.info, statusStr, timestampStr,
				  ocppPayload->statusNotificationReq.vendorId,
				  ocppPayload->statusNotificationReq.vendorErrorCode);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppStatusNotification_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->statusNotificationReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "errorCode") == 0)
		{
			OcppJson_ParseChargePointErrorCode(json + token[i + 1].start,
											   token[i + 1].end - token[i + 1].start,
											   &ocppPayload->statusNotificationReq.errorCode);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "info") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->statusNotificationReq.info);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(json + token[i + 1].start,
										token[i + 1].end - token[i + 1].start,
										&ocppPayload->statusNotificationReq.status);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "timestamp") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->statusNotificationReq.timestamp);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "vendorId") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->statusNotificationReq.vendorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "vendorErrorCode") == 0)
		{
			OcppJson_ToString(json, &token[i + 1],
							  ocppPayload->statusNotificationReq.vendorErrorCode);

			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppStatusNotification_BuildResponse(void* payload, char* string,
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
OcppRetType OcppStatusNotification_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
												 void* payload)
{
	*tokenSize = 0;
	return OCPP_OK;
}