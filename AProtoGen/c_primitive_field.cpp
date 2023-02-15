
#include "mathlimits.h"
#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"
#include "c_primitive_field.h"
CPrimitiveFieldGenerator::CPrimitiveFieldGenerator(
        const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
    SetCommVar(descriptor_, &vars_);
    vars_["rand"] = vars_["c_name"] + "_rand"; 
    vars_["type"] = GetCPrimitiveType(descriptor_);
    vars_["cpptype"] = PrimitiveTypeName(descriptor_->cpp_type());
    vars_["wire_format_field_type"] = 
        "::google::protobuf::internal::WireFormatLite::" +
        FieldDescriptorProto_Type_Name(
                static_cast<FieldDescriptorProto_Type>(
                    descriptor_->type()));
    vars_["declared_type"] = DeclaredTypeMethodNamePrefix(descriptor_->type());
    switch(descriptor_->cpp_type()) {
        case FieldDescriptor::CPPTYPE_INT32:
            vars_["max"] = "2147483647";
            vars_["min"] = "-2147483648";
            break;
        case FieldDescriptor::CPPTYPE_UINT32:
            vars_["max"] = "4294967295";
            vars_["min"] = "0";
            break;
        case FieldDescriptor::CPPTYPE_INT64:
            vars_["max"] = "9223372036854775807"; 
            vars_["min"] = "-9223372036854775808";
            break;
        case FieldDescriptor::CPPTYPE_UINT64:
            vars_["max"] = "18446744073709551615"; 
            vars_["min"] = "0";
            break;
        case FieldDescriptor::CPPTYPE_FLOAT:
            vars_["max"] = "3.40282e+38"; 
            vars_["min"] = "1.17549e-38";
            break;
        case FieldDescriptor::CPPTYPE_DOUBLE:
            vars_["max"] = "1.79769e+308"; 
            vars_["min"] = "2.22507e-308";
            break;
        default:
            break;
    }
    if ("int8_t" == vars_["type"]) {
        vars_["max"] = "127"; 
        vars_["min"] = "-128";
    } else if ("uint8_t" == vars_["type"]) {
        vars_["max"] = "255"; 
        vars_["min"] = "0";
    } else if ("int16_t" == vars_["type"]) {
        vars_["max"] = "32767"; 
        vars_["min"] = "-32768";
    }else if ("uint16_t" == vars_["type"]) {
        vars_["max"] = "65535"; 
        vars_["min"] = "0";
    }
    vars_["format"] = GetCPrimitiveTypePrintFormat(descriptor_);
    vars_["json_type"] = GetPrimitiveTypeJsonType(descriptor_);
    
}
    
bool CPrimitiveFieldGenerator::
GenerateClear(Printer* printer)
{
    printer->Print(vars_,
            "$param_var$->$field_name$ = 0;\n");
    return true;
}

bool CPrimitiveFieldGenerator::
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "$type$* temp = &$param_var$->$field_name$;\n");
    GenerateReadPrimitive("temp", descriptor_, printer);
    return true;
}

bool  CPrimitiveFieldGenerator::
GenerateEncode(Printer* printer) {
    int fixed_size = FixedSize(descriptor_->type());
    if (fixed_size == -1) {
        printer->Print(vars_,
                "used_size += $tag_size$ +\n"
                "  ::google::protobuf::internal::WireFormatLite::$declared_type$Size(\n"
                "    $non_null_ptr_to_name$);\n");
    } else {
        vars_["fixed_size"] = StrCat(fixed_size);
        printer->Print(vars_,
                "used_size += $tag_size$ + $fixed_size$;\n");
    }

    printer->Print("if(used_size > size) {\n"
                    "   return -1;\n"
                    "}\n");

    printer->Print(vars_,
        "buffer = ::google::protobuf::internal::WireFormatLite::Write$declared_type$ToArray("
        "$field_number$, $non_null_ptr_to_name$, buffer);\n");
    
	return true;
}

