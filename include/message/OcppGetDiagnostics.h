#ifndef __OCPP_GET_DIAGNOSTIC_H
#define __OCPP_GET_DIAGNOSTIC_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char location[OCPP_LOCATION_MAX_LENGTH];
	int retries;
	int retryInterval;
	OcppDateTime startTime;
	OcppDateTime stopTime;
} OcppGetDiagnosticRequest;

typedef struct
{
	OcppCiString255Type filename;
} OcppGetDiagnosticResponse;

#endif // __OCPP_GET_DIAGNOSTIC_H