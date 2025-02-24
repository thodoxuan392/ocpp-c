#ifndef __OCPP_DATE_TIME_H
#define __OCPP_DATE_TIME_H

#include <OcppConfig.h>
#include <OcppPrvHeader.h>

OcppRetType OcppDateTime_ToString(OcppDateTime* dateTime, char* string, uint32_t* stringLen);
OcppRetType OcppDateTime_FromString(char* string, uint32_t stringLen, OcppDateTime* dateTime);

#endif // __OCPP_DATE_TIME_H