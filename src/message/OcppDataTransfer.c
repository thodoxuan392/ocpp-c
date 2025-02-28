#include <OcppDataTransfer.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppDataTransfer_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(string, "{\"vendorId\": \"%s\",\"messageId\": \"%s\",\"data\": \"%s\"}",
				  ocppPayload->dataTransferReq.vendorId, ocppPayload->dataTransferReq.messageId,
				  ocppPayload->dataTransferReq.data);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppDataTransfer_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
										  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 4)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 4, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "vendorId") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->dataTransferReq.vendorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "messageId") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->dataTransferReq.messageId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "data") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->dataTransferReq.data);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppDataTransfer_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStrLength[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	memset(statusStrLength, 0, sizeof(statusStrLength));

	(void)OcppJson_BuildMessageStatus(ocppPayload->dataTransferRes.status, statusStrLength,
									  &buildStrLength);

	ret = sprintf(string, "{\"status\": \"%s\", \"data\": \"%s\"}", statusStrLength,
				  ocppPayload->dataTransferRes.data);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppDataTransfer_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
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
		if(OcppJson_Equal(json, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(json + token[i + 1].start,
										token[i + 1].end - token[i + 1].start,
										&ocppPayload->clearChargingProfileRes.status);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "data") == 0)
		{
			OcppJson_ToString(json, &token[i + 1], ocppPayload->dataTransferRes.data);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}