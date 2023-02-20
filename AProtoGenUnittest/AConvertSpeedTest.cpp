// AConvert.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include "AProtocol_speed_test.h"

int main(int argc, char* argv[]) {
    std::map<std::string, std::chrono::milliseconds> c_map;
    std::map<std::string, std::chrono::milliseconds> cpp_map;
    if (!run_AProtocol_encode_speed_test(c_map, cpp_map)) {
        std::cout << "Failed run_AResource_encode_speed_test" << std::endl; 
        return 0;
    }

    std::cout << "Encoding" << std::endl;
    for (auto iter: c_map) {
        std::cout << iter.first << ", c_map:" <<iter.second.count()  << std::endl;
    }

    for (auto iter: cpp_map) {
        std::cout << iter.first << ", cpp_map:" <<iter.second.count()  << std::endl;
    }

    if (!run_AProtocol_decode_speed_test(c_map, cpp_map)) {
        std::cout << "Failed run_AResource_decode_speed_test" << std::endl; 
        return 0;
    }

    std::cout << "Decoding" << std::endl;
    for (auto iter: c_map) {
        std::cout << iter.first << ", c_map:" <<iter.second.count()  << std::endl;
    }

    for (auto iter: cpp_map) {
        std::cout << iter.first << ", cpp_map:" <<iter.second.count()  << std::endl;
    }
    return 0;

}
