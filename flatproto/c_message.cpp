#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"
#include "c_gen_decode.h"
#include "c_field.h"
#include "c_message.h"

void PrintFieldComment(Printer *printer, const FieldDescriptor * field)
{
    map<string, string> vars;
    DebugStringOptions options;
    options.elide_group_body = true;
    options.elide_oneof_body = true;
    std::string def = field->DebugStringWithOptions(options);
    vars["comment"] = def.substr(0, def.find_first_of('\n'));
    printer->Print(vars, "// $comment$\n");

}

bool EmitFieldNonDefaultCondition(io::Printer* printer,
        const string& prefix,
        const FieldDescriptor* field) {
    if (!field->is_repeated() && !field->containing_oneof()) {
        if (field->cpp_type() == FieldDescriptor::CPPTYPE_STRING) {
            printer->Print("{\n");
            printer->Indent();
            return true;
        } else if (field->cpp_type() != FieldDescriptor::CPPTYPE_MESSAGE) {
            printer->Print(
                    "if ($prefix$$name$ != 0) {\n",
                    "prefix", prefix,
                    "name", GetMessageFieldName(field));
            printer->Indent();
            return true;
        }
    }
    return false;
}

bool EmitFieldNonDefaultConditionJson(io::Printer* printer,
        const string& prefix,
        const FieldDescriptor* field) {
    if (!field->is_repeated() && !field->containing_oneof()) {
        if (field->cpp_type() == FieldDescriptor::CPPTYPE_STRING) {
            printer->Print("{\n");
            printer->Indent();
            return true;
        } else if (field->cpp_type() != FieldDescriptor::CPPTYPE_MESSAGE) {
            printer->Print(
                    "if ($prefix$$name$ != 0 || json_print_option.always_print_primitive_fields) {\n",
                    "prefix", prefix,
                    "name", GetMessageFieldName(field));
            printer->Indent();
            return true;
        }
    }
    return false;
}

CMessageGenerator::   
CMessageGenerator(const Descriptor* descriptor)
    : descriptor_(descriptor) ,
      field_genertors_(descriptor) {

    SetConstName(&vars_);
    vars_["c_name"] = GetCStructName(descriptor); 
    vars_["cpp_name"] = GetCppStructFullName(descriptor); 
    vars_["c_2_cpp_fun"] = GetC2CppFunName(descriptor); 
    vars_["cpp_2_c_fun"] = GetCpp2CFunName(descriptor); 

    // 过滤字段 
    // 1、oneof select字段 
    // 2、数组的长度字段
    // 这两种字段不参与代码生成
    vector<const FieldDescriptor*> exclude_fields;
    set<const FieldDescriptor*> oneof_selects;

    for (int i = 0; i < descriptor->field_count(); i++) {
        const FieldDescriptor* field = descriptor->field(i);
        const OneofDescriptor* oneof = field->containing_oneof();
        if (oneof) {
            oneof_fields_[oneof].push_back(field);
            string name = GetCStructUnionSelectVarName(oneof);
            const FieldDescriptor* tmp =
                descriptor_->FindFieldByName(name);
            if (tmp != NULL) oneof_selects.insert(tmp);
            continue;
        }
        if (IsRepeated(field) || IsBytes(field)) {
            const FieldDescriptor* tmp = descriptor_->FindFieldByName(
                    GetCArrayLenVarName(field));
            if (tmp != NULL) exclude_fields.push_back(tmp);
        }
        fields_.push_back(field);
    }

    std::copy(oneof_selects.begin(), oneof_selects.end(), 
            std::back_inserter(exclude_fields));

    for (size_t i = 0; i < exclude_fields.size(); i++) {
       vector<const FieldDescriptor*>::iterator it = 
           find(fields_.begin(), fields_.end(), exclude_fields[i]);
        if (it != fields_.end()) {
           fields_.erase(it);
        }
    }
}
    
    
bool CMessageGenerator::
GenerateUnitTestDeclear(Printer* printer) {
    printer->Print(GetFillCFun().c_str());    
    printer->Print(";\n");    
    printer->Print(GetFillCppFun().c_str());    
    printer->Print(";\n");
    printer->Print(GetCompareCppFun().c_str());    
    printer->Print(";\n");
  return true;
}
    
bool CMessageGenerator::
GenerateUnitTestDefine(Printer* printer) {
    return GenerateUnitTestFillDefine(printer, false) &&
    GenerateUnitTestFillDefine(printer, true) &&
    GenerateUnitTestCompareDefine(printer);
}

bool CMessageGenerator::
GenerateSpeedTestDeclear(Printer* printer) {
    printer->Print(GetFillFullCFun().c_str());    
    printer->Print(";\n");    
    printer->Print(GetFillFullCppFun().c_str());    
    printer->Print(";\n");
  return true;
}
    
bool CMessageGenerator::
GenerateSpeedTestDefine(Printer* printer) {
    return GenerateUnitTestFillDefine(printer, false) &&
    GenerateUnitTestFillDefine(printer, true);
}


