#ifndef __OCPP_GET_CONFIGURATION_H
#define __OCPP_GET_CONFIGURATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	OcppCiString50Type key;
	bool readonly;
	OcppCiString500Type value;
} OcppKeyValue;

typedef struct
{
	OcppCiString50Type key[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
} OcppGetConfigurationRequest;

typedef struct
{
	OcppKeyValue configurationKey[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
	OcppCiString50Type unkownKey[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
} OcppGetConfigurationResponse;

#endif // __OCPP_GET_CONFIGURATION_H