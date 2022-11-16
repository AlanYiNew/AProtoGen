// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_MESSAGE_H__
#define C_MESSAGE_H__

#include <map>
#include <set> 
#include <string> 

#include "c_base_generator.h"
#include "c_field.h"

namespace google {
namespace protobuf {
    class FieldDescriptor;
} }


namespace google {
namespace protobuf {
namespace io {
    class Printer;
} } }

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;

class CMessageGenerator {
public:
    CMessageGenerator(const Descriptor* descriptor);

    // 生成清空声明
    bool GenerateClearDeclaration(Printer* printer);
    // 生成清空定义
    bool GenerateClearDefine(Printer* printer);

    // 生成设置写标记
    bool GenerateSetWritedDeclaration(Printer* printer);
    bool GenerateSetWritedDefine(Printer* printer);

    // 生成序列化声明
    bool GenerateEncodeDeclaration(Printer* printer);
    bool GenerateEncodeDeclarationWithCachedSize(Printer* printer);
    bool GenerateEncodeDeclarationByteSizeLong(Printer* printer);
    bool GenerateEncodeDeclarationByteSizeLongWithCachedSize(Printer* printer);

    // 生成序列化函数定义
    bool GenerateEncodeDefine(Printer* printer);
    bool GenerateEncodeDefineWithCachedSize(Printer* printer);
    bool GenerateEncodeDefineByteSizeLong(Printer* printer);
    bool GenerateEncodeDefineByteSizeLongWithCachedSize(Printer* printer);

    // 生成反序列化声明
    bool GenerateDecodeDeclaration(Printer* printer);
    bool GenerateDecodeDeclarationWithStream(Printer* printer);
    // 生成反序列化函数定义
    bool GenerateDecodeDefine(Printer* printer);
    bool GenerateDecodeDefineWithStream(Printer* printer);
    
    // 生成C结构体转string声明
    bool GenerateStringDeclaration(Printer* printer);
    // 生成C结构体转string定义
    bool GenerateStringDefine(Printer* printer);
    // 生成C结构体转tlog格式string声明
    bool GenerateStringDeclarationTlog(Printer* printer);
    // 生成C结构体转tlog格式string定义
    bool GenerateStringDefineTlog(Printer* printer);

    // 生成C结构体和Json互转声明
    bool GenerateJsonDeclarationEncode(Printer* printer);
    bool GenerateJsonDeclarationDecode(Printer* printer);
    bool GenerateJsonDeclarationEncodeWithDocument(Printer* printer);
    bool GenerateJsonDeclarationDecodeWithDocument(Printer* printer);
    // 生成C结构体和Json互转定义
    bool GenerateJsonDefineEncode(Printer* printer);
    bool GenerateJsonDefineDecode(Printer* printer);
    bool GenerateJsonDefineEncodeWithDocument(Printer* printer);
    bool GenerateJsonDefineDecodeWithDocument(Printer* printer);

    //生成从cmdid获得对应oneof字段名的接口
    bool GenerateOneofFieldNameDefine(Printer* printer);
    bool GenerateOneofFieldNameDeclaration(Printer* printer);
    
    // 生成单元测试声明
    bool GenerateUnitTestDeclear(Printer* printer);
    // 生成单元测试定义
    bool GenerateUnitTestDefine(Printer* printer);
    // 生成编码测试
    bool GenerateEncodeUnitTest(Printer* printer);
    // 生成解码测试
    bool GenerateDecodeUnitTest(Printer* printer);

    // 生成性能测试声明
    bool GenerateSpeedTestDeclear(Printer* printer);
    // 生成性能测试定义
    bool GenerateSpeedTestDefine(Printer* printer);
    // 生成编码性能测试
    bool GenerateEncodeSpeedTest(Printer* printer);
    // 生成解码性能测试
    bool GenerateDecodeSpeedTest(Printer* printer);

    // 生成赋值声明
    bool GenerateC2CppDefine(Printer* printer);
    bool GenerateCpp2CDefine(Printer* printer);
protected:
    // 生成填充C/CPP函数
    bool GenerateUnitTestFillDefine(Printer* printer, 
                                    bool fill_cpp=false, 
                                    bool fill_full=false);
    bool GenerateUnitTestCompareDefine(Printer* printer);

public:
    // 获取填充C函数
    string GetFillCFun();
    // 获取填充Cpp函数
    string GetFillCppFun();
    // 获取填充满C函数
    string GetFillFullCFun();
    // 获取填充满Cpp函数
    string GetFillFullCppFun();
    // 获取比较C&Cpp函数
    string GetCompareCppFun();
    // 获取解析函数签名
    string GetClearFuncDeclaration(
            const Descriptor* descriptor);
    string GetSetWritedFuncDeclaration(
            const Descriptor* descriptor);
    string GetDecodeFuncDeclaration(
            const Descriptor* descriptor);
    string GetDecodeFuncDeclarationWithStream(
            const Descriptor* descriptor);
    string GetEncodeFuncDeclaration(
            const Descriptor* descriptor);
    string GetEncodeFuncDeclarationWithCachedSize(
            const Descriptor* descriptor);
    string GetEncodeFuncDeclarationByteSizeLong(
            const Descriptor* descriptor);
    string GetEncodeFuncDeclarationByteSizeLongWithCachedSize(
            const Descriptor* descriptor);
    string GetStringFuncDeclaration(
            const Descriptor* descriptor);
    string GetStringFuncDeclarationTlog(
            const Descriptor* descriptor);
    string GetJsonFuncDeclarationEncode(
            const Descriptor* descriptor);  
    string GetJsonFuncDeclarationEncodeWithDocument(
            const Descriptor* descriptor);  
    string GetJsonFuncDeclarationDecode(
            const Descriptor* descriptor);
    string GetJsonFuncDeclarationDecodeWithDocument(
            const Descriptor* descriptor);
    string GetOneofFieldNameFuncDeclaration(
        const Descriptor* descriptor);
    // void GenerateEncodeDefineBody(Printer* printer);

protected:
    const Descriptor* descriptor_;
    CFieldGeneratorMap  field_genertors_;
    vector<const FieldDescriptor*> fields_; // 排除oneof select与数组refer的其他字段
    map<const OneofDescriptor*, vector<const FieldDescriptor*> > oneof_fields_; // oneof field
    map<string, string> vars_;
};

#endif // C_MESSAGE_H__
