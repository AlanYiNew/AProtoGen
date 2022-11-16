#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"
#include "c_enum_field.h"
CEnumFieldGenerator::CEnumFieldGenerator(
        const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
    SetCommVar(descriptor_, &vars_);
    enum_descriptor_ = descriptor_->enum_type();
    vars_["rand"] = vars_["c_name"] + "_rand"; 
    vars_["enum_max"] = SimpleItoa(GetMax()->number());
    vars_["enum_min"] = SimpleItoa(GetMin()->number());
    vars_["type"] = GetCEnumName(descriptor_->enum_type());
    vars_["cpp_type"] = GetCppEnumFullName(descriptor_->enum_type());
    

}

    
    
bool CEnumFieldGenerator::
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "$type$* temp = &$param_var$->$field_name$;\n");
    GenerateReadEnum("temp", descriptor_, printer);
    return true;
}

bool  CEnumFieldGenerator::GenerateEncode(Printer* printer) {
    printer->Print(vars_,
            "used_size += $tag_size$ +\n"
            "  ::google::protobuf::internal::WireFormatLite::EnumSize($non_null_ptr_to_name$);\n"
            "if(used_size > size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(\n"
            "  $field_number$, $param_var$->$field_name$, buffer);\n");
  return true;
}

bool CEnumFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    printer->Print(vars_,
            "total_size += $tag_size$ +\n"
            "  ::google::protobuf::internal::WireFormatLite::EnumSize($non_null_ptr_to_name$);\n");
  return true;
}


bool CEnumFieldGenerator::
GenerateString(Printer* printer) {
    printer->Print(vars_,
            "string_size = snprintf(buffer, buffer_size, \"%d%c\", $non_null_ptr_to_name$, delimiter);\n"
            "if(string_size > buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");
  return true;
}

bool CEnumFieldGenerator::
GenerateStringTlog(Printer* printer) {
    GenerateString(printer);
    return true;
}

bool CEnumFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    printer->Print(vars_,
            "rapidjson::Value json_value;\n"
            "json_value.SetInt($non_null_ptr_to_name$);\n");
    PrintJsonAddMember(printer, &vars_);
    return true;
}

bool CEnumFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    printer->Print(vars_,
        "if (!json_value.IsInt()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s json value type error, it is supposed to be a int, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Print("return -2;\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
        "$non_null_ptr_to_name$ = static_cast<$type$>(json_value.GetInt());\n");
  return true;
}


void CEnumFieldGenerator::
GenerateReadEnum(const string& var_name,
                 const FieldDescriptor* field,
                 Printer* printer) {
    vars_["var_name"] = var_name; 
    printer->Print(vars_,
      "int value;\n"
      "if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<\n"
      "  int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(\n"
      "    input, &value)) return -2;\n"
      "*$var_name$ = static_cast<$type$>(value);\n");
}

const EnumValueDescriptor* CEnumFieldGenerator::GetMax() {
    int max = -1;
    int max_index = -1;
    for (int i = 0; i < enum_descriptor_->value_count(); i++) {
        if (enum_descriptor_->value(i)->number() > max) {
            max = enum_descriptor_->value(i)->number(); 
            max_index = i;
        }
    }
    if (max_index != -1) {
        return enum_descriptor_->value(max_index); 
    }
    return NULL;
}

const EnumValueDescriptor* CEnumFieldGenerator::GetMin() {
    int min = numeric_limits<int>::max();
    int min_index = -1;
    for (int i = 0; i < enum_descriptor_->value_count(); i++) {
        if (enum_descriptor_->value(i)->number() < min) {
            min = enum_descriptor_->value(i)->number(); 
            min_index = i;
        }
    }
    if (min_index != -1) {
        return enum_descriptor_->value(min_index); 
    }
    return NULL;
}

void CEnumFieldGenerator::
GenerateRandom(Printer* printer, bool cpp) {
    if (!cpp) {
        printer->Print(vars_, 
              "$type$ $rand$ = static_cast<$type$>("
              "random()%($enum_max$-$enum_min$)+$enum_min$);\n");
    } else {
        printer->Print(vars_, 
              "$cpp_type$ $rand$ = static_cast<$cpp_type$>("
              "random()%($enum_max$-$enum_min$)+$enum_min$);\n");
    }
    
}

bool CEnumFieldGenerator::
GenerateAutoFillC(Printer* printer, bool full_up) {
    GenerateRandom(printer);
    printer->Print(vars_,
      "$param_c_var$->set_$cpp_name$($rand$);\n"); 
    return true;
}
    
