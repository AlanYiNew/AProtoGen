# CMakeList.txt: AConvert 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project ("FlatProtoUnitTest")


SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(Protobuf_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/")
SET(Protobuf_LIBRARY ../lib/)
SET(CMAKE_CURRENT_BINARY_DIR ./)

SET(PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../test_proto")
SET(LIB_PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../proto")
FILE(GLOB PROTO_FILES "${PROTO_PATH}/*.proto")
FILE(GLOB LIB_PROTO_FILES "${LIB_PROTO_PATH}/*.proto")
foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" ".h" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_SOURCES ${OUTPUT_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_encodec.cpp" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_ENCODEC_SOURCES ${OUTPUT_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_decodec.cpp" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_DECODEC_SOURCES ${OUTPUT_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_json.cpp" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_JSON_SOURCES ${OUTPUT_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${LIB_PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" ".h" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND LIB_PROTO_CSOURCES ${OUTPUT_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_unit_test.cpp" UNITEST_SOURCE ${PROTO_FILE})
    list(APPEND UNITEST_SOURCES ${UNITEST_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_speed_test.cpp" SPEEDEST_SOURCE ${PROTO_FILE})
    list(APPEND SPEEDEST_SOURCES ${SPEEDEST_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_assign.h" ASSIGN_SOURCE ${PROTO_FILE})
    list(APPEND ASSIGN_SOURCES ${ASSIGN_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${LIB_PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_assign.h" ASSIGN_SOURCE ${PROTO_FILE})
    list(APPEND LIBPROTO_ASSIGN_SOURCES ${ASSIGN_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" ".pb.cc" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_PROTO_SOURCES ${OUTPUT_SOURCE}) 
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


message(${CMAKE_BINARY_DIR}/flatproto/AConvert.exe)
add_custom_command(OUTPUT ${OUTPUT_SOURCES} ${OUTPUT_DECODEC_SOURCES} ${OUTPUT_ENCODEC_SOURCES} ${OUTPUT_JSON_SOURCES} 
                   PRE_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe --flat_out=${PROTO_PATH}  -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${LIB_PROTO_CSOURCES}
                   PRE_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe --flat_out=${LIB_PROTO_PATH} --flat_opt=test -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${UNITEST_SOURCES} ${SPEEDEST_SOURCES}
                   PRE_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe --flat_out=${PROTO_PATH} --flat_opt=test -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${LIB_PROTO_SOURCES} ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${ASSIGN_SOURCES}
                   PRE_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe --flat_out=${PROTO_PATH} --flat_opt=assign -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${LIB_PROTO_SOURCES} ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${LIBPROTO_ASSIGN_SOURCES}
                   PRE_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe --flat_out=${LIB_PROTO_PATH} --flat_opt=assign -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${CMAKE_BINARY_DIR}/flatproto/AConvert.exe
                   COMMENT ${COMMAND})

# 将源代码添加到此项目的可执行文件。
message(${UNITEST_SOURCES})

add_executable(FlatProtoUnitTest ${LIBPROTO_ASSIGN_SOURCES} ${ASSIGN_SOURCES}  ${SRC_FILES} ${OUTPUT_SOURCES} ${OUTPUT_JSON_SOURCES} ${OUTPUT_DECODEC_SOURCES} ${OUTPUT_ENCODEC_SOURCES} ${LIB_PROTO_CSOURCES} ${SPEEDEST_SOURCES} ${UNITEST_SOURCES} ${LIB_PROTO_CSOURCES} ${OUTPUT_PROTO_SOURCES} ${LIB_PROTO_SOURCES})
target_link_libraries(FlatProtoUnitTest libprotobufd libprotocd libprotobuf-lited)
target_compile_options(FlatProtoUnitTest PRIVATE "/MTd$<$<CONFIG:Debug>:>")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FlatProtoUnitTest PROPERTY CXX_STANDARD 14)
endif()



