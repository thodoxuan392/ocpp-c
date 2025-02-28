#include <OcppJson.h>

#include <string.h>
#include <jsmn.h>

typedef enum
{
	OCPP_PAYLOAD_TYPE_REQ,
	OCPP_PAYLOAD_TYPE_RES,

	OCPP_PAYLOAD_TYPE_MAX
} OcppJson_PayloadType;

typedef OcppRetType (*OcppJson_BuildPayloadFnc)(void* payload, char* string,
												uint32_t* stringLength);
typedef OcppRetType (*OcppJson_ParsePayloadFnc)(char* json, jsmntok_t* token, uint32_t* tokenLen,
												void* payload);

typedef struct
{
	OcppJson_BuildPayloadFnc buildFnc;
	OcppJson_ParsePayloadFnc parseFnc;
} OcppJson_PayloadOperation;

static OcppRetType OcppJson_FindGenericDataInTable(char* string, uint32_t stringLength,
												   const char** mappingTable,
												   uint32_t mappingTableLength,
												   uint32_t* foundIndex);
static OcppRetType OcppJson_GetGenericDataInTable(uint32_t index, const char** mappingTable,
												  uint32_t mappingTableLength, char* string,
												  uint32_t* stringLength);

static const OcppJson_PayloadOperation
	OcppJson_PayloadOperationMapping[OCPP_ACTION_MAX][OCPP_PAYLOAD_TYPE_MAX] = {
		[OCPP_ACTION_AUTHORIZE] =
			{
				{OcppAuthorize_BuildRequest, OcppAuthorize_ParseRequest},
				{OcppAuthorize_BuildResponse, OcppAuthorize_ParseResponse},
			},
		[OCPP_ACTION_BOOT_NOTIFICATION] =
			{
				{OcppBootNotification_BuildRequest, OcppBootNotification_ParseRequest},
				{OcppBootNotification_BuildResponse, OcppBootNotification_ParseResponse},
			},
		[OCPP_ACTION_CANCEL_RESERVATION] =
			{
				{OcppCancelReservation_BuildRequest, OcppCancelReservation_ParseRequest},
				{
					OcppCancelReservation_BuildResponse,
					OcppCancelReservation_ParseResponse,
				},
			},
		[OCPP_ACTION_CHANGE_AVAILABILITY] =
			{
				{OcppChangeAvailability_BuildRequest, OcppChangeAvailability_ParseRequest},
				{OcppChangeAvailability_BuildResponse, OcppChangeAvailability_ParseResponse},
			},
		[OCPP_ACTION_CHANGE_CONFIGURATION] =
			{
				{OcppChangeConfiguration_BuildRequest, OcppChangeConfiguration_ParseRequest},
				{OcppChangeConfiguration_BuildResponse, OcppChangeConfiguration_ParseResponse},
			},
		[OCPP_ACTION_CLEAR_CACHE] =
			{
				{OcppClearCache_BuildRequest, OcppClearCache_ParseRequest},
				{
					OcppClearCache_BuildResponse,
					OcppClearCache_ParseResponse,
				},
			},
		[OCPP_ACTION_CLEAR_CHARGING_PROFILE] =
			{
				{OcppClearChargingProfile_BuildRequest, OcppClearChargingProfile_ParseRequest},
				{OcppClearChargingProfile_BuildResponse, OcppClearChargingProfile_ParseResponse},
			},
		[OCPP_ACTION_DATA_TRANSFER] =
			{
				{OcppDataTransfer_BuildRequest, OcppDataTransfer_ParseRequest},
				{OcppDataTransfer_BuildResponse, OcppDataTransfer_ParseResponse},
			},
		[OCPP_ACTION_DIAGNOSTIC_STATUS_NOTIFICATION] =
			{
				{OcppDiagnosticStatusNotification_BuildRequest,
				 OcppDiagnosticStatusNotification_ParseRequest},
				{OcppDiagnosticStatusNotification_BuildResponse,
				 OcppDiagnosticStatusNotification_ParseResponse},
			},
		[OCPP_ACTION_FIRMWARE_STATUS_NOTIFICATION] =
			{
				{OcppFirmwareStatusNotification_BuildRequest,
				 OcppFirmwareStatusNotification_ParseRequest},
				{OcppFirmwareStatusNotification_BuildResponse,
				 OcppFirmwareStatusNotification_ParseResponse},
			},
		[OCPP_ACTION_GET_COMPOSITE_SCHEDULE] =
			{
				{OcppGetCompositeSchedule_BuildRequest, OcppGetCompositeSchedule_ParseRequest},
				{OcppGetCompositeSchedule_BuildResponse, OcppGetCompositeSchedule_ParseResponse},
			},
		[OCPP_ACTION_GET_CONFIGURATION] =
			{
				{OcppGetConfiguration_BuildRequest, OcppGetConfiguration_ParseRequest},
				{OcppGetConfiguration_BuildResponse, OcppGetConfiguration_ParseResponse},
			},
		[OCPP_ACTION_GET_DIAGNOSTIC] =
			{
				{OcppGetDiagnostic_BuildRequest, OcppGetDiagnostic_ParseRequest},
				{OcppGetDiagnostic_BuildResponse, OcppGetDiagnostic_ParseResponse},
			},
		[OCPP_ACTION_GET_LOCAL_LIST_VERSION] =
			{
				{OcppGetLocalListVersion_BuildRequest, OcppGetLocalListVersion_ParseRequest},
				{
					OcppGetLocalListVersion_BuildResponse,
					OcppGetLocalListVersion_ParseResponse,
				},
			},
		[OCPP_ACTION_HEARTBEAT] =
			{
				{OcppHeartBeat_BuildRequest, OcppHeartBeat_ParseRequest},
				{OcppHeartBeat_BuildResponse, OcppHeartBeat_ParseResponse},
			},
		[OCPP_ACTION_METER_VALUE] =
			{
				{OcppMeterValue_BuildRequest, OcppMeterValue_ParseRequest},
				{OcppMeterValue_BuildResponse, OcppMeterValue_ParseResponse},
			},
		[OCPP_ACTION_REMOTE_START_TRANSACTION] =
			{
				{OcppRemoteStartTransaction_BuildRequest, OcppRemoteStartTransaction_ParseRequest},
				{OcppRemoteStartTransaction_BuildResponse,
				 OcppRemoteStartTransaction_ParseResponse},
			},
		[OCPP_ACTION_REMOTE_STOP_TRANSACTION] =
			{
				{OcppRemoteStopTransaction_BuildRequest, OcppRemoteStopTransaction_ParseRequest},
				{OcppRemoteStopTransaction_BuildResponse, OcppRemoteStopTransaction_ParseResponse},
			},
		[OCPP_ACTION_RESERVE_NOW] =
			{
				{OcppReserveNow_BuildRequest, OcppReserveNow_ParseRequest},
				{OcppReserveNow_BuildResponse, OcppReserveNow_ParseResponse},
			},
		[OCPP_ACTION_RESET] =
			{
				{OcppReset_BuildRequest, OcppReset_ParseRequest},
				{OcppReset_BuildResponse, OcppReset_ParseResponse},
			},
		[OCPP_ACTION_SEND_LOCAL_LIST] =
			{
				{OcppSendLocalList_BuildRequest, OcppSendLocalList_ParseRequest},
				{OcppSendLocalList_BuildResponse, OcppSendLocalList_ParseResponse},
			},
		[OCPP_ACTION_SET_CHARGING_PROFILE] =
			{
				{OcppSetChargingProfile_BuildRequest, OcppSetChargingProfile_ParseRequest},
				{OcppSetChargingProfile_BuildResponse, OcppSetChargingProfile_ParseResponse},
			},
		[OCPP_ACTION_START_TRANSACTION] =
			{
				{OcppStartTransaction_BuildRequest, OcppStartTransaction_ParseRequest},
				{OcppStartTransaction_BuildResponse, OcppStartTransaction_ParseResponse},
			},
		[OCPP_ACTION_STATUS_NOTIFICATION] =
			{
				{OcppStatusNotification_BuildRequest, OcppStatusNotification_ParseRequest},
				{OcppStatusNotification_BuildResponse, OcppStatusNotification_ParseResponse},
			},
		[OCPP_ACTION_STOP_TRANSACTION] =
			{
				{OcppStopTransaction_BuildRequest, OcppStopTransaction_ParseRequest},
				{
					OcppStopTransaction_BuildResponse,
					OcppStopTransaction_ParseResponse,
				},
			},
		[OCPP_ACTION_TRIGGER_MESSAGE] =
			{
				{OcppTriggerMessage_BuildRequest, OcppTriggerMessage_ParseRequest},
				{OcppTriggerMessage_BuildResponse, OcppTriggerMessage_ParseResponse},
			},
		[OCPP_ACTION_UNLOCK_CONNECTOR] =
			{
				{OcppUnlockConnector_BuildRequest, OcppUnlockConnector_ParseRequest},
				{OcppUnlockConnector_BuildResponse, OcppUnlockConnector_ParseResponse},
			},
		[OCPP_ACTION_UPDATE_FIRMWARE] =
			{
				{OcppUpdateFirmware_BuildRequest, OcppUpdateFirmware_ParseRequest},
				{OcppUpdateFirmware_BuildResponse, OcppUpdateFirmware_ParseResponse},
			},
};