bool CMessageGenerator::
GenerateUnitTestFillDefine(Printer* printer, bool fill_cpp) {
    if (fill_cpp) {
        printer->Print(GetFillCppFun().c_str());
        
    } else {
        printer->Print(GetFillCFun().c_str());
    }

    printer->Print(" {\n");
    printer->Indent();
    for (size_t i = 0; i < fields_.size(); i++) {
        const FieldDescriptor* field = fields_[i];
        printer->Print("{\n");
        printer->Indent();
        CFieldGenerator* generator = field_genertors_.Get(field); 

        if (fill_cpp) {
            generator->GenerateAutoFillCpp(printer);
        }   else {
            generator->GenerateAutoFillC(printer);
        }

        printer->Outdent();
        printer->Print("}\n");
    }
    map<const OneofDescriptor*, 
        vector<const FieldDescriptor*> >::iterator it; 
    for (it = oneof_fields_.begin(); 
            it != oneof_fields_.end(); ++it) {
        printer->Print("{\n");
        printer->Indent();
        printer->Print(
          "int $oneof_name$_enum[] = {\n", 
          "oneof_name", it->first->name()); 
        printer->Indent();
        for (int i = 0; i < it->first->field_count(); i++) {
            const FieldDescriptor* field = it->first->field(i);
            printer->Print(GetCUnionFieldIDName(field).c_str());
            if (i + 1 != it->first->field_count()) {
                printer->Print(", ");
                if (0 == (i+1)%3) printer->Print("\n");
            }
        }
        printer->Print("};\n");
        printer->Outdent();
        
        printer->Print(
           "int length = sizeof($oneof_name$_enum)/sizeof(int);\n"
           "int rand_enum = $oneof_name$_enum[random() % length];\n"
           "switch (rand_enum) {\n", 
           "oneof_name", it->first->name());
        
        printer->Indent();
        for (size_t i = 0; i < it->second.size(); i++) {
            const FieldDescriptor* field = it->second[i];
            printer->Print(
              "case $value$:{\n",
              "value", GetCUnionFieldIDName(field));
            printer->Indent();
            CFieldGenerator* generator = field_genertors_.Get(field); 

            if (fill_cpp) {
                generator->GenerateAutoFillCpp(printer);
            }   else {
                generator->GenerateAutoFillC(printer);
            }
            printer->Outdent();
            printer->Print("}\nbreak;\n");
        }
        printer->Outdent();
        printer->Print("}\n");
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
    
bool CMessageGenerator::
GenerateUnitTestCompareDefine(Printer* printer) {
    printer->Print(GetCompareCppFun().c_str());
    printer->Print("{\n");
    printer->Indent();
    for (size_t i = 0; i < fields_.size(); i++) {
        const FieldDescriptor* field = fields_[i];
        printer->Print("{\n");
        printer->Indent();
        CFieldGenerator* generator = field_genertors_.Get(field); 
        generator->GenerateCompareCAndCpp(printer);
        printer->Outdent();
        printer->Print("}\n");
    }
    map<const OneofDescriptor*, 
        vector<const FieldDescriptor*> >::iterator it; 
    for (it = oneof_fields_.begin(); 
            it != oneof_fields_.end(); ++it) {
        printer->Print("{\n");
        printer->Print(
          "switch ($param_c_var$->$oneof_select$()) {\n", 
          "param_c_var", vars_["param_c_var"], 
          "oneof_select", GetCStructUnionSelectVarName(it->first));
        printer->Indent();
        for (size_t i = 0; i < it->second.size(); i++) {
            const FieldDescriptor* field = it->second[i];
            printer->Print(
              "case $value$:{\n",
              "value", GetCUnionFieldIDName(field));
            printer->Indent();
            CFieldGenerator* generator = field_genertors_.Get(field); 
            generator->GenerateCompareCAndCpp(printer);
            printer->Outdent();
            printer->Print("}\nbreak;\n");
        }
        printer->Print("}\n");
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
    
bool CMessageGenerator::
GenerateEncodeUnitTest(Printer* printer) {
    
    // protobuf编码测试
    printer->Print(
      "static $c_name$ msg_obj_c;\n"
      "memset(&msg_obj_c, 0, sizeof(msg_obj_c));\n"
      "$fill_c$(&msg_obj_c);\n"
      "int byte_size = $byte_size_long_func$(&msg_obj_c);\n"
      "std::string buff;\n"
      "buff.resize(byte_size);\n"
      "$cpp_name$ msg_obj_cpp;\n"
      "int ret = 0;\n"
      "if(byte_size > 0) {\n"
      " if (-1 != (ret = $serialize_func$(\n"
      "     &msg_obj_c, (uint8_t*)string_as_array(&buff), byte_size - 1))) {\n"
      "     std::cout << \"$serialize_func$ error:\" << \"buffer size not enough but did not check\" << std::endl;\n"
      "     return false;\n"
      " }\n"
      "}\n"
      "if (byte_size != (ret = $serialize_func$(\n"
      "  &msg_obj_c, (uint8_t*)string_as_array(&buff), byte_size))) {\n"
      "  std::cout << \"$serialize_func$ error:\" << \"byte_size_long ret \" << byte_size << \"; serialize_func ret \" << ret << std::endl;\n"
      "  return false;\n"
      "}\n"
      "msg_obj_cpp.ParseFromString(buff);\n"
      "if (!$compare_func$(&msg_obj_c, &msg_obj_cpp)) {\n"
      "  std::cout << \"$compare_func$ not pass\" << std::endl;\n"
      "  std::cout<<\"msg_obj_cpp:\\n\"<<msg_obj_cpp.DebugString()<<std::endl;"
      "  return false;\n"
      "}\n"
      
      // 比较pbc和pbc++对内容相同的c/c++结构体序列化出的包大小是否相等
      // 因为pb对序列化的顺序没有要求，故不比较内容
      "std::string buff_cpp;\n"
      "msg_obj_cpp.SerializeToString(&buff_cpp);\n"
      "if(buff_cpp.size() != byte_size) {\n"
      "  std::cout << \"$serialize_func$ error:\" << \"c serilaized string not equals to c++ serialized string\"<< std::endl;\n"
      "  std::cout << \"c size: \" << byte_size << \"c++ size: \" << buff_cpp.size() << std::endl;\n"
      "  return false;\n"
      "}\n",
      "cpp_name", GetCppStructFullName(descriptor_),
      "c_name", GetCStructName(descriptor_),
      "fill_cpp", GetFillCppFuncName(descriptor_),
      "fill_c", GetFillCFuncName(descriptor_),
      "parse_func", GetDecodeFuncName(descriptor_),
      "serialize_func", GetEncodeFuncName(descriptor_),
      "byte_size_long_func", GetEncodeFuncNameByteSizeLong(descriptor_),
      "compare_func", GetCompareCAndCppFuncName(descriptor_));
    
    
    // json接口的编码测试
    printer -> Print(
        // 使用pbc将c结构体编码为json字符串
        "// use pbc to encode an object to json string\n"
        "memset(&msg_obj_c, 0, sizeof(msg_obj_c));\n"
        "$fill_c$(&msg_obj_c);\n"
        "$cpp_name$ msg_obj_cpp_json;\n"
        "int buffer_len = 10000000;\n"
        "char* buffer = (char *)malloc(buffer_len);\n"
        "JSONPRINTOPTIONSPBC json_print_option;\n"
        "memset(&json_print_option, 0, sizeof(json_print_option));\n"
        "json_print_option.always_print_primitive_fields=true;\n"
        "json_print_option.preserve_proto_field_names=true;\n"
        "if ((ret = $to_json_func$(&msg_obj_c, buffer, buffer_len, json_print_option)) < 0) {\n"
        "   printf(\"[ERROR][%s][%d] $to_json_func$ error ret = [%d], please check\\n\", __FUNCTION__, __LINE__, ret);\n"
        "   return false;"
        "}\n"

        // 使用pbc++解码json字符串，测试pbc++能否解码pbc编码的json格式
        "// use pbc++ to decode the json string\n"
        "google::protobuf::util::JsonStringToMessage(buffer, &msg_obj_cpp_json);\n"
        "if (!$compare_func$(&msg_obj_c, &msg_obj_cpp_json)) {\n"
        "   std::cout << \"$compare_func$ not pass\" << std::endl;\n"
        "   printf(\"json string c: %s\\n\", buffer);\n"
        "   std::string json_string_cpp;\n"
        "   google::protobuf::util::JsonPrintOptions print_options;\n"
        "   print_options.always_print_enums_as_ints = true;\n"
        "   MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);\n"
        "   std::cout << \"json string cpp: \" << json_string_cpp << std::endl;\n"
        "   return false;\n"
        "}\n"

        // 使用pbc解码json字符串，测试pbc能否解码自己编码的json格式
        "// use pbc to decode the json string\n"
        "$c_name$ msg_obj_c_json;\n"
        "memset(&msg_obj_c_json, 0, sizeof(msg_obj_c_json));\n"
        "JSONPARSEOPTIONSPBC json_parse_option;\n"
        "memset(&json_parse_option, 0, sizeof(json_parse_option));\n"
        "if ((ret = $from_json_func$(buffer ,&msg_obj_c_json, json_parse_option)) < 0) {\n"
        "   printf(\"[ERROR][%s][%d] $from_json_func$ error ret = [%d], please check\\n\", __FUNCTION__, __LINE__, ret);\n"
        "   return false;"
        "}\n"
        "if (memcmp(&msg_obj_c, &msg_obj_c_json, sizeof(msg_obj_c)) !=0 ) {\n"
        "   std::cout<< \"error\" << std::endl;\n"
        "   return false;"
        "}"

        // 使用pbc解码json字符串，测试pbc能否解码自己编码的json格式
        // 使用url_encode_strings选项编码和解码
        "// use pbc to encode and decode the json string(with url_encode_strings option)\n"
        "memset(&json_print_option, 0, sizeof(json_print_option));\n"
        "json_print_option.always_print_primitive_fields=true;\n"
        "json_print_option.preserve_proto_field_names=true;\n"
        "json_print_option.url_encode_strings=true;\n"
        // "   printf(\"json: %s\\n\", buffer);\n"
        "if ((ret = $to_json_func$(&msg_obj_c, buffer, buffer_len, json_print_option)) < 0) {\n"
        "   printf(\"[ERROR][%s][%d] $to_json_func$ error ret = [%d], please check\\n\", __FUNCTION__, __LINE__, ret);\n"
        "   printf(\"error json: %s\", buffer);\n"
        "   return false;"
        "}\n"
        "memset(&msg_obj_c_json, 0, sizeof(msg_obj_c_json));\n"
        "memset(&json_parse_option, 0, sizeof(json_parse_option));\n"
        "json_parse_option.url_encode_strings=true;\n"
        "if ((ret = $from_json_func$(buffer ,&msg_obj_c_json, json_parse_option)) < 0) {\n"
        "   printf(\"[ERROR][%s][%d] $from_json_func$ error ret = [%d], please check\\n\", __FUNCTION__, __LINE__, ret);\n"
        "   printf(\"error json: %s\", buffer);\n"
        "   return false;"
        "}\n"
        "if (memcmp(&msg_obj_c, &msg_obj_c_json, sizeof(msg_obj_c)) !=0 ) {\n"
        "   std::cout<< \"error, msg_obj_c and msg_obj_c_json not equal\" << std::endl;\n"
        "   return false;"
        "}"

        // 比较pbc和pbc++生成的json字符串是否完全相同，此处暂时屏蔽，二者存在不影响相互编解码的差异
        // "std::string json_string_cpp;\n"
        // "google::protobuf::util::JsonPrintOptions print_options;\n"
        // "print_options.always_print_enums_as_ints = true;\n"
        // "MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);\n"
        // "if (std::string(buffer) != json_string_cpp) {\n"
        // "   printf(\"json string c: %s\\n\", buffer);\n"
        // "   std::cout << \"json string cpp: \" << json_string_cpp << std::endl;\n"
        // "}\n"

        "free(buffer);\n" ,

        "cpp_name", GetCppStructFullName(descriptor_),
        "fill_c", GetFillCFuncName(descriptor_),
        "to_json_func", GetJsonFuncNameEncode(descriptor_),
        "from_json_func", GetJsonFuncNameDecode(descriptor_),
        "c_name", GetCStructName(descriptor_),
        "assign_c2cpp", GetC2CppFunName(descriptor_),
        "compare_func", GetCompareCAndCppFuncName(descriptor_));
    return true;
}


bool CMessageGenerator::
GenerateDecodeUnitTest(Printer* printer) {
    printer->Print(
      "$cpp_name$ msg_obj_cpp;\n"
      "$fill_cpp$(&msg_obj_cpp);\n"
      "std::string buff;\n"
      "msg_obj_cpp.SerializeToString(&buff);\n"
      "static $c_name$ msg_obj_c;\n"
      "memset(&msg_obj_c, 0, sizeof(msg_obj_c));\n"
      "int ret = 0;\n"
      "if (0 != (ret = $parse_func$(\n"
      "  (unsigned char*)buff.c_str(), buff.size(), &msg_obj_c))) {\n"
      "  std::cout << \"$parse_func$ error:\" << ret << std::endl;\n"
      "  return false;\n"
      "}\n"
      "if (!$compare_func$(&msg_obj_c, &msg_obj_cpp)) {\n"
      "  std::cout << \"$compare_func$ not pass\" << std::endl;\n"
      "  std::cout<<\"msg_obj_cpp:\\n\"<<msg_obj_cpp.DebugString()<<std::endl;"
      "  return false;\n"
      "}\n", 
      "cpp_name", GetCppStructFullName(descriptor_),
      "c_name", GetCStructName(descriptor_),
      "fill_c", GetFillCFuncName(descriptor_),
      "fill_cpp", GetFillCppFuncName(descriptor_),
      "parse_func", GetDecodeFuncName(descriptor_),
      "compare_func", GetCompareCAndCppFuncName(descriptor_));

    // json接口的解码测试
    printer -> Print(
        // 使用pbc++将c++结构体编码为json字符串
        "// use pbc++ to encode an object to json string\n"
        "std::string json_string_cpp;\n"
        "google::protobuf::util::JsonPrintOptions print_options;\n"
        "print_options.always_print_enums_as_ints = true;\n"
        "MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);\n"

        // 使用pbc解码json字符串，测试pbc能否解码pbc++编码的json格式
        "// use pbc to decode the json string\n"
        "memset(&msg_obj_c, 0, sizeof(msg_obj_c));\n"
        "JSONPARSEOPTIONSPBC json_parse_option;\n"
        "memset(&json_parse_option, 0, sizeof(json_parse_option));\n"
        "if ((ret = $from_json_func$((char *)json_string_cpp.c_str() ,&msg_obj_c, json_parse_option)) < 0) {\n"
        "   printf(\"$from_json_func$ error ret = [%d]\\n\", ret);\n"
        "}\n"
        "if (!$compare_func$(&msg_obj_c, &msg_obj_cpp)) {\n"
        "  std::cout << \"$compare_func$ not pass\" << std::endl;\n"
        "  std::cout << \"json string cpp: \" << json_string_cpp << std::endl;"
        "  return false;\n"
        "}\n",        
        "to_json_func", GetJsonFuncNameEncode(descriptor_),
        "from_json_func", GetJsonFuncNameDecode(descriptor_),
        "c_name", GetCStructName(descriptor_),
        "assign_c2cpp", GetC2CppFunName(descriptor_),
        "compare_func", GetCompareCAndCppFuncName(descriptor_));

    // simple string输出测试
    // printer -> Print(
    //     "std::string buffer(msg_obj_cpp.DebugString().size() *10+ 10000,' ');\n"
    //     "int simple_string_ret = $c_name$SimpleString(&msg_obj_c,(char*)buffer.c_str(),msg_obj_cpp.DebugString().size() *10+ 10000 ,'|');\n"
    //     "if(simple_string_ret == -1){\n"
    //     "   printf(\"size not enough\\n\");\n"
    //     "}\n"
    //     "printf(\"$c_name$(%d): %s\\n\\n\\n\", simple_string_ret, buffer.c_str());\n"
    //     "for(int i=0;i<simple_string_ret;i++) {\n"
    //     "   printf(\"%c\", buffer[i]);\n"
    //     "}\n"
    //     "std::cout<<\"CPP: \"<<std::endl;\n"
    //     "std::cout<<msg_obj_cpp.DebugString();\n",

    //     "to_json_func", GetJsonFuncNameEncode(descriptor_),
    //     "from_json_func", GetJsonFuncNameDecode(descriptor_),
    //     "c_name", GetCStructName(descriptor_),
    //     "assign_c2cpp", GetC2CppFunName(descriptor_),
    //     "compare_func", GetCompareCAndCppFuncName(descriptor_));
    
    return true;
}

bool CMessageGenerator::
GenerateEncodeSpeedTest(Printer* printer) {
    map<string,string> vars;
    vars["cpp_name"] = GetCppStructFullName(descriptor_);
    vars["c_name"] = GetCStructName(descriptor_);
    vars["fill_c"] = GetFillCFuncName(descriptor_);
    vars["serialize_func"] = GetEncodeFuncName(descriptor_);
    vars["byte_size_long_func"] = GetEncodeFuncNameByteSizeLong(descriptor_);
    vars["assign_c2cpp"] = GetC2CppFunName(descriptor_);
    vars["loop_count"] = "10";
    vars["param_c_map"] = "c_map";
    vars["param_cpp_map"] = "cpp_map";

    printer->Print(vars,
        "std::chrono::high_resolution_clock::time_point current_time, start_time;\n"
        "std::chrono::milliseconds c_elapsed_time{}, cpp_elapsed_time{};\n"
        "int len1,len2;\n"
        "::google::protobuf::uint8* c_buffer;\n"
        "static $c_name$ c_message;\n"
        "$cpp_name$ cpp_message;\n"
        "std::string cpp_buffer;\n"
        "memset(&c_message, 0, sizeof(c_message)); //这个memset因为string的\\0, 而且数组下标是从0开始加的\n"
        "$fill_c$(&c_message);\n"
        "$assign_c2cpp$(c_message, cpp_message);\n"

        "len1 = $byte_size_long_func$(&c_message);\n"
        "c_buffer = ( ::google::protobuf::uint8*)malloc(len1);\n"
        "start_time = std::chrono::high_resolution_clock::now();\n"
        "for(int i = 0; i < $loop_count$; i++) {\n"
        "    len2 = $serialize_func$(&c_message, c_buffer, len1);\n"
        "}\n"
        "current_time = std::chrono::high_resolution_clock::now();\n"
        "c_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);\n"
        
        "start_time = std::chrono::high_resolution_clock::now();\n"
        "for(int i = 0; i < $loop_count$; i++) {\n"
        "     cpp_message.SerializeToString(&cpp_buffer);\n"
        "}\n"
        "current_time = std::chrono::high_resolution_clock::now();\n"
        "cpp_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);\n"
        
        "$param_c_map$[\"$c_name$\"] += c_elapsed_time;\n"
        "$param_cpp_map$[\"$cpp_name$\"] += cpp_elapsed_time;\n"
        "free(c_buffer);\n");
    return true;
}


bool CMessageGenerator::
GenerateDecodeSpeedTest(Printer* printer) {
    map<string,string> vars;
    vars["cpp_name"] = GetCppStructFullName(descriptor_);
    vars["c_name"] = GetCStructName(descriptor_);
    vars["fill_c"] = GetFillCFuncName(descriptor_);
    vars["parse_func"] = GetDecodeFuncName(descriptor_);
    vars["serialize_func"] = GetEncodeFuncName(descriptor_);
    vars["byte_size_long_func"] = GetEncodeFuncNameByteSizeLong(descriptor_);
    vars["assign_c2cpp"] = GetC2CppFunName(descriptor_);
    vars["loop_count"] = "100";
    vars["param_c_map"] = "c_map";
    vars["param_cpp_map"] = "cpp_map";

    printer->Print(vars,
        "std::chrono::high_resolution_clock::time_point current_time, start_time;\n"
        "std::chrono::milliseconds c_elapsed_time{}, cpp_elapsed_time{};\n"
        "int len1,len2;\n"
        "::google::protobuf::uint8* c_buffer;\n"
        "static $c_name$ c_message;\n"
        "$cpp_name$ cpp_message;\n"
        "std::string cpp_buffer;\n"
        "memset(&c_message, 0, sizeof(c_message)); //这个memset因为string的\\0, 而且数组下标是从0开始加的\n"
        "$fill_c$(&c_message);\n"
        "$assign_c2cpp$(c_message, cpp_message);\n"

        "len1 = $byte_size_long_func$(&c_message);\n"
        "c_buffer = ( ::google::protobuf::uint8*)malloc(len1);\n"
        "len2 = $serialize_func$(&c_message, c_buffer, len1);\n"
        "cpp_message.SerializeToString(&cpp_buffer);\n"
        
        "start_time = std::chrono::high_resolution_clock::now(); \n"
        "for(int i = 0; i < $loop_count$; i++) {\n"
        "    $parse_func$(c_buffer, len2, &c_message);\n"
        "}\n"
        "current_time = std::chrono::high_resolution_clock::now(); \n"
        "c_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);\n"
        
        "start_time = std::chrono::high_resolution_clock::now(); \n"
        "for(int i = 0; i < $loop_count$; i++) {\n"
        "     cpp_message.ParseFromString(cpp_buffer);\n"
        "}\n"
        "current_time = std::chrono::high_resolution_clock::now();"
        "cpp_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);\n"
      
        "$param_c_map$[\"$c_name$\"] += c_elapsed_time;\n"
        "$param_cpp_map$[\"$cpp_name$\"] += cpp_elapsed_time;\n"
        "free(c_buffer);\n");
    return true;
}

string CMessageGenerator::GetFillCFun() {
    return  "void " + GetFillCFuncName(descriptor_) + "(" + 
        GetCStructName(descriptor_) + "* " + vars_["param_c_var"] + 
        ")";
}
    
string CMessageGenerator::GetFillCppFun() {
    return  "void " + GetFillCppFuncName(descriptor_) + "(" + 
        GetCppStructFullName(descriptor_) + "* " + 
        vars_["param_cpp_var"] + ")";
}
    
string CMessageGenerator::GetFillFullCFun() {
    return  "void " + GetFillCFuncName(descriptor_) + "(" + 
        GetCStructName(descriptor_) + "* " + vars_["param_c_var"] + 
        ")";
}
    
string CMessageGenerator::GetFillFullCppFun() {
    return  "void " + GetFillCppFuncName(descriptor_) + "(" + 
        GetCppStructFullName(descriptor_) + "* " + 
        vars_["param_cpp_var"] + ")";
}
 

string CMessageGenerator::GetCompareCppFun() {
   return  "bool " + GetCompareCAndCppFuncName(descriptor_) + "(" + 
        GetCStructName(descriptor_) + "* " + 
        vars_["param_c_var"] + ", " + GetCppStructFullName(descriptor_) + 
        "* " + vars_["param_cpp_var"] + ")";
}

string CMessageGenerator::
GetDecodeFuncDeclaration(const Descriptor* descriptor) {
    return 
        "int32_t " + GetDecodeFuncName(descriptor) + "(\n" + 
        "  const uint8_t* data,\n" + 
        "  int size,\n" + 
        "  " + GetCStructName(descriptor) + 
        "* " + vars_["param_var"] +  ")";
}
 
string CMessageGenerator::
GetDecodeFuncDeclarationWithStream(const Descriptor* descriptor) {
    return 
        "int32_t " + GetDecodeFuncNameWithStream(descriptor) + "(\n" + 
        "  ::google::protobuf::io::CodedInputStream* input,\n" + 
        "  " + GetCStructName(descriptor) + "* " + 
        vars_["param_var"] +  ")";
}

    
string CMessageGenerator::
GetClearFuncDeclaration(const Descriptor* descriptor)
{
    return 
        "void " + GetClearFuncName(descriptor) + "(" + 
        GetCStructName(descriptor) + "* " + 
        vars_["param_var"] + ")";
}

string CMessageGenerator::
GetSetWritedFuncDeclaration(const Descriptor* descriptor)
{
    return 
        "void " + GetSetMessageWritedFuncName(descriptor) + "(" + 
        GetCStructName(descriptor) + "* " + 
        vars_["param_var"] + ")";
}

string CMessageGenerator::
GetEncodeFuncDeclaration(const Descriptor* descriptor) {
    return 
        "int " + GetEncodeFuncName(descriptor) + +"(\n" + 
        "  " + GetCStructName(descriptor) + "* " + 
        vars_["param_var"] +  ", uint8_t* buffer, int size)";
}

string CMessageGenerator::
GetEncodeFuncDeclarationWithCachedSize(const Descriptor* descriptor) {
    return 
        "int " + GetEncodeFuncNameWithCachedSize(descriptor) + +"(\n" + 
        "  const " + GetCStructName(descriptor) + "* " + 
        vars_["param_var"] +  
         ",  " + GetCCachedSizeStructName(descriptor) + "* " + 
         vars_["param_cached_size"] +", ::google::protobuf::uint8* buffer, int size)";
}

string CMessageGenerator::
GetEncodeFuncDeclarationByteSizeLong(const Descriptor* descriptor) {
    return 
        "int " + GetEncodeFuncNameByteSizeLong(descriptor) + +"(\n" + 
        "  " + GetCStructName(descriptor) + "* " + 
        vars_["param_var"] +  ")";
}

string CMessageGenerator::
GetEncodeFuncDeclarationByteSizeLongWithCachedSize(const Descriptor* descriptor) {
    return 
        "int " + GetEncodeFuncNameByteSizeLongWithCachedSize(descriptor) + +"(\n" + 
        "  " + GetCStructName(descriptor) + "* " + 
        vars_["param_var"] + 
        ",  " + GetCCachedSizeStructName(descriptor) + "* " + 
        vars_["param_cached_size"] + ")";
}


string CMessageGenerator::
GetStringFuncDeclaration(const Descriptor* descriptor) {
    return 
        "int " + GetStringFuncName(descriptor) + "(\n" + 
        GetCStructName(descriptor) + 
        "* " + vars_["param_var"]  + 
        ", char* buffer," + 
        " int size," +  
        " char delimiter)";
}

string CMessageGenerator::
GetJsonFuncDeclarationEncode(const Descriptor* descriptor) {
    return 
        "int32_t " + GetJsonFuncNameEncode(descriptor) + "(\n" + 
        GetCStructName(descriptor) + 
        "* " + vars_["param_var"]  + 
        ", char* buffer," + 
        " int size," + 
        " JSONPRINTOPTIONSPBC json_print_option)";
}

string CMessageGenerator::
GetJsonFuncDeclarationEncodeWithDocument(const Descriptor* descriptor) {
    return 
        "int32_t " + GetJsonFuncNameEncodeWithDocument(descriptor) + "(\n" + 
        GetCStructName(descriptor) + 
        "* " + vars_["param_var"]  + 
        ", rapidjson::Document* document, rapidjson::Document::AllocatorType* allocator,"+ 
        " JSONPRINTOPTIONSPBC json_print_option)";
}

string CMessageGenerator::
GetJsonFuncDeclarationDecode(const Descriptor* descriptor) {
    return 
        "int32_t " + GetJsonFuncNameDecode(descriptor) + "(\n" + 
        "const char* buffer, " + 
        GetCStructName(descriptor) + 
        "* " + vars_["param_var"]  + 
        ", JSONPARSEOPTIONSPBC json_parse_option)";
}

string CMessageGenerator::
GetJsonFuncDeclarationDecodeWithDocument(const Descriptor* descriptor) {
    return 
        "int32_t " + GetJsonFuncNameDecodeWithDocument(descriptor) + "(\n" + 
        "rapidjson::Document* document, " + 
        GetCStructName(descriptor) + 
        "* " + vars_["param_var"]  +
        ", JSONPARSEOPTIONSPBC json_parse_option)";;
}



bool CMessageGenerator::   
GenerateDecodeDeclaration(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetDecodeFuncDeclaration(descriptor_));
  return true;
}
    
bool CMessageGenerator::   
GenerateDecodeDeclarationWithStream(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetDecodeFuncDeclarationWithStream(descriptor_));
  return true;
}

bool CMessageGenerator::   
GenerateDecodeDefine(Printer* printer) {
    printer->Print("$func$ {\n", 
            "func", GetDecodeFuncDeclaration(descriptor_));
    printer->Indent();
    printer->Print(
            "::google::protobuf::io::CodedInputStream" 
            " input(data, size);\n "
            "return $func_stream_name$(&input, $msg_var$);\n",
            "func_stream_name", GetDecodeFuncNameWithStream(descriptor_),
            "msg_var", vars_["param_var"]);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CMessageGenerator::   
GenerateDecodeDefineWithStream(Printer* printer) {
    printer->Print("$func$ {\n", 
            "func", GetDecodeFuncDeclarationWithStream(descriptor_));
    printer->Indent();
    
    // 生成repeated 长度定义
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (field->is_repeated()) {
            printer->Print("int32_t $size$ = 0;\n", 
                    "size", GetRepeatedSizeName(field));
        }
    }

    printer->Print("::google::protobuf::uint32 tag;\n");
    printer->Print("for (;;) {\n") ;
    printer->Indent();

    string cut_off;
    if (GetFieldMaxNumber(descriptor_) <= 
            CBaseGenerator::kSingleByteTagMaxIndex) {
        cut_off = SimpleItoa(CBaseGenerator::kSingleByteTagMax);
    }
    else {
        cut_off = SimpleItoa(CBaseGenerator::kDoubleByteTagMax);
    }
    printer->Print(
            "::std::pair< ::google::protobuf::uint32, bool> p "
            "= input->ReadTagWithCutoffNoLastTag($cut_off$u);\n", 
            "cut_off", cut_off);
    printer->Print("tag = p.first;\n"
            "if (!p.second && 0 == tag) return 0;\n");
    printer->Print("switch (::google::protobuf"
            "::internal::WireFormatLite::GetTagFieldNumber(tag)) {\n");
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        //printer->Print("//$comment$", "comment", field->DebugString());
        printer->Print("case $case_value$: {\n", 
                "case_value", SimpleItoa(field->number()));
        printer->Indent();
         
        uint32_t tag = 
            google::protobuf::internal::WireFormat::MakeTag(field);
        printer->Print(
                "if (static_cast< ::google::protobuf::uint8>(tag) ==\n"
                "    static_cast< ::google::protobuf::uint8>("
                "$truncated$u /* $full$ & 0xFF */)) {\n",
                "truncated", SimpleItoa(tag & 0xFF),
                "full", SimpleItoa(tag));

        printer->Indent();
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateDecode(printer);
        printer->Outdent();
        printer->Print(
                "}\n"
                "else {\n");
        printer->Indent();
        PrintErrorLog(printer, 
                "buff type(%d) not match " + SimpleItoa(google::protobuf::internal::WireFormat::WireTypeForField(field)), 
                "tag&0x07");
        printer->Outdent();
        printer->Print(
                "  return -10$i$;\n"
                "}\n", "i", SimpleItoa(i));
        printer->Outdent();
        printer->Print("}\nbreak;\n");
    }
    printer->Print("default : {\n");
    printer->Indent();
    printer->Print("if (tag == 0) return 0;\n"
            "if (!::google::protobuf::internal::WireFormatLite::SkipField(input, tag)) {\n");
    printer->Indent();
    PrintErrorLog(printer, "SkipField failed tag(%d)", "tag");
    printer->Print("return -11;\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Outdent();
    printer->Print("}\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Outdent();
    printer->Print("return 0;\n");
    printer->Print("}\n\n");
  return true;
}

bool CMessageGenerator::   
GenerateStringDeclaration(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetStringFuncDeclaration(descriptor_));
  return true;
}

bool CMessageGenerator::   
GenerateStringDefine(Printer* printer) {

    printer->Print("$func$ {\n", 
        "func", GetStringFuncDeclaration(descriptor_));

    printer->Print("// @@protoc_insertion_point(message_debug_string_start:$full_name$)\n",
            "full_name",descriptor_->full_name());
    printer->Indent();
    printer->Print(
            "int buffer_size = size;\n"
            "int string_size = 0;\n");

    // 处理不在oneof中的字段
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (NULL != field->containing_oneof()) continue;
        PrintFieldComment(printer, field);
        bool have_enclosing_if = EmitFieldNonDefaultCondition(
                printer, vars_["param_var"]+"->", field);
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateString(printer);
        if (have_enclosing_if) {
            printer->Outdent();
            printer->Print(
                    "}\n"
                    "\n");
        }
    }

    // 处理oneof中的字段 
    string enumfieldvalue;
    for (int i = 0; i < descriptor_->oneof_decl_count(); i++) { 
        printer->Print(
                "switch ($param_var$->$unionvarname$()) {\n",
                "unionvarname", GetCStructUnionSelectVarName(descriptor_->oneof_decl(i)),
                "param_var", vars_["param_var"]);
        printer->Indent();
        for (int j = 0; j < descriptor_->oneof_decl(i)->field_count(); j++) {
            const FieldDescriptor* field = descriptor_->oneof_decl(i)->field(j);
            PrintFieldComment(printer, field);

#ifdef UNION_NORAML
            enumfieldvalue = GetCUnionEnumFieldName(field);
#else
            enumfieldvalue = GetCUnionFieldIDName(field);
#endif
            printer->Print("case $enumfieldvalue$: {\n",
                    "enumfieldvalue",enumfieldvalue);
            printer->Indent();
            
            CFieldGenerator* filed_generator = field_genertors_.Get(field);
            filed_generator->GenerateString(printer);

            printer->Print(
                    "break;\n");
            printer->Outdent();
            printer->Print(
                    "}\n");
        }

        printer->Outdent();
        printer->Print(
                "}\n");
    }
    printer->Print(
                "if(size != buffer_size) {\n"
                "   buffer--;\n"
                "   buffer_size++;\n"
                "}\n"
                "buffer[0] = '\\0';\n"
                "return size - buffer_size;\n");
    printer->Outdent();
    printer->Print("}\n\n");
    return true;
}

bool CMessageGenerator::   
GenerateJsonDeclarationEncode(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetJsonFuncDeclarationEncode(descriptor_));
  return true;
}

