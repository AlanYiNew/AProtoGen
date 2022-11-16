#ifdef ENABLE_PB_LOG
#include "comm/comm_gamecore/log_module.h"
#endif 
#include "AResource_encodec.h"
#include "pbc_extension_encodec.h"

int SerializeResInnerToArray(
  ResInner* msg_obj, uint8_t* buffer, int size) {
  ResInnerCachedSize_ cached_size;
  int32_t obj_size = ResInnerByteSizeLongWithCachedSize(msg_obj, &cached_size);
  if (obj_size < 0 || obj_size > size) {
    #ifdef ENABLE_PB_LOG
    GLOG_ERROR("buff(%d) less than obj size(%d), or obj size < 0", size, obj_size);
    #else
    printf("[ERROR][%s][%d]buff(%d) less than obj size(%d), or obj size < 0\n", __FUNCTION__, __LINE__, size, obj_size);
    #endif
    return -1;
  }
  return SerializeResInnerToArrayWithCachedSize(msg_obj, &cached_size, (::google::protobuf::uint8*)buffer, size);
}
int SerializeResInnerToArrayWithCachedSize(
  ResInner* msg_obj,  ResInnerCachedSize_* msg_obj_cached_size, ::google::protobuf::uint8* buffer, int size) {
  // @@protoc_insertion_point(serialize_to_array_start:Res.Inner)
  int32_t used_size = 0;
  int32_t temp_sub_message_size = 0;
  (void)temp_sub_message_size;

  // int32 temp = 1;
  if (msg_obj->temp != 0) {
    used_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->temp);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, msg_obj->temp, buffer);
  }

  return used_size;
  // @@protoc_insertion_point(serialize_to_array_end:Res.Inner)
}

int ResInnerByteSizeLong(
  ResInner* msg_obj) {
  ResInnerCachedSize_ cached_size;
  return ResInnerByteSizeLongWithCachedSize(msg_obj, &cached_size);
}
int ResInnerByteSizeLongWithCachedSize(
  ResInner* msg_obj,  ResInnerCachedSize_* msg_obj_cached_size) {
// @@protoc_insertion_point(message_byte_size_start:Res.Inner)
  int32_t total_size = 0;
  int32_t temp_sub_message_size = 0;
  (void)temp_sub_message_size;

  // int32 temp = 1;
  if (msg_obj->temp != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->temp);
  }

  msg_obj_cached_size->cached_size_ = total_size;
  return total_size;
}

