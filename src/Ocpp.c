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
static OcppRetType Ocpp_GetOcppHandleBySocketId(int socketId, OcppHandle** ocppHandle);
static OcppRetType Ocpp_ClearRxBuffer(OcppHandle* ocppHandle);

static OcppHandle* Ocpp_handleRefTable[OCPP_CLIENT_NO_SUPPORT];
static bool Ocpp_isConnected[OCPP_CLIENT_NO_SUPPORT];
static uint8_t Ocpp_noClient = 0;
static OcppMessage Ocpp_rxMessage;

OcppRetType Ocpp_Init(OcppHandle* ocppHandle)
{
	Ocpp_handleRefTable[Ocpp_noClient++] = ocppHandle;
	ocppHandle->webSocketIntf->registerEventCallbackPf(Ocpp_WebSocketEventCallback);
}
OcppRetType Ocpp_DeInit(OcppHandle* ocppHandle)
{
	ocppHandle->rxBufferLength = 0;
}
OcppRetType Ocpp_Loop(OcppHandle* ocppHandle)
{
	if(Ocpp_ParseMessage(ocppHandle, ocppHandle->rxBuffer, ocppHandle->rxBufferLength,
						 &Ocpp_rxMessage) == OCPP_OK)
	{
		ocppHandle->rxBufferLength = 0;
		if(ocppHandle->messageListener != NULL)
		{
			ocppHandle->messageListener(&Ocpp_rxMessage);
		}
	}
}
OcppRetType Ocpp_IsConnected(OcppHandle* ocppHandle)
{
	return (ocppHandle->connected) ? OCPP_OK : OCPP_NOT_OK;
}
OcppRetType Ocpp_RegisterMessageListener(OcppHandle* ocppHandle,
										 OcppMessageListener messageListener)
{
	ocppHandle->messageListener = messageListener;
}

OcppRetType Ocpp_InitMessage(OcppMessage* message)
{
	memset(message, 0, sizeof(OcppMessage));
	return OCPP_OK;
}

OcppRetType Ocpp_SendMessage(OcppHandle* ocppHandle, OcppMessage* message)
{
	OcppRetType retType;
	uint32_t txSize;

	// Get action from request pool stored before
	if(message->messageTypeId == OCPP_MESSAGE_TYPE_CALL_RESULT)
	{
		retType = Ocpp_GetActionIdByUniqueId(ocppHandle, message->uniqueId, &message->call.action);
		if(retType != OCPP_OK)
		{
			Ocpp_LogError(("[OCPP] Cannot get action with UniqueId#%s\r\n", message->call.action,
						   message->uniqueId));
			return OCPP_NOT_OK;
		}
	}

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

	// Save request to pool if client send request message
	if(message->messageTypeId == OCPP_MESSAGE_TYPE_CALL)
	{
		retType = Ocpp_SetActionIdByUniqueId(ocppHandle, message->uniqueId, message->call.action);
		if(retType != OCPP_OK)
		{
			Ocpp_LogError(("[OCPP] Cannot save action %d by uniqueId#%s\r\n", message->call.action,
						   message->uniqueId));
			return OCPP_NOT_OK;
		}
	}

	return OCPP_OK;
}

static OcppRetType Ocpp_WebSocketEventCallback(int socketId, OcppWebSocketEvent event,
											   uint8_t* data, uint32_t dataSize)
{
	OcppHandle* ocppHandle;
	OcppRetType ret = Ocpp_GetOcppHandleBySocketId(socketId, &ocppHandle);
	if(ret != OCPP_OK)
	{
		Ocpp_LogError(("[OCPP] Cannot get Ocpp Client by socketId %d\r\n", socketId));
		return OCPP_NOT_OK;
	}

	if(event == OCPP_WEB_SOCKET_EVENT_CONNECTED)
	{
		ocppHandle->connected = true;
	}
	else if(event == OCPP_WEB_SOCKET_EVENT_DISCONNECTED)
	{
		ocppHandle->connected = false;
	}
	else if(event == OCPP_WEB_SOCKET_EVENT_RX_DATA)
	{
		if((dataSize + ocppHandle->rxBufferLength) > OCPP_RX_BUFFER_MAX_LENGTH)
		{
			Ocpp_LogError(("[OCPP] Message buffer is overflow %d, maximum %d\r\n",
						   dataSize + ocppHandle, OCPP_RX_BUFFER_MAX_LENGTH));
			return OCPP_NOT_OK;
		}
		memcpy(&ocppHandle->rxBuffer[ocppHandle->rxBufferLength], data, dataSize);
		ocppHandle->rxBufferLength += dataSize;
	}

	return OCPP_OK;
}
static OcppRetType Ocpp_WebSocketSendData(OcppHandle* ocppHandle, uint8_t* data, uint32_t dataSize)
{
	int socketId = ocppHandle->webSocketIntf->socketId;
	if(!ocppHandle->connected)
	{
		return OCPP_NOT_OK;
	}
	return ocppHandle->webSocketIntf->sendDataPf(socketId, data, dataSize);
}

