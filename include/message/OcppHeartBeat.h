#ifndef __OCPP_HEARTBEAT_H
#define __OCPP_HEARTBEAT_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
} OcppHeartBeatRequest;

typedef struct
{
	OcppDateTime currentTime;
} OcppHeartBeatResponse;

#endif // __OCPP_HEARTBEAT_H