int SerializeReshelloworldToArray(
  Reshelloworld* msg_obj, uint8_t* buffer, int size) {
  ReshelloworldCachedSize_ cached_size;
  int32_t obj_size = ReshelloworldByteSizeLongWithCachedSize(msg_obj, &cached_size);
  if (obj_size < 0 || obj_size > size) {
    #ifdef ENABLE_PB_LOG
    GLOG_ERROR("buff(%d) less than obj size(%d), or obj size < 0", size, obj_size);
    #else
    printf("[ERROR][%s][%d]buff(%d) less than obj size(%d), or obj size < 0\n", __FUNCTION__, __LINE__, size, obj_size);
    #endif
    return -1;
  }
  return SerializeReshelloworldToArrayWithCachedSize(msg_obj, &cached_size, (::google::protobuf::uint8*)buffer, size);
}
int SerializeReshelloworldToArrayWithCachedSize(
  Reshelloworld* msg_obj,  ReshelloworldCachedSize_* msg_obj_cached_size, ::google::protobuf::uint8* buffer, int size) {
  // @@protoc_insertion_point(serialize_to_array_start:Res.helloworld)
  int32_t used_size = 0;
  int32_t temp_sub_message_size = 0;
  (void)temp_sub_message_size;

  // int32 id = 1;
  if (msg_obj->id != 0) {
    used_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->id);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, msg_obj->id, buffer);
  }

  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  {
    if(msg_obj_cached_size->str > 0)
     {int32_t str_byte_size = msg_obj_cached_size->str;
      used_size += 1 +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
                            str_byte_size);
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(2,
                                                                             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(str_byte_size, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteRawToArray(msg_obj->str,
                                                                         str_byte_size, buffer);
    }

  }

  // int32 opt = 3;
  if (msg_obj->opt != 0) {
    used_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->opt);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, msg_obj->opt, buffer);
  }

  // .Res.Inner inner1 = 4;
  if (msg_obj->has_inner1()) {
    int32_t inner1_byte_size = msg_obj_cached_size->inner1.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner1_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             4,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner1_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner1(), &msg_obj_cached_size->inner1, buffer, inner1_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner1", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner1", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner1_byte_size;
  }
  // .Res.Inner inner2 = 5;
  if (msg_obj->has_inner2()) {
    int32_t inner2_byte_size = msg_obj_cached_size->inner2.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner2_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             5,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner2_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner2(), &msg_obj_cached_size->inner2, buffer, inner2_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner2", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner2", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner2_byte_size;
  }
  // .Res.Inner inner3 = 6;
  if (msg_obj->has_inner3()) {
    int32_t inner3_byte_size = msg_obj_cached_size->inner3.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner3_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             6,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner3_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner3(), &msg_obj_cached_size->inner3, buffer, inner3_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner3", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner3", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner3_byte_size;
  }
  // .Res.Inner inner4 = 7;
  if (msg_obj->has_inner4()) {
    int32_t inner4_byte_size = msg_obj_cached_size->inner4.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner4_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             7,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner4_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner4(), &msg_obj_cached_size->inner4, buffer, inner4_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner4", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner4", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner4_byte_size;
  }
  // .Res.Inner inner5 = 8;
  if (msg_obj->has_inner5()) {
    int32_t inner5_byte_size = msg_obj_cached_size->inner5.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner5_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             8,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner5_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner5(), &msg_obj_cached_size->inner5, buffer, inner5_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner5", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner5", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner5_byte_size;
  }
  // .Res.Inner inner6 = 9;
  if (msg_obj->has_inner6()) {
    int32_t inner6_byte_size = msg_obj_cached_size->inner6.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner6_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             9,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner6_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner6(), &msg_obj_cached_size->inner6, buffer, inner6_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner6", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner6", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner6_byte_size;
  }
  // .Res.Inner inner7 = 10;
  if (msg_obj->has_inner7()) {
    int32_t inner7_byte_size = msg_obj_cached_size->inner7.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner7_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             10,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner7_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner7(), &msg_obj_cached_size->inner7, buffer, inner7_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner7", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner7", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner7_byte_size;
  }
  // .Res.Inner inner8 = 11;
  if (msg_obj->has_inner8()) {
    int32_t inner8_byte_size = msg_obj_cached_size->inner8.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner8_byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             11,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner8_byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner8(), &msg_obj_cached_size->inner8, buffer, inner8_byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner8", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner8", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner8_byte_size;
  }
  // repeated string stringList = 15 [(.PBCExt.max_len_1) = "10", (.PBCExt.max_len_2) = "20"];
  if(msg_obj->stringListSize != 0) {
    const int count = msg_obj->stringListSize;
    if (count < 0 || count > (int)(sizeof(msg_obj->stringList)/sizeof(msg_obj->stringList[0]))) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s[%d] invalid value, please check", "", "stringListSize", count);
      #else
      printf("[ERROR][%s][%d]%s.%s[%d] invalid value, please check\n", __FUNCTION__, __LINE__, "", "stringListSize", count);
      #endif
      return -1;
    }
    for (int32_t i = 0; i < count; i++) {
      int32_t stringList_byte_size = msg_obj_cached_size->stringList[i];
      used_size += 1 +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
                            stringList_byte_size);
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(15,
                                                                             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(stringList_byte_size, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteRawToArray(msg_obj->stringList[i],
                                                                         stringList_byte_size, buffer);
    }
  }

  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  if (msg_obj->enumValListSize > 0) {
    int32_t enumValList_byte_size = msg_obj_cached_size->enumValList;
    const int n = msg_obj->enumValListSize;
    used_size += 2 +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
                          enumValList_byte_size);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             16,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(
             enumValList_byte_size), buffer);

    for (int i = 0; i < n; i++) {
      buffer = ::google::protobuf::internal::WireFormatLite::WriteEnumNoTagToArray(
             msg_obj->enumValList[i], buffer);
    }
  }
  // .Res.NumVal enumVal = 17;
  if (msg_obj->enumVal != 0) {
    used_size += 2 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(msg_obj->enumVal);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      17, msg_obj->enumVal, buffer);
  }

  switch (msg_obj->id) {
    // float a = 12 [(.PBCExt.oneof_id) = "NUMVAL0"];
    case RES_NUMVAL0: {
      used_size += 1 + 4;
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(12, msg_obj->stObject.a, buffer);
      break;
    }
    // uint32 b = 13 [(.PBCExt.oneof_id) = "NUMVAL1"];
    case RES_NUMVAL1: {
      used_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          msg_obj->stObject.b);
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(13, msg_obj->stObject.b, buffer);
      break;
    }
    // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "NUMVAL2"];
    case RES_NUMVAL2: {
      {
        int32_t c_byte_size = msg_obj_cached_size->stObject.c.cached_size_;
        used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(c_byte_size) + 1;
        if(used_size > size) {
           return -1;
        }
        buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
                 14,
                 ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
                 buffer);

        buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
                 static_cast< ::google::protobuf::uint32>(c_byte_size), buffer);
        temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
                 &msg_obj->stObject.c, &msg_obj_cached_size->stObject.c, buffer, c_byte_size);
        if (temp_sub_message_size < 0) {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("%s encode error, ret code(%d)", "c", temp_sub_message_size);
          #else
          printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "c", temp_sub_message_size);
          #endif
          return temp_sub_message_size;
        }
        buffer = buffer + c_byte_size;
      }
      break;
    }
  }
  return used_size;
  // @@protoc_insertion_point(serialize_to_array_end:Res.helloworld)
}

