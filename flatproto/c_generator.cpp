#include "c_generator.h"
#include <google/protobuf/stubs/strutil.h>

#include <google/protobuf/extension_set.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/logging.h>
#include "c_generator_helpers.h"
#include <sstream> 
#include <stdio.h> 

CGenerator::CGenerator() {
}
CGenerator::~CGenerator(){}

bool CGenerator::GenerateDefineFile(const FileDescriptor* file, Printer& printer) const{

    GenerateHead(file, printer);
    for (int i = 0; i < file->enum_type_count(); i++){
        const EnumDescriptor* enum_type = file->enum_type(i); 
        GenerateEnum(enum_type, printer);
    }
    // 生成结构体前置声明
    for (int i = 0; i < file->message_type_count(); i++) {
        const Descriptor* message_type = file->message_type(i);
        GenerateStructForwardDeclaration(message_type, printer);
        GenerateCachedSizeStructForwardDeclaration(message_type, printer);
    } 

    set<string> oneof_names; 
    for (int i = 0; i < file->message_type_count(); i++) {
        const Descriptor* message_type = file->message_type(i);
        for (int j = 0; j < message_type->oneof_decl_count(); j++) {
            if (oneof_names.insert(message_type->oneof_decl(j)->name()).second == false) 
                continue;
            GenerateUnionForwardDeclaration(message_type->oneof_decl(j), printer);
            GenerateCachedSizeUnionForwardDeclaration(message_type->oneof_decl(j), printer);
        }
    } 

    // 生成结构体
    oneof_names.clear(); 
    for (int i = 0; i < file->message_type_count(); i++) {
        const Descriptor* message_type = file->message_type(i);
        for (int j = 0; j < message_type->oneof_decl_count(); j++) {
            if (oneof_names.insert(message_type->oneof_decl(j)->name()).second == false) 
                continue;
            GenerateUnion(message_type->oneof_decl(j), printer);
            GenerateCachedSizeUnion(message_type->oneof_decl(j), printer);
        }
        GenerateStruct(message_type, printer);
        GenerateCachedSizeStruct(message_type, printer);
    } 
    GenerateEnd(file, printer);
    return true;
}

bool CGenerator::
Generate(const FileDescriptor* file,
    const string& parameter,
    GeneratorContext* generator_context,
    string* error,
    bool generate_assign) const {

    if (!IsAllMacroNameUnique(file)) {
        exit(-1);
    }
    string suffix = ".proto";
    string base_name = StripSuffixString(file->name(), suffix);
    auto temp = generator_context->Open(base_name + ".h");
    std::unique_ptr<io::ZeroCopyOutputStream> output(temp);
    Printer define_printer(temp, '$');
    if (!GenerateDefineFile(file, define_printer)) return false;
    return true;
}

void CGenerator::
GenerateHead(const FileDescriptor* file, Printer& printer) const {

    map<string, string> vars;
    vars["name"] =  ToUpper(StripSuffixString(GetFileName(file->name()), ".proto")); 
    printer.Print(vars, 
                   "#ifndef $name$_H__\n" 
                   "#define $name$_H__\n\n");
    for(int i = 0; i < file->dependency_count(); i++){
        if (kExcludeProtofile == GetFileName(file->dependency(i)->name())) continue;
        vars["name"] = StripSuffixString(file->dependency(i)->name(), ".proto") + ".h"; 
        printer.Print(vars, "#include \"$name$\"\n");
    }
    printer.Print("#include <cstring>\n");
    printer.Print("#include <cstdint>\n");
    printer.Print("\n");
}

void CGenerator::
GenerateEnd(const FileDescriptor* file, Printer& printer) const {

    map<string, string> vars;
    vars["name"] =  ToUpper(StripSuffixString(GetFileName(file->name()), ".proto")); 
    printer.Print(vars, "#endif //$name$_H__");
}

