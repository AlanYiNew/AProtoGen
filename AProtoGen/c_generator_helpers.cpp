#include "c_generator_helpers.h"
#include "aext.pb.h"
#include <google/protobuf/stubs/strutil.h>
#include "c_helper.h"

bool GetStrictFlat(const FileDescriptor* file)
{
    const FileOptions & options = file->options();
    if (!options.HasExtension(AExt::strict_flat)) {
        return false;
    }
    auto ext = options.GetExtension(AExt::strict_flat);
    if (!ext) {
        return false;
    }
    return true;
}

std::string GetMessageFieldMutableFuncName(const FieldDescriptor* descriptor)
{
    return GetMessageFieldMutableFuncName(descriptor->name());
}

std::string GetMessageFieldMutableFuncName(const std::string& field_name)
{
    return "mutable_" + GetMessageFieldAccessFuncName(field_name);
}

std::string GetMessageFieldAccessFuncName(const FieldDescriptor* descriptor)
{
    return GetMessageFieldAccessFuncName(descriptor->name());  
}

std::string GetMessageFieldAccessFuncName(const std::string& field_name)
{
    std::string ret = field_name;
    LowerString(&ret);
    return ret;
}

std::string GetMessageFieldName(const FieldDescriptor* descriptor)
{
    return GetMessageFieldName(descriptor->name());
}

std::string GetMessageFieldName(const std::string field_name)
{
    return field_name + "_";
}

std::string GetMessageFieldHasFlagClearFuncName(const FieldDescriptor* descriptor)
{
    return "clear_has_" +  descriptor->name();
}

std::string GetMessageFieldHasFlagVarName()
{
    return "has_flag_";
}

std::string GetMessageFieldHasFuncName(const FieldDescriptor* descriptor)
{
     return "has_" +  descriptor->name();
}

std::string GetUnionWrapperName(const FieldDescriptor * field)
{
    std::string camel = field->containing_oneof()->name();
    if (camel.size() > 0) {
        camel[0] = ascii_toupper(camel[0]);
    }
    return "st"+camel;
}

std::string GetCEnumValueName(EnumValueDescriptor const* descriptor){
    return ToUpper(descriptor->type()->file()->package() + "_" + descriptor->name());     
}

std::string GetFieldOptionExtendMaxLenName(const FileDescriptor* file, const string& name, int value) {

    for (int i = 0; i < file->enum_type_count(); ++i){ 
        const EnumDescriptor* descriptor = file->enum_type(i);
        if (descriptor != NULL) {
            const EnumValueDescriptor* value_descriptor = descriptor->FindValueByName(name);
            if (value_descriptor == NULL) {
                value_descriptor = descriptor->FindValueByNumber(value);
            }
            if (value_descriptor != NULL) {
                return GetCEnumValueName(value_descriptor);
            }
        }
    }

    for (int i = 0; i < file->dependency_count(); i++) {
        for (int j = 0; j < file->dependency(i)->enum_type_count(); ++j){  
            const EnumDescriptor* descriptor = file->dependency(i)->enum_type(j);
            if (descriptor == NULL) continue;
            const EnumValueDescriptor* value_descriptor = descriptor->FindValueByName(name);
            if (value_descriptor == NULL) {
                value_descriptor = descriptor->FindValueByNumber(value);
            }
            if (value_descriptor == NULL) continue;
            return GetCEnumValueName(value_descriptor);
        }

    }
    return SimpleItoa(value);
}

std::string GetFieldOptionExtendMaxLenName(const FileDescriptor* file, const string& name) {
    for (int i = 0; i < file->enum_type_count(); ++i){ 
        const EnumDescriptor* descriptor = file->enum_type(i);
        if (descriptor != NULL) {
            const EnumValueDescriptor* value_descriptor = descriptor->FindValueByName(name);
            if (value_descriptor != NULL) {
                return GetCEnumValueName(value_descriptor);
            }
        }
    }

    for (int i = 0; i < file->dependency_count(); i++) {
        for (int j = 0; j < file->dependency(i)->enum_type_count(); ++j){  
            const EnumDescriptor* descriptor = file->dependency(i)->enum_type(j);
            if (descriptor == NULL) continue;
            const EnumValueDescriptor* value_descriptor = descriptor->FindValueByName(name);
            if (value_descriptor == NULL) continue;
            return GetCEnumValueName(value_descriptor);
        }

    }
    return name;
}