const char* OcppJson_MessageStatusMapping[OCPP_MESSAGE_STATUS_MAX] = {
	[OCPP_MESSAGE_STATUS_ACCEPTED] = "Accepted",
	[OCPP_MESSAGE_STATUS_REJECTED] = "Rejected",
	[OCPP_MESSAGE_STATUS_FAILED] = "Failed",
	[OCPP_MESSAGE_STATUS_FAULTED] = "Faulted",
	[OCPP_MESSAGE_STATUS_OCCUPIED] = "Occupied",
	[OCPP_MESSAGE_STATUS_UNAVAILABLE] = "Unavailable",
	[OCPP_MESSAGE_STATUS_BLOCKED] = "Blocked",
	[OCPP_MESSAGE_STATUS_PENDING] = "Pending",
	[OCPP_MESSAGE_STATUS_EXPIRED] = "Expired",
	[OCPP_MESSAGE_STATUS_INVALID] = "Invalid",
	[OCPP_MESSAGE_STATUS_CONCURRENT_TX] = "ConcurrentTx",
	[OCPP_MESSAGE_STATUS_SCHEDULED] = "Scheduled",
	[OCPP_MESSAGE_STATUS_REBOOT_REQUIRED] = "RebootRequired",
	[OCPP_MESSAGE_STATUS_NOT_SUPPORTED] = "NotSupported",
	[OCPP_MESSAGE_STATUS_UNKNOWN_MESSAGE_ID] = "UnkownMessageId",
	[OCPP_MESSAGE_STATUS_UNKNOWN_VENDOR_ID] = "UnkownVendorId",
	[OCPP_MESSAGE_STATUS_VERSION_MISMATCH] = "VersionMismatch",
	[OCPP_MESSAGE_STATUS_NOT_IMPLEMENTED] = "NotImplemented",
	[OCPP_MESSAGE_STATUS_UNLOCKED] = "Unlocked",
	[OCPP_MESSAGE_STATUS_UNLOCK_FAILED] = "UnlockFailed",
	[OCPP_MESSAGE_STATUS_AVAILABLE] = "Available",

};

const char* OcppJson_ChargingRateUnitTypeMapping[OCPP_CHARGING_RATE_UNIT_MAX] = {
	[OCPP_CHARGING_RATE_UNIT_A] = "A",
	[OCPP_CHARGING_RATE_UNIT_W] = "W",
};

const char* OcppJson_ChargingProfilePurposeMapping[OCPP_CHARGING_PROFILE_PP_MAX] = {
	[OCPP_CHARGING_PROFILE_PP_CP_MAX] = "ChargePointMaxProfile",
	[OCPP_CHARGING_PROFILE_PP_TX_DEFAULT_MAX] = "TxDefaultProfile",
	[OCPP_CHARGING_PROFILE_PP_TX_PROFILE] = "TxProfile",
};

const char* OcppJson_ChargingProfileKindMapping[OCPP_CHARGING_PROFILE_KIND_MAX] = {
	[OCPP_CHARGING_PROFILE_KIND_ABSOLUTE] = "Absolute",
	[OCPP_CHARGING_PROFILE_KIND_RECURRING] = "Recurring",
	[OCPP_CHARGING_PROFILE_KIND_RELATIVE] = "Relative",
};

const char* OcppJson_RecurrencyKindMapping[OCPP_RECURRENCY_KIND_MAX] = {
	[OCPP_RECURRENCY_KIND_DAILY] = "Daily",
	[OCPP_RECURRENCY_KIND_WEEKLY] = "Weekly",
};

const char* OcppJson_ChargePointErrorCodeMapping[OCPP_CP_ERR_MAX] = {
	[OCPP_CP_ERR_CONN_LOCK_FAIL] = "ConnectorLockFailure",
	[OCPP_CP_ERR_EV_COMM] = "EVCommunicationError",
	[OCPP_CP_ERR_GND_FAILURE] = "GroundFailure",
	[OCPP_CP_ERR_HIGH_TEMPERATURE] = "HighTemperature",
	[OCPP_CP_ERR_INTERNAL_ERROR] = "InternalError",
	[OCPP_CP_ERR_LOCAL_LIST_CONFLICT] = "LocalListConflict",
	[OCPP_CP_ERR_NO_ERROR] = "NoError",
	[OCPP_CP_ERR_OTHER_ERROR] = "OtherError",
	[OCPP_CP_ERR_OVER_CURR_FAL] = "OverCurrentFailure",
	[OCPP_CP_ERR_POWER_METER_FAIL] = "PowerMeterFailure",
	[OCPP_CP_ERR_POWER_SWI_FAIL] = "PowerSwitchFailure",
	[OCPP_CP_ERR_READER_FAIL] = "ReaderFailure",
	[OCPP_CP_ERR_RESET_FAIL] = "ResetFailure",
	[OCPP_CP_ERR_UNDER_VOLTAGE] = "UnderVoltage",
	[OCPP_CP_ERR_OVER_VOLTAGE] = "OverVoltage",
	[OCPP_CP_ERR_WEAK_SIGNAL] = "WeakSignal",
};

const char* OcppJson_SampledValueContextMapping[OCPP_SAMPLED_VALUE_CONTEXT_MAX] = {
	[OCPP_SAMPLED_VALUE_CONTEXT_INTERRUPTION_BEGIN] = "Interruption.Begin",
	[OCPP_SAMPLED_VALUE_CONTEXT_INTERRUPTION_END] = "Interruption.End",
	[OCPP_SAMPLED_VALUE_CONTEXT_SAMPLE_CLOCK] = "Sample.Clock",
	[OCPP_SAMPLED_VALUE_CONTEXT_SAMPLE_PERIOD] = "Sample.Periodic",
	[OCPP_SAMPLED_VALUE_CONTEXT_TRANSACTION_BEGIN] = "Transaction.Begin",
	[OCPP_SAMPLED_VALUE_CONTEXT_TRANSACTION_END] = "Transaction.End",
	[OCPP_SAMPLED_VALUE_CONTEXT_TRIGGER] = "Trigger",
	[OCPP_SAMPLED_VALUE_CONTEXT_OTHER] = "Other",
};

const char* OcppJson_SampledValueFormatMapping[OCPP_SAMPLED_VALUE_FORMAT_MAX] = {
	[OCPP_SAMPLED_VALUE_FORMAT_RAW] = "Raw",
	[OCPP_SAMPLED_VALUE_FORMAT_SIGNED_DATA] = "SignedData",
};

