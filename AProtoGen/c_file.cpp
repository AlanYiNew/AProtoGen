
#include <google/protobuf/stubs/strutil.h>
#include "c_generator_helpers.h"    
#include "c_message.h"    

#include "c_file.h"    

CFileGenerator::
CFileGenerator(const FileDescriptor* descriptor)
    : descriptor_(descriptor) {

  for (int i = 0; i < descriptor->message_type_count(); i++) {
      const Descriptor* message_descriptor = descriptor->message_type(i);
      CMessageGenerator* generator =
          new CMessageGenerator(message_descriptor);
      message_generators_.push_back(generator);
  }
}
    
CFileGenerator::~CFileGenerator() {
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        delete(message_generators_[i]);
    }
    message_generators_.clear();
}
    

bool CFileGenerator::
GenerateEncodeHeader(Printer* printer) {
    GenerateEncodeHeaderHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->
            GenerateEncodeDeclaration(printer);
        message_generators_[i]->
            GenerateEncodeDeclarationWithCachedSize(printer);
        message_generators_[i]->
            GenerateEncodeDeclarationByteSizeLong(printer);
        message_generators_[i]->
            GenerateEncodeDeclarationByteSizeLongWithCachedSize(printer);
    }
    GenerateEncodeHeaderEnd(printer);
    return true;
}


    
bool CFileGenerator::
GenerateClearSource(Printer* printer) {
    GenerateClearSourceHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateClearDefine(printer);
        message_generators_[i]->GenerateSetWritedDefine(printer);
    }
    return true;
}

bool CFileGenerator::
GenerateEncodeSource(Printer* printer) {
    GenerateEncodeSourceHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->
            GenerateEncodeDefine(printer);
        message_generators_[i]->
            GenerateEncodeDefineWithCachedSize(printer);
        message_generators_[i]->
            GenerateEncodeDefineByteSizeLong(printer);
        message_generators_[i]->
            GenerateEncodeDefineByteSizeLongWithCachedSize(printer);
    }
    return true;
}

void CFileGenerator::
GenerateClearSourceHead(Printer* printer) {
    printer->Print(
    "#include \"$name$.h\"\n",
    "name", GetClearFileBaseName(descriptor_->name()));
    
    
    printer->Print("\n");
}

void CFileGenerator::
GenerateEncodeSourceHead(Printer* printer) {
    // map<string, string> vars;
    // vars["name"] = StripSuffixString(descriptor_->name(), ".proto") + ".h";
    // printer->Print(vars, "#include \"$name$\"\n");

    GenerateGLogInclude(printer);
    printer->Print(
    "#include \"$name$.h\"\n",
    "name", GetEncodeFileBaseName(descriptor_->name()));
    
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetEncodeFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }
    printer->Print("\n");

}

void CFileGenerator::
GenerateEncodeHeaderEnd(Printer* printer) {
    map<string, string> vars;
    vars["name"] = ToUpper(GetEncodeFileBaseName(descriptor_->name())); 
    printer->Print(vars, 
            "#ifdef __cplusplus\n"
            "}\n"
            "#endif\n"
            "#endif //$name$_ENCODE_H__");
}

void CFileGenerator::
GenerateEncodeHeaderHead(Printer* printer) {
    map<string, string> vars;
    vars["name"] =  ToUpper(StripSuffixString(GetFileName(descriptor_->name()), ".proto")); 
    printer->Print(vars,
            "#ifndef $name$_ENCODE_H__\n"
            "#define $name$_ENCODE_H__\n\n");

    vars["name"] = StripSuffixString(descriptor_->name(), ".proto") + ".h";
    printer->Print(vars, "#include \"$name$\"\n");
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetEncodeFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }
    printer->Print("#include <google/protobuf/wire_format_lite.h>\n");
   
    printer->Print("#include <google/protobuf/io/coded_stream.h>\n");


    printer->Print("\n");  

    vars["name"] = GetBaseProtoName(descriptor_->name()) + ".h";
    printer->Print(vars, "#include \"$name$\"\n");
    printer->Print("#include <cstdint>\n");
    printer->Print(
            "#ifdef __cplusplus\n"
            "extern \"C\"\n"
            "{\n"
            "#endif\n");

    printer->Print("\n");
}


