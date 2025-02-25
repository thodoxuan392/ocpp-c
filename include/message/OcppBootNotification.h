#ifndef __OCPP_BOOT_NOTIFICATION_H
#define __OCPP_BOOT_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

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

#endif // __OCPP_BOOT_NOTIFICATION_H