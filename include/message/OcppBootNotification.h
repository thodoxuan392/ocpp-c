#ifndef __OCPP_BOOT_NOTIFICATION_H
#define __OCPP_BOOT_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppTypes.h>

typedef struct
{
	OcppCiString25Type chargePointVendor;
	OcppCiString20Type chargePointModel;
	OcppCiString25Type chargePointSerialNumber;
	OcppCiString20Type chargeBoxSerialNumber;
	OcppCiString50Type firmwareVersion;
	OcppCiString20Type iccid;
	OcppCiString20Type imsi;
	OcppCiString25Type meterType;
	OcppCiString25Type meterSerialNumber;
} OcppBootNotificationRequest;

typedef struct
{
	OcppRegistrationStatus status;
	OcppDateTime currentTime;
	int interval;
} OcppBootNotificationResponse;

OcppRetType OcppBootNotification_BuildRequest(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppBootNotification_ParseRequest(char* json, jsmntok_t* token, uint32_t* tokenSize,
											  void* payload);
OcppRetType OcppBootNotification_BuildResponse(void* payload, char* string, uint32_t* stringLength);
OcppRetType OcppBootNotification_ParseResponse(char* json, jsmntok_t* token, uint32_t* tokenSize,
											   void* payload);

#endif // __OCPP_BOOT_NOTIFICATION_H