bool CFileGenerator::
GenerateClearHeader(Printer* printer) {
    GenerateClearHeaderHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateClearDeclaration(printer);
        message_generators_[i]->GenerateSetWritedDeclaration(printer);
    }
    GenerateClearHeaderEnd(printer);
    return true;
}
    
void CFileGenerator::
GenerateClearHeaderHead(Printer* printer) {

    printer->Print( 
      "#ifndef $name$_H__\n" 
      "#define $name$_H__\n\n",
      "name", ToUpper(GetClearFileBaseName(descriptor_->name())));
    for(int i = 0; i < descriptor_->dependency_count(); i++) {
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n"
          "#include \"string.h\"\n",
          "name", GetClearFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }
    // include对应的结构体定义头文件
    printer->Print(
      "#include \"$name$\"\n\n",
      "name", GetBaseProtoName(descriptor_->name()) + ".h");
    GenerateHeaderCommHead(printer);
}

void CFileGenerator::
GenerateClearHeaderEnd(Printer* printer) {
    GenerateHeaderCommEnd(printer);
}

bool CFileGenerator::
GenerateDecodeHeader(Printer* printer) {
    GenerateDecodeHeaderHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->
            GenerateDecodeDeclaration(printer);
        message_generators_[i]->
            GenerateDecodeDeclarationWithStream(printer);
    }
    GenerateDecodeHeaderEnd(printer);
    return true;
}

void CFileGenerator::
GenerateDecodeHeaderHead(Printer* printer) {
    printer->Print( 
      "#ifndef $name$_H__\n" 
      "#define $name$_H__\n\n",
      "name", ToUpper(GetDecodeFileBaseName(descriptor_->name())));
    
    // 暂时添加在decode的头文件中包含上级头文件
    // 如果只在源文件中，难以支持多层头文件包含
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetDecodeFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }
    printer->Print(
      "#include <google/protobuf/io/coded_stream.h>\n"
      "#include <google/protobuf/wire_format_lite.h>\n"
      "#include <cstdint>\n"
      "#include \"$name$\"\n",
      "name", GetBaseProtoName(descriptor_->name()) + ".h");
    GenerateHeaderCommHead(printer);
}


void CFileGenerator::
GenerateCAndCppAssignHead(Printer* printer) {
    map<string, string> vars;
    vars["uppername"] =  ToUpper(StripSuffixString(GetFileName(descriptor_->name()), ".proto"));
    vars["name"] =  StripSuffixString(GetFileName(descriptor_->name()), ".proto");
    printer->Print(vars, 
                   "#ifndef $uppername$_ASSIGN_H__\n" 
                   "#define $uppername$_ASSIGN_H__\n\n");
    printer->Print(vars, "#include \"$name$.h\"\n");
    printer->Print(vars, "#include \"$name$.pb.h\"\n");
    // 依赖头文件
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(descriptor_->dependency(i)->name())) continue;
        vars["name"] = StripSuffixString(descriptor_->dependency(i)->name(), ".proto") + "_assign.h"; 
        printer->Print(vars, "#include \"$name$\"\n");
    }
    printer->Print("#ifdef ENABLE_PB_LOG\n");
    printer->Print("#include \"comm/comm_gamecore/log_module.h\"\n");
    printer->Print("#endif \n");
    printer->Print("#include <cstdint>\n");
    printer->Print("\n");
}

void CFileGenerator::
GenerateHeaderCommHead(Printer* printer) {
    printer->Print(
      "#ifdef __cplusplus\n"
      "extern \"C\"\n"
      "{\n"
      "#endif\n");
}

void CFileGenerator::
GenerateHeaderCommEnd(Printer* printer) {
    printer->Print(
      "#ifdef __cplusplus\n"
      "}\n"
      "#endif\n"
      "#endif \n");
}