const char* OcppJson_SampledValueMeasurandMapping[OCPP_SAMPLED_VALUE_MEASURAND_MAX] = {
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_EX_REG] = "Energy.Active.Export.Register",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_IM_REG] = "Energy.Active.Import.Register",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_EX_REG] = "Energy.Reactive.Export.Register",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_IM_REG] = "Energy.Reactive.Import.Register",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_EX_INT] = "Energy.Active.Export.Interval",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_IM_INT] = "Energy.Active.Import.Interval",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_EX_INT] = "Energy.Reactive.Export.Interval",
	[OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_IM_INT] = "Energy.Reactive.Import.Interval",
	[OCPP_SAMPLED_VALUE_MEASURAND_PO_ACT_EX] = "Power.Active.Export",
	[OCPP_SAMPLED_VALUE_MEASURAND_PO_ACT_IM] = "Power.Active.Import",
	[OCPP_SAMPLED_VALUE_MEASURAND_PO_OFFER] = "Power.Offered",
	[OCPP_SAMPLED_VALUE_MEASURAND_PO_REACT_EX] = "Power.Reactive.Export",
	[OCPP_SAMPLED_VALUE_MEASURAND_PO_REACT_IM] = "Power.Reactive.Import",
	[OCPP_SAMPLED_VALUE_MEASURAND_PO_FACTOR] = "Power.Factor",
	[OCPP_SAMPLED_VALUE_MEASURAND_CURR_IM] = "Current.Import",
	[OCPP_SAMPLED_VALUE_MEASURAND_CURR_EX] = "Current.Export",
	[OCPP_SAMPLED_VALUE_MEASURAND_CURR_OFFER] = "Current.Offered",
	[OCPP_SAMPLED_VALUE_MEASURAND_VOLT] = "Voltage",
	[OCPP_SAMPLED_VALUE_MEASURAND_FREQ] = "Frequency",
	[OCPP_SAMPLED_VALUE_MEASURAND_TEMPERATURE] = "Temperature",
	[OCPP_SAMPLED_VALUE_MEASURAND_SOC] = "SoC",
	[OCPP_SAMPLED_VALUE_MEASURAND_RPM] = "RPM",
};

const char* OcppJson_SampledValuePhaseMapping[OCPP_SAMPLED_VALUE_PHASE_MAX] = {
	[OCPP_SAMPLED_VALUE_PHASE_L1] = "L1",		[OCPP_SAMPLED_VALUE_PHASE_L2] = "L2",
	[OCPP_SAMPLED_VALUE_PHASE_L3] = "L3",		[OCPP_SAMPLED_VALUE_PHASE_N] = "N",
	[OCPP_SAMPLED_VALUE_PHASE_L1_N] = "L1-N",	[OCPP_SAMPLED_VALUE_PHASE_L2_N] = "L2-N",
	[OCPP_SAMPLED_VALUE_PHASE_L3_N] = "L3-N",	[OCPP_SAMPLED_VALUE_PHASE_L1_L2] = "L1-L2",
	[OCPP_SAMPLED_VALUE_PHASE_L2_L3] = "L2-L3", [OCPP_SAMPLED_VALUE_PHASE_L3_L1] = "L3-L1",
};

const char* OcppJson_SampledValueLocationMapping[OCPP_SAMPLED_VALUE_LOC_MAX] = {
	[OCPP_SAMPLED_VALUE_LOC_CABLE] = "Cable", [OCPP_SAMPLED_VALUE_LOC_EV] = "EV",
	[OCPP_SAMPLED_VALUE_LOC_INLET] = "Inlet", [OCPP_SAMPLED_VALUE_LOC_OUTLET] = "Outlet",
	[OCPP_SAMPLED_VALUE_LOC_BODY] = "Body",
};

const char* OcppJson_SampledValueUnitMapping[OCPP_SAMPLED_VALUE_UNIT_MAX] = {
	[OCPP_SAMPLED_VALUE_UNIT_WH] = "Wh",
	[OCPP_SAMPLED_VALUE_UNIT_KWH] = "kWh",
	[OCPP_SAMPLED_VALUE_UNIT_VARH] = "varh",
	[OCPP_SAMPLED_VALUE_UNIT_KVARH] = "kvarh",
	[OCPP_SAMPLED_VALUE_UNIT_W] = "W",
	[OCPP_SAMPLED_VALUE_UNIT_KW] = "kW",
	[OCPP_SAMPLED_VALUE_UNIT_VA] = "VA",
	[OCPP_SAMPLED_VALUE_UNIT_KVA] = "kVA",
	[OCPP_SAMPLED_VALUE_UNIT_VAR] = "var",
	[OCPP_SAMPLED_VALUE_UNIT_KVAR] = "kvar",
	[OCPP_SAMPLED_VALUE_UNIT_A] = "A",
	[OCPP_SAMPLED_VALUE_UNIT_V] = "V",
	[OCPP_SAMPLED_VALUE_UNIT_K] = "K",
	[OCPP_SAMPLED_VALUE_UNIT_CELCIUS] = "Celcius",
	[OCPP_SAMPLED_VALUE_UNIT_CELSIUS] = "Celsius",
	[OCPP_SAMPLED_VALUE_UNIT_FAHRENHEIT] = "Fahrenheit",
	[OCPP_SAMPLED_VALUE_UNIT_PERCENT] = "Percent",
};

const char* OcppJson_UpdateTypeMapping[OCPP_UPDATE_TYPE_MAX] = {
	[OCPP_UPDATE_TYPE_DIFFERENTIAL] = "Differential",
	[OCPP_UPDATE_TYPE_FULL] = "Full",
};

const char* OcppJson_AvailabilityTypeMapping[OCPP_AVAILABILITY_TYPE_MAX] = {
	[OCPP_AVAILABILITY_TYPE_INOPERATIVE] = "Inoperative",
	[OCPP_AVAILABILITY_TYPE_OPERATIVE] = "Operative",
};

const char* OcppJson_DiagnosticsStatusMapping[OCPP_DIAGNOSTIC_STATUS_MAX] = {
	[OCPP_DIAGNOSTIC_STATUS_IDLE] = "Idle",
	[OCPP_DIAGNOSTIC_STATUS_UPLOADED] = "Uploaded",
	[OCPP_DIAGNOSTIC_STATUS_UPLOAD_FAILED] = "UploadFailed",
	[OCPP_DIAGNOSTIC_STATUS_UPLOADING] = "Uploading",
};

const char* OcppJson_FirmwareStatusMapping[OCPP_FIRMWARE_STATUS_MAX] = {
	[OCPP_FIRMWARE_STATUS_DOWNLOADED] = "Downloaded",
	[OCPP_FIRMWARE_STATUS_DOWNLOAD_FAILED] = "DownloadFailed",
	[OCPP_FIRMWARE_STATUS_DOWNLOADING] = "Downloading",
	[OCPP_FIRMWARE_STATUS_IDLE] = "Idle",
	[OCPP_FIRMWARE_STATUS_INSTALLATION_FAILED] = "InstallationFailed",
	[OCPP_FIRMWARE_STATUS_INSTALLING] = "Installing",
	[OCPP_FIRMWARE_STATUS_INSTALLED] = "Installed",
};

const char* OcppJson_ReasonMapping[OCPP_REASON_MAX] = {
	[OCPP_REASON_EMG_STOP] = "EmergencyStop",
	[OCPP_REASON_EV_DISCONNECTED] = "EVDisconnected",
	[OCPP_REASON_HARD_RESET] = "HardReset",
	[OCPP_REASON_LOCAL] = "Local",
	[OCPP_REASON_OTHER] = "Other",
	[OCPP_REASON_POWER_LOSS] = "PowerLoss",
	[OCPP_REASON_REBOOT] = "Reboot",
	[OCPP_REASON_REMOTE] = "Remote",
	[OCPP_REASON_SOFT_RESET] = "SoftReset",
	[OCPP_REASON_UNLOCK_COMMAND] = "UnlockCommand",
	[OCPP_REASON_DEAUTHORIZED] = "DeAuthorized",
};

