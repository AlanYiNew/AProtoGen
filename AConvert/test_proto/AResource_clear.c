#include "AResource_clear.h"

void ClearResInner(ResInner* msg_obj) {
  msg_obj->temp = 0;
}

void SetResInnerWrited(ResInner* msg_obj) {
}

void ClearReshelloworld(Reshelloworld* msg_obj) {
  switch (msg_obj->id) {
    case RES_1: {
      msg_obj->stObject.a = 0;
      break;
    }
    case RES_2: {
      msg_obj->stObject.b = 0;
      break;
    }
    case RES_3: {
      memset(&msg_obj->stObject.c, 0, sizeof(msg_obj->stObject.c));
      break;
    }
    default: 
       memset(&msg_obj->stObject, 0, sizeof(msg_obj->stObject));
    break;
  }
  msg_obj->id = 0;
  msg_obj->str[0]='\0';
  msg_obj->opt = 0;
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
  msg_obj->enumVal = static_cast<RES_NumVal>(0);
}

void SetReshelloworldWrited(Reshelloworld* msg_obj) {
  switch (msg_obj->id) {
    case RES_1: {
      break;
    }
    case RES_2: {
      break;
    }
    case RES_3: {
      SetResInnerWrited(&msg_obj->stObject.c);
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

