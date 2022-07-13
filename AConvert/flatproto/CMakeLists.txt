# CMakeList.txt: AConvert 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project ("AConvert")


SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(Protobuf_INCLUDE_DIR ../include/)
SET(Protobuf_LIBRARY ../lib/)
SET(CMAKE_CURRENT_BINARY_DIR ./)

SET(PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../test_proto")
SET(LIB_PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../proto")
FILE(GLOB PROTO_FILES "${PROTO_PATH}/*.proto")
FILE(GLOB LIB_PROTO_FILES "${LIB_PROTO_PATH}/*.proto")
foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" ".pb.cc" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_SOURCES ${OUTPUT_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${LIB_PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" ".pb.cc" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND LIB_PROTO_SOURCES ${OUTPUT_SOURCE}) 
endforeach()


file(GLOB SRC_FILES
        *.cpp
        *.cc
        *.h
        )

include_directories(${Protobuf_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${LIB_PROTO_PATH})
link_directories(${Protobuf_LIBRARY})
link_directories(${Protobuf_INCLUDE_DIR})

add_custom_command(OUTPUT ${LIB_PROTO_SOURCES}
                   PRE_BUILD
                   COMMAND ../lib/protoc.exe --cpp_out=${LIB_PROTO_PATH}  -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${OUTPUT_SOURCES}
                   PRE_BUILD
                   COMMAND ../lib/protoc.exe --cpp_out=${PROTO_PATH} -I${PROTO_PATH} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${LIB_PROTO_SOURCES}
                   COMMENT ${COMMAND})




# 将源代码添加到此项目的可执行文件。
add_executable(AConvert ${SRC_FILES} ${OUTPUT_SOURCES} ${LIB_PROTO_SOURCES})
target_link_libraries(AConvert libprotobuf libprotoc libprotobuf-lite)
target_compile_options(AConvert PRIVATE "/MT$<$<CONFIG:Release>:>")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AConvert PROPERTY CXX_STANDARD 14)
endif()



