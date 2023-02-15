#include "c_generator_helpers.h"

#include "c_string_field.h" 
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/wire_format.h>   ////后续去掉

CStringFieldGenerator::
CStringFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {

    SetCommVar(descriptor_, &vars_);
    if (!GetMaxLen(descriptor->options(), max_len_) || 
            max_len_.size() <= 0) {
         GOOGLE_LOG(ERROR) << descriptor->containing_type()->name() 
                           << "." 
                           << descriptor->name() 
                           << " get max len error, please check!!"; 
    }
    vars_["array_max"] = max_len_[0];
    

    vars_["array_max"] = GetFieldOptionExtendMaxLenName(descriptor->file(), max_len_[0]);
    max_len_[0] = vars_["array_max"];
    // max_len_[0] = GetFieldOptionExtendMaxLenName(descriptor->file(), max_len_[0]);
    if(max_len_.size() == 2)
      max_len_[1] = GetFieldOptionExtendMaxLenName(descriptor->file(), max_len_[1]);

    if (IsBytes()) {
        vars_["array_num"] = GetCArrayLenVarName(descriptor);
    }
}
 
    
bool CStringFieldGenerator::   
GenerateClear(Printer* printer)
{
    printer->Print(vars_,
            "$param_var$->$field_name$[0]='\\0';\n");
    return true;
}

bool CStringFieldGenerator::   
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "char* temp = &$param_var$->$field_name$[0];\n");
    GenerateReadString("temp", max_len_[0], printer);
    return true;
}

bool  CStringFieldGenerator::
GenerateEncode(Printer* printer) {
  if (IsBytes()) { 
      vars_["str_length"] =  vars_["param_var"] + "->" + vars_["array_num"];
      PrintFillFullVarDefine(printer, &vars_, descriptor_);
  } else {
      vars_["str_length"] =  vars_["param_cached_size"] + "->" + vars_["field_name"];
  }
  printer->Print(vars_,
          "if($str_length$ > 0)\n {");
  printer->Indent();
  printer->Print(vars_,
          "int32_t $field_name$_byte_size = $str_length$;\n"
          "used_size += $tag_size$ +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(\n"
          "                      $field_name$_byte_size);\n"
          "if(used_size > size) {\n"
          "   return -1;\n"
          "}\n"

          "buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray($field_number$,\n"
          "                                                                       ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, buffer);\n"
          "buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray($field_name$_byte_size, buffer);\n"
          "buffer = ::google::protobuf::io::CodedOutputStream::WriteRawToArray($non_null_ptr_to_name$,\n"
          "                                                                   $field_name$_byte_size, buffer);\n");
  printer->Outdent();
  printer->Print("}\n\n");
  return true;
}

bool CStringFieldGenerator::   
GenerateEncodeByteSizeLong(Printer* printer) {
  if (IsBytes()) { 
      vars_["str_length"] =  vars_["param_var"] + "->" + vars_["array_num"];
      PrintFillFullVarDefine(printer, &vars_, descriptor_);
  } else {
      vars_["strlen"] = "strlen(" + vars_["non_null_ptr_to_name"] + ")";
      vars_["str_length"] =  vars_["param_cached_size"] + "->" + vars_["field_name"];
      printer->Print(vars_,
                "$str_length$ = $strlen$;\n");
  }

  printer->Print(vars_,
          "if($str_length$ > 0)\n {");
  printer->Indent();
  printer->Print(vars_,
            "temp_sub_message_size = ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(\n"
            " $str_length$);\n"
            "total_size += $tag_size$ + temp_sub_message_size;\n");
  printer->Outdent();
  printer->Print("}\n\n");
  return true;
}