string GetCUnionFieldIDName(const FieldDescriptor* descriptor) {
    string name; 
    if (!GetOneOfFieldValueName(descriptor->options(), name)) {
        GOOGLE_LOG(ERROR) << descriptor->name() << " need union_field_value option"; 
        return "";
    }
    vector<string> names; 
    SplitStringUsing(name, "::", &names);
        
    for (size_t i = 0; i < names.size(); i++) {
        StripWhitespace(&names[i]);
    }

    if (names.size() > 1) {
       JoinStrings(names, "_", &name);
       return ToUpper(name);
    }
    return ToUpper(descriptor->file()->package() + "_"  + name);
}

string GetCppUnionFieldUseVarName(const OneofDescriptor* descriptor){
    string name;
    if (!GetOneOfUseFieldName(descriptor->options(), name)) {
        GOOGLE_LOG(ERROR) << descriptor->name() << " need use_field option";
        return "";
    }
    vector<string> tmp; 
    SplitStringUsing(name, ".", &tmp);
    size_t i = 0;
    for (; i < tmp.size() - 1; i++) {
        StripWhitespace(&tmp[i]);
        tmp[i] = "mutable_" + ToLower(tmp[i]) + "()"; 
    }
    StripWhitespace(&tmp[i]);
    tmp[i] =  "set_" + ToLower(tmp[i]);
    return JoinStrings(tmp, "->");
}

string GetCStructUnionSelectVarName(const OneofDescriptor* descriptor) {
    
    std::string name;
    if (!GetOneOfUseFieldName(descriptor->options(), name)) {
        GOOGLE_LOG(ERROR) << descriptor->name() << " need use_field option";
        return "";
    }
    // a.b.id形式需要拆解 mutable_a()->mutable_b()->id
    std::vector<std::string> res;
    SplitStringUsing(name, ".", &res);
    if (res.size() <= 1) return GetMessageFieldAccessFuncName(name);

    for (size_t i = 0; i < res.size()-1; i++)
    {
        res[i] = GetMessageFieldAccessFuncName(res[i]) + "()";
    }
    res[res.size() - 1] = GetMessageFieldName(res[res.size() - 1]);

    std::string result;
    JoinStrings(res, ".", &result);
    return result;
}

string GetCStructUnionSelectFieldName(const OneofDescriptor* descriptor) {

    std::string name;
    if (!GetOneOfUseFieldName(descriptor->options(), name)) {
        GOOGLE_LOG(ERROR) << descriptor->name() << " need use_field option";
        return "";
    }
    // a.b.id形式需要拆解 mutable_a()->mutable_b()->id
    std::vector<std::string> res;
    SplitStringUsing(name, ".", &res);
    if (res.size() <= 1) return GetMessageFieldName(name);

    for (size_t i = 0; i < res.size()-1; i++)
    {
        res[i] = GetMessageFieldMutableFuncName(res[i]) + "()";
    }
    res[res.size() - 1] = GetMessageFieldName(res[res.size() - 1]);

    std::string result;
    JoinStrings(res, "->", &result);
    return result;
}

string GetCArrayLenVarName(const FieldDescriptor* descriptor, bool fill_true) {
    string array_use_field;
    if (GetArrayUseFieldName(descriptor->options(), array_use_field)) {
        //GOOGLE_LOG(INFO) << "array use field name=" <<  array_use_field;
        return array_use_field;
    } else if(IsBytes(descriptor) || IsRepeated(descriptor)) {
        return GetCArrayLenVarNameDefault(descriptor);
    }
    return "";
}

string GetCArrayLenVarNameDefault(const FieldDescriptor* descriptor) {
    return descriptor->name() + "Size";
}

bool NeedGenerateArrayLenField(const FieldDescriptor* descriptor) {
    string array_use_field;
    return  (IsRepeated(descriptor) || IsBytes(descriptor)) 
            && (descriptor->containing_oneof() == NULL)
            && (!GetArrayUseFieldName(descriptor->options(), array_use_field));
}

bool GetArrayUseFieldName(const FieldOptions& options, string& name){
    if (options.HasExtension(AExt::refer)) {
        name = options.GetExtension(AExt::refer);
        return true;
    }
    return false;
}

