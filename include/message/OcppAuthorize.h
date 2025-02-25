#ifndef __OCPP_AUTHORIZE_H
#define __OCPP_AUTHORIZE_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef OcppMessageStatus OcppAuthorizationStatus;
typedef struct
{
	OcppIdToken idTag;
} OcppAuthorizeRequest;

typedef struct
{
	OcppIdTagInfo idTagInfo;
} OcppAuthorizeResponse;

#endif // __OCPP_AUTHORIZE_H