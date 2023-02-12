#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"
#include "c_message_field.h"

using internal::WireFormat;

CMessageFieldGenerator::
CMessageFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {

    SetCommVar(descriptor_, &vars_);
    vars_["type"] = GetCStructName(descriptor_->message_type());
    vars_["compare_fun"] = GetCompareCAndCppFuncName(descriptor_->message_type());
    vars_["func_name"] = GetDecodeFuncNameWithStream(descriptor_->message_type());
    vars_["clear_func_name"] = GetClearFuncName(descriptor_->message_type());
    vars_["set_writed_func_name"] = GetSetMessageWritedFuncName(descriptor_->message_type());
    vars_["cached_size_name"] = "cached_size_";
    vars_["access_func"] = GetMessageFieldAccessFuncName(descriptor_);
    vars_["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
    vars_["has_func"] = GetMessageFieldHasFuncName(descriptor_);
    vars_["clear_has_func"] = GetMessageFieldHasFlagClearFuncName(descriptor_);
    vars_["c_2_cpp_fun"] = GetC2CppFunName(descriptor_->message_type());
    vars_["cpp_2_c_fun"] = GetCpp2CFunName(descriptor_->message_type());
}

bool CMessageFieldGenerator::
GenerateClear(Printer* printer) {
    printer->Print(vars_, 
            "$clear_func_name$(&$param_var$->$access_func$());\n"
            "$param_var$->$clear_has_func$();\n");
    return true;
}
    
bool CMessageFieldGenerator::
GenerateSetWrited(Printer* printer) {
    printer->Print(vars_, 
            "$set_writed_func_name$(&$param_var$->$access_func$());\n");
    return true;
}

void CMessageFieldGenerator::
GenerateReadMessage(const string& var_name,
                    const FieldDescriptor* field,
                    Printer* printer) {
    vars_["var_name"] = var_name;
    if (field->type() == FieldDescriptor::TYPE_MESSAGE) {
        printer->Print(vars_,
          "int32_t length;\n"
          "if (!input->ReadVarintSizeAsInt(&length)) {\n");
        printer->Indent();
        PrintErrorLog(printer, "ReadVarintSizeAsInt failed");
        printer->Print(vars_, " return -1;\n");
        printer->Outdent();
        printer->Print(vars_,
          "}\n"
          "std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = "
          "input->IncrementRecursionDepthAndPushLimit(length);\n"
          "if (p.second < 0 || 0 != $func_name$(input, $var_name$)) {\n");
        printer->Indent();
        PrintErrorLog(printer, 
                "IncrementRecursionDepthAndPushLimit failed(%d) or " + 
                vars_[var_name] + "failed",
                "(int)p.second");
        printer->Print(vars_, "return -2;\n");
        printer->Outdent();
        printer->Print(vars_,
          "}\n"
          "if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {\n");
        printer->Indent();
        PrintErrorLog(printer, 
                "DecrementRecursionDepthAndPopLimit failed(%d)",
                "p.first");
        printer->Print("return -3;\n");
        printer->Outdent();
        printer->Print("}\n");
    } else {
        printer->Print(vars_,
          "if (!input->IncrementRecursionDepth()) return false;\n"
          "if (0 != $func_name$(input, $var_name$))"
          " return -2;\n"
          "input->DecrementRecursionDepth();\n"
          "if (!input->LastTagWas(MakeTag($field_number$,"
          " WIRETYPE_END_GROUP))) {\n");
        printer->Indent();
        printer->Print("return -3;\n");
        printer->Outdent();
        printer->Print("}\n");
    }
}
    
bool CMessageFieldGenerator::
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "$type$* temp = $param_var$->$mutable_func$();\n");
    GenerateReadMessage("temp", descriptor_, printer);
    return true;
}

