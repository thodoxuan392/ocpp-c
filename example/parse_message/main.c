#include <stdio.h>
#include <stdint.h>

#include <Ocpp.h>

#define SOCKET_ID 1

/**
 * @brief WebSocket
 */
static OcppRetType OcppWebSocketIntf_SendData(int socketId, uint8_t* data, uint32_t dataSize);
static OcppRetType
	OcppWebSocketIntf_RegisterEventCallback(OcppWebSocket_EventCallback eventCallback);

static const OcppWebSocketIntf ocppWebSocketIntf = {
	.socketId = SOCKET_ID,
	.sendDataPf = OcppWebSocketIntf_SendData,
	.registerEventCallbackPf = OcppWebSocketIntf_RegisterEventCallback,
};

static OcppWebSocket_EventCallback OcppWebSocket_EventCallbackFunc;

/**
 * @brief Ocpp
 *
 */
static OcppRetType Ocpp_MessageHandler(OcppMessage* message);

static OcppHandle ocppHandle = {
	.webSocketIntf = &ocppWebSocketIntf,
	.requestPool =
		{
			{
				.uniqueId = "uniqueId#1",
			},
			{
				.uniqueId = "uniqueId#2",
			},
			{
				.uniqueId = "uniqueId#3",
			},
			{
				.uniqueId = "uniqueId#4",
			},
			{
				.uniqueId = "uniqueId#5",
			},
		},
};

static char* authorizeReqMessageStr =
	"[2,\"uniqueId#1\",\"Authorize\",{\"idTag\": \"idTag#123456789\"}]";

static char* authorizeResMessageStr =
	"[3,\"uniqueId#1\",{\"idTagInfo\": {\"expiryDate\": \"2025-1-0T0:0:0Z\",\"parentIdTag\": "
	"\"idTag#123456789\",\"status\": \"Accepted\"}}]";

static char* bootNotificationReqMessageStr =
	"[2,\"uniqueId#1\",\"BootNotification\",{\"chargePointVendor\": \"eboost\", "
	"\"chargePointModel\": \"obc\",\"chargePointSerialNumber\": \" "
	"Test\",\"chargeBoxSerialNumber\": \"123456\",\"firmwareVersion\": \"1.2.3\",\"iccid\": "
	"\"iccidTest\",\"imsi\": \"imsiTest\",\"meterType\": \"Test\",\"meterSerialNumber\": "
	"\"Test\"}]";

static char* bootNotificationResMessageStr =
	"[3,\"uniqueId#1\",{\"status\": \"Blocked\", \"currentTime\": "
	"\"2025-0-0T0:0:0Z\",\"interval\": 100}]";

static char* cancelReservationReqStr = R"(
	[2,"uniqueId#1","CancelReservation"
	{
    "reservationId": 12345
	}
	]
)";

static char* cancelReservationResStr = R"(
	[3,"uniqueId#1",
	{
    "status": "Accepted"
	}
	]
)";

static char* changeAvailabilityReqStr = R"(
	[2,"uniqueId#1","ChangeAvailability"
	{
    "connectorId": 1,
    "type": "Inoperative"
	}
	]
)";

static char* changeAvailabilityResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* changeConfigurationReqStr = R"(
	[2,"uniqueId#1","ChangeConfiguration"
	{
		"key": "maxChargingLimit",
		"value": "100"
	}
	]
)";

static char* changeConfigurationResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* clearCacheReqStr = R"(
	[2,"uniqueId#1","ClearCache"
	{}
	]
)";

static char* clearCacheResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* clearChargingProfileReqStr = R"(
	[2,"uniqueId#1","ClearChargingProfile"
	{
		"id": 1,
		"connectorId": 2,
		"chargingProfilePurpose": "TxProfile",
		"stackLevel": 0
	}
	]
)";

static char* clearChargingProfileResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* dataTransferReqStr = R"(
	[2,"uniqueId#1","DataTransfer"
	{
		"vendorId": "MyVendor",
		"messageId": "12345",
		"data": "Some additional data"
	}
	]
)";

static char* dataTransferResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted",
		"data": "Response data information"
	}
	]
)";

static char* diagnosticStatusNotificationReqStr = R"(
	[2,"uniqueId#1","DiagnosticsStatusNotification"
	{
		"status": "Uploaded"
	}
	]
)";

static char* diagnosticStatusNotificationResStr = R"(
	[3,"uniqueId#1",
	{}
	]
)";

static char* firmwareStatusNotificationReqStr = R"(
	[2,"uniqueId#1","FirmwareStatusNotification"
	{
		"status": "Installed"
	}
	]
)";

