#include "c_generator.h"


#include <google/protobuf/extension_set.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/logging.h>

#include <sstream> 
#include <stdio.h> 

CGenerator::CGenerator() {
}


bool CGenerator::
Generate(const FileDescriptor* file,
        const string& parameter,
        GeneratorContext* generator_context,
        string* error) const {


    string suffix = ".proto";
    string base_name = StripSuffixString(file->name(), suffix);
    Printer define_printer(generator_context->Open(base_name + ".h"), '$');
    if (!GenerateDefineFile(file, define_printer)) return false;
    return true;
}

bool CGenerator::
GenerateDefineFile(const FileDescriptor* file, Printer& printer) const {


    return true;
}