bool CEnumFieldGenerator::
GenerateAutoFillCpp(Printer* printer, bool full_up) {
    GenerateRandom(printer, true);
    printer->Print(vars_, 
      "$param_cpp_var$->set_$cpp_name$($rand$);\n"); 
    return true;
}
    
bool CEnumFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    printer->Print(vars_, 
            "if ((int)$param_cpp_var$->$cpp_name$() !="
            "(int)$param_c_var$->$cpp_name$()) {\n"
            "  std::cout << \"$parent_type$::$c_name$ not equal [c:\"\n"
            "       << $param_c_var$->$cpp_name$() << \", cpp:\"\n"
            "       << $param_cpp_var$->$cpp_name$()\n" 
            "       << \"]\" << std::endl;\n" 
            "  return false;\n"
            "}\n");
    return true;
}
    
bool CEnumFieldGenerator::
GenerateClear(Printer* printer) {
    printer->Print(vars_,
      "$param_var$->$field_name$ = static_cast<$type$>(0);\n");   
	return true;
}
    
bool CEnumFieldGenerator::
GenerateAssignCToCpp(Printer* printer)
{
    printer->Print(vars_, "$param_cpp_var$.set_$cpp_name$(($cpp_type$)$param_c_var$.$cpp_name$());\n");
    return true;
}
 
bool CEnumFieldGenerator::
GenerateAssignCppToC(Printer* printer)
{
    printer->Print(vars_, "$param_c_var$.set_$cpp_name$(($type$)$param_cpp_var$.$cpp_name$());\n");
    return true;
}

COneofEnumFieldGenerator::
COneofEnumFieldGenerator(const FieldDescriptor* descriptor) 
    : CEnumFieldGenerator(descriptor) {
}

    
bool COneofEnumFieldGenerator::
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "$type$* temp = "
            "&$param_var$->$mutable_func$();\n");
    GenerateReadEnum("temp", descriptor_, printer);
    printer->Print(vars_, 
            "if ($param_var$->$c_oneof_use_var$() != "
            "$oneof_field_value$) return -10;\n");
    return true;
}


bool COneofEnumFieldGenerator::
GenerateAutoFillC(Printer* printer, bool full_up) {
    GenerateRandom(printer);
    printer->Print(vars_,
      "$param_c_var$->set_$cpp_name$($rand$);\n"
      "$param_c_var$->$cpp_oneof_use_var$($oneof_field_value$);\n"
      "$oneof_field_value$;\n");
    return true;
}

bool COneofEnumFieldGenerator::
GenerateAutoFillCpp(Printer* printer, bool full_up) {
    GenerateRandom(printer, true);
    printer->Print(vars_, 
      "$param_cpp_var$->set_$cpp_name$($rand$);\n"
      "$param_cpp_var$->$cpp_oneof_use_var$($oneof_field_value$);\n"); 
    return true;
}

bool COneofEnumFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    printer->Print(vars_, 
            "if ((int)$param_cpp_var$->$cpp_name$() != \n"
            "(int)$param_c_var$->$cpp_name$()) {\n"
            "  std::cout << \"$parent_type$::$c_name$ not equal [c:\"\n"
            "       << $param_c_var$->$oneof_var$.$c_name$\n"
            "       << \", cpp:\"\n"
            "       << $param_cpp_var$->$cpp_name$()\n" 
            "       << \"]\" << std::endl;\n" 
            "  return false;\n"
            "}\n");  
    return true;
}

bool COneofEnumFieldGenerator::
GenerateClear(Printer* printer) {
    printer->Print(vars_,
      "$param_var$->$oneof_var$.$field_name$ = static_cast<$type$>(0);\n"); 
	return true;
}

bool COneofEnumFieldGenerator::
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

bool COneofEnumFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    printer->Print(vars_, "$param_cpp_var$.set_$cpp_name$(($cpp_type$)$param_c_var$.$cpp_name$());\n");
    return true;
}
 
bool COneofEnumFieldGenerator::
GenerateAssignCppToC(Printer* printer)
{
    printer->Print(vars_, "$param_c_var$.set_$cpp_name$(($type$)$param_cpp_var$.$cpp_name$());\n");
    return true;
}