bool CMessageGenerator::   
GenerateJsonDeclarationEncodeWithDocument(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetJsonFuncDeclarationEncodeWithDocument(descriptor_));
  return true;
}

bool CMessageGenerator::   
GenerateJsonDeclarationDecodeWithDocument(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetJsonFuncDeclarationDecodeWithDocument(descriptor_));
  return true;
}

bool CMessageGenerator::   
GenerateJsonDeclarationDecode(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetJsonFuncDeclarationDecode(descriptor_));
  return true;
}

bool CMessageGenerator::   
GenerateJsonDefineEncodeWithDocument(Printer* printer) {
    printer->Print("$func$ {\n", 
        "func", GetJsonFuncDeclarationEncodeWithDocument(descriptor_));
    printer->Print("// @@protoc_insertion_point(message_debug_string_start:$full_name$)\n",
            "full_name",descriptor_->full_name());
    printer->Indent();
    // 处理不在oneof中的字段
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (NULL != field->containing_oneof()) continue;
        PrintFieldComment(printer, field);
        bool have_enclosing_if = EmitFieldNonDefaultConditionJson(
                printer, vars_["param_var"]+"->", field);
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateJsonEncode(printer);
        if (have_enclosing_if) {
            printer->Outdent();
            printer->Print(
                    "}\n"
                    "\n");
        }
    }

    // 处理oneof中的字段 
    string enumfieldvalue;
    for (int i = 0; i < descriptor_->oneof_decl_count(); i++) { 
        printer->Print(
                "switch ($param_var$->$unionvarname$()) {\n",
                "unionvarname", GetCStructUnionSelectVarName(descriptor_->oneof_decl(i)),
                "param_var", vars_["param_var"]);
        printer->Indent();
        for (int j = 0; j < descriptor_->oneof_decl(i)->field_count(); j++) {
            const FieldDescriptor* field = descriptor_->oneof_decl(i)->field(j);
            PrintFieldComment(printer, field);

#ifdef UNION_NORAML
            enumfieldvalue = GetCUnionEnumFieldName(field);
#else
            enumfieldvalue = GetCUnionFieldIDName(field);
#endif
            printer->Print("case $enumfieldvalue$: {\n",
                    "enumfieldvalue",enumfieldvalue);
            printer->Indent();
            
            CFieldGenerator* filed_generator = field_genertors_.Get(field);
            filed_generator->GenerateJsonEncode(printer);

            printer->Print(
                    "break;\n");
            printer->Outdent();
            printer->Print(
                    "}\n");
        }

        printer->Outdent();
        printer->Print(
                "}\n");
    }
    printer->Print("return 0;\n");
    printer->Outdent();
    printer->Print("}\n\n");
    return true;
}