bool GetMaxLen(const FieldOptions& options, vector<string>&  max_len){

    // 当此程序不包含pbc_extension.proto 用下面代码获取
    /*    
    const Reflection* reflection = options.GetReflection();    
    const UnknownFieldSet& unkonw_field_set = reflection->GetUnknownFields(options);
    for (int k = 0; k < unkonw_field_set.field_count(); k++) {
        if (MAX_LEN_1_TAG == unkonw_field_set.field(k).number() || 
                MAX_LEN_2_TAG == unkonw_field_set.field(k).number()) {
            max_len.push_back(unkonw_field_set.field(k).length_delimited());
        } 
        else if (MAX_LEN_3_TAG == unkonw_field_set.field(k).number()){
            max_len.push_back(SimpleItoa(unkonw_field_set.field(k).varint()));
        }
    }
    */
    if (options.HasExtension(AExt::count)) {
        vector<string> names;
        string name =  options.GetExtension(AExt::count);
        SplitStringUsing(name, "::", &names);
        if (names.size() > 1) {
            JoinStrings(names, "_", &name);
            max_len.push_back(ToUpper(name));
        }
        else {
            max_len.push_back(options.GetExtension(AExt::count));
        }
    }
    if (options.HasExtension(AExt::size)) {
        vector<string> names;
        string name =  options.GetExtension(AExt::size);
        SplitStringUsing(name, "::", &names);
        if (names.size() > 1) {
            JoinStrings(names, "_", &name);
            max_len.push_back(ToUpper(name));
        }
        else {
            max_len.push_back(options.GetExtension(AExt::size));
        }
    }
    
    return max_len.size() > 0;
}

bool GetOneOfUseFieldName(const OneofOptions& options, string& name) {
    if (options.HasExtension(AExt::select)) {
        name = options.GetExtension(AExt::select);
        return true;
    }
    return false;
}

string GetCUnionEnumFieldName(const FieldDescriptor* descriptor) {
    string camel = descriptor->containing_oneof()->name();; 
    if (camel.size() > 0) {
        camel[0] = ascii_toupper(camel[0]);
    }
    return "k" + camel + "_" + descriptor->name(); 
}
    
bool GetOneOfFieldValueName(const FieldOptions& options, string& name) {
    if (options.HasExtension(AExt::oneof_id)) {
        name = options.GetExtension(AExt::oneof_id);
        return true;
    }
    return false;
} 


string GetFilePath(const string& full_path) {
    uint64_t found = full_path.find_last_of("/\\");
    return full_path.substr(0,found); 
}
    
string GetFileName(const string& full_path) {
    uint64_t found = full_path.find_last_of("/\\");
    if (found + 1 >= full_path.length())
        return "";
    return full_path.substr(found + 1);
}

string GetBaseProtoName(const string& name) {
    return StripSuffixString(GetFileName(name), ".proto");
}

bool IsRepeated(const FieldDescriptor* field) {
    return field->label() == FieldDescriptor::LABEL_REPEATED;
}

bool IsPrimitiveType(const FieldDescriptor* field) {
    switch (field->cpp_type()) {
        case FieldDescriptor::CPPTYPE_INT32  :
        case FieldDescriptor::CPPTYPE_INT64  :
        case FieldDescriptor::CPPTYPE_UINT32 :
        case FieldDescriptor::CPPTYPE_UINT64 :
        case FieldDescriptor::CPPTYPE_DOUBLE :
        case FieldDescriptor::CPPTYPE_FLOAT  :
        case FieldDescriptor::CPPTYPE_BOOL   :
            return true;
        case FieldDescriptor::CPPTYPE_ENUM   :
        case FieldDescriptor::CPPTYPE_STRING :
        case FieldDescriptor::CPPTYPE_MESSAGE:
            return false;
    }
    return false;
}

const char* PrimitiveTypeCName(const FieldDescriptor* field) {
  switch (field->type()) {
    case FieldDescriptor::TYPE_INT32  : return "int32_t";
    case FieldDescriptor::TYPE_INT64  : return "int64_t";
    case FieldDescriptor::TYPE_UINT32 : return "uint32_t";
    case FieldDescriptor::TYPE_UINT64 : return "uint64_t";
    case FieldDescriptor::TYPE_DOUBLE : return "double";
    case FieldDescriptor::TYPE_FLOAT  : return "float";
    case FieldDescriptor::TYPE_BOOL   : return "bool";
    //case FieldDescriptor::CPPTYPE_ENUM   : return "int";
    case FieldDescriptor::TYPE_STRING : return "char";
    case FieldDescriptor::TYPE_BYTES: return "char";
    case FieldDescriptor::TYPE_MESSAGE: return "NULL";
    default: break;
    // No default because we want the compiler to complain if any new
    // CppTypes are added.
  }
  return "NULL";
}

bool IsEnum(const FieldDescriptor* field){
    return field->cpp_type() == FieldDescriptor::CPPTYPE_ENUM; 
}

bool IsMessage(const FieldDescriptor* field) {
    return field->cpp_type() == FieldDescriptor::CPPTYPE_MESSAGE; 
}

bool IsBytes(const FieldDescriptor* field) {
    return field->type() == FieldDescriptor::TYPE_BYTES; 
}

bool IsString(const FieldDescriptor* field) {
    return field->cpp_type() == FieldDescriptor::CPPTYPE_STRING; 
}

