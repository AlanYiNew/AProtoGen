// Author: lindaqiu@tencent.com (邱和林)
// Based on original Protocol Buffers 
// Generates c for a given .proto file.

#ifndef C_FILE_H__
#define C_FILE_H__

#include <vector>
#include <string>

namespace google {
namespace protobuf {
    class FileDescriptor;
} }


namespace google {
namespace protobuf {
namespace io {
    class Printer;
} } }

class CMessageGenerator;

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;

class CFileGenerator {
public:
    CFileGenerator(const FileDescriptor* descriptor);
    ~CFileGenerator();

    // 生成Clear头文件
    bool GenerateClearHeader(Printer* printer);
    // 生成Clear源文件
    bool GenerateClearSource(Printer* printer);

     // 生成Encode头文件
    bool GenerateEncodeHeader(Printer* printer);
    // 生成Encode源文件
    bool GenerateEncodeSource(Printer* printer);

    // 生成Decode头文件
    bool GenerateDecodeHeader(Printer* printer);
    // 生成Decode源文件
    bool GenerateDecodeSource(Printer* prinhuter);

    // 生成C结构体转字符串头文件
    bool GenerateStringHeader(Printer* printer);
    // 生成C结构体转字符串源文件
    bool GenerateStringSource(Printer* printer);

    // 生成C结构体和Json互转头文件
    bool GenerateJsonHeader(Printer* printer);
    // 生成C结构体和Json互转源文件
    bool GenerateJsonSource(Printer* printer);

    // 生成单元测试头文件
    bool GenerateUnitTestHeader(Printer* printer);
    // 生成单元测试源文件
    bool GenerateUnitTestSource(Printer* printer);
    // Get 单元测试文件基础名
    static string GetUnitTestFileBaseName(const string& proto); 

    // 生成性能测试头文件
    bool GenerateSpeedTestHeader(Printer* printer);
    // 生成性能测试源文件
    bool GenerateSpeedTestSource(Printer* printer);

    // 生成性能测试头文件
    bool GenerateCAndCppAssignHeader(Printer* printer);

    // Get 单元测试文件基础名
    static string GetSpeedTestFileBaseName(const string& proto); 
protected:

    // 生成通用的头文件尾部 
    void GenerateHeaderCommHead(Printer* printer);
    void GenerateHeaderCommEnd(Printer* printer);
    // 生成包含GLOG相关的头文件包含
    void GenerateGLogInclude(Printer* printer);

    // 生成解码单元测试
    void GenerateDecodeUnitTest(Printer* printer);
    string GetDecodeUnitTestFun();
    
    //生成编码单元测试
    void GenerateEncodeUnitTest(Printer* printer);
    string GetEncodeUnitTestFun();

    // 生成解码性能测试
    void GenerateDecodeSpeedTest(Printer* printer);
    string GetDecodeSpeedTestFun();
    
    //生成编码性能测试
    void GenerateEncodeSpeedTest(Printer* printer);
    string GetEncodeSpeedTestFun();
    
    // 生成Clear头文件头部信息
    void GenerateClearHeaderHead(Printer* printer);
    // 生成Clear头文件尾部信息
    void GenerateClearHeaderEnd(Printer* printer);
    // 生成Clear源文件尾部信息
    void GenerateClearSourceHead(Printer* printer);

    // 生成解码头文件头部信息
    void GenerateDecodeHeaderHead(Printer* printer);
    // 生成解码头文件尾部信息
    void GenerateDecodeHeaderEnd(Printer* printer);
    // 生成解码
    void GenerateDecodeSourceHead(Printer* printer);

    // 生成编码头文件头部信息
    void GenerateEncodeHeaderHead(Printer* printer);
    // 生成编码头文件尾部信息
    void GenerateEncodeHeaderEnd(Printer* printer);
    // 生成编码源文件头部信息
    void GenerateEncodeSourceHead(Printer* printer);

    // 生成C与Cpp赋值头文件头部信息
    void GenerateCAndCppAssignHead(Printer* printer);
protected:
    vector<CMessageGenerator*> message_generators_; 
    const FileDescriptor* descriptor_;
};

#endif // C_FILE_H__
