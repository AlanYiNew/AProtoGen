#include <sstream>
#include <string>
#include "stdio.h"
#include "AResource_json.h"
int32_t ResInnerToJson(
ResInner* msg_obj, char* buffer, int size, JSONPRINTOPTIONSPBC json_print_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.Inner)
  rapidjson::Document document;
  document.SetObject();
  rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
  int32_t func_ret = ResInnerToJsonDocument(msg_obj, &document, &allocator, json_print_option);
  if(func_ret < 0) {
     return func_ret;
  }
  rapidjson::StringBuffer sb;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
  writer.SetIndent(' ', 1);
  document.Accept(writer);
  int32_t ret_value = snprintf(buffer, size, "%s", sb.GetString());
  if(ret_value >= size) {
  #ifdef ENABLE_PB_LOG
  GLOG_ERROR("  %d.%d json string length >= buffer size, please check", ret_value, size);
  #else
  printf("[ERROR][%s][%d]  %d.%d json string length >= buffer size, please check\n", __FUNCTION__, __LINE__, ret_value, size);
  #endif
     return -1;
  }
  return ret_value;
}
int32_t ResInnerToJsonDocument(
ResInner* msg_obj, rapidjson::Document* document, rapidjson::Document::AllocatorType* allocator, JSONPRINTOPTIONSPBC json_print_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.Inner)
  // int32 temp = 1;
  if (msg_obj->temp_ != 0 || json_print_option.always_print_primitive_fields) {
    rapidjson::Value json_value;
    json_value.SetInt(msg_obj->temp_);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("temp_", json_value , *allocator);
    } else {
      document->AddMember("temp", json_value , *allocator);
    }
  }

  return 0;
}

int32_t JsonToResInner(
const char* buffer, ResInner* msg_obj, JSONPARSEOPTIONSPBC json_parse_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.Inner)
  rapidjson::Document document;
  document.SetObject();
  if(document.Parse(buffer).HasParseError()) {
  #ifdef ENABLE_PB_LOG
  GLOG_ERROR("%u.%s parse error, please check", (unsigned)document.GetErrorOffset(), GetParseError_En(document.GetParseError()));
  #else
  printf("[ERROR][%s][%d]%u.%s parse error, please check\n", __FUNCTION__, __LINE__, (unsigned)document.GetErrorOffset(), GetParseError_En(document.GetParseError()));
  #endif
      return -1;
  }
  return JsonDocumentToResInner(&document, msg_obj, json_parse_option);
}
int32_t JsonDocumentToResInner(
rapidjson::Document* document, ResInner* msg_obj, JSONPARSEOPTIONSPBC json_parse_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.Inner)
  // int32 temp = 1;
  if(document->HasMember("temp") && !(*document)["temp"].IsNull()) {
     rapidjson::Value& json_value = (*document)["temp"];
    if(!json_value.IsInt()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s json value type error, please check", "temp_", "Int");
      #else
      printf("[ERROR][%s][%d]%s.%s json value type error, please check\n", __FUNCTION__, __LINE__, "temp_", "Int");
      #endif
      return -3;
    }
    msg_obj->temp_ = json_value.GetInt();
  }
  return 0;
}

