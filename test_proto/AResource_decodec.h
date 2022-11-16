#ifndef ARESOURCE_DECODEC_H__
#define ARESOURCE_DECODEC_H__

#include "pbc_extension_decodec.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite.h>
#include <cstdint>
#include "AResource.h"
#ifdef __cplusplus
extern "C"
{
#endif
int32_t ParseResInner(
  const uint8_t* data,
  int size,
  ResInner* msg_obj);
int32_t ParseResInnerWithStream(
  ::google::protobuf::io::CodedInputStream* input,
  ResInner* msg_obj);
int32_t ParseReshelloworld(
  const uint8_t* data,
  int size,
  Reshelloworld* msg_obj);
int32_t ParseReshelloworldWithStream(
  ::google::protobuf::io::CodedInputStream* input,
  Reshelloworld* msg_obj);
#ifdef __cplusplus
}
#endif
#endif 
