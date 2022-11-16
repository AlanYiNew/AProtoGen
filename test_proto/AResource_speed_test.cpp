#include <math.h>
#include <time.h>
#include <map>
#include "AResource_speed_test.h"
#include "AResource_assign.h"
void FillResInnerFull(ResInner* msg_obj_c) {
  {
    int32_t temp_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_c->set_temp(temp_rand);
  }
}
void FillInnerFull(Res::Inner* msg_obj_cpp) {
  {
    int32_t temp_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_cpp->set_temp(temp_rand);
  }
}
void FillReshelloworldFull(Reshelloworld* msg_obj_c) {
  {
    char tempArray[20] = {0};int str_len = 20 - 1;
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
      FillResInnerFull(msg_obj_c->mutable_inner1());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner2());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner3());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner4());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner5());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner6());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner7());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(msg_obj_c->mutable_inner8());
    }
  }
  {
    int stringList_max = 10;
    for (int i = 0; i < stringList_max; i++) {
    char arrayTemp[20] = {0};
      int stringList_len = 20 - 1;
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
    int enumValList_max = 1;
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
    switch (0) {
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
        FillResInnerFull(msg_obj_c->mutable_c());
      }
      break;
    }
  }
}
void FillhelloworldFull(Res::helloworld* msg_obj_cpp) {
  {
    int str_len = 20 - 1;
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
      FillInnerFull(msg_obj_cpp->mutable_inner1());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner2());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner3());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner4());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner5());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner6());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner7());
    }
  }
  {
    if (random()%2) {
      FillInnerFull(msg_obj_cpp->mutable_inner8());
    }
  }
  {
    int stringList_max = 10;
    for (int i = 0; i < stringList_max; i++) {
      msg_obj_cpp->add_stringlist();
      int stringList_len = 20 - 1;
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
    int enumValList_max = 1;
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
    switch (0) {
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
        FillInnerFull(msg_obj_cpp->mutable_c());
        msg_obj_cpp->set_id(RES_NUMVAL2);
      }
      break;
    }
  }
}
bool run_AResource_encode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map){
  {
    std::chrono::high_resolution_clock::time_point current_time, start_time;
    std::chrono::milliseconds c_elapsed_time, cpp_elapsed_time;
    int len1,len2;
    ::google::protobuf::uint8* c_buffer;
    static ResInner c_message;
    Res::Inner cpp_message;
    std::string cpp_buffer;
    memset(&c_message, 0, sizeof(c_message)); //这个memset因为string的\0, 而且数组下标是从0开始加的
    FillResInnerFull(&c_message);
    AssignResInnerToInner(c_message, cpp_message);
    len1 = ResInnerByteSizeLong(&c_message);
    c_buffer = ( ::google::protobuf::uint8*)malloc(len1);
    start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10; i++) {
        len2 = SerializeResInnerToArray(&c_message, c_buffer, len1);
    }
    current_time = std::chrono::high_resolution_clock::now();
    c_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10; i++) {
         cpp_message.SerializeToString(&cpp_buffer);
    }
    current_time = std::chrono::high_resolution_clock::now();
    cpp_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    c_map["ResInner"] += c_elapsed_time;
    cpp_map["Res::Inner"] += cpp_elapsed_time;
    free(c_buffer);
  }
  {
    std::chrono::high_resolution_clock::time_point current_time, start_time;
    std::chrono::milliseconds c_elapsed_time, cpp_elapsed_time;
    int len1,len2;
    ::google::protobuf::uint8* c_buffer;
    static Reshelloworld c_message;
    Res::helloworld cpp_message;
    std::string cpp_buffer;
    memset(&c_message, 0, sizeof(c_message)); //这个memset因为string的\0, 而且数组下标是从0开始加的
    FillReshelloworldFull(&c_message);
    AssignReshelloworldTohelloworld(c_message, cpp_message);
    len1 = ReshelloworldByteSizeLong(&c_message);
    c_buffer = ( ::google::protobuf::uint8*)malloc(len1);
    start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10; i++) {
        len2 = SerializeReshelloworldToArray(&c_message, c_buffer, len1);
    }
    current_time = std::chrono::high_resolution_clock::now();
    c_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10; i++) {
         cpp_message.SerializeToString(&cpp_buffer);
    }
    current_time = std::chrono::high_resolution_clock::now();
    cpp_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    c_map["Reshelloworld"] += c_elapsed_time;
    cpp_map["Res::helloworld"] += cpp_elapsed_time;
    free(c_buffer);
  }
  return true;
}
bool run_AResource_decode_speed_test(std::map<std::string, std::chrono::milliseconds>& c_map, std::map<std::string, std::chrono::milliseconds>& cpp_map){
  {
    std::chrono::high_resolution_clock::time_point current_time, start_time;
    std::chrono::milliseconds c_elapsed_time, cpp_elapsed_time;
    int len1,len2;
    ::google::protobuf::uint8* c_buffer;
    static ResInner c_message;
    Res::Inner cpp_message;
    std::string cpp_buffer;
    memset(&c_message, 0, sizeof(c_message)); //这个memset因为string的\0, 而且数组下标是从0开始加的
    FillResInnerFull(&c_message);
    AssignResInnerToInner(c_message, cpp_message);
    len1 = ResInnerByteSizeLong(&c_message);
    c_buffer = ( ::google::protobuf::uint8*)malloc(len1);
    len2 = SerializeResInnerToArray(&c_message, c_buffer, len1);
    cpp_message.SerializeToString(&cpp_buffer);
    start_time = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < 100; i++) {
        ParseResInner(c_buffer, len2, &c_message);
    }
    current_time = std::chrono::high_resolution_clock::now(); 
    c_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    start_time = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < 100; i++) {
         cpp_message.ParseFromString(cpp_buffer);
    }
    current_time = std::chrono::high_resolution_clock::now();cpp_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    c_map["ResInner"] += c_elapsed_time;
    cpp_map["Res::Inner"] += cpp_elapsed_time;
    free(c_buffer);
  }
  {
    std::chrono::high_resolution_clock::time_point current_time, start_time;
    std::chrono::milliseconds c_elapsed_time, cpp_elapsed_time;
    int len1,len2;
    ::google::protobuf::uint8* c_buffer;
    static Reshelloworld c_message;
    Res::helloworld cpp_message;
    std::string cpp_buffer;
    memset(&c_message, 0, sizeof(c_message)); //这个memset因为string的\0, 而且数组下标是从0开始加的
    FillReshelloworldFull(&c_message);
    AssignReshelloworldTohelloworld(c_message, cpp_message);
    len1 = ReshelloworldByteSizeLong(&c_message);
    c_buffer = ( ::google::protobuf::uint8*)malloc(len1);
    len2 = SerializeReshelloworldToArray(&c_message, c_buffer, len1);
    cpp_message.SerializeToString(&cpp_buffer);
    start_time = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < 100; i++) {
        ParseReshelloworld(c_buffer, len2, &c_message);
    }
    current_time = std::chrono::high_resolution_clock::now(); 
    c_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    start_time = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < 100; i++) {
         cpp_message.ParseFromString(cpp_buffer);
    }
    current_time = std::chrono::high_resolution_clock::now();cpp_elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    c_map["Reshelloworld"] += c_elapsed_time;
    cpp_map["Res::helloworld"] += cpp_elapsed_time;
    free(c_buffer);
  }
  return true;
}