void CFileGenerator::
GenerateDecodeHeaderEnd(Printer* printer) {
    GenerateHeaderCommEnd(printer);
}
    
bool CFileGenerator::
GenerateDecodeSource(Printer* printer) {
    GenerateDecodeSourceHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->
            GenerateDecodeDefine(printer);
        message_generators_[i]->
            GenerateDecodeDefineWithStream(printer);
    }
    return true;
}

void CFileGenerator::
GenerateDecodeSourceHead(Printer* printer) {
    GenerateGLogInclude(printer);
    printer->Print(
      "#include \"$name$.h\"\n",
      "name", GetDecodeFileBaseName(descriptor_->name()));
    
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetDecodeFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }
    printer->Print("\n");
}

bool CFileGenerator::
GenerateStringHeader(Printer* printer) {
    printer->Print(
      "#ifndef $name$_H__\n" 
      "#define $name$_H__\n\n",
       "name", ToUpper(GetStringFileBaseName(descriptor_->name()))); 
    
    // 暂时添加在String的头文件中包含上级头文件
    // 如果只在源文件中，难以支持多层头文件包含
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetStringFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }

    string file_name = GetBaseProtoName(descriptor_->name());
    printer->Print(
      "#include <cstdint>\n"
      "#include \"$name$.h\"\n",
      "name", file_name);

    printer->Print(
            "#ifdef __cplusplus\n"
            "extern \"C\"\n"
            "{\n"
            "#endif\n");

    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateStringDeclaration(printer);
    }
    printer->Print("#ifdef __cplusplus\n"
            "}\n"
            "#endif\n"
            "#endif //");
    return true;
}

bool CFileGenerator::
GenerateStringSource(Printer* printer) {
    printer->Print(
      "#include <string>\n"
      "#include <sstream>\n"
      "#include \"stdio.h\"\n"
      "#include \"$name$.h\"\n"
      "#include\"util.h\"\n"
      "#include <google/protobuf/util/time_util.h>\n",
      "name", GetStringFileBaseName(descriptor_->name()));
    GenerateGLogInclude(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateStringDefine(printer);
    }
    return true;
}
    
bool CFileGenerator::
GenerateJsonHeader(Printer* printer) {
    printer->Print(
      "#ifndef $name$_H__\n" 
      "#define $name$_H__\n\n",
       "name", ToUpper(GetJsonFileBaseName(descriptor_->name()))); 
   
    GenerateGLogInclude(printer);
    // 暂时添加在Json的头文件中包含上级头文件
    // 如果只在源文件中，难以支持多层头文件包含
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetJsonFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }

    string file_name = GetBaseProtoName(descriptor_->name());
    printer->Print(
      "#include <google/protobuf/stubs/strutil.h>\n"
      "#include \"rapidjson/document.h\"\n"
      "#include \"rapidjson/writer.h\"\n"   
      "#include \"rapidjson/stringbuffer.h\"\n"
      "#include \"rapidjson/prettywriter.h\"\n"
      "#include \"rapidjson/rapidjson.h\"\n"
      "#include \"rapidjson/error/en.h\"\n"
      "#include \"util.h\"\n"
      "#include \"$name$.h\"\n",
      "name", file_name);

    printer->Print(
            "#ifdef __cplusplus\n"
            "extern \"C\"\n"
            "{\n"
            "#endif\n");
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateJsonDeclarationEncode(printer);
        message_generators_[i]->GenerateJsonDeclarationEncodeWithDocument(printer);
        message_generators_[i]->GenerateJsonDeclarationDecode(printer);
        message_generators_[i]->GenerateJsonDeclarationDecodeWithDocument(printer);
    }
    printer->Print("#ifdef __cplusplus\n"
            "}\n"
            "#endif\n"
            "#endif //");
    return true;
}

