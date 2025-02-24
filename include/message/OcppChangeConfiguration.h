#ifndef __OCPP_CHANGE_CONFIGURATION_H
#define __OCPP_CHANGE_CONFIGURATION_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef struct
{
	char key[OCPP_CONFIGURATION_KEY_MAX_LENGTH];
	char value[OCPP_CONFIGURATION_VALUE_MAX_LENGTH];
} OcppChangeConfigurationRequest;

typedef struct
{
	OcppMessageStatus status;
} OcppChangeConfigurationResponse;

#endif // __OCPP_CHANGE_CONFIGURATION_H