bool  CMessageFieldGenerator::
GenerateEncodeReal(Printer* printer)
{
    vars_["encode_func_name"] = GetEncodeFuncNameWithCachedSize(descriptor_->message_type());
    printer->Print(vars_,
          "int32_t $field_name$_byte_size = $non_null_cached_size_ptr_to_name$.$cached_size_name$;\n"
          "used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize($field_name$_byte_size) + $tag_size$;\n"
          "if(used_size > size) {\n"
          "   return -1;\n"
          "}\n"

          "buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(\n"
          "         $field_number$,\n"
          "         ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,\n"
          "         buffer);\n\n"
          
          "buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(\n"
          "         static_cast< ::google::protobuf::uint32>($field_name$_byte_size), buffer);\n"
          
          "temp_sub_message_size = $encode_func_name$(\n"
          "         &$non_null_ptr_to_name$, &$non_null_cached_size_ptr_to_name$, buffer, $field_name$_byte_size);\n");
    printer->Print("if (temp_sub_message_size < 0) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s encode error, ret code(%d)", DoubleQuotesStr(vars_["field_name"]), "temp_sub_message_size");
    printer->Print("return temp_sub_message_size;\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Print(vars_, "buffer = buffer + $field_name$_byte_size;\n");
  return true;
}

bool  CMessageFieldGenerator::
GenerateEncode(Printer* printer) {
    printer->Print(vars_,
            "if ($param_var$->$has_func$()) {\n");
    printer->Indent();
    GenerateEncodeReal(printer);
    printer->Outdent();
    printer->Print("}\n");
    return true;
}

bool CMessageFieldGenerator::
GenerateEncodeByteSizeLongReal(Printer* printer) {
    vars_["encode_func_name_byte_size_long"] = GetEncodeFuncNameByteSizeLongWithCachedSize(descriptor_->message_type());
    printer->Print(vars_,
          "    temp_sub_message_size = "
          "$encode_func_name_byte_size_long$(&$non_null_ptr_to_name$, &$non_null_cached_size_ptr_to_name$);\n");
    
    printer->Print("    if (temp_sub_message_size < 0) {\n");
    printer->Indent();
    printer->Indent();
    PrintErrorLog(printer, "%s encode error, ret code(%d)", DoubleQuotesStr(vars_["field_name"]), "temp_sub_message_size");
    printer->Print("return temp_sub_message_size;\n");
    printer->Outdent();
    printer->Outdent();
    printer->Print("    }\n");

    printer->Print(vars_,
          "    total_size += $tag_size$ + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);\n");
    return true;
}


bool CMessageFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    printer->Print(vars_,
          "if ($param_var$->$has_func$()) {\n");
    GenerateEncodeByteSizeLongReal(printer);
    printer->Print("}\n\n");
    return true;
}

bool CMessageFieldGenerator::
GenerateString(Printer* printer) {
    vars_["string_func_name"] = GetStringFuncName(descriptor_->message_type());
    printer->Print("{\n");
    printer->Indent();
    printer->Print(vars_,
            "string_size = snprintf(buffer, buffer_size, \"{\");\n"
            "if(string_size >= buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"
            
            "string_size = $string_func_name$(&$non_null_ptr_to_name$, buffer, buffer_size, delimiter);\n"
            "if(string_size < 0){\n"
            "   return string_size;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"

            "string_size = snprintf(buffer, buffer_size, \"}%c\", delimiter);\n"
            "if(string_size > buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CMessageFieldGenerator::
GenerateStringTlog(Printer* printer) {
    vars_["string_tlog_func_name"] = GetStringFuncNameTlog(descriptor_->message_type());
    printer->Print("{\n");
    printer->Indent();
    printer->Print(vars_,
            "string_size = $string_tlog_func_name$(&$non_null_ptr_to_name$, buffer, buffer_size, delimiter);\n"
            "if(string_size < 0){\n"
            "   return string_size;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"

            "string_size = snprintf(buffer, buffer_size, \"%c\", delimiter);\n"
            "if(string_size > buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");
  return true;
}
    
bool CMessageFieldGenerator::
GenerateJsonEncodeReal(Printer* printer)
{
    vars_["json_func_name"] = GetJsonFuncNameEncodeWithDocument(descriptor_->message_type());
    printer->Print(vars_,
            "rapidjson::Document sub_message_document;\n"
            "sub_message_document.SetObject();\n"
            "int32_t ret = $json_func_name$(&$non_null_ptr_to_name$, &sub_message_document, allocator, json_print_option);\n"
            "if (ret != 0) return ret;\n"
            "rapidjson::Value json_value;\n"
            "json_value.Swap(sub_message_document);\n");
    PrintJsonAddMember(printer, &vars_);
    return true;
}

bool CMessageFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    printer->Print(vars_,
            "if ($param_var$->$has_func$()) {\n");
    printer->Indent();
    GenerateJsonEncodeReal(printer);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CMessageFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    vars_["json_func_name"] = GetJsonFuncNameDecodeWithDocument(descriptor_->message_type());
    printer->Print("{\n");
    printer->Indent();
    
    printer->Print(vars_,
        "if (!json_value.IsObject()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s json value type error, it is supposed to be a Object, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Print("return -2;\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
            "rapidjson::Document sub_message_document;\n"
            "sub_message_document.SetObject();\n"
            "json_value.Swap(sub_message_document);\n"
            "int32_t ret = $json_func_name$(&sub_message_document, $param_var$->mutable_$c_name$(), json_parse_option);\n"
            "if (ret != 0) return ret;\n");
    printer->Outdent();
    printer->Print("}\n");
  return true;
}


bool CMessageFieldGenerator::
GenerateAutoFillC(Printer* printer) {
  vars_["fill_fun"] = GetFillOrFillFullCFuncName();
  printer->Print(vars_, 
          "if (random()%2) {\n"
          "  $fill_fun$($param_c_var$->mutable_$cpp_name$());\n"
          "}\n");
  return true;
}

bool CMessageFieldGenerator::
GenerateAutoFillCpp(Printer* printer) {
  vars_["fill_fun"] = GetFillOrFillFullCppFuncName();
  printer->Print(vars_, 
    "if (random()%2) {\n"
    "  $fill_fun$($param_cpp_var$->mutable_$cpp_name$());\n"
    "}\n");
  return true;
}
    
bool CMessageFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    printer->Print(vars_, 
      "if ($param_c_var$->$has_func$() != (int)$param_cpp_var$->has_$cpp_name$()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "C has not match Cpp has");
    printer->Print("return false;\n");
    printer->Outdent();
    printer->Print(vars_, 
      "}\n"
      "if (!$param_c_var$->$has_func$()) return true;\n"
      "if (!$compare_fun$($param_c_var$->mutable_$cpp_name$(),"
      "$param_cpp_var$->mutable_$cpp_name$())) return false;\n");
    return true;
}

bool CMessageFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    printer->Print(vars_, 
            "if (!$c_2_cpp_fun$($param_c_var$.$cpp_name$(), *$param_cpp_var$.$mutable_func$())) return false;\n");
    return true;
}

