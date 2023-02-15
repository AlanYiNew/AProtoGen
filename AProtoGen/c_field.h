// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_FIELD_H__
#define C_FIELD_H__

#include <map> 
#include <string> 

#include "c_base_generator.h"

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
class CFieldGenerator : public CBaseGenerator {
public:
    virtual ~CFieldGenerator(){};
    // 生成
    virtual bool GenerateDecode(Printer* printer) = 0;
    virtual bool GenerateEncode(Printer* printer) = 0;
    virtual bool GenerateEncodeByteSizeLong(Printer* printer) = 0;
    virtual bool GenerateString(Printer* printer) = 0;
    virtual bool GenerateJsonEncode(Printer* printer) = 0;
    virtual bool GenerateJsonDecode(Printer* printer) = 0;

    // 生成clear 代码
    virtual bool GenerateClear(Printer* printer) = 0;
    // 生成设置写标记代码
    virtual bool GenerateSetWrited(Printer* printer) = 0;
    
    // 生成赋值C成员语句
    virtual bool GenerateAutoFillC(Printer* printer) = 0;  
    virtual bool GenerateAutoFillCpp(Printer* printer) = 0;  
    // 生成自动 
    virtual bool GenerateCompareCAndCpp(Printer* printer) = 0;  

    // 生成c赋值cpp
    virtual bool GenerateAssignCToCpp(Printer* printer) = 0;
    // 生成cpp赋值c
    virtual bool GenerateAssignCppToC(Printer* printer) = 0;
};

class CFieldGeneratorMap {
public:
    CFieldGeneratorMap(const Descriptor* descriptor);
    ~CFieldGeneratorMap();
    CFieldGenerator* Get(const FieldDescriptor* descriptor);
protected:
    static CFieldGenerator* MakeGenerator(const FieldDescriptor* field);

    const Descriptor* descriptor_;
    map<const FieldDescriptor*, CFieldGenerator*> fields_;
};

void SetConstName(map<string, string>* vars);
void SetCommVar(const FieldDescriptor* descriptor, 
                map<string, string>* vars);

// 生成自动填充repteated遍历比较代码
void GenerateAutoFillIterationHead(
        map<string, string>* vars,
        Printer* printer);
void GenerateAutoFillIterationTail(
        map<string, string>* vars, 
        Printer* printer);

// 生成repeated size比较代码
void GenerateRepeatedSizeCompare(
        map<string, string>* vars, 
        Printer* printer,
        bool is_bytes);
// 生成string size比较代码
void GenerateStringSizeCompare(map<string, string>* vars, Printer* printer);
void GenerateOneofStringSizeCompare(map<string, string>* vars, Printer* printer);

#endif //C_FIELD_H__