const char* OcppJson_ActionIdMapping[OCPP_ACTION_MAX] = {
	[OCPP_ACTION_AUTHORIZE] = "Authorize",
	[OCPP_ACTION_BOOT_NOTIFICATION] = "BootNotification",
	[OCPP_ACTION_CANCEL_RESERVATION] = "CancelReservation",
	[OCPP_ACTION_CHANGE_AVAILABILITY] = "ChangeAvailability",
	[OCPP_ACTION_CHANGE_CONFIGURATION] = "ChangeConfiguration",
	[OCPP_ACTION_CLEAR_CACHE] = "ClearCache",
	[OCPP_ACTION_CLEAR_CHARGING_PROFILE] = "ClearChargingProfile",
	[OCPP_ACTION_DATA_TRANSFER] = "DataTransfers",
	[OCPP_ACTION_DIAGNOSTIC_STATUS_NOTIFICATION] = "DiagnosticsStatusNotification",
	[OCPP_ACTION_FIRMWARE_STATUS_NOTIFICATION] = "FirmwareStatusNotification",
	[OCPP_ACTION_GET_COMPOSITE_SCHEDULE] = "GetCompositeSchedule",
	[OCPP_ACTION_GET_CONFIGURATION] = "GetConfiguration",
	[OCPP_ACTION_GET_DIAGNOSTIC] = "GetDiagnostics",
	[OCPP_ACTION_GET_LOCAL_LIST_VERSION] = "GetLocalListVersion",
	[OCPP_ACTION_HEARTBEAT] = "Heartbeat",
	[OCPP_ACTION_METER_VALUE] = "MeterValues",
	[OCPP_ACTION_REMOTE_START_TRANSACTION] = "RemoteStartTransaction",
	[OCPP_ACTION_REMOTE_STOP_TRANSACTION] = "RemoteStopTransaction",
	[OCPP_ACTION_RESERVE_NOW] = "ReserveNow",
	[OCPP_ACTION_RESET] = "Reset",
	[OCPP_ACTION_SEND_LOCAL_LIST] = "SendLocalList",
	[OCPP_ACTION_SET_CHARGING_PROFILE] = "SetChargingProfile",
	[OCPP_ACTION_START_TRANSACTION] = "StartTransaction",
	[OCPP_ACTION_STATUS_NOTIFICATION] = "StatusNotification",
	[OCPP_ACTION_STOP_TRANSACTION] = "StopTransaction",
	[OCPP_ACTION_TRIGGER_MESSAGE] = "TriggerMessage",
	[OCPP_ACTION_UNLOCK_CONNECTOR] = "UnlockConnector",
	[OCPP_ACTION_UPDATE_FIRMWARE] = "UpdateFirmware",
};

const char* OcppJson_ErrorCodeMapping[OCPP_ERROR_CODE_MAX] = {
	[OCPP_ERROR_CODE_NOT_IMPLEMENTED] = "NotImplemented",
	[OCPP_ERROR_CODE_NOT_SUPPORTED] = "NotSupported",
	[OCPP_ERROR_CODE_INTERNAL_ERROR] = "InternalError",
	[OCPP_ERROR_CODE_MESSAGE_TYPE_NOT_SUPPORTED] = "MessageTypeNotSupported",
	[OCPP_ERROR_CODE_PROTOCOL_ERROR] = "ProtocolError",
	[OCPP_ERROR_CODE_SECURITY_ERROR] = "SecurityError",
	[OCPP_ERROR_CODE_PROPERTY_CONSTRAIN_VIOLATION] = "PropertyConstraintViolation",
	[OCPP_ERROR_CODE_OCCURRENCE_CONSTRAIN_VIOLATION] = "OccurrenceConstraintViolation",
	[OCPP_ERROR_CODE_TYPE_CONSTRAIN_VIOLATION] = "TypeConstraintViolation",
	[OCPP_ERROR_CODE_GENERIC_ERROR] = "GenericError",
	[OCPP_ERROR_CODE_FORMAT_VIOLATION] = "FormatViolation",
	[OCPP_ERROR_CODE_FORMATION_VIOLATION] = "FormationViolation",
};

const char* OcppJson_ResetTypeMapping[OCPP_RESET_TYPE_MAX] = {
	[OCPP_RESET_TYPE_HARD] = "Hard",
	[OCPP_RESET_TYPE_SOFT] = "Soft",
};

const char* OcppJson_MessageTriggerMapping[OCPP_TRIGGER_MESSAGE_MAX] = {
	[OCPP_TRIGGER_MESSAGE_BOOT_NOTIFICATION] = "BootNotification",
	[OCPP_TRIGGER_MESSAGE_DIAGNOSTIC_NOTIFICATION] = "DiagnosticsStatusNotification",
	[OCPP_TRIGGER_MESSAGE_FIRMWARE_STATUS_NOTIFICATION] = "FirmwareStatusNotification",
	[OCPP_TRIGGER_MESSAGE_HEARTBEAT] = "Heartbeat",
	[OCPP_TRIGGER_MESSAGE_METER_VALUE] = "MeterValues",
	[OCPP_TRIGGER_MESSAGE_STATUS_NOTIFICATION] = "StatusNotification",
};