static char* firmwareStatusNotificationResStr = R"(
	[3,"uniqueId#1",
	{}
	]
)";

static char* getCompositeScheduleReqStr = R"(
	[2,"uniqueId#1","GetCompositeSchedule"
	{
		"connectorId": 1,
		"duration": 3600,
		"chargingRateUnit": "A"
	}
	]
)";

static char* getCompositeScheduleResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted",
		"connectorId": 1,
		"scheduleStart": "2023-10-01T12:00:00Z",
		"chargingSchedule": {
			"duration": 3600,
			"startSchedule": "2023-10-01T12:00:00Z",
			"chargingRateUnit": "A",
			"chargingSchedulePeriod": [
				{
					"startPeriod": 0,
					"limit": 16.0,
					"numberPhases": 3
				},
				{
					"startPeriod": 3600,
					"limit": 32.0,
					"numberPhases": 3
				}
			],
			"minChargingRate": 6.0
		}
	}
	]
)";

static char* getConfigurationReqStr = R"(
	[2,"uniqueId#1","GetConfiguration"
	{
		"key": [
			"MaxChargingRate",
			"ConnectionTimeout"
		]
	}
	]
)";

static char* getConfigurationResStr = R"(
	[3,"uniqueId#1",
	{
		"configurationKey": [
			{
				"key": "MaxChargingRate",
				"readonly": true,
				"value": "32"
			},
			{
				"key": "ConnectionTimeout",
				"readonly": false,
				"value": "300"
			}
		],
		"unknownKey": [
			"NonExistentKey"
		]
	}
	]
)";

static char* getDiagnosticReqStr = R"(
	[2,"uniqueId#1","GetDiagnostics",
	{
		"location": "test",
		"retries": 3,
		"retryInterval": 60,
		"startTime": "2023-10-01T12:00:00Z",
		"stopTime": "2023-10-01T14:00:00Z"
	}
	]
)";

static char* getDiagnosticResStr = R"(
	[3,"uniqueId#1",
	{
		"fileName": "device_logs_2023-10-01.log"
	}
	]
)";

static char* getLocalListVersionReqStr = R"(
	[2,"uniqueId#1","GetLocalListVersion",
	{}
	]
)";

static char* getLocalListVersionResStr = R"(
	[3,"uniqueId#1",
	{
		"listVersion": 1
	}
	]
)";

static char* getHeartBeatReqStr = R"(
	[2,"uniqueId#1","Heartbeat"
	{}
	]
)";

static char* getHeartBeatResStr = R"(
	[3,"uniqueId#1",
	{
		"currentTime": "2023-10-01T14:00:00Z"
	}
	]
)";

static char* getMeterValuesReqStr = R"(
	[2,"uniqueId#1","MeterValues"
	{
		"connectorId": 1,
		"meterValue": [
			{
				"timestamp": "2023-10-01T12:00:00Z",
				"sampledValue": [
					{
						"value": "15.5",
						"context": "Transaction.Begin",
						"format": "Raw",
						"measurand": "Energy.Active.Import.Register",
						"phase": "L1",
						"location": "EV",
						"unit": "kWh"
					},
					{
						"value": "0.8",
						"context": "Sample.Periodic",
						"format": "SignedData",
						"measurand": "Power.Factor",
						"phase": "L1",
						"location": "EV",
						"unit": "Percent"
					}
				]
			},
			{
				"timestamp": "2023-10-01T12:05:00Z",
				"sampledValue": [
					{
						"value": "16.0",
						"context": "Sample.Periodic",
						"format": "Raw",
						"measurand": "Energy.Active.Import.Register",
						"phase": "L1",
						"location": "Outlet",
						"unit": "kWh"
					}
				]
			}
		]
	}
	]
)";

static char* getMeterValuesResStr = R"(
	[3,"uniqueId#1",
	{}
	]
)";

static char* remoteStartTransactionReqStr = R"(
	[2,"uniqueId#1","RemoteStartTransaction"
	{
		"connectorId": 2,
		"idTag": "ABC1234567",
		"chargingProfile": {
			"chargingProfileId": 1,
			"transactionId": 123,
			"stackLevel": 0,
			"chargingProfilePurpose": "TxProfile",
			"chargingProfileKind": "Absolute",
			"recurrencyKind": "Daily",
			"validFrom": "2023-10-01T12:00:00Z",
			"validTo": "2023-10-31T12:00:00Z",
			"chargingSchedule": {
				"duration": 3600,
				"startSchedule": "2023-10-01T12:00:00Z",
				"chargingRateUnit": "A",
				"chargingSchedulePeriod": [
					{
						"startPeriod": 0,
						"limit": 16.0,
						"numberPhases": 3
					},
					{
						"startPeriod": 3600,
						"limit": 32.0,
						"numberPhases": 3
					}
				],
				"minChargingRate": 6.0
			}
		}
	}
	]
)";