bool CPrimitiveFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    int fixed_size = FixedSize(descriptor_->type());
    if (fixed_size == -1) {
        printer->Print(vars_,
                "total_size += $tag_size$ +\n"
                "  ::google::protobuf::internal::WireFormatLite::$declared_type$Size(\n"
                "    $non_null_ptr_to_name$);\n");
    } else {
        vars_["fixed_size"] = StrCat(fixed_size);
        printer->Print(vars_,
                "total_size += $tag_size$ + $fixed_size$;\n");
    }
	return true;
}

bool CPrimitiveFieldGenerator::
GenerateString(Printer* printer) {
    printer->Print(vars_,
            "string_size = snprintf(buffer, buffer_size, \"$format$%c\", $non_null_ptr_to_name$, delimiter);\n"
            "if(string_size > buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");
	return true;
}

bool CPrimitiveFieldGenerator::
GenerateStringTlog(Printer* printer) {
    GenerateString(printer);
	return true;
}

bool CPrimitiveFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    // protobuff官方转json将 int64、uint64类型转成string， 因为json的标准中不支持这两种类型，此处和官方保持一致
    printer->Print("rapidjson::Value json_value;\n");
    if(vars_["json_type"] == "Int64" || vars_["json_type"] == "Uint64") {
        printer->Print(vars_,
            "std::string temp_string = ::google::protobuf::SimpleItoa($non_null_ptr_to_name$);\n"
            "json_value.SetString(rapidjson::StringRef(temp_string.c_str(), temp_string.size()), *allocator);\n");
    }
    else {
        // 用message中定义的类型而不是c类型编码
        printer->Print(vars_,
            "json_value.Set$json_type$($non_null_ptr_to_name$);\n");
    }
    PrintJsonAddMember(printer, &vars_);
	return true;
}

bool CPrimitiveFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    if(vars_["json_type"] == "Int64" || vars_["json_type"] == "Uint64") {
        printer->Print(vars_,
            "if (!json_value.IsString()) {\n");
        printer->Indent();
        PrintErrorLog(printer, "%s json value type error, it is supposed to be a string, please check", DoubleQuotesStr(vars_["field_name"]));
        printer->Print("return -2;\n");
        printer->Outdent();
        printer->Print("}\n");
        if(vars_["json_type"] == "Int64") {
            printer->Print(vars_,
                "$non_null_ptr_to_name$ = atoll(json_value.GetString());\n");
        }
        else {
            printer->Print(vars_,
                "$non_null_ptr_to_name$ = strtoull(json_value.GetString(), NULL, 10);\n");
        }
    } else {
        printer->Print(vars_,
            "if(!json_value.Is$json_type$()) {\n");
        printer->Indent();
        PrintErrorLog(printer, "%s.%s json value type error, please check", DoubleQuotesStr(vars_["field_name"]), DoubleQuotesStr(vars_["json_type"]));
        printer->Print("return -3;\n");
        printer->Outdent();
            
        printer->Print(vars_,
            "}\n"
            "$non_null_ptr_to_name$ = json_value.Get$json_type$();\n");
    }
	return true;
}

void CPrimitiveFieldGenerator::
GenerateReadPrimitive(const string& var_name,
                      const FieldDescriptor* field,
                      Printer* printer) {
    vars_["var_name"]  = var_name;
    printer->Print(vars_,
      "$cpptype$ value;\n"
      "if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<\n"
      "   $cpptype$, $wire_format_field_type$>(input, &value)) return -2;\n"
      "*$var_name$ = static_cast<$type$>(value);\n");
}

void CPrimitiveFieldGenerator::
GenerateRandom(Printer* printer) {
     switch(descriptor_->cpp_type()) {
        case FieldDescriptor::CPPTYPE_INT32:
        case FieldDescriptor::CPPTYPE_UINT32:
        case FieldDescriptor::CPPTYPE_INT64:
        case FieldDescriptor::CPPTYPE_UINT64:
            printer->Print(vars_, 
              "$c_type$ $rand$ = random()%($max$ULL-($min$ULL))+($min$ULL);\n");
            break;
        case FieldDescriptor::CPPTYPE_FLOAT:
        case FieldDescriptor::CPPTYPE_DOUBLE:
            printer->Print(vars_, 
              "$c_type$ $rand$ = ($max$-($min$))*\n"
              "  (($c_type$)random()/RAND_MAX)+($min$);\n");
            break;
       default:
            break;
    }
}

