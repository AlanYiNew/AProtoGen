// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates C code for a given .proto file.

#ifndef C_GENERATOR_H__ 
#define C_GENERATOR_H__ 
#include <string>
#include <set>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

#include "c_base_generator.h"
using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::compiler;
using namespace google::protobuf::io;

class CGenerator : public CBaseGenerator {
public:

    CGenerator();
    ~CGenerator();
        
    bool Generate(const FileDescriptor* file,
                  const string& parameter,
                  GeneratorContext* generator_context,
                  string* error, bool generate_assign=false) const;

    // 生成数据结构生命定义头文件
    bool GenerateDefineFile(const FileDescriptor* file, Printer& printer) const;

    // 生成和c++对应结构体互相赋值等函数头文件
    bool GeneratorFunFile(const FileDescriptor* file, Printer& printer) const;
protected:
    /**********************************C结构声明定义文件生成*************************************/
    // 生成头文件头和include
    void GenerateHead(const FileDescriptor* file, Printer& printer) const;
    // 生成头文件尾部
    void GenerateEnd(const FileDescriptor* file, Printer& printer) const;
    // 生成enum
    void GenerateEnum(const EnumDescriptor* descriptor, Printer& printer) const;
    // 生成enum value
    void GenerateEnumValue(const  EnumValueDescriptor* descriptor, Printer& printer) const;
    // 生成结构体
    void GenerateStructForwardDeclaration(const Descriptor* descriptor, Printer& printer) const;
    void GenerateStruct(const Descriptor* descriptor, Printer& printer) const;
    // 生成结构体成员
    void GenerateStructField(const FieldDescriptor* descriptor, Printer& printer, set<string>& oneof) const;
    // 生成结构体成员函数
    void GenerateStructFieldFunc(int index, const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成cached size结构体
    void GenerateCachedSizeStructForwardDeclaration(const Descriptor* descriptor, Printer& printer) const;
    void GenerateCachedSizeStruct(const Descriptor* descriptor, Printer& printer) const;
    // 生成cached size结构体成员
    void GenerateCachedSizeStructField(const FieldDescriptor* descriptor, Printer& printer, set<string>& oneof) const;
    // 生成数组标识如"[22]"
    void GenerateArrayTag(const FieldDescriptor* descriptor, Printer& printer) const;
     // 生成cached size的数组标识如"[22]"
    void GenerateCachedSizeArrayTag(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成union
    void GenerateUnionForwardDeclaration(const OneofDescriptor* descriptor, Printer& printer) const;
    void GenerateUnion(const OneofDescriptor* descriptor, Printer& printer) const;
    void GenerateUnionFieldFunc(int index, const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成联合体成员
    void GenerateUnionField(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成cached size union
    void GenerateCachedSizeUnionForwardDeclaration(const OneofDescriptor* descriptor, Printer& printer) const;
    void GenerateCachedSizeUnion(const OneofDescriptor* descriptor, Printer& printer) const;
    // 生成cached size联合体成员
    void GenerateCachedSizeUnionField(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成联合结构体对应的enum
    void GenerateUnionFieldEnum(const OneofDescriptor* descriptor, Printer& printer) const;
    // 生成联合结构体对应的enum字段
    void GenerateUnionFieldEnumField(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成基础类型相关的函数
    void GenerateFieldPimitiveFunc(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成Message类型相关的函数
    void GenerateFieldMessageFunc(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成Enum类型相关函数
    void GenerateFieldEnumFunc(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成C类型函数
    void GenerateFieldCTypeFunc(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成Oneof字段相关函数
    void GenerateFieldOneOfMessageFunc(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成String字段相关函数
    void GenerateFieldStringFunc(const FieldDescriptor* descriptor, Printer& printer) const;
    // 生成清空所有字段的函数
    void GenerateClearFunc(const Descriptor* descriptor, Printer& printer) const;
};

#endif //C_GENERATOR_H__
