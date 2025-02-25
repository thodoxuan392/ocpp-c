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
	OCPP_MESSAGE_TYPE_CALL = 2,
	OCPP_MESSAGE_TYPE_CALL_RESULT = 3,
	OCPP_MESSAGE_TYPE_CALL_ERROR = 4
} OcppMessageTypeId;
typedef enum
{
	OCPP_ACTION_AUTHORIZE_REQ,
	OCPP_ACTION_AUTHORIZE_RES,
	OCPP_ACTION_BOOT_NOTIFICATION_REQ,
	OCPP_ACTION_BOOT_NOTIFICATION_RES,
	OCPP_ACTION_CANCEL_RESERVATION_REQ,
	OCPP_ACTION_CANCEL_RESERVATION_RES,
	OCPP_ACTION_CHANGE_AVAILABILITY_REQ,
	OCPP_ACTION_CHANGE_AVAILABILITY_RES,
	OCPP_ACTION_CHANGE_CONFIGURATION_REQ,
	OCPP_ACTION_CHANGE_CONFIGURATION_RES,
	OCPP_ACTION_CLEAR_CACHE_REQ,
	OCPP_ACTION_CLEAR_CACHE_RES,
	OCPP_ACTION_CLEAR_CHARGING_PROFILE_REQ,
	OCPP_ACTION_CLEAR_CHARGING_PROFILE_RES,
	OCPP_ACTION_DATA_TRANSFER_REQ,
	OCPP_ACTION_DATA_TRANSFER_RES,
	OCPP_ACTION_DIAGNOSTIC_STATUS_NOTIFICATION_REQ,
	OCPP_ACTION_DIAGNOSTIC_STATUS_NOTIFICATION_RES,
	OCPP_ACTION_FIRMWARE_STATUS_NOTIFICATION_REQ,
	OCPP_ACTION_FIRMWARE_STATUS_NOTIFICATION_RES,
	OCPP_ACTION_GET_COMPOSITE_SCHEDULE_REQ,
	OCPP_ACTION_GET_COMPOSITE_SCHEDULE_RES,
	OCPP_ACTION_GET_CONFIGURATION_REQ,
	OCPP_ACTION_GET_CONFIGURATION_RES,
	OCPP_ACTION_GET_DIAGNOSTIC_REQ,
	OCPP_ACTION_GET_DIAGNOSTIC_RES,
	OCPP_ACTION_GET_LOCAL_LIST_VERSION_REQ,
	OCPP_ACTION_GET_LOCAL_LIST_VERSION_RES,
	OCPP_ACTION_HEARTBEAT_REQ,
	OCPP_ACTION_HEARTBEAT_RES,
	OCPP_ACTION_METER_VALUE_REQ,
	OCPP_ACTION_METER_VALUE_RES,
	OCPP_ACTION_REMOTE_START_TRANSACTION_REQ,
	OCPP_ACTION_REMOTE_START_TRANSACTION_RES,
	OCPP_ACTION_REMOTE_STOP_TRANSACTION_REQ,
	OCPP_ACTION_REMOTE_STOP_TRANSACTION_RES,
	OCPP_ACTION_RESERVE_NOW_REQ,
	OCPP_ACTION_RESERVE_NOW_RES,
	OCPP_ACTION_RESET_REQ,
	OCPP_ACTION_RESET_RES,
	OCPP_ACTION_SEND_LOCAL_LIST_REQ,
	OCPP_ACTION_SEND_LOCAL_LIST_RES,
	OCPP_ACTION_SET_CHARGING_PROFILE_REQ,
	OCPP_ACTION_SET_CHARGING_PROFILE_RES,
	OCPP_ACTION_START_TRANSACTION_REQ,
	OCPP_ACTION_START_TRANSACTION_RES,
	OCPP_ACTION_STATUS_NOTIFICATION_REQ,
	OCPP_ACTION_STATUS_NOTIFICATION_RES,
	OCPP_ACTION_STOP_TRANSACTION_REQ,
	OCPP_ACTION_STOP_TRANSACTION_RES,
	OCPP_ACTION_TRIGGER_MESSAGE_REQ,
	OCPP_ACTION_TRIGGER_MESSAGE_RES,
	OCPP_ACTION_UNLOCK_CONNECTOR_REQ,
	OCPP_ACTION_UNLOCK_CONNECTOR_RES,
	OCPP_ACTION_UPDATE_FIRMWARE_REQ,
	OCPP_ACTION_UPDATE_FIRMWARE_RES,

} OcppActionId;

typedef enum
{
	OCPP_ERROR_CODE_NOT_IMPLEMENTED,
	OCPP_ERROR_CODE_NOT_SUPPORTED,
	OCPP_ERROR_CODE_INTERNAL_ERROR,
	OCPP_ERROR_CODE_MESSAGE_TYPE_NOT_SUPPORTED,
	OCPP_ERROR_CODE_PROTOCOL_ERROR,
	OCPP_ERROR_CODE_SECURITY_ERROR,
	OCPP_ERROR_CODE_PROPERTY_CONSTRAIN_VIOLATION,
	OCPP_ERROR_CODE_OCCURRENCE_CONSTRAIN_VIOLATION,
	OCPP_ERROR_CODE_TYPE_CONSTRAIN_VIOLATION,
	OCPP_ERROR_CODE_GENERIC_ERROR,
	OCPP_ERROR_CODE_FORMAT_VIOLATION,
	OCPP_ERROR_CODE_FORMATION_VIOLATION,

} OcppErrorCode;

typedef char OcppErrorDescription[OCPP_ERROR_DESCRIPTION_MAX_LENGTH];
typedef char OcppErrorDetails[OCPP_ERROR_DETAIL_MAX_LENGTH];
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
} OcppPayload;
typedef struct
{
	OcppActionId action;
	OcppPayload payload;
} OcppCallMessage;

typedef struct
{
	OcppPayload payload;
} OcppCallResultMessage;

typedef struct
{
	OcppErrorCode errorCode;
	OcppErrorDescription errorDescription;
	OcppErrorDetails errorDetails;
} OcppCallErrorMessage;

typedef struct
{
	OcppMessageTypeId messageTypeId;
	OcppUuid uniqueId;
	union
	{
		OcppCallMessage call;
		OcppCallResultMessage callResult;
		OcppCallErrorMessage callError;
	};
} OcppMessage;

typedef OcppRetType (*OcppMessageListener)(OcppMessage* message);

typedef struct
{
	OcppWebSocketIntf* webSocketIntf;
	OcppMessageListener messageListener;
	bool connected;
	uint8_t rxBuffer[OCPP_RX_BUFFER_MAX_LENGTH];
	uint32_t rxBufferLength;
	uint8_t txBuffer[OCPP_TX_BUFFER_MAX_LENGTH];
} OcppHandle;

OcppRetType Ocpp_Init(OcppHandle* ocppHandle);
OcppRetType Ocpp_DeInit(OcppHandle* ocppHandle);
OcppRetType Ocpp_Loop(OcppHandle* ocppHandle);
OcppRetType Ocpp_RegisterMessageListener(OcppHandle* ocppHandle,
										 OcppMessageListener messageListener);

OcppRetType Ocpp_SendMessage(OcppHandle* ocppHandle, OcppMessage* message);

#endif // __OCPP_H