bool CStringFieldGenerator::   
GenerateString(Printer* printer) {
  if (IsBytes()) { 
    PrintFillFullVarDefine(printer, &vars_, descriptor_);
    printer->Print(vars_,
          "for (int i = 0; i < count; i++) {\n");
    printer->Indent();
    printer->Print(vars_,
          "string_size = snprintf(buffer, buffer_size, \"%02X\", (unsigned char)$non_null_ptr_to_name$[i]);\n"
          "if(string_size >= buffer_size) {\n"
          "   return -1;\n"
          "}\n"
          "buffer_size -= string_size;\n"
          "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");

  } else {
    printer->Print(vars_,
            "for(int i = 0; $non_null_ptr_to_name$[i]!='\\0'; i++) {\n"
            "   char c = $non_null_ptr_to_name$[i];\n"
            "   if(c == '\\t') {\n"
            "     string_size = snprintf(buffer, buffer_size, \"\\t\");\n"
            "   } else if(c == '\\r') {\n"
            "     string_size = snprintf(buffer, buffer_size, \"\\r\");\n"
            "   } else if(c == '\\n') {\n"
            "     string_size = snprintf(buffer, buffer_size, \"\\n\");\n"
            "   } else {\n"
            "     string_size = snprintf(buffer, buffer_size, \"%c\", c);\n"
            "   }\n"
            "   if(string_size >= buffer_size) {\n"
            "      return -1;\n"
            "   }\n"
            "   buffer_size -= string_size;\n"
            "   buffer += string_size;\n"
            "}\n");
  }
  printer->Print(vars_,
                "string_size = snprintf(buffer, buffer_size, \"%c\",delimiter);\n"
                "if(string_size > buffer_size) {\n"
                "   return -1;\n"
                "}\n"
                "buffer_size -= string_size;\n"
                "buffer += string_size;\n");
  return true;
}

