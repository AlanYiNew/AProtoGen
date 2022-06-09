# CMakeList.txt: AConvert 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(Protobuf_INCLUDE_DIR ./include/)
SET(Protobuf_LIBRARY ./lib/)
SET(CMAKE_CURRENT_BINARY_DIR ./)
file(GLOB SRC_FILES
        *.cpp
        *.cc
        *.h
        )
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
link_directories(lib)
link_directories(include)

add_executable(AConvert ${SRC_FILES})



# 将源代码添加到此项目的可执行文件。
target_link_libraries(AConvert libprotobuf libprotoc libprotobuf-lite)
target_compile_options(AConvert PRIVATE "/MT$<$<CONFIG:Release>:>")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AConvert PROPERTY CXX_STANDARD 14)
endif()

# TODO: 如有需要，请添加测试并安装目标。
