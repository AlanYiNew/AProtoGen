// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_ENUM_FIELD_H__
#define C_ENUM_FIELD_H__

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

#include "c_field.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::io;

class CEnumFieldGenerator : public CFieldGenerator {
public:
    CEnumFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateEncode(Printer* printer);
    virtual bool GenerateEncodeByteSizeLong(Printer* printer);
    virtual bool GenerateString(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateJsonEncode(Printer* printer);
    virtual bool GenerateJsonDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer, bool full_fill=false);
    virtual bool GenerateAutoFillCpp(Printer* printer, bool full_fill=false);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateSetWrited(Printer* printer) { return true; }
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
protected:
    // 生成读取enum代码
    void GenerateReadEnum(const string& var_name,
                          const FieldDescriptor* field,
                          Printer* printer);
     // 生成随机数语句
    void GenerateRandom(Printer* printer, bool cpp=false);
    const EnumValueDescriptor * GetMax();
    const EnumValueDescriptor * GetMin();
protected:
    const FieldDescriptor* descriptor_;
    const EnumDescriptor* enum_descriptor_;
    map<string, string> vars_;
};

class COneofEnumFieldGenerator : public CEnumFieldGenerator {
public:
    COneofEnumFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer, bool full_fill=false);
    virtual bool GenerateAutoFillCpp(Printer* printer, bool full_fill=false);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
};

class CRepeatedEnumFieldGenerator : public CEnumFieldGenerator {
public:
    CRepeatedEnumFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateEncode(Printer* printer);
    virtual bool GenerateEncodeByteSizeLong(Printer* printer);
    virtual bool GenerateString(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateJsonEncode(Printer* printer);
    virtual bool GenerateJsonDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer, bool full_fill=false);
    virtual bool GenerateAutoFillCpp(Printer* printer, bool full_fill=false);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
protected:
    string GetRepeatedSizeName(const FieldDescriptor* field) const;
};
#endif // C_ENUM_FIELD_H__