bool IsStringOrMessage(const FieldDescriptor* field) {
  switch (field->cpp_type()) {
    case FieldDescriptor::CPPTYPE_INT32:
    case FieldDescriptor::CPPTYPE_INT64:
    case FieldDescriptor::CPPTYPE_UINT32:
    case FieldDescriptor::CPPTYPE_UINT64:
    case FieldDescriptor::CPPTYPE_DOUBLE:
    case FieldDescriptor::CPPTYPE_FLOAT:
    case FieldDescriptor::CPPTYPE_BOOL:
    case FieldDescriptor::CPPTYPE_ENUM:
      return false;
    case FieldDescriptor::CPPTYPE_STRING:
    case FieldDescriptor::CPPTYPE_MESSAGE:
      return true;
  }
  return false;
}

bool put_into_map_if_not_exist(map<string, string> &vars, const EnumValueDescriptor* value_descriptor){
    map<string, string>::iterator iter = vars.find(value_descriptor->name());

    if (iter != vars.end()){
        GOOGLE_LOG(ERROR) << value_descriptor->name() + " in " + value_descriptor->file()->name() + " duplicates with" + iter->first + " in " + iter->second;
        return false;
    }   else{
        vars.insert(std::pair<string, string>(value_descriptor->name(), value_descriptor->file()->name()));
        return true;
    }

}

