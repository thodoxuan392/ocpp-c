#ifndef __OCPP_GET_CONFIGURATION_H
#define __OCPP_GET_CONFIGURATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char key[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH][OCPP_CONFIGURATION_KEY_MAX_LENGTH];
} OcppGetConfigurationRequest;

typedef struct
{
	struct
	{
		char key[OCPP_CONFIGURATION_KEY_MAX_LENGTH];
		bool readonly;
		char value[OCPP_CONFIGURATION_VALUE_MAX_LENGTH];
	} configurationKey[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];

	struct
	{
		char key[OCPP_CONFIGURATION_KEY_MAX_LENGTH];
	} unkownKey[OCPP_GET_CONFIGURATION_ARRAY_MAX_LENGTH];
} OcppGetConfigurationResponse;

#endif // __OCPP_GET_CONFIGURATION_H