void CGenerator::
GenerateEnum(const EnumDescriptor* descriptor, Printer& printer) const {

    map<string, string> vars;
	SourceLocation stlocation;
	descriptor->GetSourceLocation(&stlocation);
	int ipos = stlocation.leading_comments.find_first_of('\n');
	vars["comment"] = stlocation.leading_comments.substr(0, ipos);
    vars["name"] = GetCEnumName(descriptor);
	
    printer.Print(vars, "/* $comment$ */\n");
    printer.Print(vars, "typedef enum tag$name$ {\n");
    printer.Indent();
    printer.Indent();
    int max = std::numeric_limits<int>::min();
    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < descriptor->value_count(); i++){
        if (descriptor->value(i)->number() > max)
        {
            max = descriptor->value(i)->number(); 
        }
        if (descriptor->value(i)->number() < min)
        {
            min = descriptor->value(i)->number(); 
        }
    }
    vars["min"] = SimpleItoa(min);
    vars["max"] = SimpleItoa(max);
    printer.Print(vars, "$name$_MIN = $min$,\n");
    for (int i = 0; i < descriptor->value_count(); i++){
        GenerateEnumValue(descriptor->value(i), printer);
    }
    printer.Print(vars, "$name$_MAX = $max$,\n");
    printer.Outdent();
    printer.Outdent();
    printer.Print(vars, "} $name$;\n"); 

    // 生成枚举的array size为枚举最大值加一
    vars["name"] = ToUpper(vars["name"]);
    vars["array_size"] = SimpleItoa(max+1);
    printer.Print(vars, "#define $name$_ARRAYSIZE $array_size$\n\n");
}

void CGenerator::GenerateEnumValue(const EnumValueDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
	SourceLocation stlocation;
	descriptor->GetSourceLocation(&stlocation);

    vars["name"] = GetCEnumValueName(descriptor);
    vars["value"] = SimpleItoa(descriptor->number());
	int ipos = stlocation.trailing_comments.find_first_of('\n');
	vars["comment"] = stlocation.trailing_comments.substr(0, ipos);

    printer.Print(vars, "$name$ = $value$, /* $comment$ */ \n");
}

void CGenerator::
GenerateStructForwardDeclaration(const Descriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetCStructName(descriptor); 
    vars["upper_name"] = ToUpper(vars["name"]); 
    printer.Print(vars, "struct tag$name$;\n");
    printer.Print(vars, "typedef struct tag$name$ $name$;\n");
    printer.Print(vars, "typedef struct tag$name$ $upper_name$;\n");
    printer.Print(vars, "typedef struct tag$name$*LP$upper_name$;\n\n");
}

void CGenerator::
GenerateStruct(const Descriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetCStructName(descriptor); 

	SourceLocation stlocation;
	descriptor->GetSourceLocation(&stlocation);
	int ipos = stlocation.leading_comments.find_first_of('\n');
	vars["comment"] = stlocation.leading_comments.substr(0, ipos);

    printer.Print(vars, "/* $comment$ */ \n");
    printer.Print(vars, "struct tag$name${\n");
    printer.Indent();
    printer.Indent();

    set<string> oneof;
        
    // 先处理非message成员
    for (int i = 0; i < descriptor->field_count(); i++) {
        GenerateStructField(descriptor->field(i), printer, oneof);
    }
    
    std::vector<const FieldDescriptor*> messages;
    // 处理非repeated message成员
    for (int i = 0; i < descriptor->field_count(); i++) {
        if (!IsRepeated(descriptor->field(i)) && 
            IsMessage(descriptor->field(i)) && descriptor->field(i)->containing_oneof() == NULL)
        {
            messages.push_back(descriptor->field(i));
        }
    }
    // 打印结构体has_flag_数组成员
    if (messages.size() > 0) {
        int bytes = messages.size() / 8;
        if (messages.size() % 8) bytes++;
        printer.Print(
                "uint8_t $has_flag$[$bytes$];\n", 
                "has_flag", GetMessageFieldHasFlagVarName(),
                "bytes", SimpleItoa(bytes));
    }
    // 打印结构体成员函数
    for (int i = 0; i < descriptor->field_count(); i++){
         GenerateStructFieldFunc(i, descriptor->field(i), printer);
    }

    printer.Outdent();
    printer.Outdent();
    printer.Print(vars, "};\n");
}

void CGenerator::
GenerateCachedSizeStructForwardDeclaration(const Descriptor* descriptor, Printer& printer) const
{
    map<string, string> vars;
    vars["name"] = GetCCachedSizeStructName(descriptor); 
    printer.Print(vars, "struct tag$name$;\n");
    printer.Print(vars, "typedef struct tag$name$ $name$;\n");
}

void CGenerator::
GenerateCachedSizeStruct(const Descriptor* descriptor, Printer& printer) const {

    map<string, string> vars;
    vars["name"] = GetCCachedSizeStructName(descriptor); 
    printer.Print(vars, "struct tag$name$ {\n");
    printer.Indent(); 
    printer.Indent(); 

    set<string> oneof;
    for (int i = 0; i < descriptor->field_count(); i++){
        GenerateCachedSizeStructField(descriptor->field(i), printer, oneof);
    }
    printer.Print("int32_t cached_size_;\n");
    printer.Outdent();
    printer.Outdent();
    printer.Print(vars, "};\n");
}

