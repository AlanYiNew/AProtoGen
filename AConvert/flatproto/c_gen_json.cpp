#include <google/protobuf/stubs/strutil.h>
#include "c_gen_json.h"

CJsonGenerator::   
CJsonGenerator(CFileGenerator* generator) 
    : generator_(generator)
{}

bool CJsonGenerator::   
Generate(const FileDescriptor* file, 
         const string& parameter,
         GeneratorContext* generator_context, 
         string* error) {

    string suffix = ".proto";
    string base_name = StripSuffixString(file->name(), suffix);
    std::unique_ptr<io::ZeroCopyOutputStream> temp(generator_context->Open(base_name + "_json.h"));
    Printer header_printer(temp.get(), '$');
    if (!generator_->GenerateJsonHeader(&header_printer)) 
        return false;

    std::unique_ptr<io::ZeroCopyOutputStream> temp2(generator_context->Open(base_name + "_json.c"));
    Printer source_printer(temp2.get(), '$');
    if (!generator_->GenerateJsonSource(&source_printer)) 
        return false;
    return true;
}