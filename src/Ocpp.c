#include <Ocpp.h>
#include <OcppJson.h>

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
static OcppRetType Ocpp_ParseMessage(OcppHandle* ocppHandle, uint8_t* data, uint32_t dataSize,
									 OcppMessage* message);
static OcppRetType Ocpp_BuildMessage(OcppHandle* ocppHandle, OcppMessage* message, uint8_t* data,
									 uint32_t* dataSize);
static OcppRetType Ocpp_GetActionIdByUniqueId(OcppHandle* ocppHandle, OcppUuid uniqueId,
											  OcppActionId* actionId);
static OcppRetType Ocpp_SetActionIdByUniqueId(OcppHandle* ocppHandle, OcppUuid uniqueId,
											  OcppActionId actionId);

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
	if(Ocpp_ParseMessage(ocppHandle, ocppHandle->rxBuffer, ocppHandle->rxBufferLength,
						 &Ocpp_rxMessage))
	{
		if(ocppHandle->messageListener != NULL)
		{
			ocppHandle->messageListener(&Ocpp_rxMessage);
		}
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

	retType = Ocpp_BuildMessage(ocppHandle, message, ocppHandle->txBuffer, &txSize);
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

static OcppRetType Ocpp_ParseMessage(OcppHandle* ocppHandle, uint8_t* data, uint32_t dataSize,
									 OcppMessage* message)
{
	jsmn_parser parser;
	jsmntok_t tokens[OCPP_MESSAGE_MAX_TOKEN];

	int noToken = jsmn_parse(&parser, data, dataSize, tokens, OCPP_MESSAGE_MAX_TOKEN);
	if(noToken < 0)
	{
		Ocpp_LogError(("[OCPP] Error parsing message %d\r\n", noToken));
		return OCPP_NOT_OK;
	}
	if((noToken < 1) || ((tokens[0].type != JSMN_ARRAY)))
	{
		Ocpp_LogError(("[OCPP] Message should be JSMN_ARRRAY and length > 1\r\n"));
		return OCPP_NOT_OK;
	}

	OcppJson_ToNumber(data, &tokens[0], &message->messageTypeId);

	switch(message->messageTypeId)
	{
		case OCPP_MESSAGE_TYPE_CALL:
			OcppJson_ToString(data, &tokens[1], message->uniqueId);
			OcppJson_ToNumber(data, &tokens[2], &message->call.action);
			if(OcppJson_ParseCallMessage(data, &tokens[3], noToken - 3, message) != OCPP_OK)
			{
				Ocpp_LogError(
					("[OCPP] Parse call message with uniqueId#%s failed\r\n", message->uniqueId));
				return OCPP_NOT_OK;
			}

			// Save request to pool
			if(Ocpp_SetActionIdByUniqueId(ocppHandle, message->uniqueId, message->call.action) !=
			   OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] Cannot save action %d by uniqueId#%s\r\n",
							   message->call.action, message->uniqueId));
				return OCPP_NOT_OK;
			}
			break;
		case OCPP_MESSAGE_TYPE_CALL_RESULT:
			OcppJson_ToString(data, &tokens[1], message->uniqueId);
			// Get request from pool
			if(Ocpp_GetActionIdByUniqueId(ocppHandle, message->uniqueId,
										  &message->callResult.action) != OCPP_OK)
			{
				Ocpp_LogError(
					("[OCPP] UniqueId#%s of Call Result not found in pool\r\n", message->uniqueId));
				return OCPP_NOT_OK;
			}
			if(OcppJson_ParseCallResultMessage(data, &tokens[2], noToken - 2, message) != OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] Parse call result message with uniqueId#%s failed\r\n",
							   message->uniqueId));
				return OCPP_NOT_OK;
			}
			break;
		case OCPP_MESSAGE_TYPE_CALL_ERROR:
			OcppJson_ToNumber(data, &tokens[1], &message->uniqueId);
			if(OcppJson_ParseCallErrorMessage(data, &tokens[2], noToken - 2, message) != OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] Parse call error message with uniqueId#%s failed\r\n",
							   message->uniqueId));
				return OCPP_NOT_OK;
			}
			break;
		default:
			break;
	}
	return OcppJson_ParseMessage(data, dataSize, message);
}
static OcppRetType Ocpp_BuildMessage(OcppHandle* ocppHandle, OcppMessage* message, uint8_t* data,
									 uint32_t* dataSize)
{
	return OcppJson_BuildMessage(data, dataSize, message);
}

static OcppRetType Ocpp_GetActionIdByUniqueId(OcppHandle* ocppHandle, OcppUuid uniqueId,
											  OcppActionId* actionId)
{
	OcppRetType ret;

	for(size_t idx = 0; idx < OCPP_REQUEST_POOL_MAX; idx++)
	{
		if(strcmp(uniqueId, ocppHandle->requestPool[idx].uniqueId) == 0)
		{
			*actionId = ocppHandle->requestPool[idx].actionId;
			ret = OCPP_OK;
			break;
		}
	}
	return ret;
}
static OcppRetType Ocpp_SetActionIdByUniqueId(OcppHandle* ocppHandle, OcppUuid uniqueId,
											  OcppActionId actionId)
{
	ocppHandle->requestPool[ocppHandle->requestIdx++].actionId = actionId;
	strcpy(ocppHandle->requestPool[ocppHandle->requestIdx++].uniqueId, uniqueId);

	return OCPP_OK;
}