void CGenerator::
GenerateArrayTag(const FieldDescriptor* descriptor, Printer& printer) const {

    map<string, string> vars;
    vars["name"] = descriptor->name();
    // 获取数组或string最大长度
    vector<string> max_len;
    GetMaxLen(descriptor->options(), max_len);
    vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);
    vars["max_len_2"] = max_len.size() > 1 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[1]) : SimpleItoa(kCharDefaultDefaultLen);
    
    if (IsRepeated(descriptor) && IsString(descriptor)) {
        printer.Print(vars, "[$max_len_1$][$max_len_2$]");
    } 
    else if (IsRepeated(descriptor)) {
        printer.Print(vars, "[$max_len_1$]");
    } else if (IsString(descriptor)) {
        printer.Print(vars, "[$max_len_1$]");
    }
}

void CGenerator::
GenerateCachedSizeArrayTag(const FieldDescriptor* descriptor, Printer& printer) const {

    map<string, string> vars;
    vars["name"] = descriptor->name();
    // 获取数组或string最大长度
    vector<string> max_len;
    GetMaxLen(descriptor->options(), max_len);
    vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);
    vars["max_len_2"] = max_len.size() > 1 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[1]) : SimpleItoa(kCharDefaultDefaultLen);
  
    if (IsRepeated(descriptor) && (IsString(descriptor) || IsMessage(descriptor)) ) {
        printer.Print(vars, "[$max_len_1$]");
    }
}