bool CMessageFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    printer->Print(vars_,
            "if (!$cpp_2_c_fun$($param_cpp_var$.$cpp_name$(), *$param_c_var$.$mutable_func$())) return false;\n");
    return true;
}

 
COneofMessageFieldGenerator::   
COneofMessageFieldGenerator(const FieldDescriptor* descriptor) 
    : CMessageFieldGenerator(descriptor) {
  std::string camel = GetUnionWrapperName(descriptor_); 
  vars_["non_null_ptr_to_name"] = StrCat(vars_["param_var"],"->", camel, ".", GetMessageFieldName(descriptor_));

}
    
bool COneofMessageFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    printer->Print(vars_, "{\n");
    GenerateEncodeByteSizeLongReal(printer);
    printer->Print("}\n\n");
	return true;
}

bool COneofMessageFieldGenerator::
GenerateClear(Printer* printer)  {
    //printer->Print(vars_, "$clear_func_name$(&$param_var$->$oneof_var$.$field_name$);\n");
    printer->Print(vars_, "memset(&$param_var$->$oneof_var$.$field_name$, 0, sizeof($param_var$->$oneof_var$.$field_name$));\n");
    return true;
}

bool COneofMessageFieldGenerator::
GenerateSetWrited(Printer* printer) {
    printer->Print(vars_, 
            "$set_writed_func_name$(&$param_var$->$oneof_var$.$field_name$);\n");
    return true;
}


string CMessageFieldGenerator::
GetFillOrFillFullCFuncName() {
  return GetFillCFuncName(descriptor_->message_type());
}

string CMessageFieldGenerator::
GetFillOrFillFullCppFuncName() {
  return GetFillCppFuncName(descriptor_->message_type());
}

bool COneofMessageFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    printer->Print(vars_,
            "{\n");
    printer->Indent();
    GenerateJsonEncodeReal(printer);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool COneofMessageFieldGenerator::   
GenerateAutoFillC(Printer* printer) {
  vars_["fill_fun"] = GetFillOrFillFullCFuncName();
  printer->Print(vars_,
      "$fill_fun$($param_c_var$->mutable_$cpp_name$());\n");
  return true;
}
    
    
bool COneofMessageFieldGenerator::   
GenerateEncode(Printer* printer)
{
    printer->Print(vars_, "{\n");
    printer->Indent();
    GenerateEncodeReal(printer);
    printer->Outdent();
    printer->Print("}\n");
	return true;
}
    
