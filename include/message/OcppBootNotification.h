#ifndef __OCPP_BOOT_NOTIFICATION_H
#define __OCPP_BOOT_NOTIFICATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char chargePointVendor[OCPP_BOOT_NOTIFICATION_CHARGE_POINT_VENDOR_MAX_LENGTH];
	char chargePointModel[OCPP_BOOT_NOTIFICATION_CHARGE_POINT_MODEL_MAX_LENGTH];
	char chargePointSerialNumber[OCPP_BOOT_NOTIFICATION_CHARGE_POINT_SERIAL_NO_MAX_LENGTH];
	char chargeBoxSerialNumber[OCPP_BOOT_NOTIFICATION_CHARGE_BOX_SERIAL_NO_MAX_LENGTH];
	char fwVersion[OCPP_BOOT_NOTIFICATION_FW_VERSION_NO_MAX_LENGTH];
	char iccid[OCPP_BOOT_NOTIFICATION_ICCID_MAX_LENGTH];
	char imsi[OCPP_BOOT_NOTIFICATION_IMSI_MAX_LENGTH];
	char meterType[OCPP_BOOT_NOTIFICATION_METER_TYPE_MAX_LENGTH];
	char meterSerialNumber[OCPP_BOOT_NOTIFICATION_METER_SERIAL_NO_MAX_LENGTH];
} OcppBootNotificationRequest;

typedef struct
{
	OcppMessageStatus status;
	OcppDateTime currentTime;
	int interval;
} OcppBootNotificationResponse;

#endif // __OCPP_BOOT_NOTIFICATION_H