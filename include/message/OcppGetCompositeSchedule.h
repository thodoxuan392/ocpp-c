#ifndef __OCPP_GET_COMPOSITE_SCHEDULE_H
#define __OCPP_GET_COMPOSITE_SCHEDULE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	int duration;
	OcppChargingRateUnitType chargingRateUnit;
} OcppGetCompositeScheduleRequest;

typedef struct
{
	OcppGetCompositeScheduleStatus status;
	int connectorId;
	OcppDateTime scheduleStart;
	OcppChargingSchedule chargingSchedule;
} OcppGetCompositeScheduleResponse;

OcppRetType OcppGetCompositeSchedule_BuildRequest(void* payload, char* string,
												  uint32_t* stringLength);
OcppRetType OcppGetCompositeSchedule_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
												  void* payload);
OcppRetType OcppGetCompositeSchedule_BuildResponse(void* payload, char* string,
												   uint32_t* stringLength);
OcppRetType OcppGetCompositeSchedule_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
												   void* payload);

#endif // __OCPP_GET_COMPOSITE_SCHEDULE_H