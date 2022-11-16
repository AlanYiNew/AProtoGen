// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates C code for a given .proto file.

#ifndef C_GENERATOR_TOTAL_H__ 
#define C_GENERATOR_TOTAL_H__

#include <google/protobuf/compiler/code_generator.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::compiler;

class CTotalGenerator: public CodeGenerator {
public:
    bool Generate(const FileDescriptor* file, 
                  const string& parameter,
                  GeneratorContext* generator_context, 
                  string* error) const;
};

#endif // C_GENERATOR_TOTAL_H__
