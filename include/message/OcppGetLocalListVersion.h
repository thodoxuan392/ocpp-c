#ifndef __OCPP_GET_LOCAL_LIST_VERSION_H
#define __OCPP_GET_LOCAL_LIST_VERSION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
} OcppGetLocalListVersionRequest;

typedef struct
{
	int listVersion;
} OcppGetLocalListVersionResponse;
#endif // __OCPP_GET_LOCAL_LIST_VERSION_H