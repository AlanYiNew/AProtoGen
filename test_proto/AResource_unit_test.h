#ifndef ARESOURCE_UNIT_TEST_H__
#define ARESOURCE_UNIT_TEST_H__

#include <cstdint>
#include <google/protobuf/util/json_util.h>
#include <string>
#include "AResource.h"
#include "AResource.pb.h"
#include "AResource_decodec.h"
#include "AResource_encodec.h"
#include "AResource_string.h"
#include "AResource_json.h"
#include "AResource_speed_test.h"
#include "pbc_extension_unit_test.h"
#ifdef _WIN32
   #define random rand
#endif
void FillResInner(ResInner* msg_obj_c);
void FillInner(Res::Inner* msg_obj_cpp);
bool CompareInner(ResInner* msg_obj_c, Res::Inner* msg_obj_cpp);
void FillReshelloworld(Reshelloworld* msg_obj_c);
void Fillhelloworld(Res::helloworld* msg_obj_cpp);
bool Comparehelloworld(Reshelloworld* msg_obj_c, Res::helloworld* msg_obj_cpp);
bool run_AResource_encode_unit_test();
bool run_AResource_decode_unit_test();
#endif 