bool CPrimitiveFieldGenerator::
GenerateAutoFillC(Printer* printer) {
    GenerateRandom(printer);
    printer->Print(vars_,
      "$param_c_var$->set_$cpp_name$($rand$);\n"); 
    return true;
}
    
bool CPrimitiveFieldGenerator::
GenerateAutoFillCpp(Printer* printer) {
    GenerateRandom(printer);
    printer->Print(vars_, 
      "$param_cpp_var$->set_$cpp_name$($rand$);\n"); 
    return true;
}
    
bool CPrimitiveFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    printer->Print(vars_, 
            "if (fabs($param_cpp_var$->$cpp_name$() - "
            "$param_c_var$->$cpp_name$()) > 0.000001) {\n"
            "  std::cout << \"$parent_type$::$c_name$ not equal [c:\"\n"
            "       << $param_c_var$->$cpp_name$() << \", cpp:\"\n"
            "       << $param_cpp_var$->$cpp_name$()\n" 
            "       << \"]\" << std::endl;\n" 
            "  return false;\n"
            "}\n");
    return true;
}
    
string CPrimitiveFieldGenerator::
GetRandomNumber(const FieldDescriptor* descriptor) {
    switch(descriptor->cpp_type()) {
        case FieldDescriptor::CPPTYPE_INT32: 
            return SimpleItoa(
                    (signed int)(rand() % 
                        MathLimits<signed int>::kMax)); 
        case FieldDescriptor::CPPTYPE_UINT32: 
            return SimpleItoa(
                    (unsigned int)(rand() % 
                        MathLimits<unsigned int>::kMax)); 
        case FieldDescriptor::CPPTYPE_INT64: 
            return SimpleItoa(
                    (long long)(rand() % 
                        MathLimits<long long>::kMax)); 
        case FieldDescriptor::CPPTYPE_UINT64: 
            return SimpleItoa(
                    (unsigned long long)rand() % 
                    MathLimits<unsigned long long>::kMax);
        case FieldDescriptor::CPPTYPE_FLOAT: 
            return SimpleItoa(
                    (signed int)(rand() % 
                        MathLimits<signed int>::kMax));
        case FieldDescriptor::CPPTYPE_DOUBLE: 
            return SimpleItoa(
                    (unsigned long long)rand() % 
                    MathLimits<unsigned long long>::kMax);
        case FieldDescriptor::CPPTYPE_BOOL: 
            return SimpleItoa(rand() % 2);
        default:
            break;
    }
    return "";
}

bool CPrimitiveFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    printer->Print(vars_, "$param_cpp_var$.set_$cpp_name$($param_c_var$.$cpp_name$());\n");
    return true;
}
    
bool CPrimitiveFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    printer->Print(vars_, "$param_c_var$.set_$cpp_name$($param_cpp_var$.$cpp_name$());\n");
   return true; 
}
    
COneofPrimitiveFieldGenerator::
COneofPrimitiveFieldGenerator(const FieldDescriptor* descriptor)
    : CPrimitiveFieldGenerator(descriptor) {
    
}
    
    
bool COneofPrimitiveFieldGenerator::
GenerateClear(Printer* printer)
{
    printer->Print(vars_,
            "$param_var$->$oneof_var$.$field_name$ = 0;\n");
    return true;
}

bool COneofPrimitiveFieldGenerator::
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "$type$* temp = "
            "&$param_var$->$oneof_var$.$field_name$;\n");
    GenerateReadPrimitive("temp", descriptor_, printer);
    printer->Print(vars_, 
            "if ($param_var$->$c_oneof_use_var$() != $oneof_field_value$) {\n");
    printer->Indent();
    PrintErrorLog(printer, "oneof filed not match");
    printer->Print("return -10;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;

}


bool COneofPrimitiveFieldGenerator::
GenerateAutoFillC(Printer* printer) {
    GenerateRandom(printer);
    printer->Print(vars_,
      "$param_c_var$->set_$cpp_name$($rand$);\n"
     );
    return true;
}
   