void CGenerator::
GenerateUnionFieldFunc(int index, const FieldDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["union_type_name"] = GetCUnionName(descriptor->containing_oneof());
    vars["one_of_select_fieldname"] = GetCStructUnionSelectFieldName(descriptor->containing_oneof());
    vars["union_field_name"] = GetCStructUnionFieldVarName(descriptor->containing_oneof());
    vars["name"] = GetMessageFieldName(descriptor);
    vars["msgname"] = GetCStructName(descriptor->message_type());
    vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
    vars["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
    vars["has_func"] = GetMessageFieldHasFuncName(descriptor);
    vars["oneof_id"] = GetCUnionFieldIDName(descriptor);
    
    std::cout << vars["name"] << std::endl;
    vars["clear_has_func"] = GetMessageFieldHasFlagClearFuncName(descriptor);
    printer.Print(vars, "inline $msgname$* $mutable_func$() {\n");
    printer.Indent();
    printer.Print(vars,
        "if ($has_func$()){\n"
        "    $one_of_select_fieldname$ = $oneof_id$\n"
        "}\n"
        "return &$union_field_name$.$name$;\n");
    printer.Outdent();
    printer.Print("}\n");

    printer.Print(vars, "inline const $msgname$& $access_func$() const {\n");
    printer.Indent();
    printer.Print(vars,
        "return $union_field_name$.$name$;\n");
    printer.Outdent();
    printer.Print("}\n");

    printer.Print(vars, "inline int $has_func$() const{\n");
    printer.Indent();
    printer.Print(vars, "return $one_of_select_fieldname$ != $oneof_id$;\n");
    printer.Outdent();
    printer.Print("}\n");

    printer.Print(vars, "inline void $clear_has_func$() {\n");
    printer.Indent();
    //TODO 考虑跟0判断的合理性
    printer.Print(vars, "$one_of_select_fieldname$ = 0;\n");
    printer.Outdent();
    printer.Print("}\n");
}

void CGenerator::GenerateFieldPimitiveFunc(const FieldDescriptor* descriptor, Printer& printer) const{
    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor);
    vars["primitivetype"] = PrimitiveTypeCName(descriptor);
    vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
    vars["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
    vars["has_func"] = GetMessageFieldHasFuncName(descriptor);
   
    //有oneof选项的字段
    if (descriptor->containing_oneof() != NULL) {
        vars["one_of_select_fieldname"] = GetCStructUnionSelectFieldName(descriptor->containing_oneof());
        vars["union_field_name"] = GetCStructUnionFieldVarName(descriptor->containing_oneof());
        vars["oneof_id"] = GetCUnionFieldIDName(descriptor);
        // set_xxxx()
        printer.Print(vars, "inline void set_$access_func$($primitivetype$ val) {\n");
        printer.Indent();
        printer.Print(vars,
            "if (!$has_func$()){\n"
            "    $one_of_select_fieldname$ = $oneof_id$;\n"
            "}\n"
            "$union_field_name$.$name$ = val;\n");
        printer.Outdent();
        printer.Print("}\n");

        // has_xxxx()
        printer.Print(vars, "inline bool $has_func$() const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $one_of_select_fieldname$ == $oneof_id$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx()
        printer.Print(vars, "inline $primitivetype$ $access_func$() const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $union_field_name$.$name$;\n");
        printer.Outdent();
        printer.Print("}\n");
        return;
    }


    if (IsRepeated(descriptor)) {
        vector<string> max_len;
        GetMaxLen(descriptor->options(), max_len);
        vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);
        vars["refer_name"] = GetCArrayLenVarName(descriptor);
        // add_xxxx
        printer.Print(vars, "inline void add_$access_func$($primitivetype$ field) {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($refer_name$ >= $max_len_1$) return;\n"
            "$name$[$refer_name$] = field;\n"
            "$refer_name$++;\n"
            "return;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size() const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx(i)
        printer.Print(vars, "inline $primitivetype$ $access_func$(int index) const{\n");
        printer.Indent();
        printer.Print(vars, "return $name$[$refer_name$];\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        // xxxx()
        printer.Print(vars, "inline $primitivetype$ $access_func$() const{\n");
        printer.Indent();
        printer.Print(vars, "return $name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // set_xxxx
        printer.Print(vars, "inline void set_$access_func$($primitivetype$ val) {\n");
        printer.Indent();
        printer.Print(vars, "$name$ = val;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
 
}

void CGenerator::GenerateFieldEnumFunc(const FieldDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;

    vars["name"] = GetMessageFieldName(descriptor);
    vars["enumname"] = GetCEnumName(descriptor->enum_type());
    vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
    vars["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
    vars["has_func"] = GetMessageFieldHasFuncName(descriptor);

    if (IsRepeated(descriptor)) {
        vector<string> max_len;
        GetMaxLen(descriptor->options(), max_len);
        vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);
        vars["refer_name"] = GetCArrayLenVarName(descriptor);
        // add_xxxx
        printer.Print(vars, "inline void add_$access_func$($enumname$ field) {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($refer_name$ >= $max_len_1$) return;\n"
            "$name$[$refer_name$] = field;\n"
            "$refer_name$++;\n"
            "return;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size() const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx(i)
        printer.Print(vars, "inline $enumname$ $access_func$(int index) const{\n");
        printer.Indent();
        printer.Print(vars, "return $name$[$refer_name$];\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        // xxxx()
        printer.Print(vars, "inline $enumname$ $access_func$() const{\n");
        printer.Indent();
        printer.Print(vars, "return $name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // set_xxxx
        printer.Print(vars, "inline void set_$access_func$($enumname$ val) {\n");
        printer.Indent();
        printer.Print(vars, "$name$ = val;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
}

void CGenerator::GenerateFieldMessageFunc(const FieldDescriptor* descriptor, Printer& printer) const{
    static int index = 0;
    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor);
    vars["msgname"] = GetCStructName(descriptor->message_type());
    vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
    vars["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
    vars["has_func"] = GetMessageFieldHasFuncName(descriptor);
    vars["clear_has_func"] = GetMessageFieldHasFlagClearFuncName(descriptor);
    vars["refer_name"] = GetCArrayLenVarName(descriptor);
    //TODO index不对
    vars["has_mask"] = SimpleItoa(1 << (index % 8));
    vars["has_index"] = SimpleItoa(index / 8);
    vars["has_var"] = GetMessageFieldHasFlagVarName();
    if (!IsRepeated(descriptor)) {
        index++;
    }
    // mutable_xxxx()
    if (IsRepeated(descriptor)) {
        vector<string> max_len;
        GetMaxLen(descriptor->options(), max_len);
        vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);

        printer.Print(vars, "inline $msgname$* add_$access_func$() {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($refer_name$ >= $max_len_1$) return NULL;\n"
            "memset($name$[$refer_name$], 0, sizeof($name$[$refer_name$]));\n"
            "$msgname$* ret = &$name$[$refer_name$]"
            "$refer_name$++;"
            "return ret;\n");
        printer.Outdent();
        printer.Print("}\n");

        printer.Print(vars, "inline void add_$access_func$(const $msgname$& field) {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($refer_name$ >= $max_len_1$) return NULL;\n"
            "$name$[$refer_name$] = field;\n"
            "$refer_name$++;\n"
            "return;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size(const $type$* fiel) const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        printer.Print(vars, "inline $msgname$* $mutable_func$() {\n");
        printer.Indent();
        printer.Print(vars,
            "if (!$has_func$()){\n"
            "    $has_var$[$has_index$] |= $has_mask$;\n"
            "}\n"
            "return &$name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }

    // xxxx()
    if (IsRepeated(descriptor)) {
        printer.Print(vars, "inline const $msgname$& $access_func$(int index) const {\n");
        printer.Indent();
        printer.Print(vars,
            "return $name$[index];\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        //printer.Print(vars, "inline int $access_func$_size(const $type$* fiel) {\n");
        printer.Print(vars, "inline int $access_func$_size() const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {

        printer.Print(vars, "inline const $msgname$& $access_func$() const {\n");
        printer.Indent();
        printer.Print(vars,
            "return $name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }

    // set_xxxx()
    if (IsRepeated(descriptor)) {
        printer.Print(vars, "inline void set_$access_func$(int index, const $msgname$& field) {\n");
        printer.Indent();
        printer.Print(vars,
            "if (index < $refer_name$ && index >= 0){\n"
            "    $name$[index] = field"
            "}\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        //printer.Print(vars, "inline int $access_func$_size(const $type$* fiel) {\n");
        printer.Print(vars, "inline int $access_func$_size() const{\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        printer.Print(vars, "inline void set_$access_func$(const $msgname$& field) {\n");
        printer.Indent();
        printer.Print(vars,
            "$name$ = field;\n");
        printer.Outdent();
        printer.Print("}\n");
    }

    // has_xxxx()
    if (IsRepeated(descriptor)) {
        printer.Print(vars, "inline int $has_func$() const{\n");
        printer.Indent();
        printer.Print(vars, "return $refer_name$ != 0;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size(const $type$* fiel) {\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        printer.Print(vars, "inline int $has_func$() const{\n");
        printer.Indent();
        printer.Print(vars, "return ($has_var$[$has_index$] & $has_mask$) != 0;\n");
        printer.Outdent();
        printer.Print("}\n");
    }

    // clear_has_xxxx()
    if (IsRepeated(descriptor)) {
        printer.Print(vars, "inline void $clear_has_func$() {\n");
        printer.Indent();
        printer.Print(vars, "$refer_name$ == 0;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size(const $type$* fiel) {\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        printer.Print(vars, "inline void $clear_has_func$() {\n");
        printer.Indent();
        printer.Print(vars, "$has_var$[$has_index$] &=  ~$has_mask$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
}

void CGenerator::GenerateFieldOneOfMessageFunc(const FieldDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    if (IsMessage(descriptor)) {
        vars["union_type_name"] = GetCUnionName(descriptor->containing_oneof());
        vars["one_of_select_fieldname"] = GetCStructUnionSelectFieldName(descriptor->containing_oneof());
        vars["union_field_name"] = GetCStructUnionFieldVarName(descriptor->containing_oneof());
        vars["name"] = GetMessageFieldName(descriptor);
        vars["msgname"] = GetCStructName(descriptor->message_type());
        vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
        vars["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
        vars["has_func"] = GetMessageFieldHasFuncName(descriptor);
        
        vars["oneof_id"] = GetCUnionFieldIDName(descriptor);

        vars["clear_has_func"] = GetMessageFieldHasFlagClearFuncName(descriptor);
        // mutable_xxxx()
        printer.Print(vars, "inline $msgname$* $mutable_func$() {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($has_func$()){\n"
            "    memset(&$union_field_name$.$name$, 0, sizeof($union_field_name$.$name$));\n"
            "    $one_of_select_fieldname$ = $oneof_id$;\n"
            "}\n"
            "return &$union_field_name$.$name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx()
        printer.Print(vars, "inline const $msgname$& $access_func$() const {\n");
        printer.Indent();
        printer.Print(vars,
            "return $union_field_name$.$name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // set_xxxx()
        printer.Print(vars, "inline void set_$access_func$(const $msgname$& field) {\n");
        printer.Indent();
        printer.Print(vars,
            "$union_field_name$.$name$ = field;\n");
        printer.Outdent();
        printer.Print("}\n");

        // has_xxxx()
        printer.Print(vars, "inline int $has_func$() const{\n");
        printer.Indent();
        printer.Print(vars, "return $one_of_select_fieldname$ != $oneof_id$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // clear_has_xxxx()
        printer.Print(vars, "inline void $clear_has_func$() {\n");
        printer.Indent();
        //TODO 考虑跟0判断的合理性
        printer.Print(vars, "$one_of_select_fieldname$ = 0;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        //TODO 优化
        GenerateFieldPimitiveFunc(descriptor, printer);
    }
}

void CGenerator::GenerateFieldCTypeFunc(const FieldDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor);
   
    vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
    vars["mutable_func"] = GetMessageFieldMutableFuncName(descriptor);
    vars["has_func"] = GetMessageFieldHasFuncName(descriptor);
    
    GOOGLE_CHECK(GetCTypeName(descriptor->options(), vars["primitivetype"]) == true);

    if (IsRepeated(descriptor)) {
        vector<string> max_len;
        GetMaxLen(descriptor->options(), max_len);
        vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);
        vars["refer_name"] = GetCArrayLenVarName(descriptor);
        // add_xxxx
        printer.Print(vars, "inline void add_$access_func$($primitivetype$ field) {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($refer_name$ >= $max_len_1$) returnl;\n"
            "$name$[$refer_name$] = field\n"
            "$refer_name$++;\n"
            "return;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size() {\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // xxxx(i)
        printer.Print(vars, "inline $primitivetype$ $name$(int index) {\n");
        printer.Indent();
        printer.Print(vars, "return $name$[$refer_name$];\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        // xxxx
        printer.Print(vars, "inline $primitivetype$ $access_func$() {\n");
        printer.Indent();
        printer.Print(vars, "return $name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // set_xxxx
        printer.Print(vars, "inline void set_$access_func$($primitivetype$ val) {\n");
        printer.Indent();
        printer.Print(vars, "$name$ = val;\n");
        printer.Outdent();
        printer.Print("}\n");
    }

}

void CGenerator::
GenerateStructFieldFunc(int index, const FieldDescriptor* descriptor, Printer& printer) const {
    
    string c_type_name;
    if (descriptor->containing_oneof() != NULL) {
        GenerateFieldOneOfMessageFunc(descriptor, printer);
    }
    else if (IsMessage(descriptor)) {
        GenerateFieldMessageFunc(descriptor, printer);
    }
    else if (IsEnum(descriptor)) {
        GenerateFieldEnumFunc(descriptor, printer);
    }
    else if (GetCTypeName(descriptor->options(), c_type_name)) {
        GenerateFieldCTypeFunc(descriptor, printer);
    }
    else if (IsString(descriptor)) {
        GenerateFieldStringFunc(descriptor, printer);
    }
    else if (IsPrimitiveType(descriptor)) {
        GenerateFieldPimitiveFunc(descriptor, printer);
    }
    else {
        GOOGLE_LOG(ERROR) << "Error Field" << descriptor->name();
    }
}

void CGenerator::GenerateFieldStringFunc(const FieldDescriptor* descriptor, Printer& printer) const{
    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor);
    vars["type"] = PrimitiveTypeCName(descriptor);
    vars["access_func"] = GetMessageFieldAccessFuncName(descriptor);
    
    if (IsRepeated(descriptor)) {
        vars["refer_name"] = GetCArrayLenVarName(descriptor);
        std::vector<std::string> max_len;
        GetMaxLen(descriptor->options(), max_len);
        vars["max_len_1"] = max_len.size() > 0 ? GetFieldOptionExtendMaxLenName(descriptor->file(), max_len[0]) : SimpleItoa(kRepeatDefaultDefaultLen);
        // xxxx()
        printer.Print(vars, "inline const $type$* $access_func$(int index) const {\n");
        printer.Indent();
        printer.Print(vars,
            "return $name$[index];\n");
        printer.Outdent();
        printer.Print("}\n");

        // add_xxxx()
        printer.Print(vars, "inline void add_$access_func$(const $type$* field) {\n");
        printer.Indent();
        printer.Print(vars,
            "if ($refer_name$ >= $max_len_1$) return;\n"
#if defined (_WIN32) || (_WIN64)
            "strncpy_s($name$[$refer_name$++],  sizeof($name$[0]), field, strlen(field));\n");
#else
            "strncpy($name$[$refer_name$++], field,  sizeof($name$[0]));$name$[$refer_name$-1][sizeof($name$[0]) - 1] = 0;\n");
#endif
        printer.Outdent();
        printer.Print("}\n");

        // xxxx_size()
        printer.Print(vars, "inline int $access_func$_size(const $type$* fiel) {\n");
        printer.Indent();
        printer.Print(vars,
            "return $refer_name$;\n");
        printer.Outdent();
        printer.Print("}\n");
    }
    else {
        // xxxx()
        printer.Print(vars, "inline const $type$* $access_func$() const {\n");
        printer.Indent();
        printer.Print(vars,
            "return $name$;\n");
        printer.Outdent();
        printer.Print("}\n");

        // set_xxxx()
        printer.Print(vars, "inline void set_$access_func$(const $type$* field) {\n");
        printer.Indent();
        printer.Print(vars,
#if defined (_WIN32) || (_WIN64)
            "strncpy_s($name$,  sizeof($name$), field, strlen(field));\n");
#else
            "strncpy($name$, field,  sizeof($name$));$name$[sizeof($name$)-1]=0;\n");
#endif
        printer.Outdent();
        printer.Print("}\n");
    }
}

void CGenerator::
GenerateStructField(const FieldDescriptor* descriptor, Printer& printer, set<string>& oneof) const {

    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor);
    vars["type"] = PrimitiveTypeCName(descriptor);
    if (descriptor->containing_oneof() != NULL) {
        string oneof_name = descriptor->containing_oneof()->name();
        if (oneof.insert(oneof_name).second == false)
            return;

        vars["msgname"] = GetCUnionName(descriptor->containing_oneof());
        vars["varname"] = GetCStructUnionFieldVarName(descriptor->containing_oneof()); 
        printer.Print(vars, "$msgname$ $varname$");
    }
    else if (IsMessage(descriptor)) {
        vars["msgname"] = GetCStructName(descriptor->message_type());
        // 非数组,需要赋值标记
        if (!IsRepeated(descriptor)) {
            vars["name"] = GetMessageFieldName(descriptor);
            printer.Print("// struct have to be access by function\n");
        }
        printer.Print(vars, "$msgname$ $name$");
    } 
    else if (IsEnum(descriptor)) {
        vars["msgname"] = GetCEnumName(descriptor->enum_type());
        printer.Print(vars, "$msgname$ $name$");
    }
    else {
        string c_type_name; 
        if (GetCTypeName(descriptor->options(), c_type_name))
        {
            vars["type"] = c_type_name; 
        }
        printer.Print(vars, "$type$ $name$");
    }
    

    // 排除oneof内有数组的异常情况
    if (descriptor->containing_oneof() == NULL) {
        GenerateArrayTag(descriptor, printer);
    }

	SourceLocation stlocation;
	descriptor->GetSourceLocation(&stlocation);
	int ipos = stlocation.trailing_comments.find_first_of('\n');
	vars["comment"] = stlocation.trailing_comments.substr(0, ipos);
    printer.Print(vars, "; /* $comment$ */ \n");

    // 如果extention中没有num_field但该字段需要refer，则添加refer字段
    if(NeedGenerateArrayLenField(descriptor)) {
        printer.Print("uint32_t $name$;\n",
                      "name", GetCArrayLenVarNameDefault(descriptor));    
    }
}

void CGenerator::
GenerateCachedSizeStructField(const FieldDescriptor* descriptor, Printer& printer, set<string>& oneof) const {

    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor);
    vars["type"] = PrimitiveTypeCName(descriptor);
    if (descriptor->containing_oneof() != NULL) {
        string oneof_name = descriptor->containing_oneof()->name();
        // handle string in union
        if(IsString(descriptor)) {
            printer.Print(vars, "int32_t $name$;\n");
        }
        if (oneof.insert(oneof_name).second == false)
            return;

        vars["msgname"] = GetCUnionName(descriptor->containing_oneof());
        vars["msgname_cached_size"] = GetCCachedSizeUnionName(descriptor->containing_oneof());
        vars["varname"] = GetCStructUnionFieldVarName(descriptor->containing_oneof()); 
        printer.Print(vars, "$msgname_cached_size$ $varname$;\n");
        return;
    } else if (IsMessage(descriptor)) {
        vars["msgname"] = GetCCachedSizeStructName(descriptor->message_type());
        printer.Print(vars, "$msgname$ $name$");
    } else if(IsRepeated(descriptor) || IsString(descriptor)) {
        printer.Print(vars, "int32_t $name$");
    } else {
        return;
    }

    // 排除oneof内有数组的异常情况
    if (descriptor->containing_oneof() == NULL) {
        GenerateCachedSizeArrayTag(descriptor, printer);
    }

    printer.Print(";\n");
}
  
void CGenerator::
GenerateUnionFieldEnum(const OneofDescriptor* descriptor, Printer& printer) const {

    map<string, string> vars;
    vars["name"] = GetCUnionEnumName(descriptor); 
    printer.Print(vars, "typedef enum tag$name$ {\n");
    printer.Indent(); 
    printer.Indent();

    for (int i = 0; i < descriptor->field_count(); i++) {
        GenerateUnionFieldEnumField(descriptor->field(i), printer);
    }
    vars["unsetname"] = ToUpper(descriptor->name()) + "_NOT_SET";
    printer.Print(vars, "$unsetname$ = 0\n");
    printer.Outdent();
    printer.Outdent();
    printer.Print(vars, "} $name$;\n\n");
}

void CGenerator::
GenerateUnionFieldEnumField(const FieldDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetCUnionEnumFieldName(descriptor);
    vars["value"] = SimpleItoa(descriptor->index() + 1);
    printer.Print(vars, "$name$ = $value$,\n");
}

void CGenerator::
GenerateUnionForwardDeclaration(const OneofDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetCUnionName(descriptor); 
    printer.Print(vars, "union tag$name$;\n");
    vars["upper_name"] = ToUpper(vars["name"]); 
    printer.Print(vars, "typedef union tag$name$ $name$;\n");
    printer.Print(vars, "typedef union tag$name$ $upper_name$;\n");
    printer.Print(vars, "typedef union tag$name$* LP$upper_name$;\n");
}

void CGenerator::
GenerateUnion(const OneofDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;

	SourceLocation stlocation;
	descriptor->GetSourceLocation(&stlocation);
	int ipos = stlocation.leading_comments.find_first_of('\n');
	vars["comment"] = stlocation.leading_comments.substr(0, ipos);


    vars["name"] = GetCUnionName(descriptor); 
    printer.Print(vars, "/* $comment$ */ \n");
    printer.Print(vars, "union tag$name$ {\n");
    printer.Indent(); 
    printer.Indent();

    for (int i = 0; i < descriptor->field_count(); i++) {
        GenerateUnionField(descriptor->field(i), printer);
    }
    printer.Outdent();
    printer.Outdent();
    printer.Print(vars, "};\n");
    
}

void CGenerator::
GenerateCachedSizeUnionForwardDeclaration(const OneofDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetCCachedSizeUnionName(descriptor); 
    printer.Print(vars, "union tag$name$;\n");
    printer.Print(vars, "typedef union tag$name$ $name$;\n");
}
 
void CGenerator::
GenerateCachedSizeUnion(const OneofDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = GetCCachedSizeUnionName(descriptor); 
    printer.Print(vars, "typedef union tag$name$ {\n");
    printer.Indent(); 
    printer.Indent();

    for (int i = 0; i < descriptor->field_count(); i++) {
        GenerateCachedSizeUnionField(descriptor->field(i), printer);
    }
    printer.Outdent();
    printer.Outdent();
    printer.Print(vars, "} $name$;\n");
}
  
void CGenerator::
GenerateUnionField(const FieldDescriptor* descriptor, Printer& printer) const {

    map<string, string> vars;
    vars["name"] = GetMessageFieldName(descriptor->name());
    vars["type"] = PrimitiveTypeCName(descriptor);
    if (IsMessage(descriptor)) {
        vars["msgname"] = descriptor->message_type()->file()->package() + descriptor->message_type()->name(); 
        printer.Print(vars, "$msgname$ $name$");
    } 
    else {
        string c_type_name; 
        if (GetCTypeName(descriptor->options(), c_type_name))
        {
            vars["type"] = c_type_name; 
        }
        printer.Print(vars, "$type$ $name$");
    }
    GenerateArrayTag(descriptor, printer);

	SourceLocation stlocation;
	descriptor->GetSourceLocation(&stlocation);
	int ipos = stlocation.trailing_comments.find_first_of('\n');
	vars["comment"] = stlocation.trailing_comments.substr(0, ipos);
    printer.Print(vars, "; /* $comment$ */ \n");
}
    
void CGenerator::
GenerateCachedSizeUnionField(const FieldDescriptor* descriptor, Printer& printer) const {
    map<string, string> vars;
    vars["name"] = descriptor->name();
    if (IsMessage(descriptor)) {
        vars["msgname"] = descriptor->message_type()->file()->package() + descriptor->message_type()->name() + "CachedSize_"; 
        printer.Print(vars, "$msgname$ $name$");
    } 
    else {
        return;
    }
    GenerateArrayTag(descriptor, printer);
    printer.Print(";\n");
}
