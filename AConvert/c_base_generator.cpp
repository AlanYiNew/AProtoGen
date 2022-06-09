#include "c_base_generator.h"


#include <google/protobuf/extension_set.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/logging.h>

#include <sstream> 
#include <stdio.h> 


const int CBaseGenerator::kCharDefaultDefaultLen = 128;
const int CBaseGenerator::kRepeatDefaultDefaultLen = 64;
const int CBaseGenerator::kSingleByteTagMaxIndex = 15; 
const int CBaseGenerator::kSingleByteTagMax = 127;
const int CBaseGenerator::kDoubleByteTagMax = 16383;

const string CBaseGenerator::kFieldOptionExtendMaxLenTypeName = "MaxLength";
const string CBaseGenerator::kExcludeProtofile = "descriptor.proto";


 