bool COneofPrimitiveFieldGenerator::
GenerateAutoFillCpp(Printer* printer) {

    GenerateRandom(printer);
    printer->Print(vars_, 
      "$param_cpp_var$->set_$cpp_name$($rand$);\n"
      "$param_cpp_var$->$cpp_oneof_use_var$($oneof_field_value$);\n"); 
    return true;

}
    
bool COneofPrimitiveFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    printer->Print(vars_, 
            "if (fabs($param_cpp_var$->$cpp_name$() -"
            " $param_c_var$->$cpp_name$()) > 0.000001) {\n"
            "  std::cout << \"$parent_type$::$c_name$ not equal [c:\"\n"
            "       << $param_c_var$->$cpp_name$()\n"
            "       << \", cpp:\"\n"
            "       << $param_cpp_var$->$cpp_name$()\n" 
            "       << \"]\" << std::endl;\n" 
            "  return false;\n"
            "}\n");
    return true;
}

bool COneofPrimitiveFieldGenerator::
GenerateStringTlog(Printer* printer) {
    // 打印filed name
    printer->Print(vars_, 
            "string_size = snprintf(buffer, buffer_size, \"%s%c\", \"$field_name$\", delimiter);\n"
            "if(string_size > buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");     
    // 打印内容
    GenerateString(printer);
    return true;
}
    
bool COneofPrimitiveFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    printer->Print(vars_, "$param_cpp_var$.set_$cpp_name$($param_c_var$.$cpp_name$());\n");
    return true;
} 
  
bool COneofPrimitiveFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    printer->Print(vars_, "$param_c_var$.set_$cpp_name$($param_cpp_var$.$cpp_name$());\n");
    return true;
}
    
CRepeatedPrimitiveFieldGenerator::
CRepeatedPrimitiveFieldGenerator(const FieldDescriptor* descriptor) 
    : CPrimitiveFieldGenerator(descriptor) {
}

    
    
