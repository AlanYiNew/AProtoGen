// Based on original Protocol Buffers 
// Generates C code for a given .proto file.

#ifndef C_BASE_GENERATOR_H__ 
#define C_BASE_GENERATOR_H__ 
#include <string>
#include <set>

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include "google/protobuf/compiler/code_generator.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::compiler;
using namespace google::protobuf::io;

class CBaseGenerator : public google::protobuf::compiler::CodeGenerator{
public:
   static const int kCharDefaultDefaultLen;
   static const int kRepeatDefaultDefaultLen;
   static const int kSingleByteTagMaxIndex; 
   static const int kSingleByteTagMax;
   static const int kDoubleByteTagMax;
   static const string kFieldOptionExtendMaxLenTypeName;
   static const string kExcludeProtofile;

};
#endif //C_BASE_GENERATOR_H__