bool CMessageGenerator::   
GenerateJsonDefineEncode(Printer* printer) {
    printer->Print("$func$ {\n", 
        "func", GetJsonFuncDeclarationEncode(descriptor_));

    printer->Print("// @@protoc_insertion_point(message_debug_string_start:$full_name$)\n",
            "full_name",descriptor_->full_name());
    printer->Indent();
    printer->Print(
            "rapidjson::Document document;\n"
            "document.SetObject();\n"
            "rapidjson::Document::AllocatorType& allocator = document.GetAllocator();\n"
            "int32_t func_ret = $func$($msg_var$, &document, &allocator, json_print_option);\n"
            "if(func_ret < 0) {\n"
            "   return func_ret;\n"
            "}\n"
            "rapidjson::StringBuffer sb;\n"
            "rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);\n"
            "writer.SetIndent(' ', 1);\n"
            "document.Accept(writer);\n"
            "int32_t ret_value = snprintf(buffer, size, \"%s\", sb.GetString());\n"
            "if(ret_value >= size) {\n",
            "func", GetJsonFuncNameEncodeWithDocument(descriptor_),
            "msg_var", vars_["param_var"]);
    PrintErrorLog(printer, "  %d.%d json string length >= buffer size, please check", "ret_value", "size");
    printer->Print(
            "   return -1;\n"
            "}\n"
            "return ret_value;\n");
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CMessageGenerator::   
GenerateJsonDefineDecode(Printer* printer) {
    printer->Print("$func$ {\n", 
        "func", GetJsonFuncDeclarationDecode(descriptor_));

    printer->Print("// @@protoc_insertion_point(message_debug_string_start:$full_name$)\n",
            "full_name",descriptor_->full_name());
    printer->Indent();
    printer->Print(
            "rapidjson::Document document;\n"
            "document.SetObject();\n"
            "if(document.Parse(buffer).HasParseError()) {\n");
    PrintErrorLog(printer, "%u.%s parse error, please check", "(unsigned)document.GetErrorOffset()", "GetParseError_En(document.GetParseError())");
    printer->Print(
            "    return -1;\n"
            "}\n"
            "return $func$(&document, $msg_var$, json_parse_option);\n",
            "func", GetJsonFuncNameDecodeWithDocument(descriptor_),
            "msg_var", vars_["param_var"]);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CMessageGenerator::   
GenerateJsonDefineDecodeWithDocument(Printer* printer) {
    printer->Print("$func$ {\n", 
        "func", GetJsonFuncDeclarationDecodeWithDocument(descriptor_));

    printer->Print("// @@protoc_insertion_point(message_debug_string_start:$full_name$)\n",
            "full_name",descriptor_->full_name());
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        
        PrintFieldComment(printer, field);

        // 在代码生成阶段判断json_name和field_name是否相等
        // 如果不相等，json的解码需要能处理两者中的任一个
        if(field->json_name() == field->name()) {
            printer->Print(
                "if(document->HasMember(\"$field_name$\") && !(*document)[\"$field_name$\"].IsNull()) {\n"
                "   rapidjson::Value& json_value = (*document)[\"$field_name$\"];\n", 
                "field_name", field->name());
        } else {
            printer->Print(
                "if((document->HasMember(\"$json_name$\") && !(*document)[\"$json_name$\"].IsNull())|| (document->HasMember(\"$field_name$\") && !(*document)[\"$field_name$\"].IsNull())) {\n"
                "   rapidjson::Value& json_value = (document->HasMember(\"$json_name$\") ? (*document)[\"$json_name$\"] : (*document)[\"$field_name$\"]);\n",
                "json_name", field->json_name(), 
                "field_name", field->name());
        }

        printer->Indent();
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateJsonDecode(printer);
        printer->Outdent();
        printer->Print("}\n");
    }

    printer->Print("return 0;\n");
    printer->Outdent();
    printer->Print("}\n\n");
  return true;
}

bool CMessageGenerator::GenerateClearDeclaration(Printer* printer) {
    printer->Print("$func$;\n",
            "func", GetClearFuncDeclaration(descriptor_));
    return true;
}

bool CMessageGenerator::GenerateSetWritedDeclaration(Printer* printer) {
    printer->Print("$func$;\n",
            "func", GetSetWritedFuncDeclaration(descriptor_));
    return true;
}
    
bool CMessageGenerator::GenerateSetWritedDefine(Printer* printer) {
    printer->Print("$func$ {\n", 
            "func", GetSetWritedFuncDeclaration(descriptor_));
    printer->Indent();
    
    // 1、先处理oneof字段
    for (int i = 0; i < descriptor_->oneof_decl_count(); i++) { 
        printer->Print(
                "switch ($param_var$->$unionvarname$()) {\n",
                "unionvarname", GetCStructUnionSelectVarName(descriptor_->oneof_decl(i)),
                "param_var", vars_["param_var"]);
        printer->Indent();
        for (int j = 0; j < descriptor_->oneof_decl(i)->field_count(); j++) {
            const FieldDescriptor* field = descriptor_->oneof_decl(i)->field(j);
            string enumfieldvalue;
            enumfieldvalue = GetCUnionFieldIDName(field);
            printer->Print("case $enumfieldvalue$: {\n",
                    "enumfieldvalue",enumfieldvalue);
            printer->Indent();
            
            CFieldGenerator* filed_generator = field_genertors_.Get(field);
            filed_generator->GenerateSetWrited(printer);

            printer->Print("break;\n");
            printer->Outdent();
            printer->Print("}\n");
        }
        printer->Print("default: \nbreak;\n");

        printer->Outdent();
        printer->Print("}\n");
    }

    // 2、处理非oneof字段
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (NULL != field->containing_oneof()) continue;
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateSetWrited(printer);
    }
    printer->Outdent();
    printer->Print("}\n\n");
    return true;
}
    
