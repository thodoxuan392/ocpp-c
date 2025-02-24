#ifndef __OCPP_UPDATE_FIRMWARE_H
#define __OCPP_UPDATE_FIRMWARE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char location[OCPP_LOCATION_MAX_LENGTH];
	int retries;
	OcppDateTime retrieveDate;
	int retryInterval;
} OcppUpdateFirmwareRequest;

typedef struct
{
} OcppUpdateFirmwareResponse;

#endif // __OCPP_UPDATE_FIRMWARE_H