CRepeatedEnumFieldGenerator::
CRepeatedEnumFieldGenerator(const FieldDescriptor* descriptor)
    : CEnumFieldGenerator(descriptor) {
    vars_["var_name"] = "temp";
    vars_["size"] = GetRepeatedSizeName(descriptor_);
}

    
bool CRepeatedEnumFieldGenerator::
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
      "uint32_t length;\n"
      "if (!input->ReadVarint32(&length)) return -1;\n"
      "::google::protobuf::io::CodedInputStream::Limit limit = "
          "input->PushLimit(static_cast<int>(length));\n"
      "while (input->BytesUntilLimit() > 0) {\n"
      "  if ($size$ >= $array_max$) return -3;\n"
      "  $type$* $var_name$ = &$param_var$->$field_name$[$size$];\n");
    printer->Indent();
    GenerateReadEnum(vars_["var_name"], descriptor_, printer);
    printer->Print(vars_, "$size$++;\n");
    printer->Outdent();
    printer->Print(vars_,
             "}\n"
             "$param_var$->$array_num$ = $size$;\n"
             "input->PopLimit(limit);\n");
    return true;
}

bool  CRepeatedEnumFieldGenerator::
GenerateEncode(Printer* printer) {

    vars_["declared_type"] = DeclaredTypeMethodNamePrefix(descriptor_->type());
    if (descriptor_->is_packed()) {
        printer->Print(vars_,
                "if ($param_var$->$array_num$ > 0) {\n");
        printer->Indent();

        printer->Print(vars_,
      
        "int32_t $field_name$_byte_size = $param_cached_size$->$field_name$;\n"
        "const int n = $param_var$->$array_num$;\n"
        "used_size += $tag_size$ +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(\n"
        "                      $field_name$_byte_size);\n"
        "if(used_size > size) {\n"
        "   return -1;\n"
        "}\n"

        "buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(\n"
        "         $field_number$,\n"
        "         ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,\n"
        "         buffer);\n\n"
        "buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(\n"
        "         static_cast< ::google::protobuf::uint32>(\n"
        "         $field_name$_byte_size), buffer);\n\n"
        "for (int i = 0; i < n; i++) {\n"
        "  buffer = ::google::protobuf::internal::WireFormatLite::WriteEnumNoTagToArray(\n"
        "         $param_var$->$field_name$[i], buffer);\n"
        "}\n");

        printer->Outdent();
        printer->Print("}\n");
    }

  return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    printer->Print(vars_,
            "{\n"
            "  int32_t data_size = 0;\n"
            "  uint32_t count = static_cast<uint32_t>($param_var$->$array_num$);");
    printer->Indent();
    printer->Print(vars_,
            "for (uint32_t i = 0; i < count; i++) {\n"
            "  data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(\n"
            "    $param_var$->$field_name$[static_cast<int>(i)]);\n"
            "}\n"
            "$param_cached_size$->$field_name$ = data_size;\n");

    if (descriptor_->is_packed()) {
        printer->Print(vars_,
                "if (data_size > 0) {\n"
                "  total_size += $tag_size$ +\n"
                "    ::google::protobuf::internal::WireFormatLite::Int32Size(\n"
                "        static_cast< ::google::protobuf::int32>(data_size));\n"
                "}\n"

                "total_size += data_size;\n");
    } else {
        printer->Print(vars_,
                "total_size += ($tag_size$UL * count) + data_size;\n");
    }
    printer->Outdent();
    printer->Print("}\n");

  return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateString(Printer* printer) {
    printer->Print("{\n");
    printer->Indent();

    printer->Print(vars_,
                "string_size = snprintf(buffer, buffer_size, \"[\");\n"
                "if(string_size >= buffer_size) {\n"
                "   return -1;\n"
                "}\n"
                "buffer_size -= string_size;\n"
                "buffer += string_size;\n"
                "const int n = $param_var$->$array_num$;\n"
                "for (int i = 0; i < n; i++) {\n");
    printer->Indent();
    printer->Print(vars_,
                "string_size = snprintf(buffer, buffer_size, \"%d%c\", $param_var$->$field_name$[i], delimiter);\n"
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

bool CRepeatedEnumFieldGenerator::
GenerateStringTlog(Printer* printer) {
    GOOGLE_LOG(ERROR) << vars_["parent_type"] 
                          << "." 
                          << vars_["field_name"] 
                          << " Tlog string generation current does not support repeated types ";
	return false;
}

bool CRepeatedEnumFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    printer->Print(vars_,
            "if($param_var$->$array_num$ > 0 || json_print_option.always_print_primitive_fields) {\n");
    printer->Indent();
    printer->Print(vars_,
            "rapidjson::Value json_value;\n"
            "json_value.SetArray();\n"
            "const int n = $param_var$->$array_num$;\n"
            "for (int i = 0; i < n; i++) {\n"
            "   json_value.PushBack($param_var$->$field_name$[i], *allocator);\n"
            "}\n");
    PrintJsonAddMember(printer, &vars_);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    printer->Print(vars_,
      "if (!json_value.IsArray()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s json value type error, it's supposed to be an array, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Print("return -2;\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
      "if (json_value.Size() > $array_max$) {\n");       // check array length
    printer->Indent();
    PrintErrorLog(printer, "%d.%d json_value.Size() > $array_max$, please check", "json_value.Size()", vars_["array_max"]);
    printer->Print("return -3;\n");
    printer->Outdent();
    printer->Print("}\n");
    
    printer->Print(vars_,
        "for (rapidjson::SizeType i = 0; i < json_value.Size(); i++){ // rapidjson uses SizeType instead of size_t.\n");
    printer->Indent();

    printer->Print(vars_,
      "if (!json_value[i].IsInt()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s.%d json value in array type error, it is supposed to be a int, please check", DoubleQuotesStr(vars_["field_name"]), "i");
    printer->Print("return -4;\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
        "  $param_var$->$field_name$[i] = static_cast<$type$>(json_value[i].GetInt());\n");

    printer->Outdent();
    printer->Print("}\n");
    printer->Print(vars_,
        "$param_var$->$array_num$ = json_value.Size();\n");
    
    return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateAutoFillC(Printer* printer, bool full_up) {
    GenerateAutoFillIterationHead(&vars_, printer, full_up);
    printer->Indent();
    GenerateRandom(printer);
    printer->Print(vars_,
        "$param_c_var$->add_$cpp_name$($rand$);\n");
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateAutoFillCpp(Printer* printer, bool full_up) {
    GenerateAutoFillIterationHead(&vars_, printer, full_up);
    printer->Indent();
    GenerateRandom(printer, true);
    printer->Print(vars_,
      "$param_cpp_var$->add_$cpp_name$($rand$);\n");
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    GenerateRepeatedSizeCompare(&vars_, printer, GetFillFullExtOption(descriptor_), false);
    printer->Print(vars_,
      "for (int i = 0; i < $param_cpp_var$->$cpp_name$_size(); i++) {\n"
      "  if ((int)$param_cpp_var$->$cpp_name$(i) != (int)$param_c_var$->$cpp_name$(i)) {\n"
      "     std::cout << \"$parent_type$::$c_name$ repeated:\"\n"
      "          << i << \" element not equal\"\n"
      "          << std::endl;\n"
      "     return false;\n"
      "  }\n"
      "}\n");
    return true;
}

bool CRepeatedEnumFieldGenerator::
GenerateClear(Printer* printer) {
    // 如果没有指定长度refer字段则需要将refer字段清空
    if (NeedGenerateArrayLenField(descriptor_)) {
        printer->Print(vars_, "$param_var$->$array_num$ = 0;\n");
    }
    return true;
}

string CRepeatedEnumFieldGenerator::
GetRepeatedSizeName(const FieldDescriptor* field) const {
    return field->name() + "_size";
}

bool CRepeatedEnumFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    // 数组长度字段不为空 
    if (!GetFillFullExtOption(descriptor_)) {
        printer->Print(vars_, "for (uint32_t i = 0; i < $param_c_var$.$array_num$; i++) {\n");
    }
    else {
        printer->Print(vars_, "for (uint32_t i = 0; i < $array_max$; i++) {\n");
    }
    printer->Indent();
    printer->Print(vars_, "$param_cpp_var$.add_$cpp_name$(($cpp_type$)$param_c_var$.$cpp_name$(i));\n");
    printer->Outdent();
    printer->Print(vars_, "}\n");
    return true;
}
   
bool CRepeatedEnumFieldGenerator::
GenerateAssignCppToC(Printer* printer) {

    printer->Print(vars_, "for (uint32_t i = 0; i < $param_cpp_var$.$cpp_name$_size() && i < $array_max$; i++) {\n");
    printer->Indent();
    printer->Print(vars_, "$param_c_var$.add_$cpp_name$(($type$)$param_cpp_var$.$cpp_name$(i));\n");

   
    printer->Outdent();
    printer->Print(vars_, "}\n");
    return true;
}

