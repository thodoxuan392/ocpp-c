#ifndef __OCPP_METER_VALUE_H
#define __OCPP_METER_VALUE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	int connectorId;
	int transactionId;
	OcppMeterValue meterValue[OCPP_METER_VALUE_ARRAY_MAX_LENGTH];
} OcppMeterValueRequest;

typedef struct
{
} OcppMeterValueResponse;

OcppRetType OcppMeterValue_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppMeterValue_ParseRequest(char* json, jsmntok_t* token, uint32_t tokenSize,
										void* payload);
OcppRetType OcppMeterValue_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppMeterValue_ParseResponse(char* json, jsmntok_t* token, uint32_t tokenSize,
										 void* payload);

#endif // __OCPP_METER_VALUE_H