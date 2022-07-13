// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates C code for a given .proto file.

#ifndef C_BASE_GENERATOR_H__ 
#define C_BASE_GENERATOR_H__ 
#include <string>
#include <set>

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::compiler;
using namespace google::protobuf::io;

class CBaseGenerator {
public:
   static const int kCharDefaultDefaultLen;
   static const int kRepeatDefaultDefaultLen;
   static const int kSingleByteTagMaxIndex; // 单字节的tag, 最大Index
   static const int kSingleByteTagMax; // 单字节的tag, 最大值
   static const int kDoubleByteTagMax; // 双字节的tag, 最大值
   static const string kFieldOptionExtendMaxLenTypeName;
   static const string kExcludeProtofile;

};
#endif //C_BASE_GENERATOR_H__