bool COneofMessageFieldGenerator::   
GenerateDecode(Printer* printer) {
    printer->Print(vars_, 
            "if ($param_var$->$c_oneof_use_var$() != $oneof_field_value$) {\n");
    printer->Indent();
    PrintErrorLog(printer, "oneof filed not match");
    printer->Print(vars_, "return -10;\n");
    printer->Outdent();
    printer->Print(vars_,
            "}\n"
            "$type$* temp = "
            "&$param_var$->$oneof_var$.$field_name$;\n");
    GenerateReadMessage("temp", descriptor_, printer);
    return true;
}

bool COneofMessageFieldGenerator::   
GenerateAutoFillCpp(Printer* printer) {
  vars_["fill_fun"] = GetFillOrFillFullCppFuncName();
  printer->Print(vars_, 
          "$fill_fun$($param_cpp_var$->mutable_$cpp_name$());\n"
          "$param_cpp_var$->$cpp_oneof_use_var$($oneof_field_value$);\n"); 
  return true;
}
    
bool COneofMessageFieldGenerator::   
GenerateCompareCAndCpp(Printer* printer) {
    printer->Print(vars_, 
      "if (!$compare_fun$($param_c_var$->mutable_$cpp_name$(),\n"
      "  $param_cpp_var$->mutable_$cpp_name$())) return false;\n");
    return true;
}

bool COneofMessageFieldGenerator::
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
    vars_["string_tlog_func_name"] = GetStringFuncNameTlog(descriptor_->message_type());
    printer->Print("{\n");
    printer->Indent();
    printer->Print(vars_,
            "string_size = $string_tlog_func_name$(&$non_null_ptr_to_name$, buffer, buffer_size, delimiter);\n"
            "if(string_size < 0){\n"
            "   return string_size;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"

            "string_size = snprintf(buffer, buffer_size, \"%c\", delimiter);\n"
            "if(string_size > buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
 
bool COneofMessageFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    printer->Print(vars_, 
            "if (!$c_2_cpp_fun$($param_c_var$.$access_func$(), *$param_cpp_var$.mutable_$cpp_name$())) return false;\n");
    return true;
}

bool COneofMessageFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    printer->Print(vars_,
            "if (!$cpp_2_c_fun$($param_cpp_var$.$cpp_name$(), *$param_c_var$.$mutable_func$())) return false;\n");
    return true;
}

CRepeatedMessageFieldGenerator::   
CRepeatedMessageFieldGenerator(const FieldDescriptor* descriptor) 
    : CMessageFieldGenerator(descriptor) {
        
    }
    
    
bool CRepeatedMessageFieldGenerator::   
GenerateDecode(Printer* printer) {
        
    printer->Print(vars_, "if ($size$ >= $array_max$) {\n");
    printer->Indent();
    PrintErrorLog(printer,
            "over max array count " + vars_["array_max"]);
    printer->Print("return -1;\n");
    printer->Outdent();
    printer->Print(vars_,
            "}\n"
            "$type$* temp = &$param_var$->$field_name$[$size$];\n"
            "memset(temp, 0, sizeof(*temp));\n");
    GenerateReadMessage("temp", descriptor_, printer);   
    printer->Print(vars_, "$size$++;\n");
    printer->Print(vars_, "$param_var$->$array_num$ = $size$;\n");

    return true;
}
    
