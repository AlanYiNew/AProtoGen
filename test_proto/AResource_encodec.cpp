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
  const ResInner* msg_obj,  ResInnerCachedSize_* msg_obj_cached_size, ::google::protobuf::uint8* buffer, int size) {
  // @@protoc_insertion_point(serialize_to_array_start:Res.Inner)
  int32_t used_size = 0;
  int32_t temp_sub_message_size = 0;
  (void)temp_sub_message_size;

  // int32 temp = 1;
  if (msg_obj->temp_ != 0) {
    used_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->temp_);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, msg_obj->temp_, buffer);
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
  if (msg_obj->temp_ != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->temp_);
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
  const Reshelloworld* msg_obj,  ReshelloworldCachedSize_* msg_obj_cached_size, ::google::protobuf::uint8* buffer, int size) {
  // @@protoc_insertion_point(serialize_to_array_start:Res.helloworld)
  int32_t used_size = 0;
  int32_t temp_sub_message_size = 0;
  (void)temp_sub_message_size;

  // int32 id = 1;
  if (msg_obj->id_ != 0) {
    used_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->id_);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, msg_obj->id_, buffer);
  }

  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  {
    if(msg_obj_cached_size->str_ > 0)
     {int32_t str__byte_size = msg_obj_cached_size->str_;
      used_size += 1 +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
                            str__byte_size);
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(2,
                                                                             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(str__byte_size, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteRawToArray(msg_obj->str_,
                                                                         str__byte_size, buffer);
    }

  }

  // int32 opt = 3;
  if (msg_obj->opt_ != 0) {
    used_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->opt_);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, msg_obj->opt_, buffer);
  }

  // .Res.Inner inner1 = 4;
  if (msg_obj->has_inner1()) {
    int32_t inner1__byte_size = msg_obj_cached_size->inner1_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner1__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             4,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner1__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner1_, &msg_obj_cached_size->inner1_, buffer, inner1__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner1_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner1_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner1__byte_size;
  }
  // .Res.Inner inner2 = 5;
  if (msg_obj->has_inner2()) {
    int32_t inner2__byte_size = msg_obj_cached_size->inner2_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner2__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             5,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner2__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner2_, &msg_obj_cached_size->inner2_, buffer, inner2__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner2_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner2_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner2__byte_size;
  }
  // .Res.Inner inner3 = 6;
  if (msg_obj->has_inner3()) {
    int32_t inner3__byte_size = msg_obj_cached_size->inner3_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner3__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             6,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner3__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner3_, &msg_obj_cached_size->inner3_, buffer, inner3__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner3_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner3_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner3__byte_size;
  }
  // .Res.Inner inner4 = 7;
  if (msg_obj->has_inner4()) {
    int32_t inner4__byte_size = msg_obj_cached_size->inner4_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner4__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             7,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner4__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner4_, &msg_obj_cached_size->inner4_, buffer, inner4__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner4_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner4_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner4__byte_size;
  }
  // .Res.Inner inner5 = 8;
  if (msg_obj->has_inner5()) {
    int32_t inner5__byte_size = msg_obj_cached_size->inner5_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner5__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             8,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner5__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner5_, &msg_obj_cached_size->inner5_, buffer, inner5__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner5_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner5_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner5__byte_size;
  }
  // .Res.Inner inner6 = 9;
  if (msg_obj->has_inner6()) {
    int32_t inner6__byte_size = msg_obj_cached_size->inner6_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner6__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             9,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner6__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner6_, &msg_obj_cached_size->inner6_, buffer, inner6__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner6_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner6_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner6__byte_size;
  }
  // .Res.Inner inner7 = 10;
  if (msg_obj->has_inner7()) {
    int32_t inner7__byte_size = msg_obj_cached_size->inner7_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner7__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             10,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner7__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner7_, &msg_obj_cached_size->inner7_, buffer, inner7__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner7_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner7_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner7__byte_size;
  }
  // .Res.Inner inner8 = 11;
  if (msg_obj->has_inner8()) {
    int32_t inner8__byte_size = msg_obj_cached_size->inner8_.cached_size_;
    used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(inner8__byte_size) + 1;
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             11,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(inner8__byte_size), buffer);
    temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
             &msg_obj->inner8_, &msg_obj_cached_size->inner8_, buffer, inner8__byte_size);
    if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner8_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner8_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
    }
    buffer = buffer + inner8__byte_size;
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
    for (int32_t i = 0; i < count; i++) {
      int32_t stringList__byte_size = msg_obj_cached_size->stringList_[i];
      used_size += 1 +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
                            stringList__byte_size);
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(15,
                                                                             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(stringList__byte_size, buffer);
      buffer = ::google::protobuf::io::CodedOutputStream::WriteRawToArray(msg_obj->stringList_[i],
                                                                         stringList__byte_size, buffer);
    }
  }

  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  if (msg_obj->enumValListSize > 0) {
    int32_t enumValList__byte_size = msg_obj_cached_size->enumValList_;
    const int n = msg_obj->enumValListSize;
    used_size += 2 +::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
                          enumValList__byte_size);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
             16,
             ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
             buffer);

    buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
             static_cast< ::google::protobuf::uint32>(
             enumValList__byte_size), buffer);

    for (int i = 0; i < n; i++) {
      buffer = ::google::protobuf::internal::WireFormatLite::WriteEnumNoTagToArray(
             msg_obj->enumValList_[i], buffer);
    }
  }
  // .Res.NumVal enumVal = 17;
  if (msg_obj->enumVal_ != 0) {
    used_size += 2 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(msg_obj->enumVal_);
    if(used_size > size) {
       return -1;
    }
    buffer = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      17, msg_obj->enumVal_, buffer);
  }

  switch (msg_obj->id()) {
    // float a = 12 [(.PBCExt.oneof_id) = "NUMVAL0"];
    case RES_NUMVAL0: {
      used_size += 1 + 4;
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(12, msg_obj->id_, buffer);
      break;
    }
    // uint32 b = 13 [(.PBCExt.oneof_id) = "NUMVAL1"];
    case RES_NUMVAL1: {
      used_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          msg_obj->id_);
      if(used_size > size) {
         return -1;
      }
      buffer = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(13, msg_obj->id_, buffer);
      break;
    }
    // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "NUMVAL2"];
    case RES_NUMVAL2: {
      {
        int32_t c__byte_size = msg_obj_cached_size->stObject.c.cached_size_;
        used_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(c__byte_size) + 1;
        if(used_size > size) {
           return -1;
        }
        buffer = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
                 14,
                 ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
                 buffer);

        buffer = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
                 static_cast< ::google::protobuf::uint32>(c__byte_size), buffer);
        temp_sub_message_size = SerializeResInnerToArrayWithCachedSize(
                 &msg_obj->stObject.c_, &msg_obj_cached_size->stObject.c, buffer, c__byte_size);
        if (temp_sub_message_size < 0) {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("%s encode error, ret code(%d)", "c_", temp_sub_message_size);
          #else
          printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "c_", temp_sub_message_size);
          #endif
          return temp_sub_message_size;
        }
        buffer = buffer + c__byte_size;
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
  if (msg_obj->id_ != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->id_);
  }

  // string str = 2 [(.PBCExt.max_len_1) = "20"];
  {
    msg_obj_cached_size->str_ = strlen(msg_obj->str_);
    if(msg_obj_cached_size->str_ > 0)
     {temp_sub_message_size = ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
       msg_obj_cached_size->str_);
      total_size += 1 + temp_sub_message_size;
    }

  }

  // int32 opt = 3;
  if (msg_obj->opt_ != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        msg_obj->opt_);
  }

  // .Res.Inner inner1 = 4;
  if (msg_obj->has_inner1()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner1_, &msg_obj_cached_size->inner1_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner1_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner1_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner2 = 5;
  if (msg_obj->has_inner2()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner2_, &msg_obj_cached_size->inner2_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner2_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner2_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner3 = 6;
  if (msg_obj->has_inner3()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner3_, &msg_obj_cached_size->inner3_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner3_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner3_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner4 = 7;
  if (msg_obj->has_inner4()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner4_, &msg_obj_cached_size->inner4_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner4_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner4_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner5 = 8;
  if (msg_obj->has_inner5()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner5_, &msg_obj_cached_size->inner5_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner5_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner5_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner6 = 9;
  if (msg_obj->has_inner6()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner6_, &msg_obj_cached_size->inner6_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner6_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner6_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner7 = 10;
  if (msg_obj->has_inner7()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner7_, &msg_obj_cached_size->inner7_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner7_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner7_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
  }

  // .Res.Inner inner8 = 11;
  if (msg_obj->has_inner8()) {
      temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->inner8_, &msg_obj_cached_size->inner8_);
      if (temp_sub_message_size < 0) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("%s encode error, ret code(%d)", "inner8_", temp_sub_message_size);
      #else
      printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "inner8_", temp_sub_message_size);
      #endif
      return temp_sub_message_size;
      }
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(temp_sub_message_size);
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
    total_size += 1 *
        ::google::protobuf::internal::FromIntSize(count);
    for (int32_t i = 0; i < count; i++) {
       msg_obj_cached_size->stringList_[i] = strlen(msg_obj->stringList_[i]);
       total_size += ::google::protobuf::internal::WireFormatLite::LengthDelimitedSize(
         msg_obj_cached_size->stringList_[i]);
    }
  }

  // repeated .Res.NumVal enumValList = 16 [(.PBCExt.max_len_1) = "1"];
  {
    int32_t data_size = 0;
    uint32_t count = static_cast<uint32_t>(msg_obj->enumValListSize);for (uint32_t i = 0; i < count; i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
        msg_obj->enumValList_[static_cast<int>(i)]);
    }
    msg_obj_cached_size->enumValList_ = data_size;
    if (data_size > 0) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast< ::google::protobuf::int32>(data_size));
    }
    total_size += data_size;
  }
  // .Res.NumVal enumVal = 17;
  if (msg_obj->enumVal_ != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(msg_obj->enumVal_);
  }

  switch (msg_obj->id()) {
    // float a = 12 [(.PBCExt.oneof_id) = "NUMVAL0"];
    case RES_NUMVAL0: {
      total_size += 1 + 4;
      break;
    }
    // uint32 b = 13 [(.PBCExt.oneof_id) = "NUMVAL1"];
    case RES_NUMVAL1: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          msg_obj->id_);
      break;
    }
    // .Res.Inner c = 14 [(.PBCExt.oneof_id) = "NUMVAL2"];
    case RES_NUMVAL2: {
      {
          temp_sub_message_size = ResInnerByteSizeLongWithCachedSize(&msg_obj->stObject.c_, &msg_obj_cached_size->stObject.c);
          if (temp_sub_message_size < 0) {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("%s encode error, ret code(%d)", "c_", temp_sub_message_size);
          #else
          printf("[ERROR][%s][%d]%s encode error, ret code(%d)\n", __FUNCTION__, __LINE__, "c_", temp_sub_message_size);
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

