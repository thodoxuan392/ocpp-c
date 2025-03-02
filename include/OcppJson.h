#ifndef __OCPP_JSON_H
#define __OCPP_JSON_H

#include <OcppConfig.h>
#include <OcppTypes.h>
#include <OcppMessage.h>

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

OcppRetType OcppJson_ParseCallMessage(char* string, jsmntok_t* token, uint32_t* tokenLen,
									  OcppCallMessage* message);
OcppRetType OcppJson_BuildCallMessage(OcppCallMessage* message, char* string,
									  uint32_t* stringLength);
OcppRetType OcppJson_ParseCallResultMessage(char* string, jsmntok_t* token, uint32_t* tokenLen,
											OcppCallResultMessage* message);
OcppRetType OcppJson_BuildCallResultMessage(OcppCallResultMessage* message, char* string,
											uint32_t* stringLength);
OcppRetType OcppJson_ParseCallErrorMessage(char* string, jsmntok_t* token, uint32_t* tokenLen,
										   OcppCallErrorMessage* message);
OcppRetType OcppJson_BuildCallErrorMessage(OcppCallErrorMessage* message, char* string,
										   uint32_t* stringLength);
/***
 * For Enum Type
 */
OcppRetType OcppJson_ParseMessageStatus(char* string, uint32_t stringLength,
										OcppMessageStatus* type);
OcppRetType OcppJson_BuildMessageStatus(OcppMessageStatus type, char* string,
										uint32_t* stringLength);
OcppRetType OcppJson_ParseChargingRateUnitType(char* string, uint32_t stringLength,
											   OcppChargingRateUnitType* type);
OcppRetType OcppJson_BuildChargingRateUnitType(OcppChargingRateUnitType type, char* string,
											   uint32_t* stringLength);
OcppRetType OcppJson_ParseChargingProfilePurpose(char* string, uint32_t stringLength,
												 OcppChargingProfilePurpose* type);
OcppRetType OcppJson_BuildChargingProfilePurpose(OcppChargingProfilePurpose type, char* string,
												 uint32_t* stringLength);
OcppRetType OcppJson_ParseChargingProfileKind(char* string, uint32_t stringLength,
											  OcppChargingProfileKind* type);
OcppRetType OcppJson_BuildChargingProfileKind(OcppChargingProfileKind type, char* string,
											  uint32_t* stringLength);
OcppRetType OcppJson_ParseChargingProfileKind(char* string, uint32_t stringLength,
											  OcppChargingProfileKind* type);
OcppRetType OcppJson_BuildChargingProfileKind(OcppChargingProfileKind type, char* string,
											  uint32_t* stringLength);
OcppRetType OcppJson_ParseRecurrencyKind(char* string, uint32_t stringLength,
										 OcppRecurrencyKind* type);
OcppRetType OcppJson_BuildRecurrencyKind(OcppRecurrencyKind type, char* string,
										 uint32_t* stringLength);
OcppRetType OcppJson_ParseChargePointErrorCode(char* string, uint32_t stringLength,
											   OcppChargePointErrorCode* type);