int ReshelloworldByteSizeLong(
  Reshelloworld* msg_obj) {
  ReshelloworldCachedSize_ cached_size;
  return ReshelloworldByteSizeLongWithCachedSize(msg_obj, &cached_size);
}
int ReshelloworldByteSizeLongWithCachedSize(
  Reshelloworld* msg_obj,  ReshelloworldCachedSize_* msg_obj_cached_size) {
// @@protoc_insertion_point(message_byte_size_start:Res.helloworld)
  int32_t total_size = 0;
  int32_t temp_sub_message_size = 0;
  (void)temp_sub_message_size;

  // int32 id = 1;
  if (msg_obj->id != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->id);
  }

  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  {
    msg_obj_cached_size->str = strlen(msg_obj->str);
    if(msg_obj_cached_size->str > 0)
     {temp_sub_message_size = ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
       msg_obj_cached_size->str);
      total_size += 1 + temp_sub_message_size;
    }

  }

  // int32 opt = 3;
  if (msg_obj->opt != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->opt);
  }

  // .Res.Inner inner1 = 4;
  if (msg_obj->has_inner1()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner1(), &msg_obj_cached_size->inner1);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner1", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner1", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner2 = 5;
  if (msg_obj->has_inner2()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner2(), &msg_obj_cached_size->inner2);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner2", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner2", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner3 = 6;
  if (msg_obj->has_inner3()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner3(), &msg_obj_cached_size->inner3);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner3", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner3", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner4 = 7;
  if (msg_obj->has_inner4()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner4(), &msg_obj_cached_size->inner4);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner4", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner4", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner5 = 8;
  if (msg_obj->has_inner5()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner5(), &msg_obj_cached_size->inner5);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner5", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner5", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner6 = 9;
  if (msg_obj->has_inner6()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner6(), &msg_obj_cached_size->inner6);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner6", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner6", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner7 = 10;
  if (msg_obj->has_inner7()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner7(), &msg_obj_cached_size->inner7);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner7", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner7", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner8 = 11;
  if (msg_obj->has_inner8()) {
      temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->inner8(), &msg_obj_cached_size->inner8);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner8", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner8", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // repeated string stringList = 15 [(.PBCExt.max_len_1) = "10", (.PBCExt.max_len_2) = "20"];
  if(msg_obj->stringListSize != 0) {
    const int count = msg_obj->stringListSize;
    if (count < 0 || count > (int)(sizeof(msg_obj->stringList)/sizeof(msg_obj->stringList[0]))) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s.%s[%d] invalid value, please check", "", "stringListSize", count);
      #else
      printf("[ERROR][%s][%d]%s.%s[%d] invalid value, please check\n", __FUNCTION__, __LINE__, "", "stringListSize", count);
      #endif
      return -1;
    }
    total_size += 1 *
        ::google::protobuf::internal::FromIntSize(count);
    for (int32_t i = 0; i < count; i++) {
       msg_obj_cached_size->stringList[i] = strlen(msg_obj->stringList[i]);
       total_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
         msg_obj_cached_size->stringList[i]);
    }
  }

  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  {
    int32_t data_size = 0;
    uint32_t count = static_cast<uint32_t>(msg_obj->enumValListSize);for (uint32_t i = 0; i < count; i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
        msg_obj->enumValList[static_cast<int>(i)]);
    }
    msg_obj_cached_size->enumValList = data_size;
    if (data_size > 0) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast< ::google::protobuf::int32>(data_size));
    }
    total_size += data_size;
  }
  // .Res.NumVal enumVal = 17;
  if (msg_obj->enumVal != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(msg_obj->enumVal);
  }

  switch (msg_obj->id) {
    // float a = 12 [(.PBCExt.oneof_id) = "NUMVAL0"];
    case RES_NUMVAL0: {
      total_size += 1 + 4;
      break;
    }
    // uint32 b = 13 [(.PBCExt.oneof_id) = "NUMVAL1"];
    case RES_NUMVAL1: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          msg_obj->stObject.b);
      break;
    }
    // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "NUMVAL2"];
    case RES_NUMVAL2: {
      {
          temp_sub_message_size =     ResInnerByteSizeLongWithCachedSize(&msg_obj->stObject.c, &msg_obj_cached_size->stObject.c);
          if (temp_sub_message_size < 0) {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("%s encode error, ret code(%d)", "c", temp_sub_message_size);
          #else
          printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "c", temp_sub_message_size);
          #endif
          return temp_sub_message_size;
          }
          total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
      }

      break;
    }
  }
  msg_obj_cached_size->cached_size_ = total_size;
  return total_size;
}