bool CStringFieldGenerator::
GenerateJsonEncode(Printer* printer) {
  if (IsBytes()) { 
    PrintFillFullVarDefineWithBraceJson(printer, &vars_, descriptor_);
    printer->Print(vars_,
            "int base64_escape_len = ::google::protobuf::CalculateBase64EscapedLen(count);\n"
            "std::string buffer;\n"
            "buffer.resize(base64_escape_len);\n"
            "int ret_size = ::google::protobuf::Base64Escape((const unsigned char*)$non_null_ptr_to_name$, count, string_as_array(&buffer), buffer.size()); \n"
            "if (ret_size != base64_escape_len) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s Base64Escape failed, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Outdent();
    printer->Print(vars_,
            "  return -2;\n"
            "}\n"
            "rapidjson::Value json_value;\n"
            "json_value.SetString(buffer.c_str(), base64_escape_len, *allocator);\n");
    PrintJsonAddMember(printer, &vars_);
    printer->Print("}\n");

    printer->Outdent();
  } else {
    printer->Print(vars_,
            "if(strlen($non_null_ptr_to_name$) > 0 || json_print_option.always_print_primitive_fields) {\n"
            "   rapidjson::Value json_value;\n"
            "   if(json_print_option.url_encode_strings) {\n"
            "     std::string temp = UrlEncode(std::string($non_null_ptr_to_name$));\n"
            "     json_value.SetString(temp.c_str(), temp.size(), *allocator);\n"
            "   }\n"
            "   else {\n"
            "     json_value.SetString(rapidjson::StringRef($non_null_ptr_to_name$));\n"
            "   }\n");
    PrintJsonAddMember(printer, &vars_);
    printer->Print("}\n");
  }
  return true;
}

bool CStringFieldGenerator::
GenerateJsonDecode(Printer* printer) {
    printer->Print(vars_,
            "if (!json_value.IsString()) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s json value type error, it is supposed to be a string, please check", DoubleQuotesStr(vars_["field_name"]));
    printer->Print("return -2;\n");
    printer->Outdent();
    printer->Print("}\n");

    if (IsBytes()) { 
        printer->Print(vars_,
                "// LIBPROTOBUF_EXPORT bool Base64Unescape(StringPiece src, string* dest);\n"
                "::google::protobuf::StringPiece src(json_value.GetString(), json_value.GetStringLength());\n"
                "std::string unescaped_str;\n"
                "int ret = ::google::protobuf::Base64Unescape(src, &unescaped_str);\n"
                "if(ret == false) return -3;\n"
                "if (unescaped_str.size() > $array_max$) return -4;\n"
                "memcpy($non_null_ptr_to_name$, unescaped_str.c_str(), unescaped_str.size());\n");
        printer->Print(vars_, "$param_var$->$array_num$ = unescaped_str.size();\n");
    } 

    else {
        printer->Print(vars_,
                "int ret = 0;\n"
                "if(json_parse_option.url_encode_strings){ \n"
                " std::string urldecode_str;\n"
                " int ret = UrlDecode(std::string(json_value.GetString(), json_value.GetStringLength()), urldecode_str);\n");

        printer->Print(vars_,
                "if(ret != 0) {\n");
        printer->Indent();
        PrintErrorLog(printer, "%s UrlDecode error, string[%s], urldecode ret[%d], please check", DoubleQuotesStr(vars_["field_name"]), "json_value.GetString()", "ret");
        printer->Print("return -3;\n");
        printer->Outdent();
        printer->Print("}\n");

        printer->Print(vars_,         
                "   ret = snprintf($non_null_ptr_to_name$, $array_max$, \"%s\", urldecode_str.c_str());\n"
                "}\n"
                "else {\n"
                "   ret = snprintf($non_null_ptr_to_name$, $array_max$, \"%s\", json_value.GetString());\n"
                "}\n");

        printer->Print(vars_,
                "if(ret >= $array_max$) {\n");
        printer->Indent();
        PrintErrorLog(printer, "%s.%d.%d string length > array max length, please check", DoubleQuotesStr(vars_["field_name"]), "ret", vars_["array_max"]);
        printer->Print("return -4;\n");
        printer->Outdent();
        printer->Print("}\n");
    }
    return true;
}

void CStringFieldGenerator::   
GenerateReadString(const string& var_name,
                   const string& max_len_name,
                   Printer* printer) {

    printer->Print(
            "uint32_t length;\n"
            "if (!input->ReadVarint32(&length)) return -10;\n");
    if (IsBytes()) {
        printer->Print(
                "if (length > $max_len_name$) {\n", 
                "max_len_name", max_len_name);
        printer->Indent();
        PrintErrorLog(printer, "string length(%d) > buff length(%d)", "length", max_len_name);
        printer->Print("return -11;\n");
        printer->Outdent();
        printer->Print(
                "}\n"
                "if (!input->ReadRaw($var_name$, length)) return -12;\n",
                "var_name", var_name);
        printer->Print(vars_,
                "$param_var$->$array_num$ = length;\n");
    }
    else {
        printer->Print(
            "if (length >= $max_len_name$) {\n",
            "max_len_name", max_len_name);
        printer->Indent();
        PrintErrorLog(printer, "string length(%d) >= buff length(%d)", "length", max_len_name);
        printer->Print("return -11;\n");
        printer->Outdent();
        printer->Print(
                "}\n"
                "if (!input->ReadRaw($var_name$, length)) return -12;\n"
                "$var_name$[length] = '\\0';\n",
                "var_name", var_name);
    }
}

bool CStringFieldGenerator::IsBytes() {
    return FieldDescriptor::TYPE_BYTES == descriptor_->type(); 
}

void CStringFieldGenerator::
GenerateRandomHead(Printer* printer, bool fill_full) {
    if(IsBytes()) {
      vars_["mod_number"] = "2";
    } else {
      vars_["mod_number"] = "1";
    }
    
    if(fill_full) {
        if(IsBytes()) {
            printer->Print(vars_, "int $c_name$_len = $array_max$;\n");
        }
        else {
            printer->Print(vars_, "int $c_name$_len = $array_max$ - 1;\n");
        }
    } else {
        printer->Print(vars_,
            "int $c_name$_len = random() % $array_max$;\n");
    }
  
    
    printer->Print(vars_,
      "for (int j = 0; j < $c_name$_len; j++) {\n"
      "  char tmp;\n"
      "  switch(random() % $mod_number$) {\n"
      "    case 0:\n"
      "    tmp = random() % 127 + 1;\n"
      "    break;\n");
    if (IsBytes()) {
       printer->Print("    case 1:\n"
                      "    tmp = random() % 255 - 128;\n"
                      "    break;\n");
    }
    printer->Print("  }\n");
}

    
void CStringFieldGenerator::
GenerateRandomTail(Printer* printer) {
    printer->Print("}\n");
}

bool CStringFieldGenerator::
GenerateAutoFillC(Printer* printer) {
    printer->Print(vars_, "char tempArray[$array_max$] = {0};");
    GenerateRandomHead(printer, false);
    printer->Print(vars_, 
      " tempArray[j] = tmp;\n");
    //TODO
    if (IsBytes()) {
      printer->Print(vars_, 
        " $param_c_var$->$array_num$++;\n");
    }
    GenerateRandomTail(printer);
    printer->Print(vars_,
        "  $param_c_var$->set_$cpp_name$(tempArray);\n");
    return true;
}


bool CStringFieldGenerator::
GenerateAutoFillCpp(Printer* printer) {
    GenerateRandomHead(printer, false);
    printer->Print(vars_, 
      "  $param_cpp_var$->mutable_$cpp_name$()->push_back(tmp);\n");
    /*
    if (IsBytes()) {
      printer->Print(vars_, 
        "  $param_c_var$->set_$array_num$("
        "$param_c_var$->$array_num$()+1);\n");
    }
    */
    GenerateRandomTail(printer);
    return true;
}

bool CStringFieldGenerator::
GenerateCompareCAndCpp(Printer* printer) {
    if (IsBytes()) {
        GenerateRepeatedSizeCompare(&vars_, printer, true);
    }
    else {
        GenerateStringSizeCompare(&vars_, printer);
    }
    printer->Print(vars_,
      "if (0 != memcmp($param_cpp_var$->$cpp_name$().c_str(),"
      "$param_c_var$->$cpp_name$(), $param_cpp_var$->$cpp_name$().size())) {\n"
      "   std::cout << \"$parent_type$::$c_name$ :\"\n"
      "             <<  \" element not equal\"\n"
      "             << std::endl;\n"
      "   return false;\n"
      "}\n");
    return true;
}

bool CStringFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {

    printer->Print(vars_, "$param_cpp_var$.set_$cpp_name$(std::string($param_c_var$.$cpp_name$()");

    // 处理bytes类型
    if (IsBytes()) {
        // 长度字段为空, 按最大处理
        printer->Print(vars_, ", $param_c_var$.$array_num$");
    }
    printer->Print("));\n");
    return true;
}

bool CStringFieldGenerator::
GenerateAssignCppToC(Printer* printer) {

    if (IsBytes()) {
        printer->Print(vars_, 
                "int32_t $cpp_name$_len = (uint64_t)$param_cpp_var$.$cpp_name$().size() > sizeof($param_c_var$.$field_name$) ? "
                "sizeof($param_c_var$.$field_name$) : $param_cpp_var$.$cpp_name$().size();\n"
                "memcpy(&$param_c_var$.$c_name$, $param_cpp_var$.$cpp_name$().c_str(), $cpp_name$_len);\n");
        printer->Print(vars_, "$param_c_var$.$array_num$ = $cpp_name$_len;\n");
    }
    else {
        printer->Print(vars_,
                "int32_t $cpp_name$_len = (uint64_t)$param_cpp_var$.$cpp_name$().size() >= sizeof($param_c_var$.$field_name$) ? "
                "sizeof($param_c_var$.$field_name$) - 1 : $param_cpp_var$.$cpp_name$().size();\n"
                "strncpy(&$param_c_var$.$field_name$[0], $param_cpp_var$.$cpp_name$().c_str(), $cpp_name$_len);\n"
                "$param_c_var$.$field_name$[$cpp_name$_len] = 0;\n");
    }
    return true;
}

COneOfStringFieldGenerator::   
COneOfStringFieldGenerator(const FieldDescriptor* descriptor) 
    : CStringFieldGenerator(descriptor) {
}

bool COneOfStringFieldGenerator::   
GenerateClear(Printer* printer)
{
    printer->Print(vars_,
            "$param_var$->$oneof_var$.$field_name$[0]=0;\n");
    return true;
}
    
bool COneOfStringFieldGenerator::   
GenerateDecode(Printer* printer) {
    printer->Print(vars_,
            "char* temp = "
            "&$param_var$->$oneof_var$.$field_name$[0];\n");
    GenerateReadString("temp", max_len_[0], printer);
    printer->Print(vars_, 
            "if ($param_var$->$c_oneof_use_var$() != $oneof_field_value$) {\n");
    printer->Indent();
    PrintErrorLog(printer, "oneof filed not match");
    printer->Print("return -10;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}

bool COneOfStringFieldGenerator::   
GenerateAutoFillC(Printer* printer) {
    vars_["array_max"] = max_len_[0];
    printer->Print(vars_,
        "char arrayTemp[$array_max$] = {0};\n");
    GenerateRandomHead(printer, false);
    printer->Indent();
    //GenerateRandomHead(printer, false);
    printer->Print(vars_,
        "   arrayTemp[j] = tmp;\n");
    GenerateRandomTail(printer);
    printer->Print(vars_, 
      " $param_c_var$->set_$cpp_name$(arrayTemp);\n");
    printer->Print(vars_,
      "$param_c_var$->set_$c_oneof_use_var$($oneof_field_value$);\n");
    return true;
}
   
bool COneOfStringFieldGenerator::   
GenerateAutoFillCpp(Printer* printer) {

    GenerateRandomHead(printer, false);
    printer->Print(vars_, 
      "  $param_cpp_var$->mutable_$cpp_name$()->push_back(tmp);\n");
    GenerateRandomTail(printer);
    printer->Print(vars_,
      "$param_cpp_var$->$cpp_oneof_use_var$($oneof_field_value$);\n"
      );
	return true;
}
   
bool COneOfStringFieldGenerator::   
GenerateCompareCAndCpp(Printer* printer) {
    if (IsBytes()) {
        GenerateRepeatedSizeCompare(&vars_, printer, true);
    }
    else {
        GenerateOneofStringSizeCompare(&vars_, printer);
    }
   printer->Print(vars_,
      "if (0 != memcmp($param_cpp_var$->$cpp_name$().c_str(),"
      "$param_c_var$->$cpp_name$(), $param_cpp_var$->$cpp_name$().size())) {\n"
      "   std::cout << \"$parent_type$::$c_name$ :\"\n"
      "             <<  \" element not equal\"\n"
      "             << std::endl;\n"
      "   return false;\n"
      "}\n");
    return true;   
}

bool COneOfStringFieldGenerator::
GenerateAssignCToCpp(Printer* printer) {
    printer->Print(vars_,
            "$param_cpp_var$.set_$cpp_name$(std::string($param_c_var$.$cpp_name$()));\n");
    return true;
}
   
bool COneOfStringFieldGenerator::
GenerateAssignCppToC(Printer* printer) {
    // 暂时这么处理后期将打印的字符串模板化
    printer->Print(vars_,
                "int32_t $cpp_name$_len = (uint64_t)$param_cpp_var$.$cpp_name$().size() >= sizeof($param_c_var$.$oneof_var$.$field_name$) ? "
                "sizeof($param_c_var$.$oneof_var$.$field_name$) - 1 : $param_cpp_var$.$cpp_name$().size();\n"
                "strncpy(&$param_c_var$.$oneof_var$.$field_name$[0], $param_cpp_var$.$cpp_name$().c_str(), $cpp_name$_len);\n"
                "$param_c_var$.$oneof_var$.$field_name$[$cpp_name$_len] = 0;\n");
    return true;
}
    
CRepeatedStringFieldGenerator::   
CRepeatedStringFieldGenerator(const FieldDescriptor* descriptor)
    : CStringFieldGenerator(descriptor) {

    if (max_len_.size() < 2) {
      GOOGLE_LOG(ERROR) << descriptor->containing_type()->name() 
                        << "." 
                        << descriptor->name() 
                        << " get max len error, please check!!";
    }
    vars_["array_num"] = GetCArrayLenVarName(descriptor);
}
    
bool CRepeatedStringFieldGenerator::   
GenerateClear(Printer* printer)
{
    // 如果没有指定长度refer字段则需要将refer字段清空
    if (NeedGenerateArrayLenField(descriptor_)) {
        printer->Print(vars_, "$param_var$->$array_num$ = 0;\n");
    }
    return true;
}

bool CRepeatedStringFieldGenerator::   
GenerateDecode(Printer* printer) {
    printer->Print(vars_, 
            "if ($size$ >= $array_max$) {\n");
    printer->Indent();
    PrintErrorLog(printer,
            "over max array count " + vars_["array_max"]);
    printer->Print("return -1;\n");
    printer->Outdent();
    printer->Print(vars_,
            "}\n"
            "char* temp = &$param_var$->$field_name$[$size$][0];\n");
    GenerateReadString("temp", max_len_[1], printer);
    printer->Print(vars_, "$size$++;\n");
    printer->Print(vars_, "$param_var$->$array_num$ = $size$;\n");
    return true;
}

bool  CRepeatedStringFieldGenerator::
GenerateEncode(Printer* printer) {
  PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
  printer->Print(vars_,
    "for (int32_t i = 0; i < count; i++) {\n");;
  printer->Indent();
  printer->Print(vars_,
    "int32_t $field_name$_byte_size = $param_cached_size$->$field_name$[i];\n"
    "used_size += $tag_size$ +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(\n"
    "                      $field_name$_byte_size);\n"
    "if(used_size > size) {\n"
    "   return -1;\n"
    "}\n"
    "buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray($field_number$,\n"
    "                                                                       ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, buffer);\n"
    "buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray($field_name$_byte_size, buffer);\n"
    "buffer = ::google::protobuf::io::CodedOutputStream::WriteRawToArray($param_var$->$field_name$[i],\n"
    "                                                                   $field_name$_byte_size, buffer);\n");
  printer->Outdent();
  printer->Print("}\n");
  printer->Outdent();
  printer->Print("}\n\n");
  return true;
}

bool CRepeatedStringFieldGenerator::   
GenerateEncodeByteSizeLong(Printer* printer) {
    PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
    printer->Print(vars_,
            "total_size += $tag_size$ *\n"
            "    ::google::protobuf::internal::FromIntSize(count);\n"
            "for (int32_t i = 0; i < count; i++) {\n"
            "   $param_cached_size$->$field_name$[i] = strlen($param_var$->$field_name$[i]);\n"
            "   total_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(\n"
            "     $param_cached_size$->$field_name$[i]);\n"
            "}\n");
    printer->Outdent();
    printer->Print("}\n\n");
	  return true;
}

bool CRepeatedStringFieldGenerator::   
GenerateString(Printer* printer) {
    printer->Print("{\n");
    printer->Indent();
    PrintFillFullVarDefine(printer, &vars_, descriptor_);
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
            "for (int j = 0; $param_var$->$field_name$[i][j] != '\\0'; j++) {\n"
            "   char c = $param_var$->$field_name$[i][j];\n"
            "   if(c == '\\t') {\n"
            "     string_size = snprintf(buffer, buffer_size, \"\\t\");\n"
            "   } else if(c == '\\r') {\n"
            "     string_size = snprintf(buffer, buffer_size, \"\\r\");\n"
            "   } else if(c == '\\n') {\n"
            "     string_size = snprintf(buffer, buffer_size, \"\\n\");\n"
            "   } else {\n"
            "     string_size = snprintf(buffer, buffer_size, \"%c\", c);\n"
            "   }\n"
            "   if(string_size >= buffer_size) {\n"
            "      return -1;\n"
            "   }\n"
            "   buffer_size -= string_size;\n"
            "   buffer += string_size;\n"
            "}\n"
            "string_size = snprintf(buffer, buffer_size, \"%c\", delimiter);\n"
            "if(string_size >= buffer_size) {\n"
            "   return -1;\n"
            "}\n"
            "buffer_size -= string_size;\n"
            "buffer += string_size;\n");
    printer->Outdent();
    printer->Print("}\n");
    printer->Print(vars_,
            "buffer_size++;\n"
            "buffer--;\n"
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

bool CRepeatedStringFieldGenerator::   
GenerateStringTlog(Printer* printer) {
  GOOGLE_LOG(ERROR) << vars_["parent_type"] 
                        << "." 
                        << vars_["field_name"] 
                        << " Tlog string generation current does not support repeated types ";
  return false;
}

bool CRepeatedStringFieldGenerator::
GenerateJsonEncode(Printer* printer) {
  PrintFillFullVarDefineWithBrace(printer, &vars_, descriptor_);
  printer->Print(vars_,
            "rapidjson::Value json_value;\n"
            "json_value.SetArray();\n"
            "if(json_print_option.url_encode_strings){ \n"
            "   rapidjson::Value string_json_value;\n"
            "   for (int i = 0; i < count; i++) {\n"
            "     std::string temp = UrlEncode(std::string($param_var$->$field_name$[i]));\n"
            "     string_json_value.SetString(temp.c_str(), temp.size(), *allocator);    // allocate the string\n"
            "     json_value.PushBack(string_json_value, *allocator);     // allocate the value\n"
            "   }\n"
            "}\n"
            "else {\n"
            "   for (int i = 0; i < count; i++) {\n"
            "     json_value.PushBack(rapidjson::StringRef($param_var$->$field_name$[i]), *allocator);  // only need to allocate the value\n"
            "   }\n"
            "}\n");
  PrintJsonAddMember(printer, &vars_);
  printer->Outdent();
  printer->Print("}\n");
  return true;
}

bool CRepeatedStringFieldGenerator::
GenerateJsonDecode(Printer* printer) {
  vars_["array_max1"] = max_len_[0];
  vars_["array_max2"] = max_len_[1];

  printer->Print(vars_,
      "if (!json_value.IsArray()) {\n");
  printer->Indent();
  PrintErrorLog(printer, "%s json value type error, it's supposed to be an array, please check", DoubleQuotesStr(vars_["field_name"]));
  printer->Print("return -2;\n");
  printer->Outdent();
  printer->Print("}\n");
  
  printer->Print(vars_,
      "if (json_value.Size() > $array_max1$) {\n");       // check array length
  printer->Indent();
  PrintErrorLog(printer, "%d.%d json_value.Size() > $array_max$, please check", "json_value.Size()", vars_["array_max1"]);
  printer->Print("return -3;\n");
  printer->Outdent();
  printer->Print("}\n");
  
  printer->Print(vars_,
      "for (rapidjson::SizeType i = 0; i < json_value.Size(); i++) {\n");
  printer->Indent();

  printer->Print(vars_,
      "if (!json_value[i].IsString()) {\n");
  printer->Indent();
  PrintErrorLog(printer, "%s.%d json value in array type error, it is supposed to be a string, please check", DoubleQuotesStr(vars_["field_name"]), "i");
  printer->Print("return -4;\n");
  printer->Outdent();
  printer->Print("}\n");

  printer->Print(vars_,
            "int ret = 0;\n"
            "if(json_parse_option.url_encode_strings){ \n"
            " std::string urldecode_str;\n"
            " int ret = UrlDecode(std::string(json_value[i].GetString(), json_value[i].GetStringLength()), urldecode_str);\n");
          
  printer->Print(vars_,
          "if(ret != 0) {\n");
  printer->Indent();
  PrintErrorLog(printer, "%s.%d UrlDecode error, string[%s], urldecode ret[%d], please check", DoubleQuotesStr(vars_["field_name"]), "i", "json_value[i].GetString()", "ret");
  printer->Print("return -5;\n");
  printer->Outdent();
  printer->Print("}\n");

  printer->Print(vars_,
          " ret = snprintf($param_var$->$field_name$[i], $array_max2$, \"%s\", urldecode_str.c_str());\n"
          "}\n"
          "else {\n"
          " ret = snprintf($param_var$->$field_name$[i], $array_max2$, \"%s\", json_value[i].GetString());\n"
          "}\n");

  // 检查字符串长度是否超过限制
  printer->Print(vars_,
      "if (ret >= $array_max2$) {\n");
  printer->Indent();
  PrintErrorLog(printer, "%s.%d string length[%d] out of bound[%d], please check", DoubleQuotesStr(vars_["field_name"]), "i", "ret", vars_["array_max2"]);
  printer->Print("return -6;\n");
  printer->Outdent();
  printer->Print("}\n");

  printer->Outdent();
  printer->Print("}\n");

  printer->Print(vars_, "$param_var$->$array_num$ = json_value.Size();\n");
  return true;
}

    
bool CRepeatedStringFieldGenerator::   
GenerateAutoFillC(Printer* printer) {
    vars_["array_max"] = max_len_[0];
    GenerateAutoFillIterationHead(&vars_, printer);
    vars_["array_max"] = max_len_[1];
    printer->Print(vars_,
        "char arrayTemp[$array_max$] = {0};\n");
    printer->Indent();
    GenerateRandomHead(printer, false);
    printer->Print(vars_,
        "   arrayTemp[j] = tmp;\n");

    GenerateRandomTail(printer);
    printer->Print(vars_,
        "  $param_c_var$->add_$cpp_name$(arrayTemp);\n");
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}
    
bool CRepeatedStringFieldGenerator::   
GenerateAutoFillCpp(Printer* printer) {
    vars_["array_max"] = max_len_[0];
    GenerateAutoFillIterationHead(&vars_, printer);
    printer->Print(vars_,
      "  $param_cpp_var$->add_$cpp_name$();\n");
    printer->Indent();
    vars_["array_max"] = max_len_[1];
    GenerateRandomHead(printer, false);
    printer->Print(vars_, 
      "  $param_cpp_var$->mutable_$cpp_name$(i)->push_back(tmp);\n");
    GenerateRandomTail(printer);
    printer->Outdent();
    GenerateAutoFillIterationTail(&vars_, printer);
    return true;
}
    
bool CRepeatedStringFieldGenerator::   
GenerateCompareCAndCpp(Printer* printer) {

    GenerateRepeatedSizeCompare(&vars_, printer,false);
    printer->Print(vars_, 
      "for (int i = 0; i < $param_cpp_var$->$cpp_name$_size(); i++) {\n"
      "  if (0 != memcmp($param_cpp_var$->$cpp_name$(i).c_str(),\n"
      "    $param_c_var$->$cpp_name$(i), $param_cpp_var$->$cpp_name$(i).size())) {\n"
      "    std::cout << \"$parent_type$::$c_name$ repeated:\"\n"
      "         << i << \" element not equal\"\n"
      "         << std::endl;\n"
      "    return false;\n"
      " }\n"
      "}\n");
    return true;
}

bool CRepeatedStringFieldGenerator::   
GenerateAssignCToCpp(Printer* printer) {


    printer->Print(vars_, 
            "for (uint32_t i = 0; i < $param_c_var$.$array_num$; i++) {\n");
    printer->Indent();
    printer->Print(vars_, 
            "$param_cpp_var$.add_$cpp_name$($param_c_var$.$cpp_name$(i));\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
   
bool CRepeatedStringFieldGenerator::   
GenerateAssignCppToC(Printer* printer) {
    
    printer->Print(vars_, 
            "for (uint32_t i = 0; i < $param_cpp_var$.$cpp_name$_size() && i < $array_max$; i++) {\n");
    printer->Indent();

    // bytes/string 数组即二维数组，针对bytes第二维全拷贝 例子:
    // char buff[10][20];
    // char tmp[20];
    // memcpy(tmp, buff[0], sizeof(buff[0]));
    // string 第二维按实际长度拷贝 
    if (IsBytes()) {
        printer->Print(vars_, 
                "int32_t len = (uint64_t)$param_cpp_var$.$cpp_name$(i).size() >= sizeof($param_c_var$.$field_name$[i]) ?"
                " sizeof($param_c_var$.$c_name$[i]) : $param_cpp_var$.$cpp_name$(i).size();\n");
        printer->Print(vars_, "memcpy(&$param_c_var$.$c_name$[i], $param_cpp_var$.$cpp_name$(i).c_str(), len);\n");
    }
    else {
        printer->Print(vars_, 
                "int32_t len = (uint64_t)$param_cpp_var$.$cpp_name$(i).size() >= sizeof($param_c_var$.$field_name$[i]) ?"
                " sizeof($param_c_var$.$field_name$[i]) - 1 : $param_cpp_var$.$cpp_name$(i).size();\n");
        printer->Print(vars_, 
                "strncpy(&$param_c_var$.$field_name$[i][0], $param_cpp_var$.$cpp_name$(i).c_str(), len);\n"
                "$param_c_var$.$field_name$[i][len] = 0;\n");
    }

    // 有长度字段 
    printer->Print(vars_, "$param_c_var$.$array_num$ = i+1;\n");
    printer->Outdent();
    printer->Print("}\n");
    return true;
}
