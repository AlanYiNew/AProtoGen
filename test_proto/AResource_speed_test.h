#ifndef ARESOURCE_SPEED_TEST_H__
#define ARESOURCE_SPEED_TEST_H__

#include "pbc_extension_speed_test.h"
#include <cstdint>
#include "AResource.h"
#include "AResource.pb.h"
#include "AResource_decodec.h"
#include "AResource_encodec.h"
#ifdef _WIN32
   #define random rand
#endif
void FillResInnerFull(ResInner* msg_obj_c);
void FillInnerFull(Res::Inner* msg_obj_cpp);
void FillReshelloworldFull(Reshelloworld* msg_obj_c);
void FillhelloworldFull(Res::helloworld* msg_obj_cpp);
bool run_AResource_encode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map);
bool run_AResource_decode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map);
#endif 
