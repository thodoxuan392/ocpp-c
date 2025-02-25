#ifndef __OCPP_METER_VALUE_H
#define __OCPP_METER_VALUE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int connectorId;
	int transactionId;
	OcppMeterValue meterValue[OCPP_METER_VALUE_ARRAY_MAX_LENGTH];
} OcppMeterValueRequest;

typedef struct
{
} OcppMeterValueResponse;

#endif // __OCPP_METER_VALUE_H