#ifndef __OCPP_WEB_SOCKET_INTF_H
#define __OCPP_WEB_SOCKET_INTF_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_WEB_SOCKET_EVENT_CONNECTED,
	OCPP_WEB_SOCKET_EVENT_DISCONNECTED,
	OCPP_WEB_SOCKET_EVENT_RX_DATA
} OcppWebSocketEvent;

typedef OcppRetType (*OcppWebSocket_SendData)(int socketId, uint8_t* data, uint32_t dataSize);
typedef OcppRetType (*OcppWebSocket_EventCallback)(int socketId, OcppWebSocketEvent event,
												   uint8_t* data, uint32_t dataSize);
typedef OcppRetType (*OcppWebSocket_RegisterEventCallback)(
	OcppWebSocket_EventCallback eventCallback);

typedef struct
{
	int socketId;
	OcppWebSocket_SendData sendDataPf;
	OcppWebSocket_RegisterEventCallback registerEventCallbackPf;
} OcppWebSocketIntf;

#endif // __OCPP_WEB_SOCKET_INTF_H