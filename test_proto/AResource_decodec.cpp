#ifdef ENABLE_PB_LOG
#include "comm/comm_gamecore/log_module.h"
#endif 
#include "AResource_decodec.h"
#include "pbc_extension_decodec.h"

int32_t ParseResInner(
  const uint8_t* data,
  int size,
  ResInner* msg_obj) {
  ::google::protobuf::io::CodedInputStream input(data, size);
   return ParseResInnerWithStream(&input, msg_obj);
}
int32_t ParseResInnerWithStream(
  ::google::protobuf::io::CodedInputStream* input,
  ResInner* msg_obj) {
  ::google::protobuf::uint32 tag;
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second && 0 == tag) return 0;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int32_t* temp = &msg_obj->temp_;
          int32_t value;
          if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
             int32_t, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &value)) return -2;
          *temp = static_cast<int32_t>(value);
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 0", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 0\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -100;
        }
      }
      break;
      default : {
        if (tag == 0) return 0;
        if (!::google::protobuf::internal::WireFormatLite::SkipField(input, tag)) {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("SkipField failed tag(%d)", tag);
          #else
          printf("[ERROR][%s][%d]SkipField failed tag(%d)\n", __FUNCTION__, __LINE__, tag);
          #endif
          return -11;
        }
      }
    }
  }
return 0;
}

