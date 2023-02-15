#ifndef _C_GENERATOR_HELPER_H__
#define _C_GENERATOR_HELPER_H__
#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::io;

enum MessageOptionExtendTag {
    TDR_EQ_NAME_TAG = 1001,  // 对应的tdr名字
};

enum OneOfOptionExtendTag {
    ONE_OF_USE_FIELD_NAME_TAG = 1001,  //  指示oneof使用的字段名
};

//字段选项扩展字段
enum FieldOptionExtendTag {
    MAX_LEN_1_TAG = 1001,    // repeat或string 最大长度 
    MAX_LEN_2_TAG = 1002,    // repeat或string 最大长度 
    MAX_LEN_3_TAG = 1003,    // repeat或string 最大长度 
    ARRAY_NUM_USE_FIELD_TAG = 1004, // 指定数组长度的字段
    ONE_OF_FIELD_VALUE_TAG = 1005, // oneof字段值
    CTYPE_FIELD_VALUE_TAG = 1006, // C类型
    AUTO_REFER = 1007, // 不自动生成REFER
};


std::string GetFieldOptionExtendMaxLenName(const FileDescriptor* file, const std::string& name, int value);

std::string GetCEnumValueName(EnumValueDescriptor const* descriptor);

std::string GetFieldOptionExtendMaxLenName(const FileDescriptor* file, const string& name, int value);

std::string GetFieldOptionExtendMaxLenName(const FileDescriptor* file, const string& name); 

// 获取数组长度refer字段
string GetCArrayLenVarName(const FieldDescriptor* descriptor, bool fill_true=false);
// 获取默认数组长度refer字段
string GetCArrayLenVarNameDefault(const FieldDescriptor* descriptor);

// 是否需要自动生成数组长度字段
bool NeedGenerateArrayLenField(const FieldDescriptor* descriptor);
// 获取是否Strict Flat
bool GetStrictFlat(const FileDescriptor* file);
// 获取message字段访问接口名字
std::string GetMessageFieldAccessFuncName(const FieldDescriptor* descriptor);
std::string GetMessageFieldAccessFuncName(const std::string& field_name);
// 获取message字段可改变访口名字
std::string GetMessageFieldMutableFuncName(const FieldDescriptor* descriptor);
std::string GetMessageFieldMutableFuncName(const std::string& field_name);
// 获取message字段成员名字
std::string GetMessageFieldName(const FieldDescriptor* descriptor);
std::string GetMessageFieldName(const std::string field_name);
// 获取message字段标记变量名字
std::string GetMessageFieldHasFlagVarName();

// 获取message字段是否赋值接口名字
std::string GetMessageFieldHasFuncName(const FieldDescriptor* descriptor);

// 获取清空message字段是否赋值接口名字
std::string GetMessageFieldHasFlagClearFuncName(const FieldDescriptor* descriptor);

// 获取数组长度指定的字段名称
bool GetArrayUseFieldName(const FieldOptions& options, string& name);

// 获取最大长度Option
bool GetMaxLen(const FieldOptions& options, vector<string>&  max_len);

// 获取Union 的 Select VarName 
string GetCStructUnionSelectFieldName(const OneofDescriptor* descriptor);
string GetCStructUnionSelectVarName(const OneofDescriptor* descriptor);
string GetCppUnionFieldUseVarName(const OneofDescriptor* descriptor);

// 获取OneOf使用字段名字
bool GetOneOfUseFieldName(const OneofOptions& options, string& name);

//Union 字段名字
string GetCUnionFieldIDName(const FieldDescriptor* descriptor);

//Union 字段名字
string GetCUnionEnumFieldName(const FieldDescriptor* descriptor);

// 获取OneOf字段指示值名称
bool GetOneOfFieldValueName(const FieldOptions& options, string& name);  

// 获取文件路径
string GetFilePath(const string& full_path); 

// 获取文件名字
string GetFileName(const string& full_path);

//  获取proto文件名字前缀
string GetBaseProtoName(const string& name);

// 获取Union名字
std::string GetUnionWrapperName(const FieldDescriptor * field);

bool IsAllMacroNameUnique(const FileDescriptor* file);
bool put_into_map_if_not_exist(map<string, string> &vars, 
        const EnumValueDescriptor* value_descriptor);
bool IsStringOrMessage(const FieldDescriptor* field);
bool IsString(const FieldDescriptor* field);
bool IsBytes(const FieldDescriptor* field);
bool IsMessage(const FieldDescriptor* field);
bool IsEnum(const FieldDescriptor* field);
const char* PrimitiveTypeCName(const FieldDescriptor* field);
bool IsPrimitiveType(const FieldDescriptor* field);
bool IsRepeated(const FieldDescriptor* field);
// 获取C Primitive Type
// int32 test= 1;[ctype='char'] 有CType 先返回ctype 否者直接返回对应的C类型
string GetCPrimitiveType(const FieldDescriptor* field);
string GetCPrimitiveTypePrintFormat(const FieldDescriptor* field);
string GetCPrimitiveTypeJsonType(const FieldDescriptor* field);
string GetPrimitiveTypeJsonType(const FieldDescriptor* field);
// 获取Ctype
 bool GetCTypeName(const FieldOptions& options, string& name);
// 获取Message对应的tdr的结构名字
 string GetMessageTdrName(const MessageOptions& options);

