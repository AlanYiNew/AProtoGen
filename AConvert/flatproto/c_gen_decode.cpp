#include <google/protobuf/wire_format.h>
#include <google/protobuf/compiler/cpp/helpers.h>

#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"

#include "c_gen_decode.h"

    
using namespace google::protobuf::compiler::cpp;

CDecodeGenerator::   
CDecodeGenerator(CFileGenerator* generator)
    : generator_(generator) {
}

bool CDecodeGenerator::
Generate(const FileDescriptor* file,
        const string& parameter,
        GeneratorContext* generator_context,
        string* error)
{
    string suffix = ".proto";
    string base_name = StripSuffixString(file->name(), suffix);
    std::unique_ptr<io::ZeroCopyOutputStream> temp(generator_context->Open(base_name + "_decodec.h"));
    Printer header_printer(temp.get(), '$');
    if (!generator_->GenerateDecodeHeader(&header_printer)) return false;

    Printer source_printer(
            generator_context->Open(base_name + "_decodec.c"), '$');
    if (!generator_->GenerateDecodeSource(&source_printer)) return false;
    return true;
}
