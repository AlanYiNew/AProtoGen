#include <google/protobuf/wire_format.h>
#include <google/protobuf/compiler/cpp/helpers.h>

#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"
#include "c_gen_assign.h"

    
using namespace google::protobuf::compiler::cpp;

CAndCppAssignGenerator::   
CAndCppAssignGenerator(CFileGenerator* generator)
    : generator_(generator) {
}

bool CAndCppAssignGenerator::
Generate(const FileDescriptor* file,
        const string& parameter,
        GeneratorContext* generator_context,
        string* error)
{
    string suffix = ".proto";
    string base_name = StripSuffixString(file->name(), suffix);
    std::unique_ptr<io::ZeroCopyOutputStream> temp(generator_context->Open(base_name + "_assign.h"));
    Printer header_printer(temp.get(), '$');
    if (!generator_->GenerateCAndCppAssignHeader(&header_printer)) return false;
    return true;
}