int32_t ParseReshelloworld(
  const uint8_t* data,
  int size,
  Reshelloworld* msg_obj) {
  ::google::protobuf::io::CodedInputStream input(data, size);
   return ParseReshelloworldWithStream(&input, msg_obj);
}
int32_t ParseReshelloworldWithStream(
  ::google::protobuf::io::CodedInputStream* input,
  Reshelloworld* msg_obj) {
  int32_t stringList_size = 0;
  int32_t enumValList_size = 0;
  ::google::protobuf::uint32 tag;
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(16383u);
    tag = p.first;
    if (!p.second && 0 == tag) return 0;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int32_t* temp = &msg_obj->id_;
          int32_t value;
          if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
             int32_t, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &value)) return -2;
          *temp = static_cast<int32_t>(value);
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 0", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 0\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -100;
        }
      }
      break;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          char* temp = &msg_obj->str_[0];
          uint32_t length;
          if (!input->ReadVarint32(&length)) return -10;
          if (length >= 20) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("string length(%d) >= buff length(%d)", length, 20);
            #else
            printf("[ERROR][%s][%d]string length(%d) >= buff length(%d)\n", __FUNCTION__, __LINE__, length, 20);
            #endif
            return -11;
          }
          if (!input->ReadRaw(temp, length)) return -12;
          temp[length] = '\0';
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -101;
        }
      }
      break;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
          int32_t* temp = &msg_obj->opt_;
          int32_t value;
          if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
             int32_t, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &value)) return -2;
          *temp = static_cast<int32_t>(value);
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 0", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 0\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -102;
        }
      }
      break;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner1();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -103;
        }
      }
      break;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(42u /* 42 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner2();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -104;
        }
      }
      break;
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(50u /* 50 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner3();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -105;
        }
      }
      break;
      case 7: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(58u /* 58 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner4();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -106;
        }
      }
      break;
      case 8: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(66u /* 66 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner5();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -107;
        }
      }
      break;
      case 9: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(74u /* 74 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner6();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -108;
        }
      }
      break;
      case 10: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(82u /* 82 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner7();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -109;
        }
      }
      break;
      case 11: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(90u /* 90 & 0xFF */)) {
          ResInner* temp = msg_obj->mutable_inner8();
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1010;
        }
      }
      break;
      case 12: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(101u /* 101 & 0xFF */)) {
          float* temp = &msg_obj->stObject.a_;
          float value;
          if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
             float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(input, &value)) return -2;
          *temp = static_cast<float>(value);
          if (msg_obj->id() != RES_NUMVAL0) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("oneof filed not match");
            #else
            printf("[ERROR][%s][%d]oneof filed not match\n", __FUNCTION__, __LINE__);
            #endif
            return -10;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 5", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 5\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1011;
        }
      }
      break;
      case 13: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(104u /* 104 & 0xFF */)) {
          uint32_t* temp = &msg_obj->stObject.b_;
          uint32_t value;
          if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
             uint32_t, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(input, &value)) return -2;
          *temp = static_cast<uint32_t>(value);
          if (msg_obj->id() != RES_NUMVAL1) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("oneof filed not match");
            #else
            printf("[ERROR][%s][%d]oneof filed not match\n", __FUNCTION__, __LINE__);
            #endif
            return -10;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 0", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 0\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1012;
        }
      }
      break;
      case 14: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(114u /* 114 & 0xFF */)) {
          if (msg_obj->id() != RES_NUMVAL2) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("oneof filed not match");
            #else
            printf("[ERROR][%s][%d]oneof filed not match\n", __FUNCTION__, __LINE__);
            #endif
            return -10;
          }
          ResInner* temp = &msg_obj->stObject.c_;
          int32_t length;
          if (!input->ReadVarintSizeAsInt(&length)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("ReadVarintSizeAsInt failed");
            #else
            printf("[ERROR][%s][%d]ReadVarintSizeAsInt failed\n", __FUNCTION__, __LINE__);
            #endif
             return -1;
          }
          std::pair< ::google::protobuf::io::CodedInputStream::Limit, int> p = input->IncrementRecursionDepthAndPushLimit(length);
          if (p.second < 0 || 0 != ParseResInnerWithStream(input, temp)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("IncrementRecursionDepthAndPushLimit failed(%d) or failed", (int)p.second);
            #else
            printf("[ERROR][%s][%d]IncrementRecursionDepthAndPushLimit failed(%d) or failed\n", __FUNCTION__, __LINE__, (int)p.second);
            #endif
            return -2;
          }
          if (!input->DecrementRecursionDepthAndPopLimit(p.first)) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("DecrementRecursionDepthAndPopLimit failed(%d)", p.first);
            #else
            printf("[ERROR][%s][%d]DecrementRecursionDepthAndPopLimit failed(%d)\n", __FUNCTION__, __LINE__, p.first);
            #endif
            return -3;
          }
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1013;
        }
      }
      break;
      case 15: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(122u /* 122 & 0xFF */)) {
          if (stringList_size >= 10) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("over max array count 10");
            #else
            printf("[ERROR][%s][%d]over max array count 10\n", __FUNCTION__, __LINE__);
            #endif
            return -1;
          }
          char* temp = &msg_obj->stringList_[stringList_size][0];
          uint32_t length;
          if (!input->ReadVarint32(&length)) return -10;
          if (length >= 20) {
            #ifdef ENABLE_PB_LOG
            GLOG_ERROR("string length(%d) >= buff length(%d)", length, 20);
            #else
            printf("[ERROR][%s][%d]string length(%d) >= buff length(%d)\n", __FUNCTION__, __LINE__, length, 20);
            #endif
            return -11;
          }
          if (!input->ReadRaw(temp, length)) return -12;
          temp[length] = '\0';
          stringList_size++;
          msg_obj->stringListSize = stringList_size;
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1014;
        }
      }
      break;
      case 16: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(130u /* 130 & 0xFF */)) {
          uint32_t length;
          if (!input->ReadVarint32(&length)) return -1;
          ::google::protobuf::io::CodedInputStream::Limit limit = input->PushLimit(static_cast<int>(length));
          while (input->BytesUntilLimit() > 0) {
            if (enumValList_size >= 1) return -3;
            RES_NumVal* temp = &msg_obj->enumValList_[enumValList_size];
            int value;
            if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
              int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                input, &value)) return -2;
            *temp = static_cast<RES_NumVal>(value);
            enumValList_size++;
          }
          msg_obj->enumValListSize = enumValList_size;
          input->PopLimit(limit);
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 2", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 2\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1015;
        }
      }
      break;
      case 17: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(136u /* 136 & 0xFF */)) {
          RES_NumVal* temp = &msg_obj->enumVal_;
          int value;
          if (!::google::protobuf::internal::WireFormatLite::ReadPrimitive<
            int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
              input, &value)) return -2;
          *temp = static_cast<RES_NumVal>(value);
        }
        else {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("buff type(%d) not match 0", tag&0x07);
          #else
          printf("[ERROR][%s][%d]buff type(%d) not match 0\n", __FUNCTION__, __LINE__, tag&0x07);
          #endif
          return -1016;
        }
      }
      break;
      default : {
        if (tag == 0) return 0;
        if (!::google::protobuf::internal::WireFormatLite::SkipField(input, tag)) {
          #ifdef ENABLE_PB_LOG
          GLOG_ERROR("SkipField failed tag(%d)", tag);
          #else
          printf("[ERROR][%s][%d]SkipField failed tag(%d)\n", __FUNCTION__, __LINE__, tag);
          #endif
          return -11;
        }
      }
    }
  }
return 0;
}