bool  CRepeatedMessageFieldGenerator::
GenerateEncode(Printer* printer) {
    vars_["encode_func_name"] = GetEncodeFuncNameWithCachedSize(descriptor_->message_type());
    PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
    printer->Print(vars_,
            "for (int32_t  i = 0; i < count; i++) {\n");
    printer->Indent();
    printer->Print(vars_,
            "int32_t $field_name$_byte_size = 0;\n"
            "$field_name$_byte_size = $non_null_cached_size_ptr_to_name$[i].$cached_size_name$;\n");
    printer->Print(vars_,
            "used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize($field_name$_byte_size) + $tag_size$;\n"
            "if(used_size > size) {\n"
            "   return -1;\n"
            "}\n"

            "buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(\n"
            "         $field_number$,\n"
            "         ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,\n"
            "         buffer);\n\n"

            "buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(\n"
            "         static_cast< ::google::protobuf::uint32>($field_name$_byte_size), buffer);\n"

            "temp_sub_message_size = $encode_func_name$(\n"
            "         &$non_null_ptr_to_name$[i], &$non_null_cached_size_ptr_to_name$[i], buffer, $field_name$_byte_size);\n");
    printer->Print("if (temp_sub_message_size < 0) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s encode error, ret code(%d)", DoubleQuotesStr(vars_["field_name"]), "temp_sub_message_size");
    printer->Print("return temp_sub_message_size;\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Print(vars_, 
            "buffer = buffer + $field_name$_byte_size;\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}

    
bool CRepeatedMessageFieldGenerator::
GenerateEncodeByteSizeLong(Printer* printer) {
    vars_["encode_func_name_byte_size_long"] = GetEncodeFuncNameByteSizeLongWithCachedSize(descriptor_->message_type());
    PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
    printer->Print(vars_,
            "total_size += $tag_size$UL * count;\n"
            "for (int32_t i = 0; i < count; i++) {\n");
    
    printer->Print(vars_,
          "temp_sub_message_size = "
          "$encode_func_name_byte_size_long$( &$param_var$->$field_name$[static_cast<int>(i)], &$non_null_cached_size_ptr_to_name$[i]);\n");
    printer->Print("if (temp_sub_message_size < 0) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s encode error, ret code(%d)", DoubleQuotesStr(vars_["field_name"]), "temp_sub_message_size");
    printer->Print("return temp_sub_message_size;\n");
    printer->Outdent();
    printer->Print("}\n");

   printer->Print(vars_,
            "  total_size +=\n"
            "    ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);\n"
            "}\n");
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CRepeatedMessageFieldGenerator::
GenerateString(Printer* printer) {
    vars_["string_func_name"] = GetStringFuncName(descriptor_->message_type());
    PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
    printer->Print(vars_,
            "string_size = snprintf(buffer, buffer_size, \"[\");\n"
            "if(string_size >= buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"
            "for (int32_t i = 0; i < count; i++) {\n");
    printer->Indent();
    printer->Print(vars_,
            "string_size = snprintf(buffer, buffer_size, \"\\n{\");\n"
            "if(string_size >= buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"

            "string_size = $string_func_name$(&$param_var$->$field_name$[i], buffer, buffer_size, delimiter);\n"
            "if(string_size < 0){\n"
            "   return string_size;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n"
            
            "string_size = snprintf(buffer, buffer_size, \"}%c\", delimiter);\n"
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


bool CRepeatedMessageFieldGenerator::
GenerateStringTlog(Printer* printer) {
  GOOGLE_LOG(ERROR) << vars_["parent_type"] 
                        << "." 
                        << vars_["field_name"] 
                        << " Tlog string generation current does not support repeated types ";
	return false;
}

bool CRepeatedMessageFieldGenerator::
GenerateJsonEncode(Printer* printer) {
    vars_["json_func_name"] = GetJsonFuncNameEncodeWithDocument(descriptor_->message_type());
    PrintFillFullVarDefineWithBraceJson(printer, &vars_, descriptor_);
    printer->Print(vars_, 
            "rapidjson::Value json_value;\n"
            "json_value.SetArray();\n"
            "for (int32_t i = 0; i < count; i++) {\n"
            "   rapidjson::Document sub_message_document;\n"
            "   sub_message_document.SetObject();\n"
            "   int32_t ret = $json_func_name$(&$param_var$->$field_name$[i], &sub_message_document, allocator, json_print_option);\n"
            "   if (ret != 0) return ret;\n"
            "   rapidjson::Value sub_message_value;\n"
            "   sub_message_value.Swap(sub_message_document);\n"
            "   json_value.PushBack(sub_message_value, *allocator);"
            "}\n");
    PrintJsonAddMember(printer, &vars_);
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CRepeatedMessageFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    vars_["json_func_name"] = GetJsonFuncNameDecodeWithDocument(descriptor_->message_type());
    printer->Print("{\n");
    printer->Indent();
    
    // 检查json value类型是否是数组
    printer->Print(vars_,"if (!json_value.IsArray()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s json value type error, it's supposed to be an array, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Print("return -2;\n");
    printer->Outdent();
    printer->Print("}\n");

    // 检查数组长度是否超过最大长度限制
    printer->Print(vars_,
    "if (json_value.Size() > $array_max$) {\n");       
    printer->Indent();
    PrintErrorLog(printer, "%d.%d json_value.Size() > $array_max$, please check", "json_value.Size()", vars_["array_max"]);
    printer->Print("return -3;\n");
    printer->Outdent();
    printer->Print("}\n");
    
    printer->Print(vars_,
        "for (rapidjson::SizeType i = 0; i < json_value.Size(); i++){ // rapidjson uses SizeType instead of size_t.\n");
      
    printer->Print(vars_,
        "if (!json_value[i].IsObject()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s.%d json value type error, it is supposed to be a Object, please check", DoubleQuotesStr(vars_["field_name"]), "i");
    printer->Print("return -4;\n");
    printer->Outdent();
    printer->Print("}\n");

    printer->Print(vars_,
        "   rapidjson::Document sub_message_document;\n"
        "   sub_message_document.SetObject();\n"
        "   json_value[i].Swap(sub_message_document);\n"
        "   int32_t ret = $json_func_name$(&sub_message_document, &$param_var$->$field_name$[i], json_parse_option);\n"
        "   if (ret != 0) return ret;\n"
        "}\n");
    printer->Print(vars_,
        "$param_var$->$array_num$ = json_value.Size();\n");
    printer->Outdent();
    printer->Print("}\n");
  return true;
}

bool CRepeatedMessageFieldGenerator::   
GenerateAutoFillC(Printer* printer) {
    vars_["fill_fun"] = GetFillOrFillFullCFuncName();
    printer->Print(vars_, "$param_c_var$->$array_num$ = 0;\n");
    GenerateAutoFillIterationHead(&vars_, printer);
    printer->Indent();
    printer->Print(vars_, 
      "$fill_fun$($param_c_var$->mutable_$cpp_name$(i));\n");
    printer->Print(vars_, "$param_c_var$->$array_num$++;\n");
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}
    
bool CRepeatedMessageFieldGenerator::   
GenerateAutoFillCpp(Printer* printer) {
    vars_["fill_fun"] = GetFillOrFillFullCppFuncName();
    GenerateAutoFillIterationHead(&vars_, printer);
    printer->Indent();
    printer->Print(vars_, 
      "$fill_fun$($param_cpp_var$->add_$cpp_name$());\n");
      /*
      "$param_cpp_var$->set_$array_num$("
      "$param_cpp_var$->$array_num$() + 1);\n");
      */
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}
    
bool CRepeatedMessageFieldGenerator::   
GenerateCompareCAndCpp(Printer* printer) {
    GenerateRepeatedSizeCompare(&vars_, printer, false);
    printer->Print(vars_,
      "for (int32_t i = 0; i < $param_cpp_var$->$cpp_name$_size(); i++) {\n"
      "  if (!$compare_fun$(&$param_c_var$->$c_name$[i],\n"
      "    $param_cpp_var$->mutable_$cpp_name$(i))) {\n"
      "     std::cout << \"$parent_type$::$c_name$ repeated:\"\n"
      "          << i << \" element not equal\"\n"
      "          << std::endl;\n"
      "      return false;\n"
      "  }\n"
      "}\n");
    return true;
}

    
bool CRepeatedMessageFieldGenerator::
GenerateClear(Printer* printer) {
    // 如果没有指定长度refer字段则需要将refer字段清空
    if (NeedGenerateArrayLenField(descriptor_)) {
        printer->Print(vars_, "$param_var$->$array_num$ = 0;\n");
    }
    return true;
}

bool CRepeatedMessageFieldGenerator::
GenerateSetWrited(Printer* printer) {

    
    printer->Print(vars_,
      "int32_t $c_name$_max = $param_var$->$array_num$;\n");
    printer->Print(vars_, 
      "for (int32_t i = 0; i < $c_name$_max; i++) {\n"
      "  $set_writed_func_name$(&$non_null_ptr_to_name$[i]);\n"
      "}\n");
    return true;
}

bool CRepeatedMessageFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    // 数组长度字段不为空 
    printer->Print(vars_, "for (uint32_t i = 0; i < $param_c_var$.$array_num$; i++) {\n");
    printer->Indent();
    printer->Print(vars_, 
            "if (!$c_2_cpp_fun$($param_c_var$.$c_name$[i], *$param_cpp_var$.add_$cpp_name$())) return false;\n");
    printer->Outdent();
    printer->Print(vars_, "}\n");
    return true;
}

bool CRepeatedMessageFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    printer->Print(vars_, "for (uint32_t i = 0; i < $param_cpp_var$.$cpp_name$_size() && i < $array_max$; i++) {\n");
    printer->Indent();
    printer->Print(vars_,
            "if (!$cpp_2_c_fun$($param_cpp_var$.$cpp_name$(i), $param_c_var$.add_$access_func$())) return false;\n");
    
    printer->Outdent();
    printer->Print(vars_, "}\n");
    return true;
}
