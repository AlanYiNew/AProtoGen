// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_MESSAGE_FIELD_H__
#define C_MESSAGE_FIELD_H__

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>

#include "c_field.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::internal;
using namespace google::protobuf::io;

class CMessageFieldGenerator : public CFieldGenerator {
public:
    CMessageFieldGenerator(const FieldDescriptor* descriptor);

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
    virtual bool GenerateSetWrited(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
protected:
    bool GenerateEncodeReal(Printer* printer);
    bool GenerateJsonEncodeReal(Printer* printer);
    bool GenerateEncodeByteSizeLongReal(Printer* printer);
    void GenerateReadMessage(const string& var_name,
                             const FieldDescriptor* field,
                             Printer* printer);
    string GetFillOrFillFullCFuncName(bool full_fill);
    string GetFillOrFillFullCppFuncName(bool full_fill);
    
protected:
    const FieldDescriptor* descriptor_;
    map<string, string> vars_;
};

class COneofMessageFieldGenerator : public CMessageFieldGenerator {
public:
    COneofMessageFieldGenerator(const FieldDescriptor* descriptor);

    // implements CFieldGenerator ------------------------------------
    virtual bool GenerateEncode(Printer* printer);
    virtual bool GenerateEncodeByteSizeLong(Printer* printer);
    virtual bool GenerateJsonEncode(Printer* printer);
    virtual bool GenerateDecode(Printer* printer);
    virtual bool GenerateAutoFillC(Printer* printer, bool full_fill=false);
    virtual bool GenerateAutoFillCpp(Printer* printer, bool full_fill=false);
    virtual bool GenerateCompareCAndCpp(Printer* printer);
    virtual bool GenerateClear(Printer* printer);
    virtual bool GenerateSetWrited(Printer* printer);
    virtual bool GenerateStringTlog(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
};

class CRepeatedMessageFieldGenerator : public CMessageFieldGenerator {
public:
    CRepeatedMessageFieldGenerator(const FieldDescriptor* descriptor);

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
    virtual bool GenerateSetWrited(Printer* printer);
    virtual bool GenerateAssignCToCpp(Printer* printer);
    virtual bool GenerateAssignCppToC(Printer* printer);
};
#endif //C_MESSAGE_FIELD_H__
