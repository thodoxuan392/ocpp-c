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
	char filename[OCPP_FILE_NAME_MAX_LENGTH];
} OcppGetDiagnosticResponse;

#endif // __OCPP_GET_DIAGNOSTIC_H