static OcppRetType Ocpp_ParseMessage(OcppHandle* ocppHandle, uint8_t* data, uint32_t dataSize,
									 OcppMessage* message)
{
	jsmn_parser parser;
	jsmntok_t tokens[OCPP_MESSAGE_MAX_TOKEN];
	uint32_t tokenSize;

	if(dataSize == 0)
	{
		return OCPP_NOT_OK;
	}

	jsmn_init(&parser);
	int noToken = jsmn_parse(&parser, data, dataSize, tokens, OCPP_MESSAGE_MAX_TOKEN);
	if(noToken <= 0)
	{
		return OCPP_NOT_OK;
	}
	if((noToken < 1) || ((tokens[0].type != JSMN_ARRAY)))
	{
		Ocpp_LogError(("[OCPP] Message should be JSMN_ARRRAY and length > 1\r\n"));
		Ocpp_ClearRxBuffer(ocppHandle);
		return OCPP_NOT_OK;
	}

	memset(message, 0, sizeof(OcppMessage));

	char actionIdStr[OCPP_ACTION_ID_MAX_LENGTH];
	memset(actionIdStr, 0, OCPP_ACTION_ID_MAX_LENGTH);

	OcppJson_ToNumber(data, &tokens[1], &message->messageTypeId);

	switch(message->messageTypeId)
	{
		case OCPP_MESSAGE_TYPE_CALL:
			OcppJson_ToString(data, &tokens[2], message->uniqueId);

			OcppJson_ToString(data, &tokens[3], actionIdStr);

			OcppJson_ParseActionId(actionIdStr, strlen(actionIdStr), &message->call.action);

			tokenSize = noToken - 4;
			if(OcppJson_ParseCallMessage(data, &tokens[4], &tokenSize, &message->call) != OCPP_OK)
			{
				Ocpp_LogError(
					("[OCPP] Parse call message with uniqueId#%s failed\r\n", message->uniqueId));
				Ocpp_ClearRxBuffer(ocppHandle);
				return OCPP_NOT_OK;
			}

			// Save request to pool
			if(Ocpp_SetActionIdByUniqueId(ocppHandle, message->uniqueId, message->call.action) !=
			   OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] Cannot save action %d by uniqueId#%s\r\n",
							   message->call.action, message->uniqueId));
				Ocpp_ClearRxBuffer(ocppHandle);
				return OCPP_NOT_OK;
			}
			break;
		case OCPP_MESSAGE_TYPE_CALL_RESULT:
			OcppJson_ToString(data, &tokens[2], message->uniqueId);
			printf("Ocpp_ParseMessage uniqueId %s \r\n", message->uniqueId);

			// Get request from pool
			if(Ocpp_GetActionIdByUniqueId(ocppHandle, message->uniqueId,
										  &message->callResult.action) != OCPP_OK)
			{
				Ocpp_LogError(
					("[OCPP] UniqueId#%s of Call Result not found in pool, clear rx buffer ...\r\n",
					 message->uniqueId));
				Ocpp_ClearRxBuffer(ocppHandle);
				return OCPP_NOT_OK;
			}
			printf("Ocpp_ParseMessage actionId %d \r\n", message->callResult.action);

			tokenSize = noToken - 3;
			if(OcppJson_ParseCallResultMessage(data, &tokens[3], &tokenSize,
											   &message->callResult) != OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] Parse call result message with uniqueId#%s failed\r\n",
							   message->uniqueId));
				Ocpp_ClearRxBuffer(ocppHandle);
				return OCPP_NOT_OK;
			}
			break;
		case OCPP_MESSAGE_TYPE_CALL_ERROR:
			OcppJson_ToString(data, &tokens[2], message->uniqueId);

			tokenSize = noToken - 3;
			if(OcppJson_ParseCallErrorMessage(data, &tokens[3], &tokenSize, &message->callError) !=
			   OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] Parse call error message with uniqueId#%s failed\r\n",
							   message->uniqueId));
				Ocpp_ClearRxBuffer(ocppHandle);
				return OCPP_NOT_OK;
			}
			break;
		default:
			break;
	}
	return OCPP_OK;
}
static OcppRetType Ocpp_BuildMessage(OcppHandle* ocppHandle, OcppMessage* message, uint8_t* data,
									 uint32_t* dataSize)
{
	OcppRetType ret;
	/**
	 * Addition Part is one of below:
	 * 1.Call: Payload
	 * 2.Call Result: Payload
	 * 3.Call Error: Error Code + Error Description + Error Details
	 */
	char actionStr[OCPP_ACTION_ID_MAX_LENGTH];
	uint32_t actionStrLen = OCPP_ACTION_ID_MAX_LENGTH;
	char additionPartStr[OCPP_MESSAGE_ADDITION_PART_MAX_LENGTH];
	uint32_t additionPartStrLen = OCPP_MESSAGE_ADDITION_PART_MAX_LENGTH; // Max allowed

	switch(message->messageTypeId)
	{
		case OCPP_MESSAGE_TYPE_CALL:
			ret = OcppJson_BuildActionId(message->call.action, actionStr, &actionStrLen);
			if(ret != OCPP_OK)
			{
				Ocpp_LogError(("[OCPP] uniqueId#%s Build action id failed with actionId %d\r\n",
							   message->uniqueId, message->call.action));
				return ret;
			}
			ret = OcppJson_BuildCallMessage(&message->call, additionPartStr, &additionPartStrLen);
			*dataSize = sprintf(data, "[%d,\"%s\",\"%s\",%s]", message->messageTypeId,
								message->uniqueId, actionStr, additionPartStr);
			break;
		case OCPP_MESSAGE_TYPE_CALL_RESULT:
			ret = OcppJson_BuildCallResultMessage(&message->callResult, additionPartStr,
												  &additionPartStrLen);
			*dataSize = sprintf(data, "[%d,\"%s\",%s]", message->messageTypeId, message->uniqueId,
								additionPartStr);
			break;
		case OCPP_MESSAGE_TYPE_CALL_ERROR:
			ret = OcppJson_BuildCallErrorMessage(&message->callError, additionPartStr,
												 &additionPartStrLen);
			*dataSize = sprintf(data, "[%d,\"%s\",%s]", message->messageTypeId, message->uniqueId,
								additionPartStr);
			break;
		default:
			break;
	}
	if(ret != OCPP_OK)
	{
		Ocpp_LogError(
			("[OCPP] uniqueId#%s Build addition part failed %d\r\n", message->uniqueId, ret));
		return ret;
	}

	if(*dataSize < 0)
	{
		Ocpp_LogError(
			("[OCPP] uniqueId#%s Build message failed %d\r\n", message->uniqueId, *dataSize));
		return OCPP_NOT_OK;
	}
	return OCPP_OK;
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
	ocppHandle->requestPool[ocppHandle->requestIdx].actionId = actionId;
	strcpy(ocppHandle->requestPool[ocppHandle->requestIdx].uniqueId, uniqueId);

	ocppHandle->requestIdx = (ocppHandle->requestIdx + 1) % OCPP_REQUEST_POOL_MAX;

	return OCPP_OK;
}

static OcppRetType Ocpp_GetOcppHandleBySocketId(int socketId, OcppHandle** ocppHandle)
{
	OcppRetType ret = OCPP_NOT_OK;
	for(size_t i = 0; i < OCPP_CLIENT_NO_SUPPORT; i++)
	{
		if((Ocpp_handleRefTable[i] != NULL) && (Ocpp_handleRefTable[i]->webSocketIntf != NULL) &&
		   (Ocpp_handleRefTable[i]->webSocketIntf->socketId == socketId))
		{
			*ocppHandle = Ocpp_handleRefTable[i];
			ret = OCPP_OK;
			break;
		}
	}

	return ret;
}

static OcppRetType Ocpp_ClearRxBuffer(OcppHandle* ocppHandle)
{
	ocppHandle->rxBufferLength = 0;
	memset(ocppHandle->rxBuffer, 0, OCPP_RX_BUFFER_MAX_LENGTH);
	return OCPP_OK;
}