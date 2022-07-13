#include <string>
#include <sstream>
#include "stdio.h"
#include "AResource_string.h"
#include"util.h"
#include <google/protobuf/util/time_util.h>
#ifdef ENABLE_PB_LOG
#include "comm/comm_gamecore/log_module.h"
#endif 
int ResInnerSimpleString(
ResInner* msg_obj, char* buffer, int size, char delimiter) {
// @@protoc_insertion_point(message_debug_string_start:Res.Inner)
  int buffer_size = size;
  int string_size = 0;
  // int32 temp = 1;
  if (msg_obj->temp != 0) {
    string_size = snprintf(buffer, buffer_size, "%d%c", msg_obj->temp, delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }

  if(size != buffer_size) {
     buffer--;
     buffer_size++;
  }
  buffer[0] = '\0';
  return size - buffer_size;
}

int ReshelloworldSimpleString(
Reshelloworld* msg_obj, char* buffer, int size, char delimiter) {
// @@protoc_insertion_point(message_debug_string_start:Res.helloworld)
  int buffer_size = size;
  int string_size = 0;
  // int32 id = 1;
  if (msg_obj->id != 0) {
    string_size = snprintf(buffer, buffer_size, "%d%c", msg_obj->id, delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }

  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  {
    for(int i = 0; msg_obj->str[i]!='\0'; i++) {
       char c = msg_obj->str[i];
       if(c == '\t') {
         string_size = snprintf(buffer, buffer_size, "\t");
       } else if(c == '\r') {
         string_size = snprintf(buffer, buffer_size, "\r");
       } else if(c == '\n') {
         string_size = snprintf(buffer, buffer_size, "\n");
       } else {
         string_size = snprintf(buffer, buffer_size, "%c", c);
       }
       if(string_size >= buffer_size) {
          return -1;
       }
       buffer_size -= string_size;
       buffer += string_size;
    }
    string_size = snprintf(buffer, buffer_size, "%c",delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }

  // int32 opt = 3;
  if (msg_obj->opt != 0) {
    string_size = snprintf(buffer, buffer_size, "%d%c", msg_obj->opt, delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }

  // .Res.Inner inner1 = 4;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner1(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner2 = 5;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner2(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner3 = 6;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner3(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner4 = 7;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner4(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner5 = 8;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner5(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner6 = 9;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner6(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner7 = 10;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner7(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.Inner inner8 = 11;
  {
    string_size = snprintf(buffer, buffer_size, "{");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = ResInnerSimpleString(&msg_obj->inner8(), buffer, buffer_size, delimiter);
    if(string_size < 0){
       return string_size;
    }
    buffer_size -= string_size;
    buffer += string_size;
    string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // repeated string stringList = 15 [(.PBCExt.max_len_1) = "10", (.PBCExt.max_len_2) = "20"];
  {
    int32_t count = static_cast<int32_t>(msg_obj->stringListSize);
    if (count < 0 || count > (int)(sizeof(msg_obj->stringList)/sizeof(msg_obj->stringList[0]))) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s[%d] invalid value, please check", "", "stringListSize", count);
      #else
      printf("[ERROR][%s][%d]%s.%s[%d] invalid value, please check\n", __FUNCTION__, __LINE__, "", "stringListSize", count);
      #endif
      return -1;
    }
    string_size = snprintf(buffer, buffer_size, "[");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    for (int i = 0; i < count; i++) {
      for (int j = 0; msg_obj->stringList[i][j] != '\0'; j++) {
         char c = msg_obj->stringList[i][j];
         if(c == '\t') {
           string_size = snprintf(buffer, buffer_size, "\t");
         } else if(c == '\r') {
           string_size = snprintf(buffer, buffer_size, "\r");
         } else if(c == '\n') {
           string_size = snprintf(buffer, buffer_size, "\n");
         } else {
           string_size = snprintf(buffer, buffer_size, "%c", c);
         }
         if(string_size >= buffer_size) {
            return -1;
         }
         buffer_size -= string_size;
         buffer += string_size;
      }
      string_size = snprintf(buffer, buffer_size, "%c", delimiter);
      if(string_size >= buffer_size) {
         return -1;
      }
      buffer_size -= string_size;
      buffer += string_size;
    }
    buffer_size++;
    buffer--;
    string_size = snprintf(buffer, buffer_size, "]%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  {
    string_size = snprintf(buffer, buffer_size, "[");
    if(string_size >= buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
    const int n = msg_obj->enumValListSize;
    for (int i = 0; i < n; i++) {
      string_size = snprintf(buffer, buffer_size, "%d%c", msg_obj->enumValList[i], delimiter);
      if(string_size >= buffer_size) {
         return -1;
      }
      buffer_size -= string_size;
      buffer += string_size;
    }
    buffer--;
    buffer_size++;
    string_size = snprintf(buffer, buffer_size, "]%c", delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }
  // .Res.NumVal enumVal = 17;
  if (msg_obj->enumVal != 0) {
    string_size = snprintf(buffer, buffer_size, "%d%c", msg_obj->enumVal, delimiter);
    if(string_size > buffer_size) {
       return -1;
    }
    buffer_size -= string_size;
    buffer += string_size;
  }

  switch (msg_obj->id) {
    // float a = 12 [(.PBCExt.oneof_id) = "1"];
    case RES_1: {
      string_size = snprintf(buffer, buffer_size, "%f%c", msg_obj->stObject.a, delimiter);
      if(string_size > buffer_size) {
         return -1;
      }
      buffer_size -= string_size;
      buffer += string_size;
      break;
    }
    // uint32 b = 13 [(.PBCExt.oneof_id) = "2"];
    case RES_2: {
      string_size = snprintf(buffer, buffer_size, "%u%c", msg_obj->stObject.b, delimiter);
      if(string_size > buffer_size) {
         return -1;
      }
      buffer_size -= string_size;
      buffer += string_size;
      break;
    }
    // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "3"];
    case RES_3: {
      {
        string_size = snprintf(buffer, buffer_size, "{");
        if(string_size >= buffer_size) {
           return -1;
        }
        buffer_size -= string_size;
        buffer += string_size;
        string_size = ResInnerSimpleString(&msg_obj->stObject.c, buffer, buffer_size, delimiter);
        if(string_size < 0){
           return string_size;
        }
        buffer_size -= string_size;
        buffer += string_size;
        string_size = snprintf(buffer, buffer_size, "}%c", delimiter);
        if(string_size > buffer_size) {
           return -1;
        }
        buffer_size -= string_size;
        buffer += string_size;
      }
      break;
    }
  }
  if(size != buffer_size) {
     buffer--;
     buffer_size++;
  }
  buffer[0] = '\0';
  return size - buffer_size;
}

