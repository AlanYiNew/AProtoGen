#include "c_generator_total.h"
#include "c_gen_decode.h"
#include "c_gen_encode.h"
#include "c_gen_string.h"
#include "c_gen_json.h"
#include "c_gen_clear.h"
#include "c_gen_assign.h"
#include "c_gen_unit_test.h"
#include "c_gen_speed_test.h"
#include "c_generator.h"
#include "c_file.h"
#include "c_generator_helpers.h"
#include "aext.pb.h"
#include <google/protobuf/stubs/strutil.h>

bool CTotalGenerator::CheckStrictFlag(const FileDescriptor* file, bool upper_layer) const
{
    if (file->name() == "aext.proto") {
        return true;
    }
    auto strict_flat = GetStrictFlat(file);
    if (upper_layer) {
        if (!strict_flat) {
            return false;
        }
    }

    for (int i = 0; i < file->dependency_count(); ++i) {
        if (!CheckStrictFlag(file->dependency(i), strict_flat)) {
            return false;
        }
    }

    return true; 
}

bool CTotalGenerator::
Generate(const FileDescriptor* file, 
        const string& parameter, 
        GeneratorContext* generator_context, 
        string* error) const {
    vector<string> params; 
    SplitStringUsing(parameter, ",", &params);
    bool generate_test = false;
    bool generate_assign = false;
    
    for (vector<string>::iterator it = params.begin(); it != params.end(); ++it) {
        if(*it == "test") {
            generate_test = true;
        }
        else if (*it == "assign") {
            generate_assign = true;
        } 
    }

    if (!CheckStrictFlag(file)) {
        GOOGLE_LOG(ERROR) << "Fail Check Strict Flag";
        return false;
    }

    CFileGenerator file_generator(file);
    CGenerator generator;
    CDecodeGenerator generator_decode(&file_generator);
    CEncodeGenerator generator_encode(&file_generator);
    CStringGenerator generator_string(&file_generator);
    CJsonGenerator generator_json(&file_generator);
    CClearGenerator generator_clear(&file_generator);
    
    bool generator_ret_value = generator.Generate(file, parameter, generator_context, error, generate_assign) && 
    generator_decode.Generate(file, parameter, generator_context, error) &&
    generator_string.Generate(file, parameter, generator_context, error) &&
    generator_json.Generate(file, parameter, generator_context, error) &&
    generator_encode.Generate(file, parameter, generator_context, error) && 
    generator_clear.Generate(file, parameter, generator_context, error) ;

    if(generate_test) {
        CUnitTestGenerator generator_unit_test(&file_generator);
        CSpeedTestGenerator generator_speed_test(&file_generator);
        generator_ret_value = generator_ret_value && 
                        generator_unit_test.Generate(file, parameter, generator_context, error) &&
                        generator_speed_test.Generate(file, parameter, generator_context, error);
    }

    if (generate_assign) {
        CAndCppAssignGenerator generator_assign(&file_generator);
        generator_ret_value = generator_ret_value && generator_assign.Generate(file, parameter, generator_context, error);
    }
    return generator_ret_value;
}