OcppRetType OcppJson_ParseMessageStatus(char* string, uint32_t stringLength,
										OcppMessageStatus* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_MessageStatusMapping,
									   OCPP_MESSAGE_STATUS_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildMessageStatus(OcppMessageStatus type, char* string,
										uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_MessageStatusMapping,
										  OCPP_MESSAGE_STATUS_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseChargingRateUnitType(char* string, uint32_t stringLength,
											   OcppChargingRateUnitType* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ChargingRateUnitTypeMapping,
									   OCPP_CHARGING_RATE_UNIT_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargingRateUnitType(OcppChargingRateUnitType type, char* string,
											   uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ChargingRateUnitTypeMapping,
										  OCPP_CHARGING_RATE_UNIT_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseChargingProfilePurpose(char* string, uint32_t stringLength,
												 OcppChargingProfilePurpose* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ChargingProfilePurposeMapping,
									   OCPP_CHARGING_PROFILE_PP_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargingProfilePurpose(OcppChargingProfilePurpose type, char* string,
												 uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ChargingProfilePurposeMapping,
										  OCPP_CHARGING_PROFILE_PP_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseChargingProfileKind(char* string, uint32_t stringLength,
											  OcppChargingProfileKind* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ChargingProfileKindMapping,
									   OCPP_CHARGING_PROFILE_KIND_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargingProfileKind(OcppChargingProfileKind type, char* string,
											  uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ChargingProfileKindMapping,
										  OCPP_CHARGING_PROFILE_KIND_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseRecurrencyKind(char* string, uint32_t stringLength,
										 OcppRecurrencyKind* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_RecurrencyKindMapping,
									   OCPP_RECURRENCY_KIND_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildRecurrencyKind(OcppRecurrencyKind type, char* string,
										 uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_RecurrencyKindMapping,
										  OCPP_RECURRENCY_KIND_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseChargePointErrorCode(char* string, uint32_t stringLength,
											   OcppChargePointErrorCode* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ChargePointErrorCodeMapping,
									   OCPP_CP_ERR_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargePointErrorCode(OcppChargePointErrorCode type, char* string,
											   uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ChargePointErrorCodeMapping,
										  OCPP_CP_ERR_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseSampledValueContext(char* string, uint32_t stringLength,
											  OcppSampledValueContext* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_SampledValueContextMapping,
									   OCPP_SAMPLED_VALUE_CONTEXT_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValueContext(OcppSampledValueContext type, char* string,
											  uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_SampledValueContextMapping,
										  OCPP_SAMPLED_VALUE_CONTEXT_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseSampledValueFormat(char* string, uint32_t stringLength,
											 OcppSampledValueFormat* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_SampledValueFormatMapping,
									   OCPP_SAMPLED_VALUE_FORMAT_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValueFormat(OcppSampledValueFormat type, char* string,
											 uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_SampledValueFormatMapping,
										  OCPP_SAMPLED_VALUE_FORMAT_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseSampledValueMeasurand(char* string, uint32_t stringLength,
												OcppSampledValueMeasurand* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_SampledValueMeasurandMapping,
									   OCPP_SAMPLED_VALUE_MEASURAND_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValueMeasurand(OcppSampledValueMeasurand type, char* string,
												uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_SampledValueMeasurandMapping,
										  OCPP_SAMPLED_VALUE_MEASURAND_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseSampledValuePhase(char* string, uint32_t stringLength,
											OcppSampledValuePhase* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_SampledValuePhaseMapping,
									   OCPP_SAMPLED_VALUE_PHASE_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValuePhase(OcppSampledValuePhase type, char* string,
											uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_SampledValuePhaseMapping,
										  OCPP_SAMPLED_VALUE_PHASE_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseSampledValueLocation(char* string, uint32_t stringLength,
											   OcppSampledValueLocation* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_SampledValueLocationMapping,
									   OCPP_SAMPLED_VALUE_LOC_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValueLocation(OcppSampledValueLocation type, char* string,
											   uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_SampledValueLocationMapping,
										  OCPP_SAMPLED_VALUE_LOC_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseSampledValueUnit(char* string, uint32_t stringLength,
										   OcppSampledValueUnit* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_SampledValueUnitMapping,
									   OCPP_SAMPLED_VALUE_UNIT_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValueUnit(OcppSampledValueUnit type, char* string,
										   uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_SampledValueUnitMapping,
										  OCPP_SAMPLED_VALUE_UNIT_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseUpdateType(char* string, uint32_t stringLength, OcppUpdateType* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_UpdateTypeMapping,
									   OCPP_UPDATE_TYPE_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildUpdateType(OcppUpdateType type, char* string, uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_UpdateTypeMapping, OCPP_UPDATE_TYPE_MAX,
										  string, stringLength);
}

OcppRetType OcppJson_ParseAvailabilityType(char* string, uint32_t stringLength,
										   OcppAvailabilityType* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_AvailabilityTypeMapping,
									   OCPP_AVAILABILITY_TYPE_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildAvailabilityType(OcppAvailabilityType type, char* string,
										   uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_AvailabilityTypeMapping,
										  OCPP_AVAILABILITY_TYPE_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseDiagnosticsStatus(char* string, uint32_t stringLength,
											OcppDiagnosticsStatus* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_DiagnosticsStatusMapping,
									   OCPP_DIAGNOSTIC_STATUS_MAX,
									   (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildDiagnosticsStatus(OcppDiagnosticsStatus type, char* string,
											uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_DiagnosticsStatusMapping,
										  OCPP_DIAGNOSTIC_STATUS_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseFirmwareStatus(char* string, uint32_t stringLength,
										 OcppFirmwareStatus* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_FirmwareStatusMapping,
									   OCPP_FIRMWARE_STATUS_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildFirmwareStatus(OcppFirmwareStatus type, char* string,
										 uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_FirmwareStatusMapping,
										  OCPP_FIRMWARE_STATUS_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseReason(char* string, uint32_t stringLength, OcppReason* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ReasonMapping,
									   OCPP_REASON_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildReason(OcppReason type, char* string, uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ReasonMapping, OCPP_REASON_MAX, string,
										  stringLength);
}
OcppRetType OcppJson_ParseActionId(char* string, uint32_t stringLength, OcppActionId* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ActionIdMapping,
									   OCPP_ACTION_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildActionId(OcppActionId type, char* string, uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ActionIdMapping, OCPP_ACTION_MAX, string,
										  stringLength);
}
OcppRetType OcppJson_ParseErrorCode(char* string, uint32_t stringLength, OcppErrorCode* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ErrorCodeMapping,
									   OCPP_ERROR_CODE_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildErrorCode(OcppErrorCode type, char* string, uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ErrorCodeMapping, OCPP_ERROR_CODE_MAX,
										  string, stringLength);
}

OcppRetType OcppJson_ParseResetType(char* string, uint32_t stringLength, OcppResetType* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_ResetTypeMapping,
									   OCPP_RESET_TYPE_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildResetType(OcppResetType type, char* string, uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_ResetTypeMapping, OCPP_TRIGGER_MESSAGE_MAX,
										  string, stringLength);
}
OcppRetType OcppJson_ParseMessageTrigger(char* string, uint32_t stringLength,
										 OcppMessageTrigger* type)
{
	if(OcppJson_FindGenericDataInTable(string, stringLength, OcppJson_MessageTriggerMapping,
									   OCPP_TRIGGER_MESSAGE_MAX, (uint32_t*)type) == OCPP_NOT_FOUND)
	{
		return OCPP_INVALID;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildMessageTrigger(OcppMessageTrigger type, char* string,
										 uint32_t* stringLength)
{
	return OcppJson_GetGenericDataInTable(type, OcppJson_MessageTriggerMapping,
										  OCPP_TRIGGER_MESSAGE_MAX, string, stringLength);
}
OcppRetType OcppJson_ParseCallMessage(char* string, jsmntok_t* token, uint32_t* tokenLen,
									  OcppCallMessage* message)
{
	OcppActionId actionId = message->action;

	return OcppJson_PayloadOperationMapping[actionId][OCPP_PAYLOAD_TYPE_REQ].parseFnc(
		string, token, tokenLen, &message->payload);
}
OcppRetType OcppJson_BuildCallMessage(OcppCallMessage* message, char* string,
									  uint32_t* stringLength)
{
	OcppActionId actionId = message->action;
	return OcppJson_PayloadOperationMapping[actionId][OCPP_PAYLOAD_TYPE_REQ].buildFnc(
		&message->payload, string, stringLength);
}
OcppRetType OcppJson_ParseCallResultMessage(char* string, jsmntok_t* token, uint32_t* tokenLen,
											OcppCallResultMessage* message)
{
	OcppActionId actionId = message->action;

	return OcppJson_PayloadOperationMapping[actionId][OCPP_PAYLOAD_TYPE_RES].parseFnc(
		string, token, tokenLen, &message->payload);
}
OcppRetType OcppJson_BuildCallResultMessage(OcppCallResultMessage* message, char* string,
											uint32_t* stringLength)
{
	OcppActionId actionId = message->action;

	return OcppJson_PayloadOperationMapping[actionId][OCPP_PAYLOAD_TYPE_RES].buildFnc(
		&message->payload, string, stringLength);
}
OcppRetType OcppJson_ParseCallErrorMessage(char* string, jsmntok_t* token, uint32_t* tokenLen,
										   OcppCallErrorMessage* message)
{
}
OcppRetType OcppJson_BuildCallErrorMessage(OcppCallErrorMessage* message, char* string,
										   uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	char errorCodeStr[OCPP_ERROR_CODE_MAX_LENGTH];

	(void)OcppJson_BuildErrorCode(message->errorCode, errorCodeStr, &buildStrLength);

	ret = sprintf(string, "\"%s\",\"%s\",\"%s\"", errorCodeStr, message->errorDescription,
				  message->errorDetails);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}

OcppRetType OcppJson_ParseDateTime(char* string, uint32_t stringLength, OcppDateTime* dateTime)
{
	if(stringLength < 20)
	{
		return OCPP_NOT_OK;
	}
	if(sscanf(string, "%d-%d-%dT%d:%d:%dZ", &dateTime->year, &dateTime->month, &dateTime->day,
			  &dateTime->hour, &dateTime->minute, &dateTime->second) != 6)
	{
		return OCPP_NOT_OK;
	}
	return OCPP_OK;
}
OcppRetType OcppJson_BuildDateTime(OcppDateTime* dateTime, char* string, uint32_t* stringLength)
{
	int ret = sprintf(string, "%02d-%02d-%02dT%02d:%02d:%02dZ", dateTime->year, dateTime->month,
					  dateTime->day, dateTime->hour, dateTime->minute, dateTime->second);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}

OcppRetType OcppJson_ParseIdTagInfo(char* string, jsmntok_t* token, uint32_t* tokenLen,
									OcppIdTagInfo* idTagInfo)
{
	size_t i;
	if(*tokenLen < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 3, got %d", *tokenLen));
		return OCPP_NOT_OK;
	}

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "expiryDate") == 0)
		{
			OcppJson_ParseDateTime(string + token[i + 1].start,
								   token[i + 1].end - token[i + 1].start, &idTagInfo->expiryDate);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "parentIdTag") == 0)
		{
			strncpy(idTagInfo->parentIdTag, string + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "status") == 0)
		{
			OcppJson_ParseMessageStatus(string + token[i + 1].start,
										token[i + 1].end - token[i + 1].start, &idTagInfo->status);
			i++;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildIdTagInfo(OcppIdTagInfo* idTagInfo, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	char dateTimeStr[OCPP_DATE_TIME_MAX_LENGTH];
	char messageStatusStr[OCPP_MESSAGE_STATUS_MAX_LENGTH];

	(void)OcppJson_BuildDateTime(&idTagInfo->expiryDate, dateTimeStr, &buildStrLength);
	(void)OcppJson_BuildMessageStatus(idTagInfo->status, messageStatusStr, &buildStrLength);

	ret = sprintf(string, "{\"expiryDate\": \"%s\",\"parentIdTag\": \"%s\",\"status\": \"%s\"}",
				  dateTimeStr, idTagInfo->parentIdTag, messageStatusStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseAuthorizationData(char* string, jsmntok_t* token, uint32_t* tokenLen,
											OcppAuthorizationData* authorizationData)
{
	size_t i;
	uint32_t tokenSize;

	if(*tokenLen < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 3, got %d", *tokenLen));
		return OCPP_NOT_OK;
	}

	char idTagInfoStr[OCPP_ID_TAG_INFO_MAX_LENGTH];

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "idTag") == 0)
		{
			strncpy(authorizationData->idTag, string + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "idTagInfo") == 0)
		{
			if(token[i + 1].type != JSMN_OBJECT)
			{
				Ocpp_LogError(("[OCPP] idTagInfo is not Object\r\n"));
				return OCPP_NOT_OK;
			}
			tokenSize = *tokenLen - i - 1;
			OcppJson_ParseIdTagInfo(string, &token[i + 1], &tokenSize,
									&authorizationData->idTagInfo);
			i += tokenSize;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildAuthorizationData(OcppAuthorizationData* authorizationData, char* string,
											uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	char idTagInfoStr[OCPP_ID_TAG_INFO_MAX_LENGTH];

	(void)OcppJson_BuildIdTagInfo(&authorizationData->idTagInfo, idTagInfoStr, &buildStrLength);

	ret = sprintf(string, "{\"idTag\": \"%s\",\"idTagInfo\": %s}", authorizationData->idTag,
				  idTagInfoStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseKeyValue(char* string, jsmntok_t* token, uint32_t* tokenLen,
								   OcppKeyValue* keyValue)
{
	size_t i;
	uint32_t tokenSize;

	if(*tokenLen < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 3, got %d", *tokenLen));
		return OCPP_NOT_OK;
	}

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "key") == 0)
		{
			strncpy(keyValue->key, string + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "readonly") == 0)
		{
			OcppJson_ToBoolean(string, &token[i + 1], &keyValue->readonly);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "value") == 0)
		{
			strncpy(keyValue->value, string + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildKeyValue(OcppKeyValue* keyValue, char* string, uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;

	ret = sprintf(string, "{\"key\": \"%s\",\"readonly\": %s,\"value\": \"%s\"}", keyValue->key,
				  OcppJson_ToBooleanStr(keyValue->readonly), keyValue->value);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseSampledValue(char* string, jsmntok_t* token, uint32_t* tokenLen,
									   OcppSampledValue* sampledValue)
{
	size_t i;
	if(*tokenLen < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 1, got %d", *tokenLen));
		return OCPP_NOT_OK;
	}

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "value") == 0)
		{
			strncpy(sampledValue->value, string + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "context") == 0)
		{
			OcppJson_ParseSampledValueContext(string + token[i + 1].start,
											  token[i + 1].end - token[i + 1].start,
											  &sampledValue->context);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "format") == 0)
		{
			OcppJson_ParseSampledValueFormat(string + token[i + 1].start,
											 token[i + 1].end - token[i + 1].start,
											 &sampledValue->format);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "measurand") == 0)
		{
			OcppJson_ParseSampledValueMeasurand(string + token[i + 1].start,
												token[i + 1].end - token[i + 1].start,
												&sampledValue->measurand);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "phase") == 0)
		{
			OcppJson_ParseSampledValuePhase(string + token[i + 1].start,
											token[i + 1].end - token[i + 1].start,
											&sampledValue->phase);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "location") == 0)
		{
			OcppJson_ParseSampledValueLocation(string + token[i + 1].start,
											   token[i + 1].end - token[i + 1].start,
											   &sampledValue->location);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "unit") == 0)
		{
			OcppJson_ParseSampledValueUnit(string + token[i + 1].start,
										   token[i + 1].end - token[i + 1].start,
										   &sampledValue->unit);
			i++;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildSampledValue(OcppSampledValue* sampledValue, char* string,
									   uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	char contextStr[OCPP_METER_VALUE_SAMPLED_VALUE_CONTEXT_MAX_LENGTH];
	char formatStr[OCPP_METER_VALUE_SAMPLED_VALUE_FORMAT_MAX_LENGTH];
	char measurandStr[OCPP_METER_VALUE_SAMPLED_VALUE_MEASURAND_MAX_LENGTH];
	char phaseStr[OCPP_METER_VALUE_SAMPLED_VALUE_PHASE_MAX_LENGTH];
	char locationStr[OCPP_METER_VALUE_SAMPLED_VALUE_LOCATION_MAX_LENGTH];
	char unitStr[OCPP_METER_VALUE_SAMPLED_VALUE_UNIT_MAX_LENGTH];

	memset(contextStr, 0, sizeof(contextStr));
	memset(formatStr, 0, sizeof(formatStr));
	memset(measurandStr, 0, sizeof(measurandStr));
	memset(phaseStr, 0, sizeof(phaseStr));
	memset(locationStr, 0, sizeof(locationStr));
	memset(unitStr, 0, sizeof(unitStr));

	(void)OcppJson_BuildSampledValueContext(sampledValue->context, contextStr, &buildStrLength);
	(void)OcppJson_BuildSampledValueFormat(sampledValue->format, formatStr, &buildStrLength);
	(void)OcppJson_BuildSampledValueMeasurand(sampledValue->measurand, measurandStr,
											  &buildStrLength);
	(void)OcppJson_BuildSampledValuePhase(sampledValue->phase, phaseStr, &buildStrLength);
	(void)OcppJson_BuildSampledValueLocation(sampledValue->location, locationStr, &buildStrLength);
	(void)OcppJson_BuildSampledValueUnit(sampledValue->unit, unitStr, &buildStrLength);

	ret = sprintf(string,
				  "{\"value\": \"%s\",\"context\": \"%s\",\"format\": \"%s\",\"measurand\": "
				  "\"%s\",\"phase\": \"%s\",\"location\": \"%s\",\"unit\": \"%s\"}",
				  sampledValue->value, contextStr, formatStr, measurandStr, phaseStr, locationStr,
				  unitStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseMeterValue(char* string, jsmntok_t* token, uint32_t* tokenLen,
									 OcppMeterValue* meterValue)
{
	size_t i;
	uint32_t tokenSize;
	uint32_t sampledValueTokenIdx;

	if(*tokenLen < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 1, got %d", tokenLen));
		return OCPP_NOT_OK;
	}

	char timestampStr[OCPP_DATE_TIME_MAX_LENGTH];
	jsmntok_t* sampledValueTokenList[OCPP_METER_VALUE_SAMPLED_VALUE_ARRAY_MAX_LENGTH];
	uint32_t sampledValueTokenListIdx = 0;

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "timestamp") == 0)
		{
			strncpy(timestampStr, string + token[i + 1].start,
					token[i + 1].end - token[i + 1].start);
			OcppJson_ParseDateTime(timestampStr, strlen(timestampStr), &meterValue->timestamp);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "sampledValue") == 0)
		{
			if(token[i + 1].type != JSMN_ARRAY)
			{
				Ocpp_LogError(("[OCPP] sampledValue should be ARRAY\r\n"));
				return OCPP_NOT_OK;
			}
			meterValue->noSampledValue = token[i + 1].size;

			sampledValueTokenIdx = i + 2;

			for(size_t sampledIdx = 0; sampledIdx < meterValue->noSampledValue; sampledIdx++)
			{
				tokenSize = *tokenLen - sampledValueTokenIdx;

				OcppJson_ParseSampledValue(string, &token[sampledValueTokenIdx], &tokenSize,
										   &meterValue->sampledValue[sampledIdx]);
				sampledValueTokenIdx += tokenSize;
			}
			i = sampledValueTokenIdx - 1;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildMeterValue(OcppMeterValue* meterValue, char* string,
									 uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;

	char timestampStr[OCPP_DATE_TIME_MAX_LENGTH];
	char sampledValueStr[OCPP_METER_VALUE_SAMPLED_VALUE_MAX_LENGTH];
	char sampledValueArrStr[OCPP_METER_VALUE_SAMPLED_VALUE_ARRAY_MAX_LENGTH *
							OCPP_METER_VALUE_SAMPLED_VALUE_MAX_LENGTH];

	memset(timestampStr, 0, sizeof(timestampStr));
	memset(sampledValueStr, 0, sizeof(sampledValueStr));
	memset(sampledValueArrStr, 0, sizeof(sampledValueArrStr));

	(void)OcppJson_BuildDateTime(&meterValue->timestamp, timestampStr, &buildStrLength);

	memset(sampledValueArrStr, 0, sizeof(sampledValueArrStr));
	strcat(sampledValueArrStr, "[");

	for(size_t i = 0; i < meterValue->noSampledValue; i++)
	{
		(void)OcppJson_BuildSampledValue(&meterValue->sampledValue[i], sampledValueStr,
										 &buildStrLength);
		strncat(sampledValueArrStr, sampledValueStr, buildStrLength);
		if(i != (meterValue->noSampledValue - 1))
		{
			strcat(sampledValueArrStr, ",");
		}
	}
	strcat(sampledValueArrStr, "]");

	ret = sprintf(string, "{\"timestamp\": \"%s\", \"sampledValue\": %s}", timestampStr,
				  sampledValueArrStr);

	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}

	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseChargingSchedulePeriod(char* string, jsmntok_t* token, uint32_t* tokenLen,
												 OcppChargingSchedulePeriod* chargingSchedulePeriod)
{
	size_t i;
	if(*tokenLen < 3)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 3, got %d", tokenLen));
		return OCPP_NOT_OK;
	}

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "startPeriod") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingSchedulePeriod->startPeriod);

			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "limit") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingSchedulePeriod->limit);

			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "numberPhases") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingSchedulePeriod->numberPhases);
			i++;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargingSchedulePeriod(OcppChargingSchedulePeriod* chargingSchedulePeriod,
												 char* string, uint32_t* stringLength)
{
	int ret;

	ret = sprintf(string, "{\"startPeriod\": %d,\"limit\": %d,\"numberPhases\": %d}",
				  chargingSchedulePeriod->startPeriod, chargingSchedulePeriod->limit,
				  chargingSchedulePeriod->numberPhases);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseChargingSchedule(char* string, jsmntok_t* token, uint32_t* tokenLen,
										   OcppChargingSchedule* chargingSchedule)
{
	size_t i;
	uint32_t tokenSize;
	uint32_t chSchPeriodTokenIdx;

	if(*tokenLen < 1)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected 1, got %d", tokenLen));
		return OCPP_NOT_OK;
	}

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "duration") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingSchedule->duration);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "startSchedule") == 0)
		{
			OcppJson_ParseDateTime(string + token[i + 1].start,
								   token[i + 1].end - token[i + 1].start,
								   &chargingSchedule->startSchedule);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "chargingRateUnit") == 0)
		{
			OcppJson_ParseChargingRateUnitType(string + token[i + 1].start,
											   token[i + 1].end - token[i + 1].start,
											   &chargingSchedule->chargingRateUnit);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "chargingSchedulePeriod") == 0)
		{
			if(token[i + 1].type != JSMN_ARRAY)
			{
				Ocpp_LogError(("[OCPP] chargingSchedulePeriod should be ARRAY\r\n"));
				return OCPP_NOT_OK;
			}
			chargingSchedule->noChargingSchedulePeriod = token[i + 1].size;

			chSchPeriodTokenIdx = i + 2;

			for(size_t chSchPeriodIdx = 0;
				chSchPeriodIdx < chargingSchedule->noChargingSchedulePeriod; chSchPeriodIdx++)
			{
				tokenSize = *tokenLen - chSchPeriodTokenIdx;

				OcppJson_ParseChargingSchedulePeriod(
					string, &token[chSchPeriodTokenIdx], &tokenSize,
					&chargingSchedule->chargingSchedulePeriod[chSchPeriodIdx]);
				chSchPeriodTokenIdx += tokenSize;
			}
			i = chSchPeriodTokenIdx - 1;
		}
		else if(OcppJson_Equal(string, &token[i], "minChargingRate") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingSchedule->minChargingRate);
			i++;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargingSchedule(OcppChargingSchedule* chargingSchedule, char* string,
										   uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	char startScheduleStr[OCPP_DATE_TIME_MAX_LENGTH];
	char chargingRateUnitStr[OCPP_CHARGING_RATE_UNIT_MAX_LENGTH];
	char chargingSchedulePeriodStr[OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX_LENGTH];
	char chargingSchedulePeriodArrStr[OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_ARR_MAX_LENGTH];

	memset(startScheduleStr, 0, sizeof(startScheduleStr));
	memset(chargingRateUnitStr, 0, sizeof(chargingRateUnitStr));
	memset(chargingSchedulePeriodStr, 0, sizeof(chargingSchedulePeriodStr));
	memset(chargingSchedulePeriodArrStr, 0, sizeof(chargingSchedulePeriodArrStr));

	(void)OcppJson_BuildDateTime(&chargingSchedule->startSchedule, startScheduleStr,
								 &buildStrLength);
	(void)OcppJson_BuildChargingRateUnitType(chargingSchedule->chargingRateUnit,
											 chargingRateUnitStr, &buildStrLength);

	strcat(chargingSchedulePeriodArrStr, "[");
	for(size_t i = 0; i < chargingSchedule->noChargingSchedulePeriod; i++)
	{
		OcppJson_BuildChargingSchedulePeriod(&chargingSchedule->chargingSchedulePeriod[i],
											 chargingSchedulePeriodStr, &buildStrLength);
		strncat(chargingSchedulePeriodArrStr, chargingSchedulePeriodStr, buildStrLength);
		if(i != (chargingSchedule->noChargingSchedulePeriod - 1))
		{
			strcat(chargingSchedulePeriodArrStr, ",");
		}
	}
	strcat(chargingSchedulePeriodArrStr, "]");

	ret = sprintf(string,
				  "{\"duration\": %d,\"startSchedule\": \"%s\",\"chargingRateUnit\": "
				  "\"%s\",\"chargingSchedulePeriod\": "
				  "%s,\"minChargingRate\": %d}",
				  chargingSchedule->duration, startScheduleStr, chargingRateUnitStr,
				  chargingSchedulePeriodArrStr, chargingSchedule->minChargingRate);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
OcppRetType OcppJson_ParseChargingProfile(char* string, jsmntok_t* token, uint32_t* tokenLen,
										  OcppChargingProfile* chargingProfile)
{
	size_t i;
	uint32_t tokenSize;
	if(*tokenLen < 5)
	{
		Ocpp_LogError(("[OCPP] Invalid token size, expected , got %d", tokenLen));
		return OCPP_NOT_OK;
	}

	for(i = 0; (i < *tokenLen) && (token[i].end <= token[0].end); i++)
	{
		if(OcppJson_Equal(string, &token[i], "chargingProfileId") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingProfile->chargingProfileId);

			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "transactionId") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingProfile->transactionId);

			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "stackLevel") == 0)
		{
			OcppJson_ToNumber(string, &token[i + 1], &chargingProfile->stackLevel);

			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "validFrom") == 0)
		{
			OcppJson_ParseDateTime(string + token[i + 1].start,
								   token[i + 1].end - token[i + 1].start,
								   &chargingProfile->validFrom);

			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "validTo") == 0)
		{
			OcppJson_ParseDateTime(string + token[i + 1].start,
								   token[i + 1].end - token[i + 1].start,
								   &chargingProfile->validTo);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "chargingProfilePurpose") == 0)
		{
			OcppJson_ParseChargingProfilePurpose(string + token[i + 1].start,
												 token[i + 1].end - token[i + 1].start,
												 &chargingProfile->chargingProfilePurpose);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "chargingProfileKind") == 0)
		{
			OcppJson_ParseChargingProfileKind(string + token[i + 1].start,
											  token[i + 1].end - token[i + 1].start,
											  &chargingProfile->chargingProfileKind);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "recurrencyKind") == 0)
		{
			OcppJson_ParseRecurrencyKind(string + token[i + 1].start,
										 token[i + 1].end - token[i + 1].start,
										 &chargingProfile->recurrencyKind);
			i++;
		}
		else if(OcppJson_Equal(string, &token[i], "chargingSchedule") == 0)
		{
			tokenSize = *tokenLen - i - 1;
			OcppJson_ParseChargingSchedule(string, &token[i + 1], &tokenSize,
										   &chargingProfile->chargingSchedule);
			i += tokenSize;
		}
	}
	*tokenLen = i;
	return OCPP_OK;
}
OcppRetType OcppJson_BuildChargingProfile(OcppChargingProfile* chargingProfile, char* string,
										  uint32_t* stringLength)
{
	int ret;
	uint32_t buildStrLength;
	char validFromStr[OCPP_DATE_TIME_MAX_LENGTH];
	char validToStr[OCPP_DATE_TIME_MAX_LENGTH];
	char chargingProfilePurposeStr[OCPP_CHARGING_PROFILE_PURPOSE_MAX_LENGTH];
	char chargingProfileKindStr[OCPP_CHARGING_PROFILE_KIND_MAX_LENGTH];
	char recurrencyKindStr[OCPP_RECURRENCY_KIND_MAX_LENGTH];
	char chargeScheduleStr[OCPP_CHARGE_SCHEDULE_CHARGING_SCH_MAX_LENGTH];

	memset(validFromStr, 0, sizeof(validFromStr));
	memset(validToStr, 0, sizeof(validToStr));
	memset(chargingProfilePurposeStr, 0, sizeof(chargingProfilePurposeStr));
	memset(chargingProfileKindStr, 0, sizeof(chargingProfileKindStr));
	memset(recurrencyKindStr, 0, sizeof(recurrencyKindStr));
	memset(chargeScheduleStr, 0, sizeof(chargeScheduleStr));

	(void)OcppJson_BuildDateTime(&chargingProfile->validFrom, validFromStr, &buildStrLength);
	(void)OcppJson_BuildDateTime(&chargingProfile->validTo, validToStr, &buildStrLength);

	(void)OcppJson_BuildChargingProfilePurpose(chargingProfile->chargingProfilePurpose,
											   chargingProfilePurposeStr, &buildStrLength);
	(void)OcppJson_BuildChargingProfileKind(chargingProfile->chargingProfileKind,
											chargingProfileKindStr, &buildStrLength);
	(void)OcppJson_BuildRecurrencyKind(chargingProfile->recurrencyKind, recurrencyKindStr,
									   &buildStrLength);
	(void)OcppJson_BuildChargingSchedule(&chargingProfile->chargingSchedule, chargeScheduleStr,
										 &buildStrLength);

	ret = sprintf(
		string,
		"{\"chargingProfileId\": %d,\"transactionId\": %d,\"stackLevel\": %d,\"validFrom\": "
		"\"%s\",\"validTo\": \"%s\",\"chargingProfilePurpose\": \"%s\",\"chargingProfileKind\": "
		"\"%s\",\"recurrencyKind\": \"%s\",\"chargeSchedule\": %s}",
		chargingProfile->chargingProfileId, chargingProfile->transactionId,
		chargingProfile->stackLevel, validFromStr, validToStr, chargingProfilePurposeStr,
		chargingProfileKindStr, recurrencyKindStr, chargeScheduleStr);
	if(ret < 0)
	{
		return OCPP_NOT_OK;
	}
	*stringLength = ret;
	return OCPP_OK;
}
bool OcppJson_Equal(const char* json, jsmntok_t* tok, const char* s)
{
	if(tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
	   strncmp(json + tok->start, s, tok->end - tok->start) == 0)
	{
		return 0;
	}
	return -1;
}
OcppRetType OcppJson_ToNumber(const char* json, jsmntok_t* tok, int* number)
{
	char* messageTypeIdStr = json + tok->start;
	uint32_t messageTypeIdStrLen = (uint32_t)(tok->start) - (uint32_t)(tok->end);
	*number = atoi(messageTypeIdStr);
	return OCPP_OK;
}
OcppRetType OcppJson_ToString(const char* json, jsmntok_t* tok, char* string)
{
	strncpy(string, json + tok->start, tok->end - tok->start);
	return OCPP_OK;
}
OcppRetType OcppJson_ToBoolean(const char* json, jsmntok_t* tok, bool* boolean)
{
	if(strncmp(json + tok->start, "false", tok->end - tok->start) == 0 ||
	   strncmp(json + tok->start, "0", tok->end - tok->start) == 0)
	{
		*boolean = false;
		return OCPP_OK;
	}
	if(strncmp(json + tok->start, "true", tok->end - tok->start) == 0 ||
	   strncmp(json + tok->start, "1", tok->end - tok->start) == 0)
	{
		*boolean = true;
		return OCPP_OK;
	}
	return OCPP_NOT_OK;
}
char* OcppJson_ToBooleanStr(bool boolean)
{
	return (boolean ? "true" : "false");
}
static OcppRetType OcppJson_FindGenericDataInTable(char* string, uint32_t stringLength,
												   const char** mappingTable,
												   uint32_t mappingTableLength,
												   uint32_t* foundIndex)
{
	OcppRetType retType = OCPP_NOT_FOUND;
	for(uint32_t idx = 0; idx < mappingTableLength; idx++)
	{
		if(0 == strncmp(mappingTable[idx], string, stringLength))
		{
			*foundIndex = idx;
			retType = OCPP_OK;
			break;
		}
	}
	return retType;
}

static OcppRetType OcppJson_GetGenericDataInTable(uint32_t index, const char** mappingTable,
												  uint32_t mappingTableLength, char* string,
												  uint32_t* stringLength)
{
	if(index >= mappingTableLength)
	{
		return OCPP_INVALID;
	}
	*stringLength = strcpy(string, mappingTable[index]);
	return OCPP_OK;
}
