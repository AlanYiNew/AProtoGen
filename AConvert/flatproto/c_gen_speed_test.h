// Author: lindaqiu@tencent.com
// Based on original Protocol Buffers 
// Generates c speed test code for a given .proto file.

#ifndef C_GEN_SPEED_TEST_H__
#define C_GEN_SPEED_TEST_H__

#include <google/protobuf/compiler/code_generator.h>

#include "c_base_generator.h" 
#include "c_file.h" 


using namespace google::protobuf;
class CSpeedTestGenerator : public CBaseGenerator {
public:
    CSpeedTestGenerator(CFileGenerator* generator);
    bool Generate(const FileDescriptor* file, 
                  const string& parameter,
                  GeneratorContext* generator_context, 
                  string* error);
protected:
    CFileGenerator* generator_;
};
#endif // C_GEN_SPEED_TEST_H__ 