OcppRetType OcppJson_BuildChargePointErrorCode(OcppChargePointErrorCode type, char* string,
											   uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValueContext(char* string, uint32_t stringLength,
											  OcppSampledValueContext* type);
OcppRetType OcppJson_BuildSampledValueContext(OcppSampledValueContext type, char* string,
											  uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValueFormat(char* string, uint32_t stringLength,
											 OcppSampledValueFormat* type);
OcppRetType OcppJson_BuildSampledValueFormat(OcppSampledValueFormat type, char* string,
											 uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValueMeasurand(char* string, uint32_t stringLength,
												OcppSampledValueMeasurand* type);
OcppRetType OcppJson_BuildSampledValueMeasurand(OcppSampledValueMeasurand type, char* string,
												uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValuePhase(char* string, uint32_t stringLength,
											OcppSampledValuePhase* type);
OcppRetType OcppJson_BuildSampledValuePhase(OcppSampledValuePhase type, char* string,
											uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValueLocation(char* string, uint32_t stringLength,
											   OcppSampledValueLocation* type);
OcppRetType OcppJson_BuildSampledValueLocation(OcppSampledValueLocation type, char* string,
											   uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValueUnit(char* string, uint32_t stringLength,
										   OcppSampledValueUnit* type);
OcppRetType OcppJson_BuildSampledValueUnit(OcppSampledValueUnit type, char* string,
										   uint32_t* stringLength);
OcppRetType OcppJson_ParseUpdateType(char* string, uint32_t stringLength, OcppUpdateType* type);
OcppRetType OcppJson_BuildUpdateType(OcppUpdateType type, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseAvailabilityType(char* string, uint32_t stringLength,
										   OcppAvailabilityType* type);
OcppRetType OcppJson_BuildAvailabilityType(OcppAvailabilityType type, char* string,
										   uint32_t* stringLength);
OcppRetType OcppJson_ParseDiagnosticsStatus(char* string, uint32_t stringLength,
											OcppDiagnosticsStatus* type);
OcppRetType OcppJson_BuildDiagnosticsStatus(OcppDiagnosticsStatus type, char* string,
											uint32_t* stringLength);
OcppRetType OcppJson_ParseFirmwareStatus(char* string, uint32_t stringLength,
										 OcppFirmwareStatus* type);
OcppRetType OcppJson_BuildFirmwareStatus(OcppFirmwareStatus type, char* string,
										 uint32_t* stringLength);
OcppRetType OcppJson_ParseReason(char* string, uint32_t stringLength, OcppReason* type);
OcppRetType OcppJson_BuildReason(OcppReason type, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseActionId(char* string, uint32_t stringLength, OcppActionId* type);
OcppRetType OcppJson_BuildActionId(OcppActionId type, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseErrorCode(char* string, uint32_t stringLength, OcppErrorCode* type);
OcppRetType OcppJson_BuildErrorCode(OcppErrorCode type, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseResetType(char* string, uint32_t stringLength, OcppResetType* type);
OcppRetType OcppJson_BuildResetType(OcppResetType type, char* string, uint32_t* stringLength);

OcppRetType OcppJson_ParseMessageTrigger(char* string, uint32_t stringLength,
										 OcppMessageTrigger* type);
OcppRetType OcppJson_BuildMessageTrigger(OcppMessageTrigger type, char* string,
										 uint32_t* stringLength);

OcppRetType OcppJson_ParseDateTime(char* string, uint32_t stringLength, OcppDateTime* dateTime);
OcppRetType OcppJson_BuildDateTime(OcppDateTime* dateTime, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseIdTagInfo(char* string, jsmntok_t* token, uint32_t* tokenLen,
									OcppIdTagInfo* idTagInfo);
OcppRetType OcppJson_BuildIdTagInfo(OcppIdTagInfo* idTagInfo, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseAuthorizationData(char* string, jsmntok_t* token, uint32_t* tokenLen,
											OcppAuthorizationData* authorizationData);
OcppRetType OcppJson_BuildAuthorizationData(OcppAuthorizationData* authorizationData, char* string,
											uint32_t* stringLength);
OcppRetType OcppJson_ParseKeyValue(char* string, jsmntok_t* token, uint32_t* tokenLen,
								   OcppKeyValue* keyValue);
OcppRetType OcppJson_BuildKeyValue(OcppKeyValue* keyValue, char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseSampledValue(char* string, jsmntok_t* token, uint32_t* tokenLen,
									   OcppSampledValue* sampledValue);
OcppRetType OcppJson_BuildSampledValue(OcppSampledValue* sampledValue, char* string,
									   uint32_t* stringLength);
OcppRetType OcppJson_ParseMeterValue(char* string, jsmntok_t* token, uint32_t* tokenLen,
									 OcppMeterValue* meterValue);
OcppRetType OcppJson_BuildMeterValue(OcppMeterValue* meterValue, char* string,
									 uint32_t* stringLength);
OcppRetType
	OcppJson_ParseChargingSchedulePeriod(char* string, jsmntok_t* token, uint32_t* tokenLen,
										 OcppChargingSchedulePeriod* chargingSchedulePeriod);
OcppRetType OcppJson_BuildChargingSchedulePeriod(OcppChargingSchedulePeriod* chargingSchedulePeriod,
												 char* string, uint32_t* stringLength);
OcppRetType OcppJson_ParseChargingSchedule(char* string, jsmntok_t* token, uint32_t* tokenLen,
										   OcppChargingSchedule* chargingSchedule);
OcppRetType OcppJson_BuildChargingSchedule(OcppChargingSchedule* chargingSchedule, char* string,
										   uint32_t* stringLength);
OcppRetType OcppJson_ParseChargingProfile(char* string, jsmntok_t* token, uint32_t* tokenLen,
										  OcppChargingProfile* chargingProfile);
OcppRetType OcppJson_BuildChargingProfile(OcppChargingProfile* chargingProfile, char* string,
										  uint32_t* stringLength);
bool OcppJson_Equal(const char* json, jsmntok_t* tok, const char* s);
OcppRetType OcppJson_ToNumber(const char* json, jsmntok_t* tok, int* number);
OcppRetType OcppJson_ToString(const char* json, jsmntok_t* tok, char* string);
OcppRetType OcppJson_ToBoolean(const char* json, jsmntok_t* tok, bool* boolean);
char* OcppJson_ToBooleanStr(bool boolean);

#endif // __OCPP_JSON_H