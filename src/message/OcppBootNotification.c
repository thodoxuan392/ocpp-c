#include <OcppBootNotification.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppBootNotification_BuildRequest(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	ret = sprintf(
		string,
		"{\"chargePointVendor\": \"%s\", \"chargePointModel\": \"%s\",\"chargePointSerialNumber\": "
		"\"%s\",\"chargeBoxSerialNumber\": \"%s\",\"firmwareVersion\": \"%s\",\"iccid\": "
		"\"%s\",\"imsi\": \"%s\",\"meterType\": \"%s\",\"meterSerialNumber\": "
		"\"%s\"}",
		ocppPayload->bootNotificationReq.chargePointVendor,
		ocppPayload->bootNotificationReq.chargePointModel,
		ocppPayload->bootNotificationReq.chargePointSerialNumber,
		ocppPayload->bootNotificationReq.chargeBoxSerialNumber,
		ocppPayload->bootNotificationReq.firmwareVersion, ocppPayload->bootNotificationReq.iccid,
		ocppPayload->bootNotificationReq.imsi, ocppPayload->bootNotificationReq.meterType,
		ocppPayload->bootNotificationReq.meterSerialNumber);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppBootNotification_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 2)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 2, got %d", tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "chargePointVendor") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.chargePointVendor, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargePointModel") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.chargePointModel, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargePointSerialNumber") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.chargePointSerialNumber,
					json + token[i + 1].start, token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargeBoxSerialNumber") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.chargeBoxSerialNumber,
					json + token[i + 1].start, token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "firmwareVersion") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.firmwareVersion, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "iccid") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.iccid, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "imsi") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.imsi, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "meterType") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.meterType, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "meterSerialNumber") == 0)
		{
			strncpy(ocppPayload->bootNotificationReq.meterSerialNumber, json + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppBootNotification_BuildResponse(void* payload, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char registrationStatusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	char dateTimeStr[OCPP_DATE_TIME_MAX_LENGTH];

	OcppJson_BuildMessageStatus(ocppPayload->bootNotificationRes.status, registrationStatusStr,
								&buildLength);
	;
	OcppJson_BuildDateTime(&ocppPayload->bootNotificationRes.currentTime, dateTimeStr,
						   &buildLength);

	ret = sprintf(string,
				  "{\"status\": \"%s\", \"currentTime\": "
				  "\"%s\",\"interval\": "
				  "%d}",
				  registrationStatusStr, dateTimeStr, ocppPayload->bootNotificationRes.interval);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppBootNotification_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											   void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(tokenSize < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 3, got %d", tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(json + token[i + 1].start,
										token[i + 1].end - token[i + 1].start,
										&ocppPayload->bootNotificationRes.status);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "currentTime") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->bootNotificationRes.currentTime);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "interval") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->bootNotificationRes.interval);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}