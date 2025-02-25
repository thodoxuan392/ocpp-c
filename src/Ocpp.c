#include <Ocpp.h>

/**
 * @brief Data handling from Websocket
 *
 */
static OcppRetType Ocpp_WebSocketEventCallback(int socketId, OcppWebSocketEvent event,
											   uint8_t* data, uint32_t dataSize);
static OcppRetType Ocpp_WebSocketSendData(OcppHandle* ocppHandle, uint8_t* data, uint32_t dataSize);

/**
 * @brief Message Parser and builder
 */
static OcppRetType Ocpp_ParseMessage(uint8_t* data, uint32_t dataSize, OcppMessage* message);
static OcppRetType Ocpp_BuildMessage(OcppMessage* message, uint8_t* data, uint32_t* dataSize);

static OcppHandle* Ocpp_handleRefTable[OCPP_CLIENT_NO_SUPPORT];
static bool Ocpp_isConnected[OCPP_CLIENT_NO_SUPPORT];
static uint8_t Ocpp_noClient = 0;
static OcppMessage Ocpp_rxMessage;

OcppRetType Ocpp_Init(OcppHandle* ocppHandle)
{
	ocppHandle->webSocketIntf->registerEventCallbackPf(Ocpp_WebSocketEventCallback);
}
OcppRetType Ocpp_DeInit(OcppHandle* ocppHandle)
{
}
OcppRetType Ocpp_Loop(OcppHandle* ocppHandle)
{
	if(Ocpp_ParseMessage(ocppHandle->rxBuffer, ocppHandle->rxBufferLength, &Ocpp_rxMessage))
	{
		ocppHandle->messageListener(&Ocpp_rxMessage);
	}
}
OcppRetType Ocpp_RegisterMessageListener(OcppHandle* ocppHandle,
										 OcppMessageListener messageListener)
{
	ocppHandle->messageListener = messageListener;
}

OcppRetType Ocpp_SendMessage(OcppHandle* ocppHandle, OcppMessage* message)
{
	OcppRetType retType;
	uint32_t txSize;

	retType = Ocpp_BuildMessage(message, ocppHandle->txBuffer, &txSize);
	if(retType != OCPP_OK)
	{
		// Log here
		return retType;
	}

	retType = Ocpp_WebSocketSendData(ocppHandle, ocppHandle->txBuffer, txSize);
	if(retType != OCPP_OK)
	{
		// Log here
		return retType;
	}

	return OCPP_OK;
}

static OcppRetType Ocpp_WebSocketEventCallback(int socketId, OcppWebSocketEvent event,
											   uint8_t* data, uint32_t dataSize)
{
}
static OcppRetType Ocpp_WebSocketSendData(OcppHandle* ocppHandle, uint8_t* data, uint32_t dataSize)
{
	int socketId = ocppHandle->webSocketIntf->socketId;
	return ocppHandle->webSocketIntf->sendDataPf(socketId, data, dataSize);
}

static OcppRetType Ocpp_ParseMessage(uint8_t* data, uint32_t dataSize, OcppMessage* message)
{
}
static OcppRetType Ocpp_BuildMessage(OcppMessage* message, uint8_t* data, uint32_t* dataSize)
{
}