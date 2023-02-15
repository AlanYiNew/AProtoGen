// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_PRIMITIVE_FIELD_H__
#define C_PRIMITIVE_FIELD_H__

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/compiler/cpp/helpers.h>

#include "c_field.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler::cpp;

class CPrimitiveFieldGenerator : public CFieldGenerator {
public:
    CPrimitiveFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateEncode(Printer* printer);
    virtual bool GenerateEncodeByteSizeLong(Printer* printer);
    virtual bool GenerateString(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateJsonEncode(Printer* printer);
    virtual bool GenerateJsonDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer);
    virtual bool GenerateAutoFillCpp(Printer* printer);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateSetWrited(Printer* printer) {return true; }
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
protected:
    // 生成读取primitive代码
    void GenerateReadPrimitive(const string& var_name,
                               const FieldDescriptor* field,
                               Printer* printer) ;
    // 获取
    string GetRandomNumber(const FieldDescriptor* descriptor);
    // 生成随机数语句
    void GenerateRandom(Printer* printer); 
protected:
    const FieldDescriptor* descriptor_;
    map<string, string> vars_;
};

// oneof primitive
class COneofPrimitiveFieldGenerator : public CPrimitiveFieldGenerator {
public:
    COneofPrimitiveFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer);
    virtual bool GenerateAutoFillCpp(Printer* printer);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
};

// repeated primitive
class CRepeatedPrimitiveFieldGenerator : public CPrimitiveFieldGenerator {
public:
    CRepeatedPrimitiveFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateEncode(Printer* printer);
    virtual bool GenerateEncodeByteSizeLong(Printer* printer);
    virtual bool GenerateString(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateJsonEncode(Printer* printer);
    virtual bool GenerateJsonDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer);
    virtual bool GenerateAutoFillCpp(Printer* printer);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
};
#endif //C_PRIMITIVE_FIELD_H__

