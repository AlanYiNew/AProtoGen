// AConvert.cpp: 定义应用程序的入口点。
//

#include "AConvert.h"
#include <google/protobuf/compiler/plugin.h>
#include <iostream>
#include "c_generator_total.h"
#include "c_generator_resource.h"
#include <google/protobuf/compiler/cpp/generator.h>
#include <google/protobuf/compiler/python/generator.h>
#include <google/protobuf/compiler/command_line_interface.h>
  
int main(int argc, char* argv[]) {
    //CGenerator generator;
    //google::protobuf::compiler::PluginMain(
    //   argc, argv, &generator);
    google::protobuf::compiler::CommandLineInterface cli;

    std::unique_ptr<CTotalGenerator> c_generator = std::make_unique<CTotalGenerator>();
    // 官方实现的C++编译器后端
    std::unique_ptr<google::protobuf::compiler::cpp::CppGenerator> cpp_generator = std::make_unique<google::protobuf::compiler::cpp::CppGenerator>();
    cli.RegisterGenerator("--cpp_out", cpp_generator.get(), "Generate C++ source and header.");
    cli.RegisterGenerator("--flat_out", "--flat_opt", c_generator.get(), "Generate Flat file.");

    std::unique_ptr<google::protobuf::compiler::python::Generator> python_generator = std::make_unique<google::protobuf::compiler::python::Generator>();
    cli.RegisterGenerator("--python3_out", python_generator.get(), "Generate C++ source and header.");

    /*
    argc = 6;
    argv[1] = "--c_out=./";
    argv[2] = "-IC:\\Users\\guoha\\source\\repos\\AConvert\\include";
    argv[3] = "-IC:\\Users\\guoha\\source\\repos\\AConvert\\proto";
    argv[4] = "-IC:\\Users\\guoha\\source\\repos\\AConvert";
    argv[5] = "C:\\Users\\guoha\\source\\repos\\AConvert\\AResource.proto";

    
    cli.RegisterGenerator("--c_out", &cgenerator,
        "Generate Foo file.");
    argc = 6;
    argv[1] = "--c_out=./";
    argv[2] = "-IC:\\Users\\guoha\\source\\repos\\AConvert\\AConvert\\include";
    argv[3] = "-IC:\\Users\\guoha\\source\\repos\\AConvert\\AConvert\\proto";
    argv[4] = "-IC:\\Users\\guoha\\source\\repos\\AConvert\\AConvert";
    argv[5] = "C:\\Users\\guoha\\source\\repos\\AConvert\\AConvert\\AResource.proto";
    */
    //std::cout << argv[2] << std:: endl;
    return cli.Run(argc, argv);
    
}



/*
int main(int argc, char* argv[]) {
    CTotalGenerator generator;
    google::protobuf::compiler::PluginMain(
        argc, argv, &generator);
    return 0;
}*/
