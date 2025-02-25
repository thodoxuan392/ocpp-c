/**
 * @file OcppPrvHeader.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __OCPP_PRIVATE_HEADER_H
#define __OCPP_PRIVATE_HEADER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <OcppConfig.h>

#define OCPP_OK 0x00
#define OCPP_NOT_OK 0x01

typedef uint8_t OcppRetType;

typedef enum
{
	OCPP_MESSAGE_STATUS_ACCEPTED,
	OCPP_MESSAGE_STATUS_REJECTED,
	OCPP_MESSAGE_STATUS_FAILED,
	OCPP_MESSAGE_STATUS_FAULTED,
	OCPP_MESSAGE_STATUS_OCCUPIED,
	OCPP_MESSAGE_STATUS_UNAVAILABLE,
	OCPP_MESSAGE_STATUS_BLOCKED,
	OCPP_MESSAGE_STATUS_PENDING,
	OCPP_MESSAGE_STATUS_EXPIRED,
	OCPP_MESSAGE_STATUS_INVALID,
	OCPP_MESSAGE_STATUS_CONCURRENT_TX,
	OCPP_MESSAGE_STATUS_SCHEDULED,
	OCPP_MESSAGE_STATUS_REBOOT_REQUIRED,
	OCPP_MESSAGE_STATUS_NOT_SUPPORTED,
	OCPP_MESSAGE_STATUS_UNKNOWN_MESSAGE_ID,
	OCPP_MESSAGE_STATUS_UNKNOWN_VENDOR_ID,
	OCPP_MESSAGE_STATUS_VERSION_MISMATCH,
	OCPP_MESSAGE_STATUS_NOT_IMPLEMENTED,
	OCPP_MESSAGE_STATUS_UNLOCKED,
	OCPP_MESSAGE_STATUS_UNLOCK_FAILED,
} OcppMessageStatus;

typedef enum
{
	OCPP_CHARGING_RATE_UNIT_A,
	OCPP_CHARGING_RATE_UNIT_B
} OcppChargingRateUnitType;

typedef enum
{
	OCPP_CHARGING_PROFILE_PP_CP_MAX,
	OCPP_CHARGING_PROFILE_PP_TX_DEFAULT_MAX,
	OCPP_CHARGING_PROFILE_PP_TX_PROFILE
} OcppChargingProfilePurpose;

typedef enum
{
	OCPP_CHARGING_PROFILE_KIND_ABSOLUTE,
	OCPP_CHARGING_PROFILE_KIND_RECURRING,
	OCPP_CHARGING_PROFILE_KIND_RELATIVE
} OcppChargingProfileKind;

typedef enum
{
	OCPP_RECURRENCY_KIND_DAILY,
	OCPP_RECURRENCY_KIND_WEEKLY
} OcppRecurrencyKind;

typedef enum
{
	OCPP_ERR_CONN_LOCK_FAIL,
	OCPP_ERR_EV_COMM,
	OCPP_ERR_GND_FAILURE,
	OCPP_ERR_HIGH_TEMPERATURE,
	OCPP_ERR_INTERNAL_ERROR,
	OCPP_ERR_LOCAL_LIST_CONFLICT,
	OCPP_ERR_NO_ERROR,
	OCPP_ERR_OTHER_ERROR,
	OCPP_ERR_OVER_CURR_FAL,
	OCPP_ERR_POWER_METER_FAIL,
	OCPP_ERR_POWER_SWI_FAIL,
	OCPP_ERR_READER_FAIL,
	OCPP_ERR_RESET_FAIL,
	OCPP_ERR_UNDER_VOLTAGE,
	OCPP_ERR_OVER_VOLTAGE,
	OCPP_ERR_WEAK_SIGNAL,
} OcppChargePointErrorCode;

typedef enum
{
	OCPP_SAMPLE_VALUE_CONTEXT_INTERRUPTION_BEGIN,
	OCPP_SAMPLE_VALUE_CONTEXT_INTERRUPTION_END,
	OCPP_SAMPLE_VALUE_CONTEXT_SAMPLE_CLOCK,
	OCPP_SAMPLE_VALUE_CONTEXT_SAMPLE_PERIOD,
	OCPP_SAMPLE_VALUE_CONTEXT_TRANSACTION_BEGIN,
	OCPP_SAMPLE_VALUE_CONTEXT_TRANSACTION_END,
	OCPP_SAMPLE_VALUE_CONTEXT_TRIGGER,
	OCPP_SAMPLE_VALUE_CONTEXT_OTHER
} OcppSampledValueContext;

typedef enum
{
	OCPP_SAMPLED_VALUE_FORMAT_RAW,
	OCPP_SAMPLED_VALUE_FORMAT_SIGNED_DATA
} OcppSampledValueFormat;

typedef enum
{
	OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_EX_REG,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_IM_REG,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_EX_REG,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_IM_REG,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_EX_INT,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_ACT_IM_INT,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_EX_INT,
	OCPP_SAMPLED_VALUE_MEASURAND_EN_REACT_IM_INT,
	OCPP_SAMPLED_VALUE_MEASURAND_PO_ACT_EX,
	OCPP_SAMPLED_VALUE_MEASURAND_PO_ACT_IM,
	OCPP_SAMPLED_VALUE_MEASURAND_PO_OFFER,
	OCPP_SAMPLED_VALUE_MEASURAND_PO_REACT_EX,
	OCPP_SAMPLED_VALUE_MEASURAND_PO_REACT_IM,
	OCPP_SAMPLED_VALUE_MEASURAND_CURR_IM,
	OCPP_SAMPLED_VALUE_MEASURAND_CURR_EX,
	OCPP_SAMPLED_VALUE_MEASURAND_CURR_OFFER,
	OCPP_SAMPLED_VALUE_MEASURAND_VOLT,
	OCPP_SAMPLED_VALUE_MEASURAND_FREQ,
	OCPP_SAMPLED_VALUE_MEASURAND_TEMPERATURE,
	OCPP_SAMPLED_VALUE_MEASURAND_SOC,
	OCPP_SAMPLED_VALUE_MEASURAND_RPM

} OcppSampledValueMeasurand;

typedef enum
{
	OCPP_SAMPLED_VALUE_PHASE_L1,
	OCPP_SAMPLED_VALUE_PHASE_L2,
	OCPP_SAMPLED_VALUE_PHASE_L3,
	OCPP_SAMPLED_VALUE_PHASE_N,
	OCPP_SAMPLED_VALUE_PHASE_L1_N,
	OCPP_SAMPLED_VALUE_PHASE_L2_N,
	OCPP_SAMPLED_VALUE_PHASE_L3_N,
	OCPP_SAMPLED_VALUE_PHASE_L1_L2,
	OCPP_SAMPLED_VALUE_PHASE_L2_L3,
	OCPP_SAMPLED_VALUE_PHASE_L3_L1

} OcppSampledValuePhase;

typedef enum
{
	OCPP_SAMPLED_VALUE_LOC_CABLE,
	OCPP_SAMPLED_VALUE_LOC_EV,
	OCPP_SAMPLED_VALUE_LOC_INLET,
	OCPP_SAMPLED_VALUE_LOC_OUTLET,
	OCPP_SAMPLED_VALUE_LOC_BODY,

} OcppSampledValueLocation;

typedef enum
{
	OCPP_SAMPLED_VALUE_UNIT_KW,
	OCPP_SAMPLED_VALUE_UNIT_KWH,
	OCPP_SAMPLED_VALUE_UNIT_VARH,
	OCPP_SAMPLED_VALUE_UNIT_KVARH,
	OCPP_SAMPLED_VALUE_UNIT_W,
	OCPP_SAMPLED_VALUE_UNIT_VA,
	OCPP_SAMPLED_VALUE_UNIT_KVA,
	OCPP_SAMPLED_VALUE_UNIT_VAR,
	OCPP_SAMPLED_VALUE_UNIT_KVAR,
	OCPP_SAMPLED_VALUE_UNIT_A,
	OCPP_SAMPLED_VALUE_UNIT_V,
	OCPP_SAMPLED_VALUE_UNIT_K,
	OCPP_SAMPLED_VALUE_UNIT_CELSIUS,
	OCPP_SAMPLED_VALUE_UNIT_FAHRENHEIT,
	OCPP_SAMPLED_VALUE_UNIT_PERCENT,

} OcppSampledValueUnit;

typedef enum
{
	OCPP_UPDATE_TYPE_DIFFERENTIAL,
	OCPP_UPDATE_TYPE_FULL
} OcppUpdateType;

typedef char OcppCiString20Type[20];
typedef char OcppCiString25Type[25];
typedef char OcppCiString50Type[50];
typedef char OcppCiString255Type[255];
typedef char OcppCiString500Type[500];
typedef struct
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t millisecond;
	int8_t timeZone;
} OcppDateTime;

typedef OcppCiString20Type OcppIdToken;
typedef struct
{
	OcppDateTime expiryDate;
	OcppIdToken parentIdTag;
	OcppMessageStatus status;
} OcppIdTagInfo;

typedef OcppMessageStatus OcppAvailabilityStatus;
typedef OcppMessageStatus OcppRegistrationStatus;
typedef OcppMessageStatus OcppCancelReservationStatus;
typedef OcppMessageStatus OcppAvailabilityStatus;
typedef OcppMessageStatus OcppConfigurationStatus;
typedef OcppMessageStatus OcppClearCacheStatus;
typedef OcppMessageStatus OcppClearChargingProfileStatus;
typedef OcppMessageStatus OcppDataTransferStatus;
typedef OcppMessageStatus OcppGetCompositeScheduleStatus;
typedef OcppMessageStatus OcppRemoteStartStopStatus;
typedef OcppMessageStatus OcppReservationStatus;
typedef OcppMessageStatus OcppResetStatus;
typedef OcppMessageStatus OcppUpdateStatus;
typedef OcppMessageStatus OcppChargingProfileStatus;
typedef OcppMessageStatus OcppTriggerMessageStatus;
typedef OcppMessageStatus OcppUnlockStatus;

typedef char OcppUuid[OCPP_UUID_LENGTH];

typedef struct
{
	OcppIdToken idTag;
	OcppIdTagInfo idTagInfo;
} OcppAuthorizationData;

typedef struct
{
	char value[OCPP_METER_VALUE_SAMPLED_VALUE_VALUE_MAX_LENGTH];
	OcppSampledValueContext context;
	OcppSampledValueFormat format;
	OcppSampledValueMeasurand measurand;
	OcppSampledValuePhase phase;
	OcppSampledValueLocation location;
	OcppSampledValueUnit unit;
} OcppSampledValue;

typedef struct
{
	OcppDateTime timestamp;
	OcppSampledValue sampledValue[OCPP_METER_VALUE_SAMPLED_VALUE_ARRAY_MAX_LENGTH];
} OcppMeterValue;

typedef enum
{
	OCPP_REASON_EMG_STOP,
	OCPP_REASON_EV_DISCONNECTED,
	OCPP_REASON_HARD_RESET,
	OCPP_REASON_LOCAL,
	OCPP_REASON_OTHER,
	OCPP_REASON_POWER_LOSS,
	OCPP_REASON_REBOOT,
	OCPP_REASON_REMOTE,
	OCPP_REASON_SOFT_RESET,
	OCPP_REASON_UNLOCK_COMMAND,
	OCPP_REASON_DEAUTHORIZED,

} OcppReason;

typedef struct
{
	int duration;
	OcppDateTime startSchedule;
	OcppChargingRateUnitType chargingRateUnit;
	struct
	{
		int startPeriod;
		int limit;
		int numberPhases;
	} chargingSchedulePeriod[OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX];
	int minChargingRate;
} OcppChargingSchedule;

typedef struct
{
	int chargingProfileId;
	int transactionId;
	int stackLevel;
	OcppDateTime validFrom;
	OcppDateTime validTo;
	OcppChargingProfilePurpose chargingProfilePurpose;
	OcppChargingProfileKind chargingProfileKind;
	OcppRecurrencyKind recurrencyKind;
	OcppChargingSchedule chargeSchedule;
} OcppChargingProfile;

#endif // __OCPP_PRIVATE_HEADER_H