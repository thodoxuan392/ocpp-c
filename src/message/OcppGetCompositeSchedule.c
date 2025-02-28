#include <OcppGetCompositeSchedule.h>

#include <OcppMessage.h>
#include <OcppJson.h>

OcppRetType OcppGetCompositeSchedule_BuildRequest(void* payload, char* string,
												  uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char chargingRateUnitStr[OCPP_CHARGING_RATE_UNIT_MAX_LENGTH];
	memset(chargingRateUnitStr, 0, sizeof(chargingRateUnitStr));

	(void)OcppJson_BuildChargingRateUnitType(ocppPayload->getCompositeScheduleReq.chargingRateUnit,
											 chargingRateUnitStr, &buildStrLength);

	ret = sprintf(string, "{\"connectorId\": %d, \"duration\": %d, \"chargingRateUnit\": \"%s\"}",
				  ocppPayload->getCompositeScheduleReq.connectorId,
				  ocppPayload->getCompositeScheduleReq.duration, chargingRateUnitStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetCompositeSchedule_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
												  void* payload)
{
	size_t i;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 3, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->getCompositeScheduleReq.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "duration") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1], &ocppPayload->getCompositeScheduleReq.duration);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargingRateUnit") == 0)
		{
			OcppJson_ParseChargingRateUnitType(
				json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
				&ocppPayload->getCompositeScheduleReq.chargingRateUnit);
			i++;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}
OcppRetType OcppGetCompositeSchedule_BuildResponse(void* payload, char* string,
												   uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	char statusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];
	char dateTimeStr[OCPP_DATE_TIME_MAX_LENGTH];
	char chargingScheduleStr[OCPP_CHARGE_SCHEDULE_CHARGING_SCH_MAX_LENGTH];

	memset(statusStr, 0, sizeof(statusStr));
	memset(dateTimeStr, 0, sizeof(dateTimeStr));
	memset(chargingScheduleStr, 0, sizeof(chargingScheduleStr));

	(void)OcppJson_BuildMessageStatus(ocppPayload->getCompositeScheduleRes.status, statusStr,
									  &buildStrLength);
	(void)OcppJson_BuildDateTime(&ocppPayload->getCompositeScheduleRes.scheduleStart, dateTimeStr,
								 &buildStrLength);
	(void)OcppJson_BuildChargingSchedule(&ocppPayload->getCompositeScheduleRes.chargingSchedule,
										 chargingScheduleStr, &buildStrLength);

	ret = sprintf(string,
				  "{\"status\": \"%s\", \"connectorId\": %d, \"scheduleStart\": \"%s\", "
				  "\"chargingSchedule\": %s}",
				  statusStr, ocppPayload->getCompositeScheduleRes.connectorId, dateTimeStr,
				  chargingScheduleStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppGetCompositeSchedule_ParseResponse(char* json, jsmntok_t* token,
												   uint32_t* tokenSize, void* payload)
{
	size_t i;
	uint32_t tokenBuild;
	OcppPayload* ocppPayload = (OcppPayload*)payload;

	if(*tokenSize < 4)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, at least 4, got %d", *tokenSize));
		return OCPP_NOT_OK;
	}
	for(i = 0; (i < *tokenSize) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(json, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(json + token[i + 1].start,
										token[i + 1].end - token[i + 1].start,
										&ocppPayload->getCompositeScheduleRes.status);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "connectorId") == 0)
		{
			OcppJson_ToNumber(json, &token[i + 1],
							  &ocppPayload->getCompositeScheduleRes.connectorId);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "scheduleStart") == 0)
		{
			OcppJson_ParseDateTime(json + token[i + 1].start, token[i + 1].end - token[i + 1].start,
								   &ocppPayload->getCompositeScheduleRes.scheduleStart);
			i++;
		}
		else if(OcppJson_Equal(json, &token[i], "chargingSchedule") == 0)
		{
			tokenBuild = *tokenSize - i - 1;
			OcppJson_ParseChargingSchedule(json, &token[i + 1], &tokenBuild,
										   &ocppPayload->getCompositeScheduleRes.chargingSchedule);
			i += tokenBuild;
		}
	}
	*tokenSize = i;
	return OCPP_OK;
}