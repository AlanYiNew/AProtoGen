#include "c_generator_resource.h"
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
#include "stdio.h"
#include <google/protobuf/stubs/strutil.h>


bool CResourceGenerator::Generate(const FileDescriptor* file,
    const string& parameter,
    GeneratorContext* generator_context,
    string* error) const {
    string filename = file->name();
    string output_filename = filename+"txt";  
    
   
    std::unique_ptr<io::ZeroCopyOutputStream> output(generator_context->Open("out.json"));
    Printer printer(output.get(), '$');
    

    for (int i = 0; i < file->message_type_count(); i++) {
        const Descriptor* message_descriptor = file->message_type(i);
        
        for (int j = 0; j < message_descriptor->field_count(); ++j) {
            const FieldDescriptor* field_descriptor = message_descriptor->field(j);
            std::map<string, string> vars;
            vars["func"] = field_descriptor->name();
            //CMessageGenerator* generator = new CMessageGenerator(message_descriptor);
            std::cout << field_descriptor->name() << std::endl;
            printer.Print(vars, "field:$func$;\n");
            printer.PrintRaw("wtf\n");
        }    
    }
    
    return true;
}