#ifndef ARESOURCE_CLEAR_H__
#define ARESOURCE_CLEAR_H__

#include "pbc_extension_clear.h"
#include "string.h"
#include "AResource.h"

#ifdef __cplusplus
extern "C"
{
#endif
void ClearResInner(ResInner* msg_obj);
void SetResInnerWrited(ResInner* msg_obj);
void ClearReshelloworld(Reshelloworld* msg_obj);
void SetReshelloworldWrited(Reshelloworld* msg_obj);
#ifdef __cplusplus
}
#endif
#endif 
