# CMakeList.txt: AConvert 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project ("AProtoGenUnitTest")

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
    string(REGEX REPLACE "[.]proto$" "_speed_test.cpp" SPEEDTEST_SOURCE ${PROTO_FILE})
    list(APPEND SPEEDTEST_SOURCES ${SPEEDTEST_SOURCE}) 
endforeach()

foreach(PROTO_FILE ${LIB_PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" "_speed_test.h" SPEEDTEST_LIB_SOURCE ${PROTO_FILE})
    list(APPEND SPEEDTEST_LIB_SOURCES ${SPEEDTEST_LIB_SOURCE}) 
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

file(GLOB UNITTEST_MAIN_SRC_FILES
        AConvertUnitTest.cpp
        *.cc
        *.h
        )

file(GLOB SPEEDTEST_MAIN_SRC_FILES
        AConvertSpeedTest.cpp
        *.cc
        *.h
        )

include_directories(${Protobuf_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROTO_PATH})
include_directories(${LIB_PROTO_PATH})
link_directories(${Protobuf_LIBRARY})
link_directories(${Protobuf_INCLUDE_DIR})

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("current platform: Linux ")
    SET(ACONVERT_EXECUTABLE ${CMAKE_BINARY_DIR}/AProtoGen/AProtoGen)
    SET(PROTOC_EXECUTABLE ${Protobuf_LIBRARY}/protoc)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("current platform: Windows ")
    SET(ACONVERT_EXECUTABLE ${CMAKE_BINARY_DIR}/AProtoGen/AConvert.exe)
    SET(PROTOC_EXECUTABLE ${Protobuf_LIBRARY}/protoc.exe)
    target_compile_options(AProtoGenUnitTest PRIVATE "/MTd$<$<CONFIG:Debug>:>")
else()
	message("current platform: unkonw ")
endif()

add_custom_command(OUTPUT ${OUTPUT_SOURCES} ${OUTPUT_DECODEC_SOURCES} ${OUTPUT_ENCODEC_SOURCES} ${OUTPUT_JSON_SOURCES} 
                   PRE_BUILD
                   COMMAND ${ACONVERT_EXECUTABLE} --flat_out=${PROTO_PATH}  -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${ACONVERT_EXECUTABLE}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${LIB_PROTO_CSOURCES} ${SPEEDTEST_LIB_SOURCES}
                   PRE_BUILD
                   COMMAND ${ACONVERT_EXECUTABLE} --flat_out=${LIB_PROTO_PATH} --flat_opt=test -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${ACONVERT_EXECUTABLE}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${UNITEST_SOURCES} ${SPEEDTEST_SOURCES}
                   PRE_BUILD
                   COMMAND ${ACONVERT_EXECUTABLE} --flat_out=${PROTO_PATH} --flat_opt=test -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${LIB_PROTO_SOURCES} ${ACONVERT_EXECUTABLE}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${ASSIGN_SOURCES}
                   PRE_BUILD
                   COMMAND ${ACONVERT_EXECUTABLE} --flat_out=${PROTO_PATH} --flat_opt=assign -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${LIB_PROTO_SOURCES} ${ACONVERT_EXECUTABLE}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${LIBPROTO_ASSIGN_SOURCES}
                   PRE_BUILD
                   COMMAND ${ACONVERT_EXECUTABLE} --flat_out=${LIB_PROTO_PATH} --flat_opt=assign -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${ACONVERT_EXECUTABLE}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${OUTPUT_PROTO_SOURCES}
                   PRE_BUILD
                   COMMAND ${PROTOC_EXECUTABLE} --cpp_out=${PROTO_PATH} -I${PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${Protobuf_LIBRARY}/${ACONVERT_EXECUTABLE}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${LIB_PROTO_SOURCES}
                   PRE_BUILD
                   COMMAND ${PROTOC_EXECUTABLE} --cpp_out=${LIB_PROTO_PATH} -I${LIB_PROTO_PATH} -I${Protobuf_INCLUDE_DIR} -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES} ${Protobuf_LIBRARY}/${PROTOC_EXECUTABLE}
                   COMMENT ${COMMAND})

add_executable(AProtoGenUnitTest ${LIB_PROTO_CSOURCES} ${OUTPUT_SOURCES} ${ASSIGN_SOURCES} ${LIBPROTO_ASSIGN_SOURCES} ${OUTPUT_DECODEC_SOURCES} ${OUTPUT_ENCODEC_SOURCES} ${UNITEST_SOURCES} ${OUTPUT_PROTO_SOURCES} ${LIB_PROTO_SOURCES} ${UNITTEST_MAIN_SRC_FILES} ${OUTPUT_JSON_SOURCES})
add_executable(AProtoGenSpeedTest ${LIB_PROTO_CSOURCES} ${OUTPUT_SOURCES} ${ASSIGN_SOURCES} ${LIBPROTO_ASSIGN_SOURCES} ${OUTPUT_DECODEC_SOURCES} ${OUTPUT_ENCODEC_SOURCES} ${SPEEDTEST_SOURCES} ${SPEEDTEST_LIB_SOURCES}  ${OUTPUT_PROTO_SOURCES} ${LIB_PROTO_SOURCES} ${OUTPUT_JSON_SOURCES} ${SPEEDTEST_MAIN_SRC_FILES})

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("current platform: Linux ")
    target_link_libraries(AProtoGenUnitTest  protoc protobuf protobuf-lite pthread)
    target_link_libraries(AProtoGenSpeedTest  protoc protobuf protobuf-lite pthread)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("current platform: Windows ")
    target_link_libraries(AProtoGenUnitTest libprotobuf libprotoc libprotobuf-lite)
    target_link_libraries(AProtoGenSpeedTest libprotobuf libprotoc libprotobuf-lite)
    target_compile_options(AProtoGenUnitTest PRIVATE "/MT$<$<CONFIG:Release>:>")
    target_compile_options(AProtoGenSpeedTest PRIVATE "/MT$<$<CONFIG:Release>:>")
else()
	message("current platform: unkonw ")
endif()
