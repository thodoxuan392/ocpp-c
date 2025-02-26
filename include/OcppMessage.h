#ifndef __OCPP_MESSAGE_H
#define __OCPP_MESSAGE_H

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
	OcppActionId action; // Not used to build and parse
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

#endif // __OCPP_MESSAGE_H