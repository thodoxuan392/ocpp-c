#ifndef __OCPP_RESET_H
#define __OCPP_RESET_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

typedef enum
{
	OCPP_RESET_TYPE_HARD,
	OCPP_RESET_TYPE_SOFT
} OcppResetType;

typedef struct
{
	OcppResetType type;
} OcppResetRequest;

typedef struct
{
	OcppResetStatus status;
} OcppResetResponse;

#endif // __OCPP_RESET_H