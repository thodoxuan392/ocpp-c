#ifndef __OCPP_SEND_LOCAL_LIST_H
#define __OCPP_SEND_LOCAL_LIST_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_LOCAL_AUTHORIZATION_UPDATE_TYPE_DIFFERENTIAL,
	OCPP_LOCAL_AUTHORIZATION_UPDATE_TYPE_FULL
} OcppLocalAuthorizationUpdateType;

typedef struct
{
	char idTag[OCPP_ID_TAG_MAX_LENGTH];
	OcppIdTagInfo idTagInfo;
} OcppLocalAuthorization;

typedef struct
{
	int listVersion;
	OcppLocalAuthorization localAuthorizationList[OCPP_LOCAL_AUTHORIZATION_ARRAY_MAX_LENGTH];
	OcppLocalAuthorizationUpdateType updateType;
} OcppSendLocalListRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppSendLocalListResponse;

#endif // __OCPP_SEND_LOCAL_LIST_H