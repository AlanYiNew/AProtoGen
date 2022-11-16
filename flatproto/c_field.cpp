#include <google/protobuf/descriptor.pb.h>

#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"
#include "c_base_generator.h"
#include "c_field.h"
#include "c_helper.h"
#include "c_message_field.h"
#include "c_string_field.h"
#include "c_enum_field.h"
#include "c_primitive_field.h"

#include <google/protobuf/wire_format.h>   
CFieldGeneratorMap::   
CFieldGeneratorMap(const Descriptor* descriptor) {
    for (int i = 0; i < descriptor->field_count(); i++) {
        const FieldDescriptor* field = descriptor->field(i);
        fields_[field] = MakeGenerator(field);
    }
}
    
CFieldGeneratorMap::~CFieldGeneratorMap() {
    map<const FieldDescriptor*, CFieldGenerator*>::iterator it;
    for (it = fields_.begin(); it != fields_.end(); ++it) {
        if (it->second != NULL) delete(it->second);
    }
    fields_.clear();
}

CFieldGenerator* CFieldGeneratorMap::
Get(const FieldDescriptor* descriptor) {
    return fields_[descriptor];
}
    
CFieldGenerator* CFieldGeneratorMap::
MakeGenerator(const FieldDescriptor* field) {
    if (field->is_repeated()) {
    switch (field->cpp_type()) {
      case FieldDescriptor::CPPTYPE_MESSAGE:
        if (field->is_map()) {
           GOOGLE_LOG(ERROR) << field->name() <<" not support map";
           return NULL;
        } else {
           return new CRepeatedMessageFieldGenerator(field);
        }
      case FieldDescriptor::CPPTYPE_STRING:
        switch (field->options().ctype()) {
          default:  // unknown ctypes.
          case FieldOptions::STRING:
           return new CRepeatedStringFieldGenerator(field);
        }
      case FieldDescriptor::CPPTYPE_ENUM:
        if (field->is_packed()) {
           return new CRepeatedEnumFieldGenerator(field);
        }
        else {
           GOOGLE_LOG(ERROR) << field->name() 
               << " not support no packed field, we only support proto3";
           return NULL;
        }
      default:
        if (field->is_packed()) {
           return new CRepeatedPrimitiveFieldGenerator(field);
        }
        else {
           GOOGLE_LOG(ERROR) << field->name() 
               << " not support no packed field, we only support proto3";
           return NULL;
        }
    }
  } else if (field->containing_oneof()) {
    switch (field->cpp_type()) {
      case FieldDescriptor::CPPTYPE_MESSAGE:
        return new COneofMessageFieldGenerator(field);
      case FieldDescriptor::CPPTYPE_STRING:
        switch (field->options().ctype()) {
          default:  // StringOneofFieldGenerator handles unknown ctypes.
          case FieldOptions::STRING:
            return new COneOfStringFieldGenerator(field);
        }
      case FieldDescriptor::CPPTYPE_ENUM:
        return new COneofEnumFieldGenerator(field);
      default:
        return new COneofPrimitiveFieldGenerator(field);
    }
  } else {
    switch (field->cpp_type()) {
      case FieldDescriptor::CPPTYPE_MESSAGE:
        return new CMessageFieldGenerator(field);
      case FieldDescriptor::CPPTYPE_STRING:
        switch (field->options().ctype()) {
          default:  // StringFieldGenerator handles unknown ctypes.
          case FieldOptions::STRING:
            return new CStringFieldGenerator(field);
        }
      case FieldDescriptor::CPPTYPE_ENUM:
        return new CEnumFieldGenerator(field);
      default:
        return new CPrimitiveFieldGenerator(field);
    }
  }
    return NULL;
}

void SetConstName(map<string, string>* vars) {
    (*vars)["param_c_var"] = "msg_obj_c";
    (*vars)["param_cpp_var"] = "msg_obj_cpp";
    (*vars)["param_var"] = "msg_obj";
    (*vars)["param_cached_size"] = "msg_obj_cached_size";
}

