#ifndef ARESOURCE_JSON_H__
#define ARESOURCE_JSON_H__

#ifdef ENABLE_PB_LOG
#include "comm/comm_gamecore/log_module.h"
#endif 
#include "pbc_extension_json.h"
#include <google/protobuf/stubs/strutil.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/error/en.h"
#include"util.h"
#include "AResource.h"
#ifdef __cplusplus
extern "C"
{
#endif
int32_t ResInnerToJson(
ResInner* msg_obj, char* buffer, int size, JSONPRINTOPTIONSPBC json_print_option);
int32_t ResInnerToJsonDocument(
ResInner* msg_obj, rapidjson::Document* document, rapidjson::Document::AllocatorType* allocator, JSONPRINTOPTIONSPBC json_print_option);
int32_t JsonToResInner(
const char* buffer, ResInner* msg_obj, JSONPARSEOPTIONSPBC json_parse_option);
int32_t JsonDocumentToResInner(
rapidjson::Document* document, ResInner* msg_obj, JSONPARSEOPTIONSPBC json_parse_option);
int32_t ReshelloworldToJson(
Reshelloworld* msg_obj, char* buffer, int size, JSONPRINTOPTIONSPBC json_print_option);
int32_t ReshelloworldToJsonDocument(
Reshelloworld* msg_obj, rapidjson::Document* document, rapidjson::Document::AllocatorType* allocator, JSONPRINTOPTIONSPBC json_print_option);
int32_t JsonToReshelloworld(
const char* buffer, Reshelloworld* msg_obj, JSONPARSEOPTIONSPBC json_parse_option);
int32_t JsonDocumentToReshelloworld(
rapidjson::Document* document, Reshelloworld* msg_obj, JSONPARSEOPTIONSPBC json_parse_option);
#ifdef __cplusplus
}
#endif
#endif //