bool CMessageGenerator::GenerateClearDefine(Printer* printer)
{
    printer->Print("$func$ {\n", 
            "func", GetClearFuncDeclaration(descriptor_));
    printer->Indent();
    
    // 1、先处理oneof字段
    for (int i = 0; i < descriptor_->oneof_decl_count(); i++) { 
        printer->Print(
                "switch ($param_var$->$unionvarname$()) {\n",
                "unionvarname", GetCStructUnionSelectVarName(descriptor_->oneof_decl(i)),
                "param_var", vars_["param_var"]);
        printer->Indent();
        for (int j = 0; j < descriptor_->oneof_decl(i)->field_count(); j++) {
            const FieldDescriptor* field = descriptor_->oneof_decl(i)->field(j);
            string enumfieldvalue;
            enumfieldvalue = GetCUnionFieldIDName(field);
            printer->Print("case $enumfieldvalue$: {\n",
                    "enumfieldvalue",enumfieldvalue);
            printer->Indent();
            
            CFieldGenerator* filed_generator = field_genertors_.Get(field);
            filed_generator->GenerateClear(printer);

            printer->Print("break;\n");
            printer->Outdent();
            printer->Print("}\n");
        }
        printer->Print(
                "default: \n"
                "   memset(&$param_var$->$oneof_var$, 0, sizeof($param_var$->$oneof_var$));\n"
                "break;\n",
                "param_var", vars_["param_var"], 
                "oneof_var", GetCStructUnionFieldVarName(descriptor_->oneof_decl(i)));

        printer->Outdent();
        printer->Print("}\n");
    }

    // 2、处理非oneof字段
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (NULL != field->containing_oneof()) continue;
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateClear(printer);
    }
    printer->Outdent();
    printer->Print("}\n\n");
  return true;
}