void SetCommVar(const FieldDescriptor* descriptor, 
                map<string, string>* vars) {
    SetConstName(vars);
    (*vars)["parent_type"] = descriptor->containing_type()->name();
    (*vars)["c_name"] = descriptor->name();
    (*vars)["c_type"] = PrimitiveTypeCName(descriptor);
    (*vars)["cpp_name"] = ToLower(descriptor->name());
    (*vars)["field_name"] = GetMessageFieldName(descriptor);
    (*vars)["field_number"] = StrCat(descriptor->number());
    (*vars)["json_name"] = descriptor->json_name();
    const OneofDescriptor* oneof_descriptor =
        descriptor->containing_oneof();
    if (oneof_descriptor) {
        (*vars)["oneof_var"] =
            GetCStructUnionFieldVarName(oneof_descriptor);
        (*vars)["c_oneof_use_var"] =  
            GetCStructUnionSelectVarName(oneof_descriptor);
        (*vars)["cpp_oneof_use_var"] =  
            GetCppUnionFieldUseVarName(oneof_descriptor);
        (*vars)["oneof_field_value"] =
            GetCUnionFieldIDName(descriptor);
        (*vars)["non_null_ptr_to_name"] = 
            StrCat((*vars)["param_var"],"->", GetCStructUnionSelectFieldName(oneof_descriptor));
        (*vars)["non_null_cached_size_ptr_to_name"] = 
            StrCat((*vars)["param_cached_size"],"->", GetUnionWrapperName(descriptor), ".", descriptor->name());
    } else {
        // 如果是非repeated message 则使用接口访问
        if (IsMessage(descriptor) && !IsRepeated(descriptor)) {
            (*vars)["non_null_ptr_to_name"] = 
                StrCat((*vars)["param_var"],"->", GetMessageFieldName(descriptor));
        } else {
            (*vars)["non_null_ptr_to_name"] = 
                StrCat((*vars)["param_var"], "->", GetMessageFieldName(descriptor));
        }
        (*vars)["non_null_cached_size_ptr_to_name"] = 
            StrCat((*vars)["param_cached_size"],"->", GetMessageFieldName(descriptor));
    }

    if (IsRepeated(descriptor) || IsBytes(descriptor)) {

        (*vars)["array_num"] = GetCArrayLenVarName(descriptor);

        vector<string> max_len;
        if (!GetMaxLen(descriptor->options(), max_len) || max_len.size() <= 0) {
            GOOGLE_LOG(ERROR) << descriptor->containing_type()->name() 
                              << "." 
                              << descriptor->name() 
                              << " get max len error, please check!!"; 
        }
        (*vars)["array_max"] = GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]);
        (*vars)["size"] = GetRepeatedSizeName(descriptor);
    }

    (*vars)["tag_size"] = StrCat(AlphaNum((int)WireFormat::TagSize(descriptor->number(), descriptor->type())));
}

void GenerateAutoFillIterationHead(
        map<string, string>* vars, 
        Printer* printer,
        bool full_fill) {

    if(full_fill) {
      printer->Print(*vars,
          "int $c_name$_max = $array_max$;\n");
    } else {
      printer->Print(*vars,
          "int $c_name$_max = random()%($array_max$ +1);\n");
    }
    printer->Print(*vars, 
      "for (int i = 0; i < $c_name$_max; i++) {\n");
}

void GenerateAutoFillIterationTail(
        map<string, string>* vars,
        Printer* printer) {

    printer->Print("}\n");
}

void GenerateRepeatedSizeCompare(
        map<string, string>* vars,
        Printer* printer,
        bool fill_full,
        bool is_bytes) {

    if (is_bytes) {
        printer->Print((*vars),
                "  int cpp_$cpp_name$_count = $param_cpp_var$->$cpp_name$().size();\n");
    }
    else {
        printer->Print((*vars),
                "  int cpp_$cpp_name$_count = $param_cpp_var$->$cpp_name$_size();\n");
    }

    if (fill_full) {
        printer->Print((*vars),
                "  int c_$cpp_name$_count = $array_max$;\n");
    }
    else {
       printer->Print((*vars),
                "  int c_$cpp_name$_count = $param_c_var$->$array_num$;\n");
    }

    printer->Print((*vars),
            "if (cpp_$cpp_name$_count != c_$cpp_name$_count) {\n"
            "  std::cout << \" $parent_type$::$c_name$ size not eq:[c:\"\n"
            "       << c_$cpp_name$_count\n"
            "       << \", cpp:\"\n"
            "       << cpp_$cpp_name$_count\n"
            "       << \"]\"\n"
            "       << std::endl;\n"
            "  return false;\n"
            "}\n");
}

void GenerateStringSizeCompare(
        map<string, string>* vars,
        Printer* printer) {
    printer->Print((*vars),
            "if ($param_cpp_var$->$cpp_name$().size() !="
            "  strlen($param_c_var$->$cpp_name$())) {\n"
            "  std::cout << \" $parent_type$::$c_name$ size not eq\"\n"
            "       << strlen($param_c_var$->$cpp_name$())\n"
            "       << \", cpp:\"\n"
            "       << $param_cpp_var$->$cpp_name$().size()\n"
            "       << \"]\"\n"
            "       << std::endl;\n"
            "  return false;\n"
            "}\n");
}
void GenerateOneofStringSizeCompare(
        map<string, string>* vars,
        Printer* printer) {

    printer->Print((*vars),
            "if ($param_cpp_var$->$cpp_name$().size() != \n"
            "  strlen($param_c_var$->$cpp_name$())) {\n"
            "  std::cout << \" $parent_type$::$c_name$ size not eq:[c:\"\n"
            "       << strlen($param_c_var$->$cpp_name$())\n"
            "       << \", cpp:\"\n"
            "       << $param_cpp_var$->$cpp_name$().size()\n"
            "       << \"]\"\n"
            "       << std::endl;\n"
            "  return false;\n"
            "}\n");
}
