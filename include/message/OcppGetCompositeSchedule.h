#ifndef __OCPP_GET_COMPOSITE_SCHEDULE_H
#define __OCPP_GET_COMPOSITE_SCHEDULE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	int duration;
	OcppChargingRateUnit chargingRateUnit;
} OcppGetCompositeScheduleRequest;

typedef struct
{
	OcppMessageStatus status;
	int connectorId;
	OcppDateTime scheduleStart;
	OcppChargeSchedule chargingSchedule;
} OcppGetCompositeScheduleResponse;

#endif // __OCPP_GET_COMPOSITE_SCHEDULE_H