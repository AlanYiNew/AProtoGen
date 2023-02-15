#include <google/protobuf/wire_format.h>
#include <google/protobuf/compiler/cpp/helpers.h>

#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"

#include "c_gen_encode.h"

using namespace google::protobuf::compiler::cpp;

CEncodeGenerator::   
CEncodeGenerator(CFileGenerator* generator)
    : generator_(generator) {
}

bool CEncodeGenerator::
Generate(const FileDescriptor* file,
        const string& parameter,
        GeneratorContext* generator_context,
        string* error)
{
    string suffix = ".proto";
    string base_name = StripSuffixString(file->name(), suffix);
    std::unique_ptr<io::ZeroCopyOutputStream> temp(generator_context->Open(base_name + "_encodec.h"));
    Printer header_printer(temp.get(), '$');
    if (!generator_->GenerateEncodeHeader(&header_printer)) return false;
    std::unique_ptr<io::ZeroCopyOutputStream> temp2(generator_context->Open(base_name + "_encodec.cpp"));
    Printer source_printer(temp2.get(), '$');
    if (!generator_->GenerateEncodeSource(&source_printer)) return false;
    return true;
}
