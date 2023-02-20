# CMakeList.txt: ${BIN_NAME} 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

SET(CMAKE_CXX_EXTENSIONS OFF)
SET(Protobuf_INCLUDE_DIR ../include/)
SET(Protobuf_LIBRARY ../lib/)
SET(CMAKE_CURRENT_BINARY_DIR ./)
SET(BIN_NAME AProtoGen)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("current platform: Linux ")
    SET(PROTOC_EXECUTABLE protoc)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("current platform: Windows ")
    SET(PROTOC_EXECUTABLE protoc.exe)
else()
	message("current platform: unkonw ")
endif()

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

add_custom_command(OUTPUT ${LIB_PROTO_SOURCES}
                   PRE_BUILD
                   COMMAND ../lib/${PROTOC_EXECUTABLE} --cpp_out=${LIB_PROTO_PATH}  -I${LIB_PROTO_PATH} ${LIB_PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${LIB_PROTO_FILES}
                   COMMENT ${COMMAND})

add_custom_command(OUTPUT ${OUTPUT_SOURCES}
                   PRE_BUILD
                   COMMAND ../lib/${PROTOC_EXECUTABLE} --cpp_out=${PROTO_PATH} -I${PROTO_PATH} -I${LIB_PROTO_PATH} ${PROTO_FILES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   DEPENDS ${PROTO_FILES} ${LIB_PROTO_SOURCES}
                   COMMENT ${COMMAND})

add_executable(${BIN_NAME} ${SRC_FILES} ${OUTPUT_SOURCES} ${LIB_PROTO_SOURCES})
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("current platform: Linux ")
    target_link_libraries(${BIN_NAME}  protoc protobuf protobuf-lite pthread)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("current platform: Windows ")
    target_link_libraries(${BIN_NAME} libprotobuf libprotoc libprotobuf-lite)
    target_compile_options(${BIN_NAME} PRIVATE "/MT$<$<CONFIG:Release>:>")
else()
	message("current platform: unkonw ")
endif()

# 将源代码添加到此项目的可执行文件。
target_link_directories(${BIN_NAME} PRIVATE ${Protobuf_LIBRARY} ${Protobuf_INCLUDE_DIR})
