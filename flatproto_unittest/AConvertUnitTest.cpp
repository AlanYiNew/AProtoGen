// AConvert.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include "AResource_unit_test.h"

int main(int argc, char* argv[]) {
    if (!run_AResource_encode_unit_test()) {
        std::cout << "Failed run_AResource_encode_unit_test" << std::endl; 
        return 0;
    }

    if (!run_AResource_decode_unit_test()) {
        std::cout << "Failed run_AResource_decode_unit_test" << std::endl; 
        return 0;
    }
    return 0;

}