static char* remoteStartTransactionResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* remoteStopTransactionReqStr = R"(
	[2,"uniqueId#1","RemoteStopTransaction"
	{
		"transactionId": 2
	}
	]
)";

static char* remoteStopTransactionResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* reserveNowReqStr = R"(
	[2,"uniqueId#1","ReserveNow"
	{
		"connectorId": 1,
		"expiryDate": "2023-10-01T12:00:00Z",
		"idTag": "USER123456",
		"parentIdTag": "PARENT123",
		"reservationId": 12345
	}
	]
)";

static char* reserveNowResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Unavailable"
	}
	]
)";

static char* resetReqStr = R"(
	[2,"uniqueId#1","Reset"
	{
		"type": "Hard"
	}
	]
)";

static char* resetResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Accepted"
	}
	]
)";

static char* sendLocalListReqStr = R"(
	[2,"uniqueId#1","SendLocalList"
	{
		"listVersion": 1,
		"localAuthorizationList": [
			{
				"idTag": "USER123456",
				"idTagInfo": {
					"expiryDate": "2023-12-31T23:59:59Z",
					"parentIdTag": "PARENT123",
					"status": "Accepted"
				}
			},
			{
				"idTag": "USER654321",
				"idTagInfo": {
					"expiryDate": "2023-11-30T23:59:59Z",
					"status": "Failed"
				}
			}
		],
		"updateType": "Full"
	}
	]
)";

static char* sendLocalListResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "VersionMismatch"
	}
	]
)";

static char* setChargingProfileReqStr = R"(
	[2,"uniqueId#1","SetChargingProfile"
	{
		"connectorId": 1,
		"csChargingProfiles": {
			"chargingProfileId": 1,
			"transactionId": 123,
			"stackLevel": 0,
			"chargingProfilePurpose": "TxProfile",
			"chargingProfileKind": "Absolute",
			"recurrencyKind": "Daily",
			"validFrom": "2023-10-01T12:00:00Z",
			"validTo": "2023-10-31T12:00:00Z",
			"chargingSchedule": {
				"duration": 3600,
				"startSchedule": "2023-10-01T12:00:00Z",
				"chargingRateUnit": "A",
				"chargingSchedulePeriod": [
					{
						"startPeriod": 0,
						"limit": 16.0,
						"numberPhases": 3
					},
					{
						"startPeriod": 3600,
						"limit": 32.0,
						"numberPhases": 3
					}
				],
				"minChargingRate": 6.0
			}
		}
	}
	]
)";

static char* setChargingProfileResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "UnSupported"
	}
	]
)";

static char* startTransactionReqStr = R"(
	[2,"uniqueId#1","StartTransaction"
	{
		"connectorId": 1,
		"idTag": "USER123456",
		"meterStart": 1000,
		"reservationId": 12345,
		"timestamp": "2023-10-01T12:00:00Z"
	}
	]
)";

static char* startTransactionResStr = R"(
	[3,"uniqueId#1",
	{
		"idTagInfo": {
			"expiryDate": "2023-12-31T23:59:59Z",
			"parentIdTag": "PARENT123",
			"status": "Accepted"
		},
		"transactionId": 12345
	}
	]
)";

static char* statusNotificationReqStr = R"(
	[2,"uniqueId#1","StatusNotification"
	{
		"connectorId": 1,
		"errorCode": "NoError",
		"info": "All systems operational",
		"status": "Available",
		"timestamp": "2023-10-01T12:00:00Z",
		"vendorId": "VendorXYZ",
		"vendorErrorCode": "None"
	}
	]
)";

static char* statusNotificationResStr = R"(
	[3,"uniqueId#1",
	{}
	]
)";

static char* stopTransactionReqStr = R"(
	[2,"uniqueId#1","StopTransaction"
	{
		"idTag": "USER123456",
		"meterStop": 1500,
		"timestamp": "2023-10-01T12:30:00Z",
		"transactionId": 12345,
		"reason": "EVDisconnected",
		"transactionData": [
			{
				"timestamp": "2023-10-01T12:15:00Z",
				"sampledValue": [
					{
						"value": "10.5",
						"context": "Transaction.End",
						"format": "Raw",
						"measurand": "Energy.Active.Import.Register",
						"phase": "L1",
						"location": "EV",
						"unit": "kWh"
					},
					{
						"value": "5.0",
						"context": "Sample.Periodic",
						"format": "SignedData",
						"measurand": "Power.Active.Import",
						"phase": "L1",
						"location": "Cable",
						"unit": "kW"
					}
				]
			}
		]
	}
	]
)";

