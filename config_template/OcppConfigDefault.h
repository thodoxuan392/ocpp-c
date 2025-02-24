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

#define OCPP_VERSION_16
#define OCPP_VERSION_201
#define OCPP_VERSION OCPP_VERSION_16

/**
 * @brief  Buffer Length definition
 *
 */
#define OCPP_TX_BUFFER_MAX_LENGTH 2048
#define OCPP_RX_BUFFER_MAX_LENGTH 2048

#define OCPP_ID_TAG_MAX_LENGTH 20
#define OCPP_DATE_TIME_MAX_LENGTH 32
#define OCPP_VENDOR_ID_MAX_LENGTH 255
#define OCPP_VENDOR_ERROR_CODE_MAX_LENGTH 50

/**
 * @brief Boot Notification
 *
 */
#define OCPP_BOOT_NOTIFICATION_CHARGE_POINT_VENDOR_MAX_LENGTH 20
#define OCPP_BOOT_NOTIFICATION_CHARGE_POINT_MODEL_MAX_LENGTH 20
#define OCPP_BOOT_NOTIFICATION_CHARGE_POINT_SERIAL_NO_MAX_LENGTH 25
#define OCPP_BOOT_NOTIFICATION_CHARGE_BOX_SERIAL_NO_MAX_LENGTH 25
#define OCPP_BOOT_NOTIFICATION_FW_VERSION_NO_MAX_LENGTH 50
#define OCPP_BOOT_NOTIFICATION_ICCID_MAX_LENGTH 20
#define OCPP_BOOT_NOTIFICATION_IMSI_MAX_LENGTH 20
#define OCPP_BOOT_NOTIFICATION_METER_TYPE_MAX_LENGTH 25
#define OCPP_BOOT_NOTIFICATION_METER_SERIAL_NO_MAX_LENGTH 25

/**
 * @brief Configuration
 *
 */
#define OCPP_CONFIGURATION_KEY_MAX_LENGTH 50
#define OCPP_CONFIGURATION_VALUE_MAX_LENGTH 500

/**
 * @brief Location
 *
 */
#define OCPP_LOCATION_MAX_LENGTH 128

/**
 * @brief File
 *
 */
#define OCPP_FILE_NAME_MAX_LENGTH 255

/**
 * @brief Data Transfer
 *
 */
#define OCPP_DATA_TRANSFER_MESSAGE_ID_MAX_LENGTH 50
#define OCPP_DATA_TRANSFER_DATA_MAX_LENGTH 255

/**
 * @brief Get Composite Schedule
 *
 */
#define OCPP_CHARGE_SCHEDULE_CHARGING_SCH_PERIOD_MAX 10

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
#define OCPP_METER_VALUE_SAMPLED_VALUE_ARRAY_MAX_LENGTH 10
#define OCPP_METER_VALUE_SAMPLED_VALUE_VALUE_MAX_LENGTH 16

/**
 * @brief Send Local Authorization
 *
 */
#define OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH 5

/**
 * @brief Status Notification
 *
 */
#define OCPP_STATUS_NOTIFICATION_INFO_MAX_LENGTH 50

/**
 * @brief Transaction Data
 *
 */
#define OCPP_TRANSACTION_DATA_ARRAY_MAX_LENGTH 5

#endif // __OCPP_CONFIG_H