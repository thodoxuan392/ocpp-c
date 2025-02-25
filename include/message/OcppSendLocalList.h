#ifndef __OCPP_SEND_LOCAL_LIST_H
#define __OCPP_SEND_LOCAL_LIST_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	int listVersion;
	OcppAuthorizationData localAuthorizationList[OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH];
	OcppUpdateType updateType;
} OcppSendLocalListRequest;

typedef struct
{
	OcppUpdateStatus status;
} OcppSendLocalListResponse;

#endif // __OCPP_SEND_LOCAL_LIST_H