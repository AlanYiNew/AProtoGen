#ifndef PBC_EXTENSION_UNIT_TEST_H__
#define PBC_EXTENSION_UNIT_TEST_H__

#include <cstdint>
#include <google/protobuf/util/json_util.h>
#include <string>
#include "pbc_extension.h"
#include "pbc_extension.pb.h"
#include "pbc_extension_decodec.h"
#include "pbc_extension_encodec.h"
#include "pbc_extension_string.h"
#include "pbc_extension_json.h"
#include "pbc_extension_speed_test.h"
#ifdef _WIN32
   #define random rand
#endif
bool run_pbc_extension_encode_unit_test();
bool run_pbc_extension_decode_unit_test();
#endif 
