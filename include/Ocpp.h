/**
 * @file OcppApi.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __OCPP_H
#define __OCPP_H

#include <OcppPrvHeader.h>
#include <OcppDateTime.h>
#include <OcppWebsocketIntf.h>
#include <message/OcppAuthorize.h>
#include <message/OcppBootNotification.h>
#include <message/OcppCancelReservation.h>
#include <message/OcppChangeAvailability.h>
#include <message/OcppChangeConfiguration.h>
#include <message/OcppClearCache.h>
#include <message/OcppClearChargingProfile.h>
#include <message/OcppDataTransfer.h>
#include <message/OcppDiagnosticStatusNotification.h>
#include <message/OcppFirmwareStatusNotification.h>
#include <message/OcppGetCompositeSchedule.h>
#include <message/OcppGetConfiguration.h>
#include <message/OcppGetDiagnostics.h>
#include <message/OcppGetLocalListVersion.h>
#include <message/OcppHeartBeat.h>
#include <message/OcppMeterValue.h>
#include <message/OcppRemoteStartTransaction.h>
#include <message/OcppRemoteStopTransaction.h>
#include <message/OcppReserveNow.h>
#include <message/OcppReset.h>
#include <message/OcppSendLocalList.h>
#include <message/OcppSetChargingProfile.h>
#include <message/OcppStartTransaction.h>
#include <message/OcppStatusNotification.h>
#include <message/OcppStopTransaction.h>
#include <message/OcppTriggerMessage.h>
#include <message/OcppUnlockConnector.h>
#include <message/OcppUpdateFirmware.h>

typedef enum
{
	OCPP_MESSAGE_AUTHORIZE_REQ,
	OCPP_MESSAGE_AUTHORIZE_RES,
	OCPP_MESSAGE_BOOT_NOTIFICATION_REQ,
	OCPP_MESSAGE_BOOT_NOTIFICATION_RES,
	OCPP_MESSAGE_CANCEL_RESERVATION_REQ,
	OCPP_MESSAGE_CANCEL_RESERVATION_RES,
	OCPP_MESSAGE_CHANGE_AVAILABILITY_REQ,
	OCPP_MESSAGE_CHANGE_AVAILABILITY_RES,
	OCPP_MESSAGE_CHANGE_CONFIGURATION_REQ,
	OCPP_MESSAGE_CHANGE_CONFIGURATION_RES,
	OCPP_MESSAGE_CLEAR_CACHE_REQ,
	OCPP_MESSAGE_CLEAR_CACHE_RES,
	OCPP_MESSAGE_CLEAR_CHARGING_PROFILE_REQ,
	OCPP_MESSAGE_CLEAR_CHARGING_PROFILE_RES,
	OCPP_MESSAGE_DATA_TRANSFER_REQ,
	OCPP_MESSAGE_DATA_TRANSFER_RES,
	OCPP_MESSAGE_DIAGNOSTIC_STATUS_NOTIFICATION_REQ,
	OCPP_MESSAGE_DIAGNOSTIC_STATUS_NOTIFICATION_RES,
	OCPP_MESSAGE_FIRMWARE_STATUS_NOTIFICATION_REQ,
	OCPP_MESSAGE_FIRMWARE_STATUS_NOTIFICATION_RES,
	OCPP_MESSAGE_GET_COMPOSITE_SCHEDULE_REQ,
	OCPP_MESSAGE_GET_COMPOSITE_SCHEDULE_RES,
	OCPP_MESSAGE_GET_CONFIGURATION_REQ,
	OCPP_MESSAGE_GET_CONFIGURATION_RES,
	OCPP_MESSAGE_GET_DIAGNOSTIC_REQ,
	OCPP_MESSAGE_GET_DIAGNOSTIC_RES,
	OCPP_MESSAGE_GET_LOCAL_LIST_VERSION_REQ,
	OCPP_MESSAGE_GET_LOCAL_LIST_VERSION_RES,
	OCPP_MESSAGE_HEARTBEAT_REQ,
	OCPP_MESSAGE_HEARTBEAT_RES,
	OCPP_MESSAGE_METER_VALUE_REQ,
	OCPP_MESSAGE_METER_VALUE_RES,
	OCPP_MESSAGE_REMOTE_START_TRANSACTION_REQ,
	OCPP_MESSAGE_REMOTE_START_TRANSACTION_RES,
	OCPP_MESSAGE_REMOTE_STOP_TRANSACTION_REQ,
	OCPP_MESSAGE_REMOTE_STOP_TRANSACTION_RES,
	OCPP_MESSAGE_RESERVE_NOW_REQ,
	OCPP_MESSAGE_RESERVE_NOW_RES,
	OCPP_MESSAGE_RESET_REQ,
	OCPP_MESSAGE_RESET_RES,
	OCPP_MESSAGE_SEND_LOCAL_LIST_REQ,
	OCPP_MESSAGE_SEND_LOCAL_LIST_RES,
	OCPP_MESSAGE_SET_CHARGING_PROFILE_REQ,
	OCPP_MESSAGE_SET_CHARGING_PROFILE_RES,
	OCPP_MESSAGE_START_TRANSACTION_REQ,
	OCPP_MESSAGE_START_TRANSACTION_RES,
	OCPP_MESSAGE_STATUS_NOTIFICATION_REQ,
	OCPP_MESSAGE_STATUS_NOTIFICATION_RES,
	OCPP_MESSAGE_STOP_TRANSACTION_REQ,
	OCPP_MESSAGE_STOP_TRANSACTION_RES,
	OCPP_MESSAGE_TRIGGER_MESSAGE_REQ,
	OCPP_MESSAGE_TRIGGER_MESSAGE_RES,
	OCPP_MESSAGE_UNLOCK_CONNECTOR_REQ,
	OCPP_MESSAGE_UNLOCK_CONNECTOR_RES,
	OCPP_MESSAGE_UPDATE_FIRMWARE_REQ,
	OCPP_MESSAGE_UPDATE_FIRMWARE_RES,

} OcppMessageId;

typedef union
{
	OcppAuthorizeRequest authorizeReq;
	OcppAuthorizeResponse authorizeRes;
	OcppBootNotificationRequest bootNotificationReq;
	OcppBootNotificationResponse bootNotificationRes;
	OcppCancelReservationRequest cancelReservationReq;
	OcppCancelReservationResponse cancelReservationRes;
	OcppChangeAvailabilityRequest changeAvailabilityReq;
	OcppChangeAvailabilityResponse changeAvailabilityRes;
	OcppChangeConfigurationRequest changeConfigurationReq;
	OcppChangeConfigurationResponse changeConfigurationRes;
	OcppClearCacheRequest clearCacheReq;
	OcppClearCacheResponse clearCacheRes;
	OcppClearChargingProfileRequest clearChargingProfileReq;
	OcppClearChargingProfileResponse clearChargingProfileRes;
	OcppDataTransferRequest dataTransferReq;
	OcppDataTransferResponse dataTransferRes;
	OcppDiagnosticStatusNotificationRequest diagnosticStatusNotificationReq;
	OcppDiagnosticStatusNotificationResponse diagnosticStatusNotificationRes;
	OcppFirmwareStatusNotificationRequest firmwareStatusNotificationReq;
	OcppFirmwareStatusNotificationResponse firmwareStatusNotificationRes;
	OcppGetCompositeScheduleRequest getCompositeScheduleReq;
	OcppGetCompositeScheduleResponse getCompositeScheduleRes;
	OcppGetConfigurationRequest getConfigurationReq;
	OcppGetConfigurationResponse getConfigurationRes;
	OcppGetDiagnosticRequest getDiagnosticReq;
	OcppGetDiagnosticResponse getDiagnosticRes;
	OcppGetLocalListVersionRequest getLocalListVersionReq;
	OcppGetLocalListVersionResponse getLocalListVersionRes;
	OcppHeartBeatRequest heartBeatReq;
	OcppHeartBeatResponse heartBeatRes;
	OcppMeterValueRequest meterValueReq;
	OcppMeterValueResponse meterValueRes;
	OcppRemoteStartTransactionRequest remoteStartTransactionReq;
	OcppRemoteStartTransactionResponse remoteStartTransactionRes;
	OcppRemoteStopTransactionRequest remoteStopTransactionReq;
	OcppRemoteStopTransactionResponse remoteStopTransactionRes;
	OcppReserveNowRequest reserveNowReq;
	OcppReserveNowResponse reserveNowRes;
	OcppResetRequest resetReq;
	OcppResetResponse resetRes;
	OcppSendLocalListRequest sendLocalListReq;
	OcppSendLocalListResponse sendLocalListRes;
	OcppSetChargingProfileRequest setChargingProfileReq;
	OcppSetChargingProfileResponse setChargingProfileRes;
	OcppStartTransactionRequest startTransactionReq;
	OcppStartTransactionResponse startTransactionRes;
	OcppStatusNotificationRequest statusNotificationReq;
	OcppStatusNotificationResponse statusNotificationRes;
	OcppStopTransactionRequest stopTransactionReq;
	OcppStopTransactionResponse stopTransactionRes;
	OcppTriggerMessageRequest triggerMessageReq;
	OcppTriggerMessageResponse triggerMessageRes;
	OcppUnlockConnectorRequest unlockConnectorReq;
	OcppUnlockConnectorResponse unlockConnectorRes;
	OcppUpdateFirmwareRequest updateFirmwareReq;
	OcppUpdateFirmwareResponse updateFirmwareRes;
} OcppMessage;

typedef OcppRetType (*OcppMessageListener)(OcppMessageId id, OcppMessage* message);

typedef struct
{
	OcppWebSocketIntf* webSocketIntf;
	OcppMessageListener messageListener;
	bool connected;
} OcppHandle;

OcppRetType Ocpp_Init(OcppHandle* ocppHandle);
OcppRetType Ocpp_DeInit(OcppHandle* ocppHandle);
OcppRetType Ocpp_Loop(OcppHandle* ocppHandle);
OcppRetType Ocpp_RegisterMessageListener(OcppHandle* ocppHandle,
										 OcppMessageListener messageListener);

OcppRetType Ocpp_SendMessage(OcppHandle* ocppHandle, OcppMessageId id, OcppMessage* message);

#endif // __OCPP_H