bool CFileGenerator::
GenerateJsonSource(Printer* printer) {
    printer->Print(   
      "#include <sstream>\n"
      "#include <string>\n"
      "#include \"stdio.h\"\n"
      "#include \"$name$.h\"\n",
      "name", GetJsonFileBaseName(descriptor_->name()));
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateJsonDefineEncode(printer);
        message_generators_[i]->GenerateJsonDefineEncodeWithDocument(printer);
        message_generators_[i]->GenerateJsonDefineDecode(printer);
        message_generators_[i]->GenerateJsonDefineDecodeWithDocument(printer);
    }
    return true;
}

bool CFileGenerator::
GenerateUnitTestHeader(Printer* printer) {
    printer->Print(
      "#ifndef $name$_H__\n" 
      "#define $name$_H__\n\n",
       "name", ToUpper(GetUnitTestFileBaseName(descriptor_->name()))); 
   
    string file_name = GetBaseProtoName(descriptor_->name());
    printer->Print(
      "#include <cstdint>\n"
      "#include <google/protobuf/util/json_util.h>\n"
      "#include <string>\n"
      "#include \"$name$.h\"\n"
      "#include \"$name$.pb.h\"\n"
      "#include \"$name$_decodec.h\"\n"
      "#include \"$name$_encodec.h\"\n"
      "#include \"$name$_string.h\"\n"
      "#include \"$name$_json.h\"\n"
      "#include \"$name$_speed_test.h\"\n",
      "name", file_name);

    // 暂时添加在decode的头文件中包含上级头文件
    // 如果只在源文件中，难以支持多层头文件包含
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n"
          "#include <iostream>\n"
          "#include <fstream>\n",
          "name", GetUnitTestFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }

    printer->Print("#ifdef _WIN32\n"
        "   #define random rand\n"
        "#endif\n");

    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateUnitTestDeclear(printer);
    }
    printer->Print(GetEncodeUnitTestFun().c_str());
    printer->Print(";\n");
    printer->Print(GetDecodeUnitTestFun().c_str());
    printer->Print(";\n");
    printer->Print("#endif \n");
    return true;
}

bool CFileGenerator::
GenerateUnitTestSource(Printer* printer) {
    printer->Print(
      "#include <math.h>\n"
      "#include \"$name$.h\"\n",
      "name", GetUnitTestFileBaseName(descriptor_->name()),
      "basename", GetBaseProtoName(descriptor_->name()));
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateUnitTestDefine(printer);
    }
    GenerateEncodeUnitTest(printer);
    GenerateDecodeUnitTest(printer);
    return true;
}
    
bool CFileGenerator::
GenerateSpeedTestHeader(Printer* printer) {
    printer->Print(
      "#ifndef $name$_H__\n" 
      "#define $name$_H__\n\n",
       "name", ToUpper(GetSpeedTestFileBaseName(descriptor_->name()))); 
    
    // 暂时添加在decode的头文件中包含上级头文件
    // 如果只在源文件中，难以支持多层头文件包含
    for(int i = 0; i < descriptor_->dependency_count(); i++){
        if (CBaseGenerator::kExcludeProtofile == GetFileName(
                    descriptor_->dependency(i)->name())) continue;
        printer->Print(
          "#include \"$name$\"\n",
          "name", GetSpeedTestFileBaseName(
              descriptor_->dependency(i)->name()) + ".h");
    }

    string file_name = GetBaseProtoName(descriptor_->name());
    printer->Print(
      "#include <cstdint>\n"
      "#include \"$name$.h\"\n"
      "#include \"$name$.pb.h\"\n"
      "#include \"$name$_decodec.h\"\n"
      "#include \"$name$_encodec.h\"\n",
      "name", file_name);

    printer->Print("#ifdef _WIN32\n"
        "   #define random rand\n"
        "#endif\n");
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateSpeedTestDeclear(printer);
    }
    printer->Print(GetEncodeSpeedTestFun().c_str());
    printer->Print(";\n");
    printer->Print(GetDecodeSpeedTestFun().c_str());
    printer->Print(";\n");
    printer->Print("#endif \n");
    return true;
}

