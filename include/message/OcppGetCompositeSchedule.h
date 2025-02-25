#ifndef __OCPP_GET_COMPOSITE_SCHEDULE_H
#define __OCPP_GET_COMPOSITE_SCHEDULE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_GET_COMPOSITE_SCHEDULE_H