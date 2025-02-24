#ifndef __OCPP_AUTHORIZE_H
#define __OCPP_AUTHORIZE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char idTag[OCPP_ID_TAG_MAX_LENGTH];
} OcppAuthorizeRequest;

typedef struct
{
	OcppIdTagInfo idTagInfo;
} OcppAuthorizeResponse;

#endif // __OCPP_AUTHORIZE_H