bool CMessageGenerator::
GenerateEncodeDeclaration(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetEncodeFuncDeclaration(descriptor_));
  return true;
}

bool CMessageGenerator::
GenerateEncodeDeclarationWithCachedSize(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetEncodeFuncDeclarationWithCachedSize(descriptor_));
  return true;
}

bool CMessageGenerator::
GenerateEncodeDeclarationByteSizeLong(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetEncodeFuncDeclarationByteSizeLong(descriptor_));
  return true;
}

bool CMessageGenerator::
GenerateEncodeDeclarationByteSizeLongWithCachedSize(Printer* printer) {
    printer->Print("$func$;\n", 
            "func", GetEncodeFuncDeclarationByteSizeLongWithCachedSize(descriptor_));
  return true;
}

bool CMessageGenerator::
GenerateEncodeDefine(Printer* printer) {
    printer->Print("$func$ {\n", 
            "func", GetEncodeFuncDeclaration(descriptor_));
    printer->Indent();
    printer->Print(
            "$cached_size_type$ cached_size;\n"
            "int32_t obj_size = $func_byte_size_long_name$($msg_var$, &cached_size);\n"
            "if (obj_size < 0 || obj_size > size) {\n",
            "cached_size_type", GetCCachedSizeStructName(descriptor_),
            "func_byte_size_long_name", GetEncodeFuncNameByteSizeLongWithCachedSize(descriptor_),
            "msg_var", vars_["param_var"]);
    printer->Indent();
    PrintErrorLog(printer,  "buff(%d) less than obj size(%d), or obj size < 0",  "size", "obj_size");
    printer->Print("return -1;\n");
    printer->Outdent();
    printer->Print(
            "}\n"
            "return $func_encode_name$($msg_var$, &cached_size, (::google::protobuf::uint8*)buffer, size);\n",
            "func_encode_name", GetEncodeFuncNameWithCachedSize(descriptor_),
            "msg_var", vars_["param_var"]);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CMessageGenerator::
GenerateEncodeDefineWithCachedSize(Printer* printer) {
    printer->Print("$func$ {\n", 
            "func", GetEncodeFuncDeclarationWithCachedSize(descriptor_));
    printer->Indent();

    printer->Print(
        "// @@protoc_insertion_point(serialize_to_array_start:$full_name$)\n",
        "full_name", descriptor_->full_name());

    printer->Print(
            "int32_t used_size = 0;\n"
            "int32_t temp_sub_message_size = 0;\n"
            "(void)temp_sub_message_size;\n"
            "\n");

    // 处理不在oneof中的字段
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (NULL != field->containing_oneof()) continue;
        PrintFieldComment(printer, field);
        bool have_enclosing_if = EmitFieldNonDefaultCondition(
                printer, vars_["param_var"]+"->", field);
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateEncode(printer);
        if (have_enclosing_if) {
            printer->Outdent();
            printer->Print(
                    "}\n"
                    "\n");
        }
    }

    // 处理oneof中的字段 
    string enumfieldvalue;
    for (int i = 0; i < descriptor_->oneof_decl_count(); i++) { 
        printer->Print(
                "switch ($param_var$->$unionvarname$()) {\n",
                "unionvarname", GetCStructUnionSelectVarName(descriptor_->oneof_decl(i)),
                "param_var", vars_["param_var"]);
        printer->Indent();
        for (int j = 0; j < descriptor_->oneof_decl(i)->field_count(); j++) {
            const FieldDescriptor* field = descriptor_->oneof_decl(i)->field(j);
            PrintFieldComment(printer, field);

#ifdef UNION_NORAML
            enumfieldvalue = GetCUnionEnumFieldName(field);
#else
            enumfieldvalue = GetCUnionFieldIDName(field);
#endif
            printer->Print("case $enumfieldvalue$: {\n",
                    "enumfieldvalue",enumfieldvalue);
            printer->Indent();
            
            CFieldGenerator* filed_generator = field_genertors_.Get(field);
            filed_generator->GenerateEncode(printer);

            printer->Print(
                    "break;\n");
            printer->Outdent();
            printer->Print(
                    "}\n");
        }

        printer->Outdent();
        printer->Print(
                "}\n");
    }

   
    printer->Print(
            "return used_size;\n");
        
    printer->Print(
        "// @@protoc_insertion_point(serialize_to_array_end:$full_name$)\n",
        "full_name", descriptor_->full_name());

    printer->Outdent();
    printer->Print("}\n\n");
  return true;
}


