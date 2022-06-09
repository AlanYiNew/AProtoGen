// AConvert.cpp: 定义应用程序的入口点。
//

#include "AConvert.h"

#include <google/protobuf/compiler/plugin.h>
#include <iostream>
#include "c_generator.h"
#include <google/protobuf/compiler/cpp/generator.h>
#include <google/protobuf/compiler/command_line_interface.h>

int main(int argc, char* argv[]) {
    //CGenerator generator;
    //google::protobuf::compiler::PluginMain(
    //   argc, argv, &generator);
    google::protobuf::compiler::CommandLineInterface cli;

    // Support generation of C++ source and headers.
    google::protobuf::compiler::cpp::CppGenerator cpp_generator;
    cli.RegisterGenerator("--cpp_out", &cpp_generator,
        "Generate C++ source and header.");


    cli.RegisterGenerator("--foo_out", &cpp_generator,
        "Generate Foo file.");
    argc = 4;
    argv[1] = "--cpp_out=.";
    argv[2] = "--proto_path=C:\\Users\\guoha\\source\\repos\\AConvert\\AConvert\\";
    argv[3] = "C:\\Users\\guoha\\source\\repos\\AConvert\\AConvert\\AResource.proto";
    //std::cout << argv[2] << std:: endl;
    return cli.Run(argc, argv);
}
