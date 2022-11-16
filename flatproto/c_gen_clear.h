#ifndef _C_GEN_CLEAR_H__
#define _C_GEN_CLEAR_H__

#include <string>
#include <set>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

#include "c_base_generator.h"
#include "c_file.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;

class CClearGenerator : public CBaseGenerator { 
public:
    CClearGenerator(CFileGenerator* generator);
    bool Generate(const FileDescriptor* file,
                  const string& parameter,
                  GeneratorContext* generator_context,
                  string* error);
protected:
    CFileGenerator* generator_;
};
#endif //  _C_GEN_CLEAR_H__


