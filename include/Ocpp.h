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

#include <OcppTypes.h>
#include <OcppConfig.h>
#include <OcppWebsocketIntf.h>
#include <OcppMessage.h>
#include <OcppJson.h>

typedef OcppRetType (*OcppMessageListener)(OcppMessage* message);

typedef struct
{
	OcppUuid uniqueId;
	OcppActionId actionId;
} OcppRequestPool;
typedef struct
{
	OcppWebSocketIntf* webSocketIntf;
	OcppMessageListener messageListener;
	bool connected;
	uint8_t rxBuffer[OCPP_RX_BUFFER_MAX_LENGTH];
	uint32_t rxBufferLength;
	uint8_t txBuffer[OCPP_TX_BUFFER_MAX_LENGTH];
	OcppRequestPool requestPool[OCPP_REQUEST_POOL_MAX];
	uint8_t requestIdx;
} OcppHandle;

OcppRetType Ocpp_Init(OcppHandle* ocppHandle);
OcppRetType Ocpp_DeInit(OcppHandle* ocppHandle);
OcppRetType Ocpp_Loop(OcppHandle* ocppHandle);
OcppRetType Ocpp_IsConnected(OcppHandle* ocppHandle);
OcppRetType Ocpp_RegisterMessageListener(OcppHandle* ocppHandle,
										 OcppMessageListener messageListener);
OcppRetType Ocpp_InitMessage(OcppMessage* message);
OcppRetType Ocpp_SendMessage(OcppHandle* ocppHandle, OcppMessage* message);

#endif // __OCPP_H