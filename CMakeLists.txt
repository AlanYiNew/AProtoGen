# CMakeList.txt: AConvert 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project ("AProtoGen")
add_compile_options(-std=c++17 -g)
add_subdirectory("AProtoGen")
add_subdirectory("AProtoGenUnittest")