bool CMessageGenerator::
GenerateEncodeDefineByteSizeLong(Printer* printer) {
    printer->Print("$func$ {\n", 
            "func", GetEncodeFuncDeclarationByteSizeLong(descriptor_));
    printer->Indent();
    printer->Print(
            "$cached_size_type$ cached_size;\n"
            "return $func_byte_size_long_name$($msg_var$, &cached_size);\n", 
            "cached_size_type", GetCCachedSizeStructName(descriptor_),
            "func_byte_size_long_name", GetEncodeFuncNameByteSizeLongWithCachedSize(descriptor_),
            "msg_var", vars_["param_var"]);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}


bool CMessageGenerator::
GenerateEncodeDefineByteSizeLongWithCachedSize(Printer* printer) {
    printer->Print("$func$ {\n", 
        "func", GetEncodeFuncDeclarationByteSizeLongWithCachedSize(descriptor_));
    printer->Print("// @@protoc_insertion_point(message_byte_size_start:$full_name$)\n",
            "full_name",descriptor_->full_name());
    printer->Indent();
    printer->Print(
            "int32_t total_size = 0;\n"
            "int32_t temp_sub_message_size = 0;\n"
            "(void)temp_sub_message_size;\n"
            "\n");

    // 处理不在oneof中的字段
    for (int i = 0; i < descriptor_->field_count(); i++) {
        const FieldDescriptor* field = descriptor_->field(i);
        if (NULL != field->containing_oneof()) continue;
        PrintFieldComment(printer, field);
        bool have_enclosing_if = EmitFieldNonDefaultCondition(
                printer, vars_["param_var"]+"->", field);
        CFieldGenerator* filed_generator = field_genertors_.Get(field);
        filed_generator->GenerateEncodeByteSizeLong(printer);
        if (have_enclosing_if) {
            printer->Outdent();
            printer->Print(
                    "}\n"
                    "\n");
        }
    }

    // 处理oneof中的字段 
    string enumfieldvalue;
    for (int i = 0; i < descriptor_->oneof_decl_count(); i++) { 
        printer->Print(
                "switch ($param_var$->$unionvarname$()) {\n",
                "unionvarname", GetCStructUnionSelectVarName(descriptor_->oneof_decl(i)),
                "param_var", vars_["param_var"]);
        printer->Indent();
        for (int j = 0; j < descriptor_->oneof_decl(i)->field_count(); j++) {
            const FieldDescriptor* field = descriptor_->oneof_decl(i)->field(j);
            PrintFieldComment(printer, field);

#ifdef UNION_NORAML
            enumfieldvalue = GetCUnionEnumFieldName(field);
#else
            enumfieldvalue = GetCUnionFieldIDName(field);
#endif
            printer->Print("case $enumfieldvalue$: {\n",
                    "enumfieldvalue",enumfieldvalue);
            printer->Indent();
            
            CFieldGenerator* filed_generator = field_genertors_.Get(field);
            filed_generator->GenerateEncodeByteSizeLong(printer);

            printer->Print(
                    "break;\n");
            printer->Outdent();
            printer->Print(
                    "}\n");
        }

        printer->Outdent();
        printer->Print(
                "}\n");
    }

    printer->Print(vars_,
            "$param_cached_size$->cached_size_ = total_size;\n");
    printer->Print(
            "return total_size;\n");

    printer->Outdent();
    printer->Print("}\n\n");
  return true;
}
    
    
bool CMessageGenerator::
GenerateC2CppDefine(Printer* printer) {

    printer->Print(vars_,
            "inline bool $c_2_cpp_fun$(const $c_name$& $param_c_var$, $cpp_name$& $param_cpp_var$) {\n");
    printer->Indent();

    // 先遍历非oneof成员
    for (size_t i = 0; i < fields_.size(); i++) {
        const FieldDescriptor* field = fields_[i];
        printer->Print("{\n");
        printer->Indent();
        CFieldGenerator* generator = field_genertors_.Get(field); 
        generator->GenerateAssignCToCpp(printer);
        printer->Outdent();
        printer->Print("}\n");
    }

    // 遍历oneof成员
    map<const OneofDescriptor*, 
        vector<const FieldDescriptor*> >::iterator it; 
    for (it = oneof_fields_.begin(); 
            it != oneof_fields_.end(); ++it) {
        printer->Print("{\n");
        printer->Print(
          "switch ($param_c_var$.$oneof_select$()) {\n", 
          "param_c_var", vars_["param_c_var"], 
          "oneof_select", GetCStructUnionSelectVarName(it->first));
        printer->Indent();
        for (size_t i = 0; i < it->second.size(); i++) {
            const FieldDescriptor* field = it->second[i];
            printer->Print(
              "case $value$:{\n",
              "value", GetCUnionFieldIDName(field));
            printer->Indent();
            CFieldGenerator* generator = field_genertors_.Get(field); 
            generator->GenerateAssignCToCpp(printer);
            printer->Outdent();
            printer->Print("}\nbreak;\n");
        }
        printer->Print("}\n");
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
    
bool CMessageGenerator::
GenerateCpp2CDefine(Printer* printer) {

    printer->Print(vars_,
            "inline bool $cpp_2_c_fun$(const $cpp_name$& $param_cpp_var$, $c_name$& $param_c_var$) {\n");
    printer->Indent();

    // 先遍历非oneof成员
    for (size_t i = 0; i < fields_.size(); i++) {
        const FieldDescriptor* field = fields_[i];
        printer->Print("{\n");
        printer->Indent();
        CFieldGenerator* generator = field_genertors_.Get(field); 
        generator->GenerateAssignCppToC(printer);
        printer->Outdent();
        printer->Print("}\n");
    }

    // 遍历oneof成员
    map<const OneofDescriptor*, 
        vector<const FieldDescriptor*> >::iterator it; 
    for (it = oneof_fields_.begin(); 
            it != oneof_fields_.end(); ++it) {
        printer->Print("{\n");
        printer->Print(
          "switch ($param_cpp_var$.$oneof_select$()) {\n", 
          "param_cpp_var", vars_["param_cpp_var"], 
          "oneof_select", GetCppUnionCaseFun(it->first));
        printer->Indent();
        for (size_t i = 0; i < it->second.size(); i++) {
            const FieldDescriptor* field = it->second[i];
            printer->Print(
              "case $value$:{\n",
              "value", GetCppUnionFieldCase(field));
            printer->Indent();
            CFieldGenerator* generator = field_genertors_.Get(field); 
            generator->GenerateAssignCppToC(printer);
            printer->Print(
                    "$param_c_var$.set_$oneof_select$($field_id$);\n", 
                    "param_c_var", vars_["param_c_var"], 
                    "oneof_select", GetCStructUnionSelectVarName(it->first),
                    "field_id", GetCUnionFieldIDName(field));
            printer->Outdent();
            printer->Print("}\nbreak;\n");
        }
        printer->Print(
                "case $field_unset_case$:\n break;\n",
                "field_unset_case", GetCppUnionFieldUnsetCase(it->first));
        printer->Print("}\n");
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
