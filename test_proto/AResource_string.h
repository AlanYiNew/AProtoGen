#ifndef ARESOURCE_STRING_H__
#define ARESOURCE_STRING_H__

#include "pbc_extension_string.h"
#include <cstdint>
#include "AResource.h"
#ifdef __cplusplus
extern "C"
{
#endif
int ResInnerSimpleString(
ResInner* msg_obj, char* buffer, int size, char delimiter);
int ReshelloworldSimpleString(
Reshelloworld* msg_obj, char* buffer, int size, char delimiter);
#ifdef __cplusplus
}
#endif
#endif //