int32_t ReshelloworldToJson(
Reshelloworld* msg_obj, char* buffer, int size, JSONPRINTOPTIONSPBC json_print_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.helloworld)
  rapidjson::Document document;
  document.SetObject();
  rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
  int32_t func_ret = ReshelloworldToJsonDocument(msg_obj, &document, &allocator, json_print_option);
  if(func_ret < 0) {
     return func_ret;
  }
  rapidjson::StringBuffer sb;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
  writer.SetIndent(' ', 1);
  document.Accept(writer);
  int32_t ret_value = snprintf(buffer, size, "%s", sb.GetString());
  if(ret_value >= size) {
  #ifdef ENABLE_PB_LOG
  GLOG_ERROR("  %d.%d json string length >= buffer size, please check", ret_value, size);
  #else
  printf("[ERROR][%s][%d]  %d.%d json string length >= buffer size, please check\n", __FUNCTION__, __LINE__, ret_value, size);
  #endif
     return -1;
  }
  return ret_value;
}
int32_t ReshelloworldToJsonDocument(
Reshelloworld* msg_obj, rapidjson::Document* document, rapidjson::Document::AllocatorType* allocator, JSONPRINTOPTIONSPBC json_print_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.helloworld)
  // int32 id = 1;
  if (msg_obj->id_ != 0 || json_print_option.always_print_primitive_fields) {
    rapidjson::Value json_value;
    json_value.SetInt(msg_obj->id_);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("id_", json_value , *allocator);
    } else {
      document->AddMember("id", json_value , *allocator);
    }
  }

  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  {
    if(strlen(msg_obj->str_) > 0 || json_print_option.always_print_primitive_fields) {
       rapidjson::Value json_value;
       if(json_print_option.url_encode_strings) {
         std::string temp = UrlEncode(std::string(msg_obj->str_));
         json_value.SetString(temp.c_str(), temp.size(), *allocator);
       }
       else {
         json_value.SetString(rapidjson::StringRef(msg_obj->str_));
       }
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("str_", json_value , *allocator);
    } else {
      document->AddMember("str", json_value , *allocator);
    }
    }
  }

  // int32 opt = 3;
  if (msg_obj->opt_ != 0 || json_print_option.always_print_primitive_fields) {
    rapidjson::Value json_value;
    json_value.SetInt(msg_obj->opt_);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("opt_", json_value , *allocator);
    } else {
      document->AddMember("opt", json_value , *allocator);
    }
  }

  // .Res.Inner inner1 = 4;
  if (msg_obj->has_inner1()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner1_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner1_", json_value , *allocator);
    } else {
      document->AddMember("inner1", json_value , *allocator);
    }
  }
  // .Res.Inner inner2 = 5;
  if (msg_obj->has_inner2()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner2_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner2_", json_value , *allocator);
    } else {
      document->AddMember("inner2", json_value , *allocator);
    }
  }
  // .Res.Inner inner3 = 6;
  if (msg_obj->has_inner3()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner3_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner3_", json_value , *allocator);
    } else {
      document->AddMember("inner3", json_value , *allocator);
    }
  }
  // .Res.Inner inner4 = 7;
  if (msg_obj->has_inner4()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner4_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner4_", json_value , *allocator);
    } else {
      document->AddMember("inner4", json_value , *allocator);
    }
  }
  // .Res.Inner inner5 = 8;
  if (msg_obj->has_inner5()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner5_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner5_", json_value , *allocator);
    } else {
      document->AddMember("inner5", json_value , *allocator);
    }
  }
  // .Res.Inner inner6 = 9;
  if (msg_obj->has_inner6()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner6_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner6_", json_value , *allocator);
    } else {
      document->AddMember("inner6", json_value , *allocator);
    }
  }
  // .Res.Inner inner7 = 10;
  if (msg_obj->has_inner7()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner7_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner7_", json_value , *allocator);
    } else {
      document->AddMember("inner7", json_value , *allocator);
    }
  }
  // .Res.Inner inner8 = 11;
  if (msg_obj->has_inner8()) {
    rapidjson::Document sub_message_document;
    sub_message_document.SetObject();
    int32_t ret = ResInnerToJsonDocument(&msg_obj->inner8_, &sub_message_document, allocator, json_print_option);
    if (ret != 0) return ret;
    rapidjson::Value json_value;
    json_value.Swap(sub_message_document);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("inner8_", json_value , *allocator);
    } else {
      document->AddMember("inner8", json_value , *allocator);
    }
  }
  // repeated string stringList = 15 [(.PBCExt.max_len_1) = "10", (.PBCExt.max_len_2) = "20"];
  if(msg_obj->stringListSize != 0) {
    const int count = msg_obj->stringListSize;
    if (count < 0 || count > (int)(sizeof(msg_obj->stringList_)/sizeof(msg_obj->stringList_[0]))) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s[%d] invalid value, please check", "", "stringListSize", count);
      #else
      printf("[ERROR][%s][%d]%s.%s[%d] invalid value, please check\n", __FUNCTION__, __LINE__, "", "stringListSize", count);
      #endif
      return -1;
    }
    rapidjson::Value json_value;
    json_value.SetArray();
    if(json_print_option.url_encode_strings){ 
       rapidjson::Value string_json_value;
       for (int i = 0; i < count; i++) {
         std::string temp = UrlEncode(std::string(msg_obj->stringList_[i]));
         string_json_value.SetString(temp.c_str(), temp.size(), *allocator);    // allocate the string
         json_value.PushBack(string_json_value, *allocator);     // allocate the value
       }
    }
    else {
       for (int i = 0; i < count; i++) {
         json_value.PushBack(rapidjson::StringRef(msg_obj->stringList_[i]), *allocator);  // only need to allocate the value
       }
    }
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("stringList_", json_value , *allocator);
    } else {
      document->AddMember("stringList", json_value , *allocator);
    }
  }
  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  if(msg_obj->enumValListSize > 0 || json_print_option.always_print_primitive_fields) {
    rapidjson::Value json_value;
    json_value.SetArray();
    const int n = msg_obj->enumValListSize;
    for (int i = 0; i < n; i++) {
       json_value.PushBack(msg_obj->enumValList_[i], *allocator);
    }
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("enumValList_", json_value , *allocator);
    } else {
      document->AddMember("enumValList", json_value , *allocator);
    }
  }
  // .Res.NumVal enumVal = 17;
  if (msg_obj->enumVal_ != 0 || json_print_option.always_print_primitive_fields) {
    rapidjson::Value json_value;
    json_value.SetInt(msg_obj->enumVal_);
    if (json_print_option.preserve_proto_field_names) {
      document->AddMember("enumVal_", json_value , *allocator);
    } else {
      document->AddMember("enumVal", json_value , *allocator);
    }
  }

  switch (msg_obj->id()) {
    // float a = 12 [(.PBCExt.oneof_id) = "NUMVAL0"];
    case RES_NUMVAL0: {
      rapidjson::Value json_value;
      json_value.SetDouble(msg_obj->id_);
      if (json_print_option.preserve_proto_field_names) {
        document->AddMember("a_", json_value , *allocator);
      } else {
        document->AddMember("a", json_value , *allocator);
      }
      break;
    }
    // uint32 b = 13 [(.PBCExt.oneof_id) = "NUMVAL1"];
    case RES_NUMVAL1: {
      rapidjson::Value json_value;
      json_value.SetUint(msg_obj->id_);
      if (json_print_option.preserve_proto_field_names) {
        document->AddMember("b_", json_value , *allocator);
      } else {
        document->AddMember("b", json_value , *allocator);
      }
      break;
    }
    // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "NUMVAL2"];
    case RES_NUMVAL2: {
      {
        rapidjson::Document sub_message_document;
        sub_message_document.SetObject();
        int32_t ret = ResInnerToJsonDocument(&msg_obj->stObject.c_, &sub_message_document, allocator, json_print_option);
        if (ret != 0) return ret;
        rapidjson::Value json_value;
        json_value.Swap(sub_message_document);
        if (json_print_option.preserve_proto_field_names) {
          document->AddMember("c_", json_value , *allocator);
        } else {
          document->AddMember("c", json_value , *allocator);
        }
      }
      break;
    }
  }
  return 0;
}