bool CRepeatedPrimitiveFieldGenerator::
GenerateClear(Printer* printer)
{
    // 如果没有指定长度refer字段则需要将refer字段清空
    if (NeedGenerateArrayLenField(descriptor_)) {
        printer->Print(vars_, 
                "$param_var$->$array_num$ = 0;\n");
    }
    return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateDecode(Printer* printer) {
    vars_["var_name"] = "temp";
    printer->Print(vars_,
      "uint32_t length;\n"
      "if (!input->ReadVarint32(&length)) return -1;\n"
      "::google::protobuf::io::CodedInputStream::Limit limit = "
      "input->PushLimit(length);\n"
      "while (input->BytesUntilLimit() > 0) {\n");
    printer->Indent();
    printer->Print(vars_,
            "if ($size$ >= $array_max$) {\n");
    printer->Indent();
    PrintErrorLog(printer, "over max array count" + vars_["array_max"]);
    printer->Print( "return -3;\n");
    printer->Outdent();
    printer->Print(vars_,
      "}\n"
      "$type$* $var_name$ = &$param_var$->$field_name$[$size$];\n");
     GenerateReadPrimitive(vars_["var_name"], descriptor_, printer);
     printer->Print(vars_, "$size$++;\n");
     printer->Outdent();
     printer->Print(vars_, "}\n");
     printer->Print(vars_, "$param_var$->$array_num$ = $size$;\n");
     printer->Print(vars_, "input->PopLimit(limit);\n");
    return true;
}

bool  CRepeatedPrimitiveFieldGenerator::
GenerateEncode(Printer* printer) {
    if (descriptor_->is_packed()) {
        // Write the tag and the size.
        PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
        printer->Print(vars_,
        "int32_t $field_name$_byte_size =  $param_cached_size$->$field_name$;\n");
        printer->Print(vars_,
        "used_size += $tag_size$ +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(\n"
        "                      $field_name$_byte_size);\n"
        "if(used_size > size) {\n"
        "   return -1;\n"
        "}\n"

        "buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(\n"
        "    $field_number$,\n"
        "    ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,\n"
        "    buffer);\n\n"
        "buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(\n"
        "         static_cast< ::google::protobuf::uint32>(\n"
        "         $field_name$_byte_size), buffer);\n\n"
        "for (int i = 0; i < count; i++) {\n"
        "    buffer = ::google::protobuf::internal::WireFormatLite::Write$declared_type$NoTagToArray(\n"
        "         static_cast< $cpptype$>(\n"
        "         $param_var$->$field_name$[i]), buffer);\n"
        "}\n");
        printer->Outdent();
        printer->Print("}\n");
    } else {

    }
    
	return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
    int fixed_size = FixedSize(descriptor_->type());
    if (fixed_size == -1) {
                printer->Print(vars_,
                "int32_t out = 0;\n"
                "for (int i = 0; i < count; i++) {\n"
                "out += ::google::protobuf::internal::WireFormatLite::$declared_type$Size($param_var$->$field_name$[i]);\n"
                "}\n"
                "int32_t data_size = out;\n");

    } else {
        vars_["fixed_size"] = StrCat(fixed_size);
        printer->Print(vars_,
                "int32_t data_size = $fixed_size$UL * count;\n");
    }
    printer->Print(vars_,
            "$param_cached_size$->$field_name$ = data_size;\n");


    if (descriptor_->is_packed()) {
        printer->Print(vars_,
                "if (data_size > 0) {\n"
                "  total_size += $tag_size$ +\n"
                "    ::google::protobuf::internal::WireFormatLite::Int32Size(\n"
                "        static_cast< ::google::protobuf::int32>(data_size));\n"
                "}\n"

                "total_size += data_size;\n");
    }
    
    printer->Outdent();
    printer->Print("}\n");
	return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateString(Printer* printer) {
    PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
    printer->Print(vars_,
                "string_size = snprintf(buffer, buffer_size, \"[\");\n"
                "if(string_size >= buffer_size) {\n"
                "   return -1;\n"
                "}\n"
                "buffer_size -= string_size;\n"
                "buffer += string_size;\n"
                "for (int i = 0; i < count; i++) {\n");
    printer->Indent();
    printer->Print(vars_,
                "string_size = snprintf(buffer, buffer_size, \"$format$%c\", $param_var$->$field_name$[i], delimiter);\n"
                "if(string_size >= buffer_size) {\n"
                "   return -1;\n"
                "}\n"
                "buffer_size -= string_size;\n"
                "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Print(vars_,
                "buffer--;\n"
                "buffer_size++;\n"
                "string_size = snprintf(buffer, buffer_size, \"]%c\", delimiter);\n"
                "if(string_size > buffer_size) {\n"
                "   return -1;\n"
                "}\n"
                "buffer_size -= string_size;\n"
                "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");
	return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateStringTlog(Printer* printer) {
    GOOGLE_LOG(ERROR) << vars_["parent_type"] 
                          << "." 
                          << vars_["field_name"] 
                          << " Tlog string generation current does not support repeated types ";
	return false;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    PrintFillFullVarDefineWithBraceJson(printer, &vars_, descriptor_);
    printer->Print(vars_,
            "rapidjson::Value json_value;\n"
            "json_value.SetArray();\n"
            "for (int i = 0; i < count; i++) {\n");
    printer->Indent();
    printer->Print("rapidjson::Value member_json_value;\n");

    //protobuff官方转json将 int64、uint64类型转成string， 因为json的标准中不支持这两种类型，此处和官方保持一致
    if(vars_["json_type"] == "Int64" || vars_["json_type"] == "Uint64") {
        printer->Print(vars_,
            "std::string temp_string = ::google::protobuf::SimpleItoa($param_var$->$field_name$[i]);\n"
            "member_json_value.SetString(rapidjson::StringRef(temp_string.c_str(), temp_string.size()), *allocator);\n");
    }
    else {
        // 用message中定义的类型而不是c类型编码
        printer->Print(vars_,
            "member_json_value.Set$json_type$($param_var$->$field_name$[i]);\n"); 
    }

    printer->Print("json_value.PushBack(member_json_value, *allocator);\n");
    printer->Outdent();
    printer->Print("}\n");
    PrintJsonAddMember(printer, &vars_);
    printer->Outdent();
    printer->Print("}\n");
	return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    
    printer->Print(vars_,
        "if (!json_value.IsArray()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s json value type error, it's supposed to be an array, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Print("return -2;\n");
    printer->Outdent();
    printer->Print("}\n");


    printer->Print(vars_,
        "if (json_value.Size() > $array_max$) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%d.%d json_value.Size() > $array_max$, please check", "json_value.Size()", vars_["array_max"]);
    printer->Print("return -3;\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
        "for (rapidjson::SizeType i = 0; i < json_value.Size(); i++){ // rapidjson uses SizeType instead of size_t.\n");
    printer->Indent();

    // 对于int64/uint64类型，只接受string类型的值
    if(vars_["json_type"] == "Int64" || vars_["json_type"] == "Uint64") {
        printer->Print(vars_,
            "if (!json_value[i].IsString()) {\n");
        printer->Indent();
        PrintErrorLog(printer, "%s.%s.%d json value in array type error, please check", DoubleQuotesStr(vars_["field_name"]), DoubleQuotesStr(vars_["json_type"]), "i");
        printer->Print("return -4;\n");
        printer->Outdent();
        printer->Print(vars_,
            "}\n"
            "$param_var$->$field_name$[i] = atoll(json_value[i].GetString());\n");
    }  else {
        printer->Print(vars_,
        "if (!json_value[i].Is$json_type$()) {\n");
        printer->Indent();
        PrintErrorLog(printer, "%s.%s.%d json value in array type error, please check", DoubleQuotesStr(vars_["field_name"]), DoubleQuotesStr(vars_["json_type"]), "i");
        printer->Print("return -4;\n");
        printer->Outdent();
        printer->Print(vars_,
            "}\n"
            " $param_var$->$field_name$[i] = json_value[i].Get$json_type$();\n");
    }
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
        "$param_var$->$array_num$ = json_value.Size();\n");
	return true;
}


bool CRepeatedPrimitiveFieldGenerator::
GenerateAutoFillC(Printer* printer) {
    GenerateAutoFillIterationHead(&vars_, printer);
    printer->Indent();
    GenerateRandom(printer);
    printer->Print(vars_, 
      "$param_c_var$->add_$cpp_name$($rand$);\n");
   
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateAutoFillCpp(Printer* printer) {
    GenerateAutoFillIterationHead(&vars_, printer);
    printer->Indent();
    GenerateRandom(printer);
    printer->Print(vars_,
      "$param_cpp_var$->add_$cpp_name$($rand$);\n");
      /*
      "$param_cpp_var$->set_$array_num$("
      "$param_cpp_var$->$array_num$() + 1);\n");
      */
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    GenerateRepeatedSizeCompare(&vars_, printer, false);
    printer->Print(vars_,
      "for (int i = 0; i < $param_cpp_var$->$cpp_name$_size(); i++) {\n"
      "  if (fabs($param_cpp_var$->$cpp_name$(i) -"
      " $param_c_var$->$cpp_name$(i)) > 0.000001) {\n"
      "     std::cout << \"$parent_type$::$c_name$ repeated:\"\n"
      "          << i << \" element not equal\"\n"
      "          << std::endl;\n"
      "     return false;\n"
      "  }\n"
      "}\n");
    return true; 
}

bool CRepeatedPrimitiveFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    // 数组长度字段不为空 
    printer->Print(vars_, "for (uint32_t i = 0; i < $param_c_var$.$array_num$; i++) {\n");
 
    printer->Indent();
    printer->Print(vars_, "$param_cpp_var$.add_$cpp_name$($param_c_var$.$cpp_name$(i));\n");
    printer->Outdent();
    printer->Print(vars_, "}\n");
    return true;
}
   
bool CRepeatedPrimitiveFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    printer->Print(vars_, "for (uint32_t i = 0; i < $param_cpp_var$.$cpp_name$_size() && i < $array_max$; i++) {\n");
    printer->Indent();
    printer->Print(vars_, "$param_c_var$.add_$cpp_name$($param_cpp_var$.$cpp_name$(i));\n");
    printer->Outdent();
    printer->Print(vars_, "}\n");
    return true;
}
