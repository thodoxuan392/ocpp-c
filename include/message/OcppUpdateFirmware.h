#ifndef __OCPP_UPDATE_FIRMWARE_H
#define __OCPP_UPDATE_FIRMWARE_H

#include <OcppConfig.h>
#include <OcppTypes.h>

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

OcppRetType OcppUpdateFirmware_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppUpdateFirmware_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											void* payload);
OcppRetType OcppUpdateFirmware_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppUpdateFirmware_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											 void* payload);

#endif // __OCPP_UPDATE_FIRMWARE_H