int32_t JsonToReshelloworld(
const char* buffer, Reshelloworld* msg_obj, JSONPARSEOPTIONSPBC json_parse_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.helloworld)
  rapidjson::Document document;
  document.SetObject();
  if(document.Parse(buffer).HasParseError()) {
  #ifdef ENABLE_PB_LOG
  GLOG_ERROR("%u.%s parse error, please check", (unsigned)document.GetErrorOffset(), GetParseError_En(document.GetParseError()));
  #else
  printf("[ERROR][%s][%d]%u.%s parse error, please check\n", __FUNCTION__, __LINE__, (unsigned)document.GetErrorOffset(), GetParseError_En(document.GetParseError()));
  #endif
      return -1;
  }
  return JsonDocumentToReshelloworld(&document, msg_obj, json_parse_option);
}
int32_t JsonDocumentToReshelloworld(
rapidjson::Document* document, Reshelloworld* msg_obj, JSONPARSEOPTIONSPBC json_parse_option) {
// @@protoc_insertion_point(message_debug_string_start:Res.helloworld)
  // int32 id = 1;
  if(document->HasMember("id") && !(*document)["id"].IsNull()) {
     rapidjson::Value& json_value = (*document)["id"];
    if(!json_value.IsInt()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s json value type error, please check", "id_", "Int");
      #else
      printf("[ERROR][%s][%d]%s.%s json value type error, please check\n", __FUNCTION__, __LINE__, "id_", "Int");
      #endif
      return -3;
    }
    msg_obj->id_ = json_value.GetInt();
  }
  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  if(document->HasMember("str") && !(*document)["str"].IsNull()) {
     rapidjson::Value& json_value = (*document)["str"];
    if (!json_value.IsString()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s json value type error, it is supposed to be a string, please check", "str_");
      #else
      printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a string, please check\n", __FUNCTION__, __LINE__, "str_");
      #endif
      return -2;
    }
    int ret = 0;
    if(json_parse_option.url_encode_strings){ 
     std::string urldecode_str;
     int ret = UrlDecode(std::string(json_value.GetString(), json_value.GetStringLength()), urldecode_str);
    if(ret != 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s UrlDecode error, string[%s], urldecode ret[%d], please check", "str_", json_value.GetString(), ret);
      #else
      printf("[ERROR][%s][%d]%s UrlDecode error, string[%s], urldecode ret[%d], please check\n", __FUNCTION__, __LINE__, "str_", json_value.GetString(), ret);
      #endif
      return -3;
    }
       ret = snprintf(msg_obj->str_, 20, "%s", urldecode_str.c_str());
    }
    else {
       ret = snprintf(msg_obj->str_, 20, "%s", json_value.GetString());
    }
    if(ret >= 20) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%d.%d string length > array max length, please check", "str_", ret, 20);
      #else
      printf("[ERROR][%s][%d]%s.%d.%d string length > array max length, please check\n", __FUNCTION__, __LINE__, "str_", ret, 20);
      #endif
      return -4;
    }
  }
  // int32 opt = 3;
  if(document->HasMember("opt") && !(*document)["opt"].IsNull()) {
     rapidjson::Value& json_value = (*document)["opt"];
    if(!json_value.IsInt()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s json value type error, please check", "opt_", "Int");
      #else
      printf("[ERROR][%s][%d]%s.%s json value type error, please check\n", __FUNCTION__, __LINE__, "opt_", "Int");
      #endif
      return -3;
    }
    msg_obj->opt_ = json_value.GetInt();
  }
  // .Res.Inner inner1 = 4;
  if(document->HasMember("inner1") && !(*document)["inner1"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner1"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner1_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner1_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner1_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner2 = 5;
  if(document->HasMember("inner2") && !(*document)["inner2"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner2"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner2_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner2_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner2_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner3 = 6;
  if(document->HasMember("inner3") && !(*document)["inner3"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner3"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner3_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner3_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner3_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner4 = 7;
  if(document->HasMember("inner4") && !(*document)["inner4"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner4"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner4_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner4_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner4_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner5 = 8;
  if(document->HasMember("inner5") && !(*document)["inner5"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner5"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner5_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner5_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner5_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner6 = 9;
  if(document->HasMember("inner6") && !(*document)["inner6"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner6"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner6_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner6_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner6_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner7 = 10;
  if(document->HasMember("inner7") && !(*document)["inner7"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner7"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner7_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner7_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner7_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // .Res.Inner inner8 = 11;
  if(document->HasMember("inner8") && !(*document)["inner8"].IsNull()) {
     rapidjson::Value& json_value = (*document)["inner8"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "inner8_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "inner8_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->inner8_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // float a = 12 [(.PBCExt.oneof_id) = "NUMVAL0"];
  if(document->HasMember("a") && !(*document)["a"].IsNull()) {
     rapidjson::Value& json_value = (*document)["a"];
    if(!json_value.IsDouble()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s json value type error, please check", "a_", "Double");
      #else
      printf("[ERROR][%s][%d]%s.%s json value type error, please check\n", __FUNCTION__, __LINE__, "a_", "Double");
      #endif
      return -3;
    }
    msg_obj->id_ = json_value.GetDouble();
  }
  // uint32 b = 13 [(.PBCExt.oneof_id) = "NUMVAL1"];
  if(document->HasMember("b") && !(*document)["b"].IsNull()) {
     rapidjson::Value& json_value = (*document)["b"];
    if(!json_value.IsUint()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s json value type error, please check", "b_", "Uint");
      #else
      printf("[ERROR][%s][%d]%s.%s json value type error, please check\n", __FUNCTION__, __LINE__, "b_", "Uint");
      #endif
      return -3;
    }
    msg_obj->id_ = json_value.GetUint();
  }
  // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "NUMVAL2"];
  if(document->HasMember("c") && !(*document)["c"].IsNull()) {
     rapidjson::Value& json_value = (*document)["c"];
    {
      if (!json_value.IsObject()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s json value type error, it is supposed to be a Object, please check", "c_");
        #else
        printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a Object, please check\n", __FUNCTION__, __LINE__, "c_");
        #endif
        return -2;
      }
      rapidjson::Document sub_message_document;
      sub_message_document.SetObject();
      json_value.Swap(sub_message_document);
      int32_t ret = JsonDocumentToResInner(&sub_message_document, &msg_obj->stObject.c_, json_parse_option);
      if (ret != 0) return ret;
    }
  }
  // repeated string stringList = 15 [(.PBCExt.max_len_1) = "10", (.PBCExt.max_len_2) = "20"];
  if(document->HasMember("stringList") && !(*document)["stringList"].IsNull()) {
     rapidjson::Value& json_value = (*document)["stringList"];
    if (!json_value.IsArray()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s json value type error, it's supposed to be an array, please check", "stringList_");
      #else
      printf("[ERROR][%s][%d]%s json value type error, it's supposed to be an array, please check\n", __FUNCTION__, __LINE__, "stringList_");
      #endif
      return -2;
    }
    if (json_value.Size() > 10) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%d.%d json_value.Size() > $array_max$, please check", json_value.Size(), 10);
      #else
      printf("[ERROR][%s][%d]%d.%d json_value.Size() > $array_max$, please check\n", __FUNCTION__, __LINE__, json_value.Size(), 10);
      #endif
      return -3;
    }
    for (rapidjson::SizeType i = 0; i < json_value.Size(); i++) {
      if (!json_value[i].IsString()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s.%d json value in array type error, it is supposed to be a string, please check", "stringList_", i);
        #else
        printf("[ERROR][%s][%d]%s.%d json value in array type error, it is supposed to be a string, please check\n", __FUNCTION__, __LINE__, "stringList_", i);
        #endif
        return -4;
      }
      int ret = 0;
      if(json_parse_option.url_encode_strings){ 
       std::string urldecode_str;
       int ret = UrlDecode(std::string(json_value[i].GetString(), json_value[i].GetStringLength()), urldecode_str);
      if(ret != 0) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s.%d UrlDecode error, string[%s], urldecode ret[%d], please check", "stringList_", i, json_value[i].GetString(), ret);
        #else
        printf("[ERROR][%s][%d]%s.%d UrlDecode error, string[%s], urldecode ret[%d], please check\n", __FUNCTION__, __LINE__, "stringList_", i, json_value[i].GetString(), ret);
        #endif
        return -5;
      }
       ret = snprintf(msg_obj->stringList_[i], 20, "%s", urldecode_str.c_str());
      }
      else {
       ret = snprintf(msg_obj->stringList_[i], 20, "%s", json_value[i].GetString());
      }
      if (ret >= 20) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s.%d string length[%d] out of bound[%d], please check", "stringList_", i, ret, 20);
        #else
        printf("[ERROR][%s][%d]%s.%d string length[%d] out of bound[%d], please check\n", __FUNCTION__, __LINE__, "stringList_", i, ret, 20);
        #endif
        return -6;
      }
    }
    msg_obj->stringListSize = json_value.Size();
  }
  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  if(document->HasMember("enumValList") && !(*document)["enumValList"].IsNull()) {
     rapidjson::Value& json_value = (*document)["enumValList"];
    if (!json_value.IsArray()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s json value type error, it's supposed to be an array, please check", "enumValList_");
      #else
      printf("[ERROR][%s][%d]%s json value type error, it's supposed to be an array, please check\n", __FUNCTION__, __LINE__, "enumValList_");
      #endif
      return -2;
    }
    if (json_value.Size() > 1) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%d.%d json_value.Size() > $array_max$, please check", json_value.Size(), 1);
      #else
      printf("[ERROR][%s][%d]%d.%d json_value.Size() > $array_max$, please check\n", __FUNCTION__, __LINE__, json_value.Size(), 1);
      #endif
      return -3;
    }
    for (rapidjson::SizeType i = 0; i < json_value.Size(); i++){ // rapidjson uses SizeType instead of size_t.
      if (!json_value[i].IsInt()) {
        #ifdef ENABLE_PB_LOG
        GLOG_ERROR("%s.%d json value in array type error, it is supposed to be a int, please check", "enumValList_", i);
        #else
        printf("[ERROR][%s][%d]%s.%d json value in array type error, it is supposed to be a int, please check\n", __FUNCTION__, __LINE__, "enumValList_", i);
        #endif
        return -4;
      }
        msg_obj->enumValList_[i] = static_cast<RES_NumVal>(json_value[i].GetInt());
    }
    msg_obj->enumValListSize = json_value.Size();
  }
  // .Res.NumVal enumVal = 17;
  if(document->HasMember("enumVal") && !(*document)["enumVal"].IsNull()) {
     rapidjson::Value& json_value = (*document)["enumVal"];
    if (!json_value.IsInt()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s json value type error, it is supposed to be a int, please check", "enumVal_");
      #else
      printf("[ERROR][%s][%d]%s json value type error, it is supposed to be a int, please check\n", __FUNCTION__, __LINE__, "enumVal_");
      #endif
      return -2;
    }
    msg_obj->enumVal_ = static_cast<RES_NumVal>(json_value.GetInt());
  }
  return 0;
}

