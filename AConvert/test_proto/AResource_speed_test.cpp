#include <math.h>
#include <sys/time.h>
#include <map>
#include "AResource_speed_test.h"
#include "AResource_assign.h"
void FillResInnerFull(ResInner* msg_obj_c) {
  {
    int32_t temp_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_c->temp = temp_rand;
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
    int str_len = 20 - 1;
    for (int j = 0; j < str_len; j++) {
      char tmp;
      switch(random() % 1) {
        case 0:
        tmp = random() % 127 + 1;
        break;
      }
     msg_obj_c->str[j] = tmp;
    }
  }
  {
    int32_t opt_rand = random()%(2147483647ULL-(-2147483648ULL))+(-2147483648ULL);
    msg_obj_c->opt = opt_rand;
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner1());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner2());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner3());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner4());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner5());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner6());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner7());
    }
  }
  {
    if (random()%2) {
      FillResInnerFull(&msg_obj_c->inner8());
    }
  }
  {
    int stringList_max = 10;
    for (int i = 0; i < stringList_max; i++) {
      int stringList_len = 20 - 1;
      for (int j = 0; j < stringList_len; j++) {
        char tmp;
        switch(random() % 1) {
          case 0:
          tmp = random() % 127 + 1;
          break;
        }
        msg_obj_c->stringList[i][j] = tmp;
      }
      msg_obj_c->stringListSize++;
    }
  }
  {
    int enumValList_max = 1;
    for (int i = 0; i < enumValList_max; i++) {
      RES_NumVal enumValList_rand = static_cast<RES_NumVal>(random()%(2-0)+0);
      msg_obj_c->enumValList[i] = enumValList_rand;
      msg_obj_c->enumValListSize++;
    }
  }
  {
    RES_NumVal enumVal_rand = static_cast<RES_NumVal>(random()%(2-0)+0);
    msg_obj_c->enumVal = enumVal_rand;
  }
  {
    int object_enum[] = {
      RES_1, RES_2, RES_3};
    switch (0) {
      case RES_1:{
        float a_rand = (3.40282e+38-(1.17549e-38))*
          ((float)random()/RAND_MAX)+(1.17549e-38);
        msg_obj_c->stObject.a = a_rand;
        msg_obj_c->id =RES_1;
      }
      break;
      case RES_2:{
        uint32_t b_rand = random()%(4294967295ULL-(0ULL))+(0ULL);
        msg_obj_c->stObject.b = b_rand;
        msg_obj_c->id =RES_2;
      }
      break;
      case RES_3:{
        FillResInnerFull(&msg_obj_c->stObject.c);
        msg_obj_c->id =RES_3;
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
      RES_1, RES_2, RES_3};
    switch (0) {
      case RES_1:{
        float a_rand = (3.40282e+38-(1.17549e-38))*
          ((float)random()/RAND_MAX)+(1.17549e-38);
        msg_obj_cpp->set_a(a_rand);
        msg_obj_cpp->set_id(RES_1);
      }
      break;
      case RES_2:{
        uint32_t b_rand = random()%(4294967295ULL-(0ULL))+(0ULL);
        msg_obj_cpp->set_b(b_rand);
        msg_obj_cpp->set_id(RES_2);
      }
      break;
      case RES_3:{
        FillInnerFull(msg_obj_cpp->mutable_c());
        msg_obj_cpp->set_id(RES_3);
      }
      break;
    }
  }
}
bool run_AResource_encode_speed_test(std::map<std::string, double>& c_map, std::map<std::string, double>& cpp_map){
  {
    struct timeval current_time, start_time;
    double c_elapsed_time = 0, cpp_elapsed_time = 0;
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
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 10; i++) {
        len2 = SerializeResInnerToArray(&c_message, c_buffer, len1);
    }
    gettimeofday(&current_time, NULL);
    c_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    c_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 10; i++) {
         cpp_message.SerializeToString(&cpp_buffer);
    }
    gettimeofday(&current_time, NULL);
    cpp_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    cpp_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    c_map["ResInner"] += c_elapsed_time;
    cpp_map["Res::Inner"] += cpp_elapsed_time;
    free(c_buffer);
  }
  {
    struct timeval current_time, start_time;
    double c_elapsed_time = 0, cpp_elapsed_time = 0;
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
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 10; i++) {
        len2 = SerializeReshelloworldToArray(&c_message, c_buffer, len1);
    }
    gettimeofday(&current_time, NULL);
    c_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    c_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 10; i++) {
         cpp_message.SerializeToString(&cpp_buffer);
    }
    gettimeofday(&current_time, NULL);
    cpp_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    cpp_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    c_map["Reshelloworld"] += c_elapsed_time;
    cpp_map["Res::helloworld"] += cpp_elapsed_time;
    free(c_buffer);
  }
  return true;
}
bool run_AResource_decode_speed_test(std::map<std::string, double>& c_map, std::map<std::string, double>& cpp_map){
  {
    struct timeval current_time, start_time;
    double c_elapsed_time = 0, cpp_elapsed_time = 0;
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
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 100; i++) {
        ParseResInner(c_buffer, len2, &c_message);
    }
    gettimeofday(&current_time, NULL);
    c_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    c_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 100; i++) {
         cpp_message.ParseFromString(cpp_buffer);
    }
    gettimeofday(&current_time, NULL);cpp_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    cpp_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    c_map["ResInner"] += c_elapsed_time;
    cpp_map["Res::Inner"] += cpp_elapsed_time;
    free(c_buffer);
  }
  {
    struct timeval current_time, start_time;
    double c_elapsed_time = 0, cpp_elapsed_time = 0;
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
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 100; i++) {
        ParseReshelloworld(c_buffer, len2, &c_message);
    }
    gettimeofday(&current_time, NULL);
    c_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    c_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < 100; i++) {
         cpp_message.ParseFromString(cpp_buffer);
    }
    gettimeofday(&current_time, NULL);cpp_elapsed_time += (current_time.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    cpp_elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    c_map["Reshelloworld"] += c_elapsed_time;
    cpp_map["Res::helloworld"] += cpp_elapsed_time;
    free(c_buffer);
  }
  return true;
}
