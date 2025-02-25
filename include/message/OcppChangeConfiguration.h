#ifndef __OCPP_CHANGE_CONFIGURATION_H
#define __OCPP_CHANGE_CONFIGURATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	OcppCiString50Type key;
	OcppCiString500Type value;
} OcppChangeConfigurationRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppChangeConfigurationResponse;

#endif // __OCPP_CHANGE_CONFIGURATION_H