bool IsAllMacroNameUnique(const FileDescriptor* file) {
    map<string, string> vars;
    for (int i = 0; i < file->enum_type_count(); ++i){ 
        const EnumDescriptor* descriptor = file->enum_type(i);
        
        for (int j = 0; j < descriptor->value_count(); ++j)
        {
            const EnumValueDescriptor* value_descriptor = descriptor->value(j);
            if (!put_into_map_if_not_exist(vars, value_descriptor)){
                return false;
            }
        }
    }

    for (int i = 0; i < file->dependency_count(); i++) {
        for (int j = 0; j < file->dependency(i)->enum_type_count(); ++j){  
            const EnumDescriptor* descriptor = file->dependency(i)->enum_type(j);
            
            for (int k = 0; k < descriptor->value_count(); ++k)
            {
                const EnumValueDescriptor* value_descriptor = descriptor->value(k);
                if (!put_into_map_if_not_exist(vars, value_descriptor)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool GetFieldLength(const string& field, map<string, string>& lengths) {
    uint64_t begin_index = field.find_first_of('['); 
    if (begin_index == std::string::npos) {
        return false; 
    }
    uint64_t end_index = field.find_first_of(']');
    if (end_index == std::string::npos) {
        return false; 
    }
    string options = field.substr(begin_index + 1, end_index - begin_index - 1);
    GOOGLE_LOG(INFO) << options;
    vector<string> items;
    SplitStringUsing(options, ",", &items);

    for (uint64_t i = 0; i < items.size(); i++) {
        if (std::string::npos != items[i].find("count") || 
                std::string::npos != items[i].find("size")) {

             GOOGLE_LOG(INFO) << items[i];
             vector<string> results;
             SplitStringUsing(items[i], "=", &results);
             if (results.size() <= 1)
                 continue;
             for (uint64_t k = 0; k < results.size(); k++) {
                 StripWhitespace(&results[k]);
             } 
             lengths[results[0]] = results[1];
        }
    }
    return lengths.size() > 0;
}

string GetCPrimitiveType(const FieldDescriptor* field)  {
    string name;
    if (GetCTypeName(field->options(), name)) {
        return name;
    }
    return PrimitiveTypeCName(field);
}

string GetCPrimitiveTypePrintFormat(const FieldDescriptor* field) {
    string type = GetCPrimitiveType(field);
    string format;
    if(type == "int8_t" || type == "int16_t" || type == "int32_t") {
        format = "%d";
    } else if(type == "uint8_t" || type == "uint16_t" || type == "uint32_t") {
        format = "%u";
    } else if(type == "int64_t") {
        format = "%\" PRId64\"";
    } else if(type == "uint64_t") {
        format = "%\" PRIu64\"";
    } else if(type == "double") {
        format = "%f";
    } else if(type == "float") {
        format = "%f";
    } else {
        GOOGLE_LOG(ERROR) << field->containing_type()->name() 
                          << "." 
                          << field->name() 
                          << " GetCPrimitiveTypePrintFormat can not deal with type " 
                          << type; 
    }
    return format;
}

string GetCPrimitiveTypeJsonType(const FieldDescriptor* field) {
    string type = GetCPrimitiveType(field);
    string json_type;
    if(type == "int8_t" || type == "int16_t" || type == "int32_t") {
        json_type = "Int";
    } else if(type == "uint8_t" || type == "uint16_t" || type == "uint32_t") {
        json_type = "Uint";
    } else if(type == "int64_t") {
        json_type = "Int64";
    } else if(type == "uint64_t") {
        json_type = "Uint64";
    } else if(type == "double" || type == "float"){
        json_type = "Double";
    } else {
        GOOGLE_LOG(ERROR) << field->containing_type()->name()
                          << "." 
                          << field->name() 
                          << " GetCPrimitiveTypeJsonType can not deal with type "
                          << type; 
    }
    return json_type;
}

string GetPrimitiveTypeJsonType(const FieldDescriptor* field) {
  switch (field->type()) {
    case FieldDescriptor::TYPE_INT32  : return "Int";
    case FieldDescriptor::TYPE_INT64  : return "Int64";
    case FieldDescriptor::TYPE_UINT32 : return "Uint";
    case FieldDescriptor::TYPE_UINT64 : return "Uint64";
    case FieldDescriptor::TYPE_DOUBLE : return "Double";
    case FieldDescriptor::TYPE_FLOAT  : return "Double";
    default:
       GOOGLE_LOG(ERROR) << field->containing_type()->name()
                          << "." 
                          << field->name() 
                          << " GetPrimitiveTypeJsonType can not deal with type "; 
  }
  return "NULL";
}



bool GetCTypeName(const FieldOptions& options, string& name)  {
    if (options.HasExtension(AExt::c_type)) {
        name = options.GetExtension(AExt::c_type);
        return true;
    }
    return false;
}

string GetMessageTdrName(const MessageOptions& options)  {
    return ""; 
}

string GetCStructName(const Descriptor* descriptor)  {
    return descriptor->file()->package() + descriptor->name();   
}

string GetCCachedSizeStructName(const Descriptor* descriptor)  {
    return GetCStructName(descriptor) + "CachedSize_";   
}

string GetCUnionName(const OneofDescriptor* descriptor)  {


#ifdef UNION_NORAML 
    return descriptor->containing_type()->file()->package() + descriptor->name() + "U";   
#else
    return descriptor->containing_type()->file()->package() + descriptor->name();   
#endif
}

string GetCCachedSizeUnionName(const OneofDescriptor* descriptor)  {
    return GetCUnionName(descriptor) + "CachedSize_";
}

string GetCEnumName(const EnumDescriptor* descriptor) {
    return ToUpper(descriptor->file()->package()) + "_" + descriptor->name();   
}

string GetCUnionEnumName(const OneofDescriptor* descriptor)  {
    return descriptor->containing_type()->file()->package() + descriptor->name() + "Case";   
}

string GetCStructVarName(const Descriptor* descriptor)  {
    return ToLower(GetCStructName(descriptor)) + "_";
}

string GetCStructUnionFieldVarName(const OneofDescriptor* descriptor)  {
    //return ToLower(descriptor->name()); 
    string name = descriptor->name(); 
    name[0] = ascii_toupper(name[0]);
    return "st" + name;  
}

string GetCppUnionCaseFun(const OneofDescriptor* descriptor)  {
    return descriptor->name() + "_case";
}

string GetCppUnionFieldCase(const FieldDescriptor* descriptor)  {
    vector<string> items;
    SplitStringUsing(descriptor->full_name(), "." , &items);
    if (items.size () > 0) {
        items[items.size()-1][0] = ascii_toupper(items[items.size()-1][0]);
        items[items.size()-1] = "k" + items[items.size()-1];
    }
    
    return JoinStrings(items, "::");
}

string GetCppUnionFieldUnsetCase(const  OneofDescriptor* descriptor)  {
    vector<string> items;
    SplitStringUsing(descriptor->full_name(), "." , &items);
    if (items.size () > 0) {
        items[items.size() - 1] = ToUpper(items[items.size() - 1]) + "_NOT_SET";
    }
    return JoinStrings(items, "::");
}

string GetTdrCStructName(const Descriptor* descriptor)  {
    return "tag" + descriptor->name();
}

string GetTdrCStructVarName(const Descriptor* descriptor)  {
    return ToLower(GetTdrCStructName(descriptor)) + "_";
}

string GetC2CppFunName(const Descriptor* descriptor)  {
    return  "Assign" + descriptor->file()->package() + descriptor->name() + "To" +  descriptor->name(); 
}

string GetCpp2CFunName(const Descriptor* descriptor)  {
    return  "Assign" +  descriptor->name() + "To" +  descriptor->file()->package() + descriptor->name(); 
}

string GetCppStructFullName(const Descriptor* descriptor)  {
    return StringReplace(descriptor->full_name(), ".", "::", true); 
}

string GetCppEnumFullName(const EnumDescriptor* descriptor)  {
    return StringReplace(descriptor->full_name(), ".", "::", true); 
}

string GetCppStructVarName(const Descriptor* descriptor)  {
    return ToLower(descriptor->name()) + "_";
}

string GetCppFieldName(const FieldDescriptor* descriptor)  {
    return ToLower(descriptor->name()); 
}

string GetTdrC2PBCFunName(const Descriptor* descriptor)  {
    //return  "Assign" + GetTdrCStructName(descriptor->name()) + "To" +  GetCStructName(descriptor->name()); 
	return "";
}

string GetPBC2TdrCFunName(const Descriptor* descriptor)  {
    //return  "Assign" + GetCStructName(descriptor->name()) + "To" + GetTdrCStructName(descriptor->name());
	return "";
}

string GetCppTypedefHeaderName(const FileDescriptor* file)  {
    return StripSuffixString(GetFileName(file->name()), ".proto") + "_typedef" + "_pb";   
}

string GetCppHeaderName(const FileDescriptor* file)  {
    return StripSuffixString(GetFileName(file->name()), ".proto") + ".pb";   
}

const EnumValueDescriptor* GetEnumValue(
        const EnumDescriptor* descriptor, 
        int value, 
        const string& name)  {
    for (int i = 0; i < descriptor->value_count(); i++){
        const EnumValueDescriptor* value_desc = descriptor->value(i);
        if (value_desc->number() == value && 
                std::string::npos != value_desc->name().find(name))
        {
            return value_desc;
        }
    } 
    return NULL;
}

int GetFieldMaxNumber(const Descriptor* descriptor)  {
    int max = 0;
    for (int i = 0; i < descriptor->field_count(); i++) {
        const FieldDescriptor* field = descriptor->field(i);
        if (field->number() > max) {
            max = field->number(); 
        }
    }
    return max;
}

string GetFillCFuncName(const FieldDescriptor * field) {
    return GetFillCFuncName(field->containing_type());
}
string GetFillCFuncName(const Descriptor * descriptor) {
    return "Fill" + GetCStructName(descriptor);
}

string GetFillCppFuncName(const FieldDescriptor * field) {
    return GetFillCppFuncName(field->containing_type());
}

string GetFillCppFuncName(const Descriptor * descriptor) {
    return "Fill" + descriptor->name();
}

string GetCompareCAndCppFuncName(const FieldDescriptor * field) {
    return GetCompareCAndCppFuncName(field->containing_type());
}

string GetCompareCAndCppFuncName(const Descriptor * descriptor) {
    return "Compare" + descriptor->name();
}

string GetRepeatedSizeName(const FieldDescriptor* field) {
    return field->name() + "_size";
} 

string GetClearFuncName(const Descriptor* descriptor) {
    return "Clear" + GetCStructName(descriptor);
}

string GetSetMessageWritedFuncName(const Descriptor* descriptor) {
    return "Set" + GetCStructName(descriptor) + "Writed";
}

string GetDecodeFuncName(const Descriptor* descriptor) {
    return "Parse" + GetCStructName(descriptor);
}

string GetDecodeFuncNameWithStream(const Descriptor* descriptor) {
    return "Parse" + GetCStructName(descriptor) + "WithStream";
}
string GetEncodeFuncName(const Descriptor* descriptor) {
    return  "Serialize" + GetCStructName(descriptor) + "ToArray";
}

string GetEncodeFuncNameWithCachedSize(const Descriptor* descriptor) {
    return  "Serialize" + GetCStructName(descriptor) + "ToArrayWithCachedSize";
}
string GetEncodeFuncNameByteSizeLong(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "ByteSizeLong";
}

string GetEncodeFuncNameByteSizeLongWithCachedSize(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "ByteSizeLongWithCachedSize";
}

string GetStringFuncName(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "SimpleString";
}

string GetStringFuncNameTlog(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "TlogString";
}

string GetJsonFuncNameEncode(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "ToJson";
}


string GetJsonFuncNameEncodeWithDocument(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "ToJsonDocument";
}

string GetJsonFuncNameDecode(const Descriptor* descriptor) {
    return "JsonTo" + GetCStructName(descriptor);
}

string GetJsonFuncNameDecodeWithDocument(const Descriptor* descriptor) {
    return "JsonDocumentTo" + GetCStructName(descriptor);
}

string GetOneofFieldNameFuncName(const Descriptor* descriptor) {
    return GetCStructName(descriptor) + "OneofFieldName";
}

string GetDecodeFileBaseName(const string& proto) {
    return GetBaseProtoName(proto)  + "_decodec";
}

string GetClearFileBaseName(const string& proto) {
    return GetBaseProtoName(proto)  + "_clear";
}


string GetEncodeFileBaseName(const string& proto) {
    return GetBaseProtoName(proto)  + "_encodec";
}

string GetStringFileBaseName(const string& proto) {
    return GetBaseProtoName(proto)  + "_string";
}

string GetJsonFileBaseName(const string& proto) {
    return GetBaseProtoName(proto)  + "_json";
}


const char* DeclaredTypeMethodNamePrefix(FieldDescriptor::Type type) {
    switch (type) {
        case FieldDescriptor::TYPE_INT32:
            return "Int32";
        case FieldDescriptor::TYPE_INT64:
            return "Int64";
        case FieldDescriptor::TYPE_UINT32:
            return "UInt32";
        case FieldDescriptor::TYPE_UINT64:
            return "UInt64";
        case FieldDescriptor::TYPE_SINT32:
            return "SInt32";
        case FieldDescriptor::TYPE_SINT64:
            return "SInt64";
        case FieldDescriptor::TYPE_FIXED32:
            return "Fixed32";
        case FieldDescriptor::TYPE_FIXED64:
            return "Fixed64";
        case FieldDescriptor::TYPE_SFIXED32:
            return "SFixed32";
        case FieldDescriptor::TYPE_SFIXED64:
            return "SFixed64";
        case FieldDescriptor::TYPE_FLOAT:
            return "Float";
        case FieldDescriptor::TYPE_DOUBLE:
            return "Double";

        case FieldDescriptor::TYPE_BOOL:
            return "Bool";
        case FieldDescriptor::TYPE_ENUM:
            return "Enum";

        case FieldDescriptor::TYPE_STRING:
            return "String";
        case FieldDescriptor::TYPE_BYTES:
            return "Bytes";
        case FieldDescriptor::TYPE_GROUP:
            return "Group";
        case FieldDescriptor::TYPE_MESSAGE:
            return "Message";

            // No default because we want the compiler to complain if any new
            // types are added.
    }
    GOOGLE_LOG(FATAL) << "Can't get here.";
    return "";
}

bool IsMapEntryMessage(const Descriptor* descriptor) {
    return descriptor->options().map_entry();
}

string ClassName(const Descriptor* descriptor) {
    const Descriptor* parent = descriptor->containing_type();
    string res;
    if (parent) res += ClassName(parent) + "_";
    res += descriptor->name();
    if (IsMapEntryMessage(descriptor)) res += "_DoNotUse";
    return res;
}

int popcnt(uint32 n) {
    int result = 0;
    while (n != 0) {
        result += (n & 1);
        n = n / 2;
    }
    return result;
}

int FixedSize(FieldDescriptor::Type type)
{
    switch (type) {
        case FieldDescriptor::TYPE_INT32   : return -1;
        case FieldDescriptor::TYPE_INT64   : return -1;
        case FieldDescriptor::TYPE_UINT32  : return -1;
        case FieldDescriptor::TYPE_UINT64  : return -1;
        case FieldDescriptor::TYPE_SINT32  : return -1;
        case FieldDescriptor::TYPE_SINT64  : return -1;
        case FieldDescriptor::TYPE_FIXED32 : return WireFormatLite::kFixed32Size;
        case FieldDescriptor::TYPE_FIXED64 : return WireFormatLite::kFixed64Size;
        case FieldDescriptor::TYPE_SFIXED32: return WireFormatLite::kSFixed32Size;
        case FieldDescriptor::TYPE_SFIXED64: return WireFormatLite::kSFixed64Size;
        case FieldDescriptor::TYPE_FLOAT   : return WireFormatLite::kFloatSize;
        case FieldDescriptor::TYPE_DOUBLE  : return WireFormatLite::kDoubleSize;

        case FieldDescriptor::TYPE_BOOL    : return WireFormatLite::kBoolSize;
        case FieldDescriptor::TYPE_ENUM    : return -1;

        case FieldDescriptor::TYPE_STRING  : return -1;
        case FieldDescriptor::TYPE_BYTES   : return -1;
        case FieldDescriptor::TYPE_GROUP   : return -1;
        case FieldDescriptor::TYPE_MESSAGE : return -1;

                                             // No default because we want the compiler to complain if any new
                                             // types are added.
    }
    GOOGLE_LOG(FATAL) << "Can't get here.";
    return -1;
}

void PrintErrorLog(Printer* printer, std::string fmt) {
    printer->Print(
            "#ifdef ENABLE_PB_LOG\n"
            "GLOG_ERROR(\"$fmt$\");\n"
            "#else\n"
            "printf(\"[ERROR][%s][%d]$fmt$\\n\", __FUNCTION__, __LINE__);\n"
            "#endif\n", 
            "fmt", fmt);
}

void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1) {
    printer->Print(
            "#ifdef ENABLE_PB_LOG\n"
            "GLOG_ERROR(\"$fmt$\", $arg1$);\n"
            "#else\n"
            "printf(\"[ERROR][%s][%d]$fmt$\\n\", __FUNCTION__, __LINE__, $arg1$);\n"
            "#endif\n", 
            "fmt", fmt, "arg1", arg1);
}

void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1, std::string arg2) {
     printer->Print(
            "#ifdef ENABLE_PB_LOG\n"
            "GLOG_ERROR(\"$fmt$\", $arg1$, $arg2$);\n"
            "#else\n"
            "printf(\"[ERROR][%s][%d]$fmt$\\n\", __FUNCTION__, __LINE__, $arg1$, $arg2$);\n"
            "#endif\n",
            "fmt", fmt, "arg1", arg1, "arg2", arg2);
}

void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1, std::string arg2, std::string arg3) {
    printer->Print(
            "#ifdef ENABLE_PB_LOG\n"
            "GLOG_ERROR(\"$fmt$\", $arg1$, $arg2$, $arg3$);\n"
            "#else\n"
            "printf(\"[ERROR][%s][%d]$fmt$\\n\", __FUNCTION__, __LINE__, $arg1$, $arg2$, $arg3$);\n"
            "#endif\n",
            "fmt", fmt, "arg1", arg1, "arg2", arg2, "arg3", arg3);
}

void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1, std::string arg2, std::string arg3, std::string arg4) {
     printer->Print(
            "#ifdef ENABLE_PB_LOG\n"
            "GLOG_ERROR(\"$fmt$\", $arg1$, $arg2$, $arg3$, $arg4$);\n"
            "#else\n"
            "printf(\"[ERROR][%s][%d]$fmt$\\n\", __FUNCTION__, __LINE__, $arg1$, $arg2$, $arg3$, $arg4$);\n"
            "#endif\n",
            "fmt", fmt, "arg1", arg1, "arg2", arg2, "arg3", arg3, "arg4", arg4);
}

std::string DoubleQuotesStr(const std::string str)
{
    return "\"" + str + "\""; 
}

void PrintCheckArraySize(Printer* printer, map<string, string>* vars, const FieldDescriptor* field)
{
    printer->Print(*vars, 
            "if (count < 0 || count > (int)(sizeof($non_null_ptr_to_name$)/sizeof($non_null_ptr_to_name$[0]))) {\n");
    printer->Indent();
    PrintErrorLog(printer, "%s.%s[%d] invalid value, please check", 
            DoubleQuotesStr((*vars)["type"]), 
            DoubleQuotesStr((*vars)["array_num"]), 
            "count");
    printer->Print("return -1;\n");
    printer->Outdent();
    printer->Print(*vars, "}\n");
}
void PrintFillFullVarDefine(Printer* printer, map<string, string>* vars, const FieldDescriptor* field)
{
    printer->Print(*vars, 
            "int32_t count = static_cast<int32_t>($param_var$->$array_num$);\n");
    PrintCheckArraySize(printer, vars, field);
}

void PrintFillFullVarDefineWithBrace(Printer* printer, map<string, string>* vars, const FieldDescriptor* field)
{

    printer->Print(*vars,
            "if($param_var$->$array_num$ != 0) {\n"
            "  const int count = $param_var$->$array_num$;\n");
    printer->Indent();
    PrintCheckArraySize(printer, vars, field);
}

void PrintFillFullVarDefineWithBraceJson(Printer* printer, map<string, string>* vars, const FieldDescriptor* field)
{

    printer->Print(*vars,
            "if($param_var$->$array_num$ > 0 || json_print_option.always_print_primitive_fields) {\n"
            "  const int count = $param_var$->$array_num$;\n");
    printer->Indent();
    PrintCheckArraySize(printer, vars, field);
}

void PrintJsonAddMember(Printer* printer, map<string, string>* vars)
{
    if((*vars)["json_name"] == (*vars)["c_name"]) {
        printer->Print(*vars,
                    "document->AddMember(\"$c_name$\", json_value , *allocator);\n");
    } else {
        printer->Print(*vars,
                    "if (json_print_option.preserve_proto_field_names) {\n"
                    "  document->AddMember(\"$c_name$\", json_value , *allocator);\n"
                    "} else {\n"
                    "  document->AddMember(\"$json_name$\", json_value , *allocator);\n"
                    "}\n");
    }
}
