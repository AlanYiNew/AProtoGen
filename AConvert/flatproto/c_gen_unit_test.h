// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c unit test code for a given .proto file.

#ifndef C_GEN_UNIT_TEST_H__
#define C_GEN_UNIT_TEST_H__

#include <google/protobuf/compiler/code_generator.h>

#include "c_base_generator.h" 
#include "c_file.h" 


using namespace google::protobuf;
class CUnitTestGenerator : public CBaseGenerator {
public:
    CUnitTestGenerator(CFileGenerator* generator);
    bool Generate(const FileDescriptor* file, 
                  const string& parameter,
                  GeneratorContext* generator_context, 
                  string* error);
protected:
    CFileGenerator* generator_;
};
#endif // C_GEN_UNIT_TEST_H__ 

