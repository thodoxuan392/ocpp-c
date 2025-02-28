#include <stdio.h>
#include <stdint.h>

#include <Ocpp.h>

/**
 * @brief WebSocket
 */
static OcppRetType OcppWebSocketIntf_SendData(int socketId, uint8_t* data, uint32_t dataSize);
static OcppRetType
	OcppWebSocketIntf_RegisterEventCallback(OcppWebSocket_EventCallback eventCallback);

static const OcppWebSocketIntf ocppWebSocketIntf = {
	.socketId = 1,
	.sendDataPf = OcppWebSocketIntf_SendData,
	.registerEventCallbackPf = OcppWebSocketIntf_RegisterEventCallback,
};

/**
 * @brief Ocpp
 *
 */
static OcppRetType Ocpp_MessageHandler(OcppMessage* message);

static OcppHandle ocppHandle = {
	.webSocketIntf = &ocppWebSocketIntf,
};

static OcppMessage authorizeReqMessage = {
	.messageTypeId = OCPP_MESSAGE_TYPE_CALL,
	.uniqueId = "uuid#123456789",
	.call =
		{
			.action = OCPP_ACTION_AUTHORIZE,
			.payload =
				{
					.authorizeReq =
						{
							.idTag = "idTag#123456789",
						},
				},
		},
};

static OcppMessage authorizeResMessage = {
	.messageTypeId = OCPP_MESSAGE_TYPE_CALL_RESULT,
	.uniqueId = "uuid#123456789",
	.callResult =
		{
			.action = OCPP_ACTION_AUTHORIZE,
			.payload =
				{
					.authorizeRes =
						{
							.idTagInfo =
								{
									.parentIdTag = "idTag#123456789",
									.expiryDate = {.year = 2025, .month = 1},
									.status = OCPP_MESSAGE_STATUS_ACCEPTED,
								},
						},
				},
		},
};

static OcppMessage bootNotificationReqMessage = {
	.messageTypeId = OCPP_MESSAGE_TYPE_CALL,
	.uniqueId = "uniqueId#1",
	.call =
		{
			.action = OCPP_ACTION_BOOT_NOTIFICATION,
			.payload.bootNotificationReq =
				{
					.chargeBoxSerialNumber = "123456",
					.chargePointModel = "obc",
					.chargePointSerialNumber = " Test",
					.chargePointVendor = "eboost",
					.firmwareVersion = "1.2.3",
					.iccid = "iccidTest",
					.imsi = "imsiTest",
					.meterSerialNumber = "Test",
					.meterType = "Test",
				},
		},
};

static OcppMessage bootNotificationResMessage = {
	.messageTypeId = OCPP_MESSAGE_TYPE_CALL_RESULT,
	.uniqueId = "uniqueId#response",
	.callResult =
		{
			.action = OCPP_ACTION_BOOT_NOTIFICATION,
			.payload.bootNotificationRes =
				{
					.currentTime =
						{
							.year = 2025,
						},
					.status = OCPP_MESSAGE_STATUS_BLOCKED,
					.interval = 100,
				},
		},
};

int main(int argc, char* argv[])
{
	Ocpp_Init(&ocppHandle);
	Ocpp_RegisterMessageListener(&ocppHandle, Ocpp_MessageHandler);

	Ocpp_SendMessage(&ocppHandle, &authorizeReqMessage);
	Ocpp_SendMessage(&ocppHandle, &authorizeResMessage);
	Ocpp_SendMessage(&ocppHandle, &bootNotificationReqMessage);
	Ocpp_SendMessage(&ocppHandle, &bootNotificationResMessage);
}

static OcppRetType OcppWebSocketIntf_SendData(int socketId, uint8_t* data, uint32_t dataSize)
{
	printf("Sending message %.*s with size %d at socket %d \r\n", dataSize, (char*)data, dataSize,
		   socketId);
}
static OcppRetType
	OcppWebSocketIntf_RegisterEventCallback(OcppWebSocket_EventCallback eventCallback)
{
}

static OcppRetType Ocpp_MessageHandler(OcppMessage* message)
{
}