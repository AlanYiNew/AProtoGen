// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_STRING_FIELD_H__
#define C_STRING_FIELD_H__

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

#include "c_field.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::io;

class CStringFieldGenerator : public CFieldGenerator {
public:
    CStringFieldGenerator(const FieldDescriptor* descriptor);

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
    virtual bool GenerateSetWrited(Printer* printer) {return true; }

    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
protected:
    // 生成读取string代码
    void GenerateReadString(const string& var_name,
                            const string& max_len_name,
                            Printer* printer);
    // 生成随机字符
    void GenerateRandomHead(Printer* printer, bool fill_up); 
    void GenerateRandomTail(Printer* printer); 
    bool IsBytes();
protected:
    const FieldDescriptor* descriptor_;
    map<string, string> vars_;
    vector<string> max_len_;
};

class COneOfStringFieldGenerator : public CStringFieldGenerator {
public:
    COneOfStringFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer, bool full_fill=false);
    virtual bool GenerateAutoFillCpp(Printer* printer, bool full_fill=false);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);

    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
};

class CRepeatedStringFieldGenerator : public CStringFieldGenerator {
public:
    CRepeatedStringFieldGenerator(const FieldDescriptor* descriptor);

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
};
#endif // C_STRING_FIELD_H__

