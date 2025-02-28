/**
 * @file OcppConfig.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __OCPP_CONFIG_H
#define __OCPP_CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <utils_logger.h>

#define Ocpp_LogInfo(message) printf message
#define Ocpp_LogWarn(message) printf message
#define Ocpp_LogError(message) printf message
#define Ocpp_LogDebug(message) printf message

#define OCPP_VERSION_16
#define OCPP_VERSION_201
#define OCPP_VERSION OCPP_VERSION_16
#define OCPP_REQUEST_POOL_MAX 5 // 5 request can be stored at one time

/**
 * @brief  Buffer Length definition
 *
 */
#define OCPP_CLIENT_NO_SUPPORT 2
#define OCPP_TX_BUFFER_MAX_LENGTH 3072
#define OCPP_RX_BUFFER_MAX_LENGTH 3072
#define OCPP_MESSAGE_MAX_LENGTH 2048
#define OCPP_MESSAGE_ADDITION_PART_MAX_LENGTH 2048
#define OCPP_UUID_LENGTH 36
#define OCPP_ACTION_ID_MAX_LENGTH 32
#define OCPP_ERROR_DESCRIPTION_MAX_LENGTH 128
#define OCPP_ERROR_DETAIL_MAX_LENGTH 256
#define OCPP_DATE_TIME_MAX_LENGTH 32
#define OCPP_MESSAGE_STATUS_MAX_LENGTH 32
#define OCPP_ID_TAG_INFO_MAX_LENGTH 128
#define OCPP_CHARGING_RATE_UNIT_MAX_LENGTH 16
#define OCPP_CHARGING_PROFILE_PURPOSE_MAX_LENGTH 32
#define OCPP_CHARGING_PROFILE_KIND_MAX_LENGTH 16
#define OCPP_RECURRENCY_KIND_MAX_LENGTH 16
#define OCPP_ERROR_CODE_MAX_LENGTH 64
#define OCPP_AVAILABILITY_TYPE_MAX_LENGTH 16

/**
 * @brief Json Token Definition
 *
 */
#define OCPP_MESSAGE_MAX_TOKEN 512

/**
 * @brief Location
 *
 */
#define OCPP_LOCATION_MAX_LENGTH 128

/**
 * @brief Data Transfer
 *
 */
#define OCPP_DATA_TRANSFER_DATA_MAX_LENGTH 255

/**
 * @brief Get Composite Schedule
 *
 */
#define OCPP_CHARGE_SCHEDULE_CHARGING_SCH_MAX_LENGTH 1024
#define OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX 10
#define OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX_LENGTH 64
#define OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_ARR_MAX_LENGTH \
	(OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX_LENGTH *      \
	 OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX)

/**
 * @brief Get Configuration
 *
 */
#define OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH 5

/**
 * @brief Meter Value
 *
 */
#define OCPP_METER_VALUE_ARRAY_MAX_LENGTH 10
#define OCPP_METER_VALUE_SAMPLED_VALUE_MAX_LENGTH 256
#define OCPP_METER_VALUE_SAMPLED_VALUE_ARRAY_MAX_LENGTH 10
#define OCPP_METER_VALUE_SAMPLED_VALUE_VALUE_MAX_LENGTH 16
#define OCPP_METER_VALUE_SAMPLED_VALUE_CONTEXT_MAX_LENGTH 32
#define OCPP_METER_VALUE_SAMPLED_VALUE_FORMAT_MAX_LENGTH 32
#define OCPP_METER_VALUE_SAMPLED_VALUE_MEASURAND_MAX_LENGTH 32
#define OCPP_METER_VALUE_SAMPLED_VALUE_PHASE_MAX_LENGTH 32
#define OCPP_METER_VALUE_SAMPLED_VALUE_LOCATION_MAX_LENGTH 32
#define OCPP_METER_VALUE_SAMPLED_VALUE_UNIT_MAX_LENGTH 32

/**
 * @brief Send Local Authorization
 *
 */
#define OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH 5

/**
 * @brief Transaction Data
 *
 */
#define OCPP_TRANSACTION_DATA_ARRAY_MAX_LENGTH 5

#endif // __OCPP_CONFIG_H