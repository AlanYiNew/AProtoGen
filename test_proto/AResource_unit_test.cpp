#include <math.h>
#include "AResource_unit_test.h"
void FillResInner(ResInner* msg_obj_c) {
  {
    int32_t temp_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_c->set_temp(temp_rand);
  }
}
void FillInner(Res::Inner* msg_obj_cpp) {
  {
    int32_t temp_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_cpp->set_temp(temp_rand);
  }
}
bool CompareInner(ResInner* msg_obj_c, Res::Inner* msg_obj_cpp){
  {
    if (fabs(msg_obj_cpp->temp() - msg_obj_c->temp()) > 0.000001) {
      std::cout << "Inner::temp not equal [c:"
           << msg_obj_c->temp() << ", cpp:"
           << msg_obj_cpp->temp()
           << "]" << std::endl;
      return false;
    }
  }
  return true;
}
void FillReshelloworld(Reshelloworld* msg_obj_c) {
  {
    char tempArray[20] = {0};int str_len = random() % 20;
    for (int j = 0; j < str_len; j++) {
      char tmp;
      switch(random() % 1) {
        case 0:
        tmp = random() % 127 + 1;
        break;
      }
     tempArray[j] = tmp;
    }
      msg_obj_c->set_str(tempArray);
  }
  {
    int32_t opt_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_c->set_opt(opt_rand);
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner1());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner2());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner3());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner4());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner5());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner6());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner7());
    }
  }
  {
    if (random()%2) {
      FillResInner(msg_obj_c->mutable_inner8());
    }
  }
  {
    int stringList_max = random()%(10 +1);
    for (int i = 0; i < stringList_max; i++) {
    char arrayTemp[20] = {0};
      int stringList_len = random() % 20;
      for (int j = 0; j < stringList_len; j++) {
        char tmp;
        switch(random() % 1) {
          case 0:
          tmp = random() % 127 + 1;
          break;
        }
         arrayTemp[j] = tmp;
      }
        msg_obj_c->add_stringlist(arrayTemp);
      msg_obj_c->stringListSize++;
    }
  }
  {
    int enumValList_max = random()%(1 +1);
    for (int i = 0; i < enumValList_max; i++) {
      RES_NumVal enumValList_rand = static_cast<RES_NumVal>(random()%(2-0)+0);
      msg_obj_c->add_enumvallist(enumValList_rand);
    }
  }
  {
    RES_NumVal enumVal_rand = static_cast<RES_NumVal>(random()%(2-0)+0);
    msg_obj_c->set_enumval(enumVal_rand);
  }
  {
    int object_enum[] = {
      RES_NUMVAL0, RES_NUMVAL1, RES_NUMVAL2};
    int length = sizeof(object_enum)/sizeof(int);
    int rand_enum = object_enum[random() % length];
    switch (rand_enum) {
      case RES_NUMVAL0:{
        float a_rand = (3.40282e+38-(1.17549e-38))*
          ((float)random()/RAND_MAX)+(1.17549e-38);
        msg_obj_c->set_a(a_rand);
      }
      break;
      case RES_NUMVAL1:{
        uint32_t b_rand = random()%(4294967295ULL-(0ULL))+(0ULL);
        msg_obj_c->set_b(b_rand);
      }
      break;
      case RES_NUMVAL2:{
        FillResInner(msg_obj_c->mutable_c());
      }
      break;
    }
  }
}
void Fillhelloworld(Res::helloworld* msg_obj_cpp) {
  {
    int str_len = random() % 20;
    for (int j = 0; j < str_len; j++) {
      char tmp;
      switch(random() % 1) {
        case 0:
        tmp = random() % 127 + 1;
        break;
      }
      msg_obj_cpp->mutable_str()->push_back(tmp);
    }
  }
  {
    int32_t opt_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_cpp->set_opt(opt_rand);
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner1());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner2());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner3());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner4());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner5());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner6());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner7());
    }
  }
  {
    if (random()%2) {
      FillInner(msg_obj_cpp->mutable_inner8());
    }
  }
  {
    int stringList_max = random()%(10 +1);
    for (int i = 0; i < stringList_max; i++) {
      msg_obj_cpp->add_stringlist();
      int stringList_len = random() % 20;
      for (int j = 0; j < stringList_len; j++) {
        char tmp;
        switch(random() % 1) {
          case 0:
          tmp = random() % 127 + 1;
          break;
        }
        msg_obj_cpp->mutable_stringlist(i)->push_back(tmp);
      }
    }
  }
  {
    int enumValList_max = random()%(1 +1);
    for (int i = 0; i < enumValList_max; i++) {
      Res::NumVal enumValList_rand = static_cast<Res::NumVal>(random()%(2-0)+0);
      msg_obj_cpp->add_enumvallist(enumValList_rand);
    }
  }
  {
    Res::NumVal enumVal_rand = static_cast<Res::NumVal>(random()%(2-0)+0);
    msg_obj_cpp->set_enumval(enumVal_rand);
  }
  {
    int object_enum[] = {
      RES_NUMVAL0, RES_NUMVAL1, RES_NUMVAL2};
    int length = sizeof(object_enum)/sizeof(int);
    int rand_enum = object_enum[random() % length];
    switch (rand_enum) {
      case RES_NUMVAL0:{
        float a_rand = (3.40282e+38-(1.17549e-38))*
          ((float)random()/RAND_MAX)+(1.17549e-38);
        msg_obj_cpp->set_a(a_rand);
        msg_obj_cpp->set_id(RES_NUMVAL0);
      }
      break;
      case RES_NUMVAL1:{
        uint32_t b_rand = random()%(4294967295ULL-(0ULL))+(0ULL);
        msg_obj_cpp->set_b(b_rand);
        msg_obj_cpp->set_id(RES_NUMVAL1);
      }
      break;
      case RES_NUMVAL2:{
        FillInner(msg_obj_cpp->mutable_c());
        msg_obj_cpp->set_id(RES_NUMVAL2);
      }
      break;
    }
  }
}
bool Comparehelloworld(Reshelloworld* msg_obj_c, Res::helloworld* msg_obj_cpp){
  {
    if (msg_obj_cpp->str().size() !=  strlen(msg_obj_c->str())) {
      std::cout << " helloworld::str size not eq"
           << strlen(msg_obj_c->str())
           << ", cpp:"
           << msg_obj_cpp->str().size()
           << "]"
           << std::endl;
      return false;
    }
    if (0 != memcmp(msg_obj_cpp->str().c_str(),msg_obj_c->str(), msg_obj_cpp->str().size())) {
       std::cout << "helloworld::str :"
                 <<  " element not equal"
                 << std::endl;
       return false;
    }
  }
  {
    if (fabs(msg_obj_cpp->opt() - msg_obj_c->opt()) > 0.000001) {
      std::cout << "helloworld::opt not equal [c:"
           << msg_obj_c->opt() << ", cpp:"
           << msg_obj_cpp->opt()
           << "]" << std::endl;
      return false;
    }
  }
  {
    if (msg_obj_c->has_inner1() != (int)msg_obj_cpp->has_inner1()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner1()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner1(),msg_obj_cpp->mutable_inner1())) return false;
  }
  {
    if (msg_obj_c->has_inner2() != (int)msg_obj_cpp->has_inner2()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner2()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner2(),msg_obj_cpp->mutable_inner2())) return false;
  }
  {
    if (msg_obj_c->has_inner3() != (int)msg_obj_cpp->has_inner3()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner3()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner3(),msg_obj_cpp->mutable_inner3())) return false;
  }
  {
    if (msg_obj_c->has_inner4() != (int)msg_obj_cpp->has_inner4()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner4()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner4(),msg_obj_cpp->mutable_inner4())) return false;
  }
  {
    if (msg_obj_c->has_inner5() != (int)msg_obj_cpp->has_inner5()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner5()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner5(),msg_obj_cpp->mutable_inner5())) return false;
  }
  {
    if (msg_obj_c->has_inner6() != (int)msg_obj_cpp->has_inner6()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner6()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner6(),msg_obj_cpp->mutable_inner6())) return false;
  }
  {
    if (msg_obj_c->has_inner7() != (int)msg_obj_cpp->has_inner7()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner7()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner7(),msg_obj_cpp->mutable_inner7())) return false;
  }
  {
    if (msg_obj_c->has_inner8() != (int)msg_obj_cpp->has_inner8()) {
      #ifdef ENABLE_PB_LOG
      GLOG_ERROR("C has not match Cpp has");
      #else
      printf("[ERROR][%s][%d]C has not match Cpp has\n", __FUNCTION__, __LINE__);
      #endif
      return false;
    }
    if (!msg_obj_c->has_inner8()) return true;
    if (!CompareInner(msg_obj_c->mutable_inner8(),msg_obj_cpp->mutable_inner8())) return false;
  }
  {
      int cpp_stringlist_count = msg_obj_cpp->stringlist_size();
      int c_stringlist_count = msg_obj_c->stringListSize;
    if (cpp_stringlist_count != c_stringlist_count) {
      std::cout << " helloworld::stringList size not eq:[c:"
           << c_stringlist_count
           << ", cpp:"
           << cpp_stringlist_count
           << "]"
           << std::endl;
      return false;
    }
    for (int i = 0; i < msg_obj_cpp->stringlist_size(); i++) {
      if (0 != memcmp(msg_obj_cpp->stringlist(i).c_str(),
        msg_obj_c->stringlist(i), msg_obj_cpp->stringlist(i).size())) {
        std::cout << "helloworld::stringList repeated:"
             << i << " element not equal"
             << std::endl;
        return false;
     }
    }
  }
  {
      int cpp_enumvallist_count = msg_obj_cpp->enumvallist_size();
      int c_enumvallist_count = msg_obj_c->enumValListSize;
    if (cpp_enumvallist_count != c_enumvallist_count) {
      std::cout << " helloworld::enumValList size not eq:[c:"
           << c_enumvallist_count
           << ", cpp:"
           << cpp_enumvallist_count
           << "]"
           << std::endl;
      return false;
    }
    for (int i = 0; i < msg_obj_cpp->enumvallist_size(); i++) {
      if ((int)msg_obj_cpp->enumvallist(i) != (int)msg_obj_c->enumvallist(i)) {
         std::cout << "helloworld::enumValList repeated:"
              << i << " element not equal"
              << std::endl;
         return false;
      }
    }
  }
  {
    if ((int)msg_obj_cpp->enumval() !=(int)msg_obj_c->enumval()) {
      std::cout << "helloworld::enumVal not equal [c:"
           << msg_obj_c->enumval() << ", cpp:"
           << msg_obj_cpp->enumval()
           << "]" << std::endl;
      return false;
    }
  }
  {
  switch (msg_obj_c->id()) {
    case RES_NUMVAL0:{
      if (fabs(msg_obj_cpp->a() - msg_obj_c->a()) > 0.000001) {
        std::cout << "helloworld::a not equal [c:"
             << msg_obj_c->a()
             << ", cpp:"
             << msg_obj_cpp->a()
             << "]" << std::endl;
        return false;
      }
    }
    break;
    case RES_NUMVAL1:{
      if (fabs(msg_obj_cpp->b() - msg_obj_c->b()) > 0.000001) {
        std::cout << "helloworld::b not equal [c:"
             << msg_obj_c->b()
             << ", cpp:"
             << msg_obj_cpp->b()
             << "]" << std::endl;
        return false;
      }
    }
    break;
    case RES_NUMVAL2:{
      if (!CompareInner(msg_obj_c->mutable_c(),
        msg_obj_cpp->mutable_c())) return false;
    }
    break;
    }
  }
  return true;
}
bool run_AResource_encode_unit_test(){
  {
    static ResInner msg_obj_c;
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    FillResInner(&msg_obj_c);
    int byte_size = ResInnerByteSizeLong(&msg_obj_c);
    std::string buff;
    buff.resize(byte_size);
    Res::Inner msg_obj_cpp;
    int ret = 0;
    if(byte_size > 0) {
     if (-1 != (ret = SerializeResInnerToArray(
         &msg_obj_c, (uint8_t*)string_as_array(&buff), byte_size - 1))) {
         std::cout << "SerializeResInnerToArray error:" << "buffer size not enough but did not check" << std::endl;
         return false;
     }
    }
    if (byte_size != (ret = SerializeResInnerToArray(
      &msg_obj_c, (uint8_t*)string_as_array(&buff), byte_size))) {
      std::cout << "SerializeResInnerToArray error:" << "byte_size_long ret " << byte_size << "; serialize_func ret " << ret << std::endl;
      return false;
    }
    msg_obj_cpp.ParseFromString(buff);
    if (!CompareInner(&msg_obj_c, &msg_obj_cpp)) {
      std::cout << "CompareInner not pass" << std::endl;
      std::cout<<"msg_obj_cpp:\n"<<msg_obj_cpp.DebugString()<<std::endl;  return false;
    }
    std::string buff_cpp;
    msg_obj_cpp.SerializeToString(&buff_cpp);
    if(buff_cpp.size() != byte_size) {
      std::cout << "SerializeResInnerToArray error:" << "c serilaized string not equals to c++ serialized string"<< std::endl;
      std::cout << "c size: " << byte_size << "c++ size: " << buff_cpp.size() << std::endl;
      return false;
    }
    // use pbc to encode an object to json string
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    FillResInnerFull(&msg_obj_c);
    Res::Inner msg_obj_cpp_json;
    int buffer_len = 10000000;
    char* buffer = (char *)malloc(buffer_len);
    JSONPRINTOPTIONSPBC json_print_option;
    memset(&json_print_option, 0, sizeof(json_print_option));
    json_print_option.always_print_primitive_fields=true;
    json_print_option.preserve_proto_field_names=true;
    if ((ret = ResInnerToJson(&msg_obj_c, buffer, buffer_len, json_print_option)) < 0) {
       printf("[ERROR][%s][%d] ResInnerToJson error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       return false;}
    // use pbc++ to decode the json string
    google::protobuf::util::JsonStringToMessage(buffer, &msg_obj_cpp_json);
    if (!CompareInner(&msg_obj_c, &msg_obj_cpp_json)) {
       std::cout << "CompareInner not pass" << std::endl;
       printf("json string c: %s\n", buffer);
       std::string json_string_cpp;
       google::protobuf::util::JsonPrintOptions print_options;
       print_options.always_print_enums_as_ints = true;
       MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);
       std::cout << "json string cpp: " << json_string_cpp << std::endl;
       return false;
    }
    // use pbc to decode the json string
    ResInner msg_obj_c_json;
    memset(&msg_obj_c_json, 0, sizeof(msg_obj_c_json));
    JSONPARSEOPTIONSPBC json_parse_option;
    memset(&json_parse_option, 0, sizeof(json_parse_option));
    if ((ret = JsonToResInner(buffer ,&msg_obj_c_json, json_parse_option)) < 0) {
       printf("[ERROR][%s][%d] JsonToResInner error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       return false;}
    if (memcmp(&msg_obj_c, &msg_obj_c_json, sizeof(msg_obj_c)) !=0 ) {
       std::cout<< "error" << std::endl;
       return false;}// use pbc to encode and decode the json string(with url_encode_strings option)
    memset(&json_print_option, 0, sizeof(json_print_option));
    json_print_option.always_print_primitive_fields=true;
    json_print_option.preserve_proto_field_names=true;
    json_print_option.url_encode_strings=true;
    if ((ret = ResInnerToJson(&msg_obj_c, buffer, buffer_len, json_print_option)) < 0) {
       printf("[ERROR][%s][%d] ResInnerToJson error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       printf("error json: %s", buffer);
       return false;}
    memset(&msg_obj_c_json, 0, sizeof(msg_obj_c_json));
    memset(&json_parse_option, 0, sizeof(json_parse_option));
    json_parse_option.url_encode_strings=true;
    if ((ret = JsonToResInner(buffer ,&msg_obj_c_json, json_parse_option)) < 0) {
       printf("[ERROR][%s][%d] JsonToResInner error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       printf("error json: %s", buffer);
       return false;}
    if (memcmp(&msg_obj_c, &msg_obj_c_json, sizeof(msg_obj_c)) !=0 ) {
       std::cout<< "error, msg_obj_c and msg_obj_c_json not equal" << std::endl;
       return false;}free(buffer);
  }
  {
    static Reshelloworld msg_obj_c;
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    FillReshelloworld(&msg_obj_c);
    int byte_size = ReshelloworldByteSizeLong(&msg_obj_c);
    std::string buff;
    buff.resize(byte_size);
    Res::helloworld msg_obj_cpp;
    int ret = 0;
    if(byte_size > 0) {
     if (-1 != (ret = SerializeReshelloworldToArray(
         &msg_obj_c, (uint8_t*)string_as_array(&buff), byte_size - 1))) {
         std::cout << "SerializeReshelloworldToArray error:" << "buffer size not enough but did not check" << std::endl;
         return false;
     }
    }
    if (byte_size != (ret = SerializeReshelloworldToArray(
      &msg_obj_c, (uint8_t*)string_as_array(&buff), byte_size))) {
      std::cout << "SerializeReshelloworldToArray error:" << "byte_size_long ret " << byte_size << "; serialize_func ret " << ret << std::endl;
      return false;
    }
    msg_obj_cpp.ParseFromString(buff);
    if (!Comparehelloworld(&msg_obj_c, &msg_obj_cpp)) {
      std::cout << "Comparehelloworld not pass" << std::endl;
      std::cout<<"msg_obj_cpp:\n"<<msg_obj_cpp.DebugString()<<std::endl;  return false;
    }
    std::string buff_cpp;
    msg_obj_cpp.SerializeToString(&buff_cpp);
    if(buff_cpp.size() != byte_size) {
      std::cout << "SerializeReshelloworldToArray error:" << "c serilaized string not equals to c++ serialized string"<< std::endl;
      std::cout << "c size: " << byte_size << "c++ size: " << buff_cpp.size() << std::endl;
      return false;
    }
    // use pbc to encode an object to json string
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    FillReshelloworldFull(&msg_obj_c);
    Res::helloworld msg_obj_cpp_json;
    int buffer_len = 10000000;
    char* buffer = (char *)malloc(buffer_len);
    JSONPRINTOPTIONSPBC json_print_option;
    memset(&json_print_option, 0, sizeof(json_print_option));
    json_print_option.always_print_primitive_fields=true;
    json_print_option.preserve_proto_field_names=true;
    if ((ret = ReshelloworldToJson(&msg_obj_c, buffer, buffer_len, json_print_option)) < 0) {
       printf("[ERROR][%s][%d] ReshelloworldToJson error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       return false;}
    // use pbc++ to decode the json string
    google::protobuf::util::JsonStringToMessage(buffer, &msg_obj_cpp_json);
    if (!Comparehelloworld(&msg_obj_c, &msg_obj_cpp_json)) {
       std::cout << "Comparehelloworld not pass" << std::endl;
       printf("json string c: %s\n", buffer);
       std::string json_string_cpp;
       google::protobuf::util::JsonPrintOptions print_options;
       print_options.always_print_enums_as_ints = true;
       MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);
       std::cout << "json string cpp: " << json_string_cpp << std::endl;
       return false;
    }
    // use pbc to decode the json string
    Reshelloworld msg_obj_c_json;
    memset(&msg_obj_c_json, 0, sizeof(msg_obj_c_json));
    JSONPARSEOPTIONSPBC json_parse_option;
    memset(&json_parse_option, 0, sizeof(json_parse_option));
    if ((ret = JsonToReshelloworld(buffer ,&msg_obj_c_json, json_parse_option)) < 0) {
       printf("[ERROR][%s][%d] JsonToReshelloworld error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       return false;}
    if (memcmp(&msg_obj_c, &msg_obj_c_json, sizeof(msg_obj_c)) !=0 ) {
       std::cout<< "error" << std::endl;
       return false;}// use pbc to encode and decode the json string(with url_encode_strings option)
    memset(&json_print_option, 0, sizeof(json_print_option));
    json_print_option.always_print_primitive_fields=true;
    json_print_option.preserve_proto_field_names=true;
    json_print_option.url_encode_strings=true;
    if ((ret = ReshelloworldToJson(&msg_obj_c, buffer, buffer_len, json_print_option)) < 0) {
       printf("[ERROR][%s][%d] ReshelloworldToJson error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       printf("error json: %s", buffer);
       return false;}
    memset(&msg_obj_c_json, 0, sizeof(msg_obj_c_json));
    memset(&json_parse_option, 0, sizeof(json_parse_option));
    json_parse_option.url_encode_strings=true;
    if ((ret = JsonToReshelloworld(buffer ,&msg_obj_c_json, json_parse_option)) < 0) {
       printf("[ERROR][%s][%d] JsonToReshelloworld error ret = [%d], please check\n", __FUNCTION__, __LINE__, ret);
       printf("error json: %s", buffer);
       return false;}
    if (memcmp(&msg_obj_c, &msg_obj_c_json, sizeof(msg_obj_c)) !=0 ) {
       std::cout<< "error, msg_obj_c and msg_obj_c_json not equal" << std::endl;
       return false;}free(buffer);
  }
  return true;
}
bool run_AResource_decode_unit_test(){
  {
    Res::Inner msg_obj_cpp;
    FillInner(&msg_obj_cpp);
    std::string buff;
    msg_obj_cpp.SerializeToString(&buff);
    static ResInner msg_obj_c;
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    int ret = 0;
    if (0 != (ret = ParseResInner(
      (unsigned char*)buff.c_str(), buff.size(), &msg_obj_c))) {
      std::cout << "ParseResInner error:" << ret << std::endl;
      return false;
    }
    if (!CompareInner(&msg_obj_c, &msg_obj_cpp)) {
      std::cout << "CompareInner not pass" << std::endl;
      std::cout<<"msg_obj_cpp:\n"<<msg_obj_cpp.DebugString()<<std::endl;  return false;
    }
    // use pbc++ to encode an object to json string
    std::string json_string_cpp;
    google::protobuf::util::JsonPrintOptions print_options;
    print_options.always_print_enums_as_ints = true;
    MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);
    // use pbc to decode the json string
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    JSONPARSEOPTIONSPBC json_parse_option;
    memset(&json_parse_option, 0, sizeof(json_parse_option));
    if ((ret = JsonToResInner((char *)json_string_cpp.c_str() ,&msg_obj_c, json_parse_option)) < 0) {
       printf("JsonToResInner error ret = [%d]\n", ret);
    }
    if (!CompareInner(&msg_obj_c, &msg_obj_cpp)) {
      std::cout << "CompareInner not pass" << std::endl;
      std::cout << "json string cpp: " << json_string_cpp << std::endl;  return false;
    }
  }
  {
    Res::helloworld msg_obj_cpp;
    Fillhelloworld(&msg_obj_cpp);
    std::string buff;
    msg_obj_cpp.SerializeToString(&buff);
    static Reshelloworld msg_obj_c;
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    int ret = 0;
    if (0 != (ret = ParseReshelloworld(
      (unsigned char*)buff.c_str(), buff.size(), &msg_obj_c))) {
      std::cout << "ParseReshelloworld error:" << ret << std::endl;
      return false;
    }
    if (!Comparehelloworld(&msg_obj_c, &msg_obj_cpp)) {
      std::cout << "Comparehelloworld not pass" << std::endl;
      std::cout<<"msg_obj_cpp:\n"<<msg_obj_cpp.DebugString()<<std::endl;  return false;
    }
    // use pbc++ to encode an object to json string
    std::string json_string_cpp;
    google::protobuf::util::JsonPrintOptions print_options;
    print_options.always_print_enums_as_ints = true;
    MessageToJsonString(msg_obj_cpp, &json_string_cpp, print_options);
    // use pbc to decode the json string
    memset(&msg_obj_c, 0, sizeof(msg_obj_c));
    JSONPARSEOPTIONSPBC json_parse_option;
    memset(&json_parse_option, 0, sizeof(json_parse_option));
    if ((ret = JsonToReshelloworld((char *)json_string_cpp.c_str() ,&msg_obj_c, json_parse_option)) < 0) {
       printf("JsonToReshelloworld error ret = [%d]\n", ret);
    }
    if (!Comparehelloworld(&msg_obj_c, &msg_obj_cpp)) {
      std::cout << "Comparehelloworld not pass" << std::endl;
      std::cout << "json string cpp: " << json_string_cpp << std::endl;  return false;
    }
  }
  return true;
}