// 获取字段选项扩展中最大长度指定的参数enum 常量名字
/*****************************结构体，枚举，变量，函数名生成函数*****************************/
 string GetCStructName(const Descriptor* descriptor) ; 
 string GetCCachedSizeStructName(const Descriptor* descriptor) ; 
 string GetCEnumName(const EnumDescriptor* descriptor) ; 
 string GetCUnionName(const OneofDescriptor* descriptor) ; 
 string GetCCachedSizeUnionName(const OneofDescriptor* descriptor) ; 
 string GetCUnionEnumName(const OneofDescriptor* descriptor) ; 
 string GetCStructVarName(const Descriptor* descriptor) ;
 string GetCStructUnionFieldVarName(const OneofDescriptor* descriptor) ;
 string GetCppUnionCaseFun(const OneofDescriptor* descriptor) ;
 string GetCppUnionFieldCase(const FieldDescriptor* descriptor) ;
 string GetCppUnionFieldUnsetCase(const  OneofDescriptor* descriptor) ;
 string GetTdrCStructName(const Descriptor* descriptor) ; 
 string GetTdrCStructVarName(const Descriptor* descriptor) ;

// 生成C2Cpp函数名
 string GetC2CppFunName(const Descriptor* descriptor) ; 
 string GetCpp2CFunName(const Descriptor* descriptor) ; 
 string GetCppStructFullName(const Descriptor* descriptor) ;
 string GetCppEnumFullName(const EnumDescriptor* descriptor) ;
 string GetCppStructVarName(const Descriptor* descriptor) ; 
 string GetCppFieldName(const FieldDescriptor* descriptor) ;


// 生成PBC和TdrC函数名
 string GetTdrC2PBCFunName(const Descriptor* descriptor) ; 
 string GetPBC2TdrCFunName(const Descriptor* descriptor) ; 

// c++结构重定义头文件名
 string GetCppTypedefHeaderName(const FileDescriptor* file) ;
 string GetCppHeaderName(const FileDescriptor* file) ;

// 通过值和部分名字来确定enum value descriptor
 const EnumValueDescriptor* GetEnumValue(
        const EnumDescriptor* descriptor, 
        int value, 
        const string& name) ;

// 获取message内部最大的Number
// uint32 test = 12; 12 为number, 也被称为tag, 但要区别于
// protobuf实现代码中tag含义:tag = number << 3 | field_type
// 所以本组件中的代码无特殊说明 12 称为number, tag为number
// 与field_type 组合值
 int GetFieldMaxNumber(const Descriptor* descriptor) ;
// 解析feild string 获取max_length
bool GetFieldLength(const string& field, map<string, string>& lengths);

// 获取填充C结构函数名字
string GetFillCFuncName(const FieldDescriptor * field);
string GetFillCFuncName(const Descriptor * descriptor);

// 获取填充Cpp结构函数名字
string GetFillCppFuncName(const FieldDescriptor * field);
string GetFillCppFuncName(const Descriptor * descriptor);

// 获取C与Cpp比较函数名字
string GetCompareCAndCppFuncName(const FieldDescriptor * field);
string GetCompareCAndCppFuncName(const Descriptor * descriptor);

//获取repeated size Name
string GetRepeatedSizeName(const FieldDescriptor* field);
// 获取clear函数名字
string GetClearFuncName(const Descriptor* descriptor);
// 获取初始化所有Messsage写标记函数名字
string GetSetMessageWritedFuncName(const Descriptor* descriptor);
//获取decode函数名字
string GetDecodeFuncName(const Descriptor* descriptor);
string GetDecodeFuncNameWithStream(const Descriptor* descriptor);
//获取encode函数的名字
string GetEncodeFuncName(const Descriptor* descriptor);
string GetEncodeFuncNameWithCachedSize(const Descriptor* descriptor);
string GetEncodeFuncNameByteSizeLong(const Descriptor* descriptor);
string GetEncodeFuncNameByteSizeLongWithCachedSize(const Descriptor* descriptor);
//获取C结构体转string函数名字
string GetStringFuncName(const Descriptor* descriptor);
string GetStringFuncNameTlog(const Descriptor* descriptor);
//获取C结构体转Json函数名字
string GetJsonFuncNameEncode(const Descriptor* descriptor);
string GetJsonFuncNameEncodeWithDocument(const Descriptor* descriptor);
string GetJsonFuncNameDecode(const Descriptor* descriptor);
string GetJsonFuncNameDecodeWithDocument(const Descriptor* descriptor);

string GetOneofFieldNameFuncName(const Descriptor* descriptor);

// 生成清空函数文件命
string GetClearFileBaseName(const string& proto);
// 生成C反序列化文件
string GetDecodeFileBaseName(const string& proto);
// 生成C序列化文件
string GetEncodeFileBaseName(const string& proto);
// 生成C结构体转string文件
string GetStringFileBaseName(const string& proto);
// 生成C结构体和json互转文件
string GetJsonFileBaseName(const string& proto);

const char* DeclaredTypeMethodNamePrefix(FieldDescriptor::Type type);
bool IsMapEntryMessage(const Descriptor* descriptor);
string ClassName(const Descriptor* descriptor);
int popcnt(uint32 n);
int FixedSize(FieldDescriptor::Type type);

// 将str转为 "str" 的字符串
std::string DoubleQuotesStr(const std::string str);

// 打印日志
void PrintErrorLog(Printer* printer, std::string fmt); 
void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1); 
void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1, std::string arg2); 
void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1, std::string arg2, std::string arg3); 
void PrintErrorLog(Printer* printer, std::string fmt, std::string arg1, std::string arg2, std::string arg3, std::string arg4); 

// 打印通用的fill_full 数组大小赋值头
void PrintFillFullVarDefine(Printer* printer, map<string, string>* vars, const FieldDescriptor* field);
void PrintFillFullVarDefineWithBrace(Printer* printer, map<string, string>* vars, const FieldDescriptor* field);
void PrintFillFullVarDefineWithBraceJson(Printer* printer, map<string, string>* vars, const FieldDescriptor* field);

// 打印json的AddMember函数，在json document中添加一个key-value pair
void PrintJsonAddMember(Printer* printer, map<string, string>* vars);

#endif