bool CFileGenerator::
GenerateSpeedTestSource(Printer* printer) {
    printer->Print(
      "#include <math.h>\n"
      "#include <ctime>\n"
      "#include <map>\n"
      "#include \"$name$.h\"\n"
      "#include \"$basename$_assign.h\"\n",
      "name", GetSpeedTestFileBaseName(descriptor_->name()),
      "basename", GetBaseProtoName(descriptor_->name()));
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateSpeedTestDefine(printer);
    }
    GenerateEncodeSpeedTest(printer);
    GenerateDecodeSpeedTest(printer);
    return true;
}

bool CFileGenerator::
GenerateCAndCppAssignHeader(Printer* printer) {
    GenerateCAndCppAssignHead(printer);
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        message_generators_[i]->GenerateCpp2CDefine(printer);
        message_generators_[i]->GenerateC2CppDefine(printer);
    }
    printer->Print("#endif \n");
    return true;
}

void CFileGenerator::
GenerateEncodeUnitTest(Printer* printer) {
    printer->Print(GetEncodeUnitTestFun().c_str());
    printer->Print("{\n");
    printer->Indent();
    printer->Print("std::time_t t = std::time(nullptr);\n");
    printer->Print("srand(t);");
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        printer->Print("{\n");
        printer->Indent();
        message_generators_[i]->GenerateEncodeUnitTest(printer);
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
}

void CFileGenerator::
GenerateDecodeUnitTest(Printer* printer) {
    printer->Print(GetDecodeUnitTestFun().c_str());
    printer->Print("{\n");
    printer->Indent();
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        printer->Print("{\n");
        printer->Indent();
        message_generators_[i]->GenerateDecodeUnitTest(printer);
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
}

void CFileGenerator::
GenerateEncodeSpeedTest(Printer* printer) {
    printer->Print(GetEncodeSpeedTestFun().c_str());
    printer->Print("{\n");
    printer->Indent();
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        printer->Print("{\n");
        printer->Indent();
        message_generators_[i]->GenerateEncodeSpeedTest(printer);
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
}

void CFileGenerator::
GenerateDecodeSpeedTest(Printer* printer) {
    printer->Print(GetDecodeSpeedTestFun().c_str());
    printer->Print("{\n");
    printer->Indent();
    for (size_t i = 0; i < message_generators_.size(); ++i) {
        printer->Print("{\n");
        printer->Indent();
        message_generators_[i]->GenerateDecodeSpeedTest(printer);
        printer->Outdent();
        printer->Print("}\n");
    }
    printer->Print("return true;\n");
    printer->Outdent();
    printer->Print("}\n");
}

string CFileGenerator::
GetEncodeUnitTestFun() {
    return "bool run_" + GetBaseProtoName(descriptor_->name()) +
        "_encode_unit_test()";
}

string CFileGenerator::
GetDecodeUnitTestFun() {
    return "bool run_" + GetBaseProtoName(descriptor_->name()) +
        "_decode_unit_test()";
}

string CFileGenerator::
GetEncodeSpeedTestFun() {
    return "bool run_" + GetBaseProtoName(descriptor_->name()) +
        "_encode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map)";
}

string CFileGenerator::
GetDecodeSpeedTestFun() {
    return "bool run_" + GetBaseProtoName(descriptor_->name()) +
        "_decode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map)";
}

string CFileGenerator::
GetUnitTestFileBaseName(const string& proto)  {
    return GetBaseProtoName(proto)  + "_unit_test";
}

string CFileGenerator::
GetSpeedTestFileBaseName(const string& proto)  {
    return GetBaseProtoName(proto)  + "_speed_test";
}
    
void CFileGenerator::
GenerateGLogInclude(Printer* printer) {
   printer->Print(
           "#ifdef ENABLE_PB_LOG\n"
           "#include \"comm/comm_gamecore/log_module.h\"\n"
           "#endif \n"); 
}


