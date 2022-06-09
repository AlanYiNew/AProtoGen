// Based on original Protocol Buffers 
// Generates C code for a given .proto file.

#ifndef C_GENERATOR_H__ 
#define C_GENERATOR_H__ 
#include <string>
#include <set>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

#include "c_base_generator.h"
using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::compiler;
using namespace google::protobuf::io;

class CGenerator : public CBaseGenerator {
public:

    CGenerator();

        
    bool Generate(const FileDescriptor* file,
                  const string& parameter,
                  GeneratorContext* generator_context,
                  string* error) const;

    // �������ݽṹ��������ͷ�ļ�
    bool GenerateDefineFile(const FileDescriptor* file, Printer& printer) const;


};
#endif //C_GENERATOR_H__
