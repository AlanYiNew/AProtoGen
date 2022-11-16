#ifndef ARESOURCE_H__
#define ARESOURCE_H__

#include "pbc_extension.h"
#include <cstring>
#include <cstdint>

/*  */
typedef enum tagRES_NumVal {
    RES_NumVal_MIN = 0,
    RES_NUMVAL0 = 0, /*  */ 
    RES_NUMVAL1 = 1, /*  */ 
    RES_NUMVAL2 = 2, /*  */ 
    RES_NumVal_MAX = 2,
} RES_NumVal;
#define RES_NUMVAL_ARRAYSIZE 3

struct tagResInner;
typedef struct tagResInner ResInner;
typedef struct tagResInner RESINNER;
typedef struct tagResInner*LPRESINNER;

struct tagResInnerCachedSize_;
typedef struct tagResInnerCachedSize_ ResInnerCachedSize_;
struct tagReshelloworld;
typedef struct tagReshelloworld Reshelloworld;
typedef struct tagReshelloworld RESHELLOWORLD;
typedef struct tagReshelloworld*LPRESHELLOWORLD;

struct tagReshelloworldCachedSize_;
typedef struct tagReshelloworldCachedSize_ ReshelloworldCachedSize_;
union tagResobject;
typedef union tagResobject Resobject;
typedef union tagResobject RESOBJECT;
typedef union tagResobject* LPRESOBJECT;
union tagResobjectCachedSize_;
typedef union tagResobjectCachedSize_ ResobjectCachedSize_;
/*  */ 
struct tagResInner{
    int32_t temp_; /*  */ 
    inline int32_t temp() const{
      return temp_;
    }
    inline void set_temp(int32_t val) {
      temp_ = val;
    }
};
struct tagResInnerCachedSize_ {
    int32_t cached_size_;
};
/*  */ 
union tagResobject {
    float a_; /*  */ 
    uint32_t b_; /*  */ 
    ResInner c_; /*  */ 
};
typedef union tagResobjectCachedSize_ {
    ResInnerCachedSize_ c;
} ResobjectCachedSize_;
/*  */ 
struct tagReshelloworld{
    int32_t id_; /*  ID */ 
    char str_[20]; /*  str */ 
    int32_t opt_; /* optional field */ 
    // struct have to be access by function
    ResInner inner1_; /*  temp */ 
    // struct have to be access by function
    ResInner inner2_; /*  temp */ 
    // struct have to be access by function
    ResInner inner3_; /*  temp */ 
    // struct have to be access by function
    ResInner inner4_; /*  temp */ 
    // struct have to be access by function
    ResInner inner5_; /*  temp */ 
    // struct have to be access by function
    ResInner inner6_; /*  temp */ 
    // struct have to be access by function
    ResInner inner7_; /*  temp */ 
    // struct have to be access by function
    ResInner inner8_; /*  temp */ 
    Resobject stObject; /*  */ 
    char stringList_[10][20]; /*  */ 
    uint32_t stringListSize;
    RES_NumVal enumValList_[1]; /*  */ 
    uint32_t enumValListSize;
    RES_NumVal enumVal_; /*  */ 
    uint8_t has_flag_[1];
    inline int32_t id() const{
      return id_;
    }
    inline void set_id(int32_t val) {
      id_ = val;
    }
    inline const char* str() const {
      return str_;
    }
    inline void set_str(const char* field) {
      strncpy_s(str_,  sizeof(str_), field, strlen(field));
    }
    inline int32_t opt() const{
      return opt_;
    }
    inline void set_opt(int32_t val) {
      opt_ = val;
    }
    inline ResInner* mutable_inner1() {
      if (has_inner1()){
          has_flag_[0] |= 1;
      }
      return &inner1_;
    }
    inline const ResInner& inner1() const {
      return inner1_;
    }
    inline void set_inner1(const ResInner& field) {
      inner1_ = field;
    }
    inline int has_inner1() const{
      return (has_flag_[0] & 1) != 0;
    }
    inline void clear_has_inner1() {
      has_flag_[0] &=  ~1;
    }
    inline ResInner* mutable_inner2() {
      if (has_inner2()){
          has_flag_[0] |= 2;
      }
      return &inner2_;
    }
    inline const ResInner& inner2() const {
      return inner2_;
    }
    inline void set_inner2(const ResInner& field) {
      inner2_ = field;
    }
    inline int has_inner2() const{
      return (has_flag_[0] & 2) != 0;
    }
    inline void clear_has_inner2() {
      has_flag_[0] &=  ~2;
    }
    inline ResInner* mutable_inner3() {
      if (has_inner3()){
          has_flag_[0] |= 4;
      }
      return &inner3_;
    }
    inline const ResInner& inner3() const {
      return inner3_;
    }
    inline void set_inner3(const ResInner& field) {
      inner3_ = field;
    }
    inline int has_inner3() const{
      return (has_flag_[0] & 4) != 0;
    }
    inline void clear_has_inner3() {
      has_flag_[0] &=  ~4;
    }
    inline ResInner* mutable_inner4() {
      if (has_inner4()){
          has_flag_[0] |= 8;
      }
      return &inner4_;
    }
    inline const ResInner& inner4() const {
      return inner4_;
    }
    inline void set_inner4(const ResInner& field) {
      inner4_ = field;
    }
    inline int has_inner4() const{
      return (has_flag_[0] & 8) != 0;
    }
    inline void clear_has_inner4() {
      has_flag_[0] &=  ~8;
    }
    inline ResInner* mutable_inner5() {
      if (has_inner5()){
          has_flag_[0] |= 16;
      }
      return &inner5_;
    }
    inline const ResInner& inner5() const {
      return inner5_;
    }
    inline void set_inner5(const ResInner& field) {
      inner5_ = field;
    }
    inline int has_inner5() const{
      return (has_flag_[0] & 16) != 0;
    }
    inline void clear_has_inner5() {
      has_flag_[0] &=  ~16;
    }
    inline ResInner* mutable_inner6() {
      if (has_inner6()){
          has_flag_[0] |= 32;
      }
      return &inner6_;
    }
    inline const ResInner& inner6() const {
      return inner6_;
    }
    inline void set_inner6(const ResInner& field) {
      inner6_ = field;
    }
    inline int has_inner6() const{
      return (has_flag_[0] & 32) != 0;
    }
    inline void clear_has_inner6() {
      has_flag_[0] &=  ~32;
    }
    inline ResInner* mutable_inner7() {
      if (has_inner7()){
          has_flag_[0] |= 64;
      }
      return &inner7_;
    }
    inline const ResInner& inner7() const {
      return inner7_;
    }
    inline void set_inner7(const ResInner& field) {
      inner7_ = field;
    }
    inline int has_inner7() const{
      return (has_flag_[0] & 64) != 0;
    }
    inline void clear_has_inner7() {
      has_flag_[0] &=  ~64;
    }
    inline ResInner* mutable_inner8() {
      if (has_inner8()){
          has_flag_[0] |= 128;
      }
      return &inner8_;
    }
    inline const ResInner& inner8() const {
      return inner8_;
    }
    inline void set_inner8(const ResInner& field) {
      inner8_ = field;
    }
    inline int has_inner8() const{
      return (has_flag_[0] & 128) != 0;
    }
    inline void clear_has_inner8() {
      has_flag_[0] &=  ~128;
    }
    inline void set_a(float val) {
      if (!has_a()){
          id_ = RES_NUMVAL0;
      }
      stObject.a_ = val;
    }
    inline bool has_a() const{
      return id_ == RES_NUMVAL0;
    }
    inline float a() const{
      return stObject.a_;
    }
    inline void set_b(uint32_t val) {
      if (!has_b()){
          id_ = RES_NUMVAL1;
      }
      stObject.b_ = val;
    }
    inline bool has_b() const{
      return id_ == RES_NUMVAL1;
    }
    inline uint32_t b() const{
      return stObject.b_;
    }
    inline ResInner* mutable_c() {
      if (has_c()){
          memset(&stObject.c_, 0, sizeof(stObject.c_));
          id_ = RES_NUMVAL2;
      }
      return &stObject.c_;
    }
    inline const ResInner& c() const {
      return stObject.c_;
    }
    inline void set_c(const ResInner& field) {
      stObject.c_ = field;
    }
    inline int has_c() const{
      return id_ != RES_NUMVAL2;
    }
    inline void clear_has_c() {
      id_ = 0;
    }
    inline const char* stringlist(int index) const {
      return stringList_[index];
    }
    inline void add_stringlist(const char* field) {
      if (stringListSize >= 10) return;
      strncpy_s(stringList_[stringListSize++],  sizeof(stringList_), field, strlen(field));
    }
    inline int stringlist_size(const char* fiel) {
      return stringListSize;
    }
    inline void add_enumvallist(RES_NumVal field) {
      if (enumValListSize >= 1) return;
      enumValList_[enumValListSize] = field;
      enumValListSize++;
      return;
    }
    inline int enumvallist_size() const{
      return enumValListSize;
    }
    inline RES_NumVal enumvallist(int index) const{
      return enumValList_[enumValListSize];
    }
    inline RES_NumVal enumval() const{
      return enumVal_;
    }
    inline void set_enumval(RES_NumVal val) {
      enumVal_ = val;
    }
};
struct tagReshelloworldCachedSize_ {
    int32_t str_;
    ResInnerCachedSize_ inner1_;
    ResInnerCachedSize_ inner2_;
    ResInnerCachedSize_ inner3_;
    ResInnerCachedSize_ inner4_;
    ResInnerCachedSize_ inner5_;
    ResInnerCachedSize_ inner6_;
    ResInnerCachedSize_ inner7_;
    ResInnerCachedSize_ inner8_;
    ResobjectCachedSize_ stObject;
    int32_t stringList_[10];
    int32_t enumValList_;
    int32_t cached_size_;
};
#endif //ARESOURCE_H__