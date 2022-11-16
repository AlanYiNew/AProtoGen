#include "AResource_clear.h"

void ClearResInner(ResInner* msg_obj) {
  msg_obj->temp_ = 0;
}

void SetResInnerWrited(ResInner* msg_obj) {
}

void ClearReshelloworld(Reshelloworld* msg_obj) {
  switch (msg_obj->id()) {
    case RES_NUMVAL0: {
      msg_obj->stObject.a_ = 0;
      break;
    }
    case RES_NUMVAL1: {
      msg_obj->stObject.b_ = 0;
      break;
    }
    case RES_NUMVAL2: {
      memset(&msg_obj->stObject.c_, 0, sizeof(msg_obj->stObject.c_));
      break;
    }
    default: 
       memset(&msg_obj->stObject, 0, sizeof(msg_obj->stObject));
    break;
  }
  msg_obj->id_ = 0;
  msg_obj->str_[0]='\0';
  msg_obj->opt_ = 0;
  ClearResInner(&msg_obj->inner1());
  msg_obj->clear_has_inner1();
  ClearResInner(&msg_obj->inner2());
  msg_obj->clear_has_inner2();
  ClearResInner(&msg_obj->inner3());
  msg_obj->clear_has_inner3();
  ClearResInner(&msg_obj->inner4());
  msg_obj->clear_has_inner4();
  ClearResInner(&msg_obj->inner5());
  msg_obj->clear_has_inner5();
  ClearResInner(&msg_obj->inner6());
  msg_obj->clear_has_inner6();
  ClearResInner(&msg_obj->inner7());
  msg_obj->clear_has_inner7();
  ClearResInner(&msg_obj->inner8());
  msg_obj->clear_has_inner8();
  msg_obj->stringListSize = 0;
  msg_obj->enumValListSize = 0;
  msg_obj->enumVal_ = static_cast<RES_NumVal>(0);
}

void SetReshelloworldWrited(Reshelloworld* msg_obj) {
  switch (msg_obj->id()) {
    case RES_NUMVAL0: {
      break;
    }
    case RES_NUMVAL1: {
      break;
    }
    case RES_NUMVAL2: {
      SetResInnerWrited(&msg_obj->stObject.c_);
      break;
    }
    default: 
    break;
  }
  SetResInnerWrited(&msg_obj->inner1());
  SetResInnerWrited(&msg_obj->inner2());
  SetResInnerWrited(&msg_obj->inner3());
  SetResInnerWrited(&msg_obj->inner4());
  SetResInnerWrited(&msg_obj->inner5());
  SetResInnerWrited(&msg_obj->inner6());
  SetResInnerWrited(&msg_obj->inner7());
  SetResInnerWrited(&msg_obj->inner8());
}