static char* stopTransactionResStr = R"(
	[3,"uniqueId#1",
	{
		"idTagInfo": {
			"expiryDate": "2023-12-31T23:59:59Z",
			"parentIdTag": "PARENT123",
			"status": "Accepted"
		}
	}
	]
)";

static char* triggerMessageReqStr = R"(
	[2,"uniqueId#1","TriggerMessage"
	{
		"requestedMessage": "BootNotification"
	}
	]
)";

static char* triggerMessageResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "NotImplemented"
	}
	]
)";

static char* unlockConnectorReqStr = R"(
	[2,"uniqueId#1","UnlockConnector"
	{
		"connectorId": 12
	}
	]
)";

static char* unlockConnectorResStr = R"(
	[3,"uniqueId#1",
	{
		"status": "Unlocked"
	}
	]
)";

static char* updateFirmwareReqStr = R"(
	[2,"uniqueId#1","UpdateFirmware"
	{
		"location": "url",
		"retrieveDate": "2023-10-01T12:00:00Z",
		"retries": 3,
		"retryInterval": 10
	}
	]
)";

static char* updateFirmwareResStr = R"(
	[3,"uniqueId#1",
	{}
	]
)";

int main(int argc, char* argv[])
{
	Ocpp_Init(&ocppHandle);
	Ocpp_RegisterMessageListener(&ocppHandle, Ocpp_MessageHandler);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								authorizeReqMessageStr, strlen(authorizeReqMessageStr));
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								authorizeResMessageStr, strlen(authorizeResMessageStr));
	// Ocpp_Loop(&ocppHandle);

	OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
									bootNotificationReqMessageStr,
									strlen(bootNotificationReqMessageStr));
	Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								bootNotificationResMessageStr,
	// 								strlen(bootNotificationResMessageStr));
	// Ocpp_Loop(&ocppHandle);
	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								cancelReservationReqStr, strlen(cancelReservationReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CANCEL_RESERVATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								cancelReservationResStr, strlen(cancelReservationResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CANCEL_RESERVATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								changeAvailabilityReqStr, strlen(changeAvailabilityReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CHANGE_AVAILABILITY;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								changeAvailabilityResStr, strlen(changeAvailabilityResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CHANGE_AVAILABILITY;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								changeConfigurationReqStr, strlen(changeConfigurationReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CHANGE_CONFIGURATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								changeConfigurationResStr, strlen(changeConfigurationResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CHANGE_CONFIGURATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, clearCacheReqStr,
	// 								strlen(clearCacheReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CLEAR_CACHE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, clearCacheResStr,
	// 								strlen(clearCacheResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CLEAR_CACHE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								clearChargingProfileReqStr, strlen(clearChargingProfileReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CLEAR_CHARGING_PROFILE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								clearChargingProfileResStr, strlen(clearChargingProfileResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_CLEAR_CHARGING_PROFILE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, dataTransferReqStr,
	// 								strlen(dataTransferReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_DATA_TRANSFER;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, dataTransferResStr,
	// 								strlen(dataTransferResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_DATA_TRANSFER;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								diagnosticStatusNotificationReqStr,
	// 								strlen(diagnosticStatusNotificationReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_DIAGNOSTIC_STATUS_NOTIFICATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								diagnosticStatusNotificationResStr,
	// 								strlen(diagnosticStatusNotificationResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_DIAGNOSTIC_STATUS_NOTIFICATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								firmwareStatusNotificationReqStr,
	// 								strlen(firmwareStatusNotificationReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_FIRMWARE_STATUS_NOTIFICATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								firmwareStatusNotificationResStr,
	// 								strlen(firmwareStatusNotificationResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_FIRMWARE_STATUS_NOTIFICATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								getCompositeScheduleReqStr, strlen(getCompositeScheduleReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_COMPOSITE_SCHEDULE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								getCompositeScheduleResStr, strlen(getCompositeScheduleResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_COMPOSITE_SCHEDULE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								getConfigurationReqStr, strlen(getConfigurationReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_CONFIGURATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								getConfigurationResStr, strlen(getConfigurationResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_CONFIGURATION;
	// Ocpp_Loop(&ocppHandle);
	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// getDiagnosticReqStr, 								strlen(getDiagnosticReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_DIAGNOSTIC; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// getDiagnosticResStr, 								strlen(getDiagnosticResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_DIAGNOSTIC; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								getLocalListVersionReqStr, strlen(getLocalListVersionReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_LOCAL_LIST_VERSION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								getLocalListVersionResStr, strlen(getLocalListVersionResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_GET_LOCAL_LIST_VERSION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, getHeartBeatReqStr,
	// 								strlen(getHeartBeatReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_HEARTBEAT;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, getHeartBeatResStr,
	// 								strlen(getHeartBeatResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_HEARTBEAT;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// getMeterValuesReqStr, 								strlen(getMeterValuesReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_METER_VALUE; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// getMeterValuesResStr, 								strlen(getMeterValuesResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_METER_VALUE; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								remoteStartTransactionReqStr,
	// 								strlen(remoteStartTransactionReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_REMOTE_START_TRANSACTION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								remoteStartTransactionResStr,
	// 								strlen(remoteStartTransactionResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_REMOTE_START_TRANSACTION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								remoteStopTransactionReqStr,
	// 								strlen(remoteStopTransactionReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_REMOTE_STOP_TRANSACTION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								remoteStopTransactionResStr,
	// 								strlen(remoteStopTransactionResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_REMOTE_STOP_TRANSACTION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, reserveNowReqStr,
	// 								strlen(reserveNowReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_RESERVE_NOW;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, reserveNowResStr,
	// 								strlen(reserveNowResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_RESERVE_NOW;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, resetReqStr,
	// 								strlen(resetReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_RESET;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA, resetResStr,
	// 								strlen(resetResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_RESET;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// sendLocalListReqStr, 								strlen(sendLocalListReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_SEND_LOCAL_LIST; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// sendLocalListResStr, 								strlen(sendLocalListResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_SEND_LOCAL_LIST; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								setChargingProfileReqStr, strlen(setChargingProfileReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_SET_CHARGING_PROFILE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								setChargingProfileResStr, strlen(setChargingProfileResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_SET_CHARGING_PROFILE;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								startTransactionReqStr, strlen(startTransactionReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_START_TRANSACTION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								startTransactionResStr, strlen(startTransactionResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_START_TRANSACTION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								statusNotificationReqStr, strlen(statusNotificationReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_STATUS_NOTIFICATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// 								statusNotificationResStr, strlen(statusNotificationResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_STATUS_NOTIFICATION;
	// Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// stopTransactionReqStr, 								strlen(stopTransactionReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_STOP_TRANSACTION; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// stopTransactionResStr, 								strlen(stopTransactionResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_STOP_TRANSACTION; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// triggerMessageReqStr, 								strlen(triggerMessageReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_TRIGGER_MESSAGE; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// triggerMessageResStr, 								strlen(triggerMessageResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_TRIGGER_MESSAGE; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// unlockConnectorReqStr, 								strlen(unlockConnectorReqStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_UNLOCK_CONNECTOR; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// unlockConnectorResStr, 								strlen(unlockConnectorResStr));
	// ocppHandle.requestPool[0].actionId = OCPP_ACTION_UNLOCK_CONNECTOR; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// updateFirmwareReqStr, 								strlen(updateFirmwareReqStr)); ocppHandle.requestPool[0].actionId =
	// OCPP_ACTION_UPDATE_FIRMWARE; Ocpp_Loop(&ocppHandle);

	// OcppWebSocket_EventCallbackFunc(SOCKET_ID, OCPP_WEB_SOCKET_EVENT_RX_DATA,
	// updateFirmwareResStr, 								strlen(updateFirmwareResStr)); ocppHandle.requestPool[0].actionId =
	// OCPP_ACTION_UPDATE_FIRMWARE; Ocpp_Loop(&ocppHandle);
}

static OcppRetType OcppWebSocketIntf_SendData(int socketId, uint8_t* data, uint32_t dataSize)
{
	printf("Sending message %.*s with size %d at socket %d \r\n", dataSize, (char*)data, dataSize,
		   socketId);
}
static OcppRetType
	OcppWebSocketIntf_RegisterEventCallback(OcppWebSocket_EventCallback eventCallback)
{
	OcppWebSocket_EventCallbackFunc = eventCallback;
}

static OcppRetType Ocpp_MessageHandler(OcppMessage* message)
{
	printf("Received message from Ocpp Server\r\n");
	// Receive message from Ocpp Server
	Ocpp_SendMessage(&ocppHandle, message); // Send back message to Ocpp Server
}