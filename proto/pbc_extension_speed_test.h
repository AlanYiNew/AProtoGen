#ifndef PBC_EXTENSION_SPEED_TEST_H__
#define PBC_EXTENSION_SPEED_TEST_H__

#include <cstdint>
#include "pbc_extension.h"
#include "pbc_extension.pb.h"
#include "pbc_extension_decodec.h"
#include "pbc_extension_encodec.h"
#ifdef _WIN32
   #define random rand
#endif
bool run_pbc_extension_encode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map);
bool run_pbc_extension_decode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map);
#endif 
