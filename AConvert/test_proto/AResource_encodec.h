#ifndef ARESOURCE_ENCODE_H__
#define ARESOURCE_ENCODE_H__

#include "AResource.h"
#include "pbc_extension_encodec.h"
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/coded_stream.h>

#include "AResource.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

int SerializeResInnerToArray(
  ResInner* msg_obj, uint8_t* buffer, int size);
int SerializeResInnerToArrayWithCachedSize(
  ResInner* msg_obj,  ResInnerCachedSize_* msg_obj_cached_size, ::google::protobuf::uint8* buffer, int size);
int ResInnerByteSizeLong(
  ResInner* msg_obj);
int ResInnerByteSizeLongWithCachedSize(
  ResInner* msg_obj,  ResInnerCachedSize_* msg_obj_cached_size);
int SerializeReshelloworldToArray(
  Reshelloworld* msg_obj, uint8_t* buffer, int size);
int SerializeReshelloworldToArrayWithCachedSize(
  Reshelloworld* msg_obj,  ReshelloworldCachedSize_* msg_obj_cached_size, ::google::protobuf::uint8* buffer, int size);
int ReshelloworldByteSizeLong(
  Reshelloworld* msg_obj);
int ReshelloworldByteSizeLongWithCachedSize(
  Reshelloworld* msg_obj,  ReshelloworldCachedSize_* msg_obj_cached_size);
#ifdef __cplusplus
}
#endif
#endif //ARESOURCE_ENCODEC_ENCODE_H__