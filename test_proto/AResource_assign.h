#ifndef ARESOURCE_ASSIGN_H__
#define ARESOURCE_ASSIGN_H__

#include "AResource.h"
#include "AResource.pb.h"
#include "pbc_extension_assign.h"
#ifdef ENABLE_PB_LOG
#include "comm/comm_gamecore/log_module.h"
#endif 
#include <cstdint>

inline bool AssignInnerToResInner(const Res::Inner& msg_obj_cpp, ResInner& msg_obj_c) {
  {
    msg_obj_c.set_temp(msg_obj_cpp.temp());
  }
  return true;
}
inline bool AssignResInnerToInner(const ResInner& msg_obj_c, Res::Inner& msg_obj_cpp) {
  {
    msg_obj_cpp.set_temp(msg_obj_c.temp());
  }
  return true;
}
inline bool AssignhelloworldToReshelloworld(const Res::helloworld& msg_obj_cpp, Reshelloworld& msg_obj_c) {
  {
    int32_t str_len = (uint64_t)msg_obj_cpp.str().size() >= sizeof(msg_obj_c.str_) ? sizeof(msg_obj_c.str_) - 1 : msg_obj_cpp.str().size();
    strncpy(&msg_obj_c.str_[0], msg_obj_cpp.str().c_str(), str_len);
    msg_obj_c.str_[str_len] = 0;
  }
  {
    msg_obj_c.set_opt(msg_obj_cpp.opt());
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner1(), *msg_obj_c.mutable_inner1())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner2(), *msg_obj_c.mutable_inner2())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner3(), *msg_obj_c.mutable_inner3())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner4(), *msg_obj_c.mutable_inner4())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner5(), *msg_obj_c.mutable_inner5())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner6(), *msg_obj_c.mutable_inner6())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner7(), *msg_obj_c.mutable_inner7())) return false;
  }
  {
    if (!AssignInnerToResInner(msg_obj_cpp.inner8(), *msg_obj_c.mutable_inner8())) return false;
  }
  {
    for (uint32_t i = 0; i < msg_obj_cpp.stringlist_size() && i < 10; i++) {
      int32_t len = (uint64_t)msg_obj_cpp.stringlist(i).size() >= sizeof(msg_obj_c.stringList_[i]) ? sizeof(msg_obj_c.stringList_[i]) - 1 : msg_obj_cpp.stringlist(i).size();
      strncpy(&msg_obj_c.stringList_[i][0], msg_obj_cpp.stringlist(i).c_str(), len);
      msg_obj_c.stringList_[i][len] = 0;
      msg_obj_c.stringListSize = i+1;
    }
  }
  {
    for (uint32_t i = 0; i < msg_obj_cpp.enumvallist_size() && i < 1; i++) {
      msg_obj_c.add_enumvallist((RES_NumVal)msg_obj_cpp.enumvallist(i));
    }
  }
  {
    msg_obj_c.set_enumval((RES_NumVal)msg_obj_cpp.enumval());
  }
  {
  switch (msg_obj_cpp.object_case()) {
    case Res::helloworld::kA:{
      msg_obj_c.set_a(msg_obj_cpp.a());
      msg_obj_c.set_id(RES_NUMVAL0);
    }
    break;
    case Res::helloworld::kB:{
      msg_obj_c.set_b(msg_obj_cpp.b());
      msg_obj_c.set_id(RES_NUMVAL1);
    }
    break;
    case Res::helloworld::kC:{
      if (!AssignInnerToResInner(msg_obj_cpp.c(), *msg_obj_c.mutable_c())) return false;
      msg_obj_c.set_id(RES_NUMVAL2);
    }
    break;
    case Res::helloworld::OBJECT_NOT_SET:
     break;
    }
  }
  return true;
}
inline bool AssignReshelloworldTohelloworld(const Reshelloworld& msg_obj_c, Res::helloworld& msg_obj_cpp) {
  {
    msg_obj_cpp.set_str(std::string(msg_obj_c.str()));
  }
  {
    msg_obj_cpp.set_opt(msg_obj_c.opt());
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner1(), *msg_obj_cpp.mutable_inner1())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner2(), *msg_obj_cpp.mutable_inner2())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner3(), *msg_obj_cpp.mutable_inner3())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner4(), *msg_obj_cpp.mutable_inner4())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner5(), *msg_obj_cpp.mutable_inner5())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner6(), *msg_obj_cpp.mutable_inner6())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner7(), *msg_obj_cpp.mutable_inner7())) return false;
  }
  {
    if (!AssignResInnerToInner(msg_obj_c.inner8(), *msg_obj_cpp.mutable_inner8())) return false;
  }
  {
    for (uint32_t i = 0; i < msg_obj_c.stringListSize; i++) {
      msg_obj_cpp.add_stringlist(msg_obj_c.stringlist(i));
    }
  }
  {
    for (uint32_t i = 0; i < msg_obj_c.enumValListSize; i++) {
      msg_obj_cpp.add_enumvallist((Res::NumVal)msg_obj_c.enumvallist(i));
    }
  }
  {
    msg_obj_cpp.set_enumval((Res::NumVal)msg_obj_c.enumval());
  }
  {
  switch (msg_obj_c.id()) {
    case RES_NUMVAL0:{
      msg_obj_cpp.set_a(msg_obj_c.a());
    }
    break;
    case RES_NUMVAL1:{
      msg_obj_cpp.set_b(msg_obj_c.b());
    }
    break;
    case RES_NUMVAL2:{
      if (!AssignResInnerToInner(msg_obj_c.c(), *msg_obj_cpp.mutable_c())) return false;
    }
    break;
    }
  }
  return true;
}
#endif 
