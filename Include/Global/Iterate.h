// ===--- Iterate.h ---------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// A set of iteration macros.                                                 //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>



#define _EXPECT_CONCAT_(lhs, rhs) lhs##rhs
#define _EXPECT_CONCAT(lhs, rhs) _EXPECT_CONCAT_(lhs, rhs)

#define _EXPECT_COUNT_( \
  __1, __2, __3, __4, __5, __6, __7, __8, __9, _10, \
  _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
  _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
  _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
  _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
  N, ... \
) N
#define _EXPECT_COUNT(...) \
  _EXPECT_COUNT_(__VA_ARGS__, \
    50, 49, 48, 47, 46, 45, 44, 43, 42, 41, \
    40, 39, 38, 37, 36, 35, 34, 33, 32, 31, \
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21, \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11, \
    10,  9,  8,  7,  6,  5,  4,  3,  2,  1 \
  )



#define _EXPECT_FOR_EACH_1( _1, _2, _3, _4, _5, each, arg, ...) _1(arg)
#define _EXPECT_FOR_EACH_2( _1, _2, _3, _4, _5, each, arg, ...) _2(arg)   _EXPECT_FOR_EACH_1( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_3( _1, _2, _3, _4, _5, each, arg, ...) _3(arg)   _EXPECT_FOR_EACH_2( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_4( _1, _2, _3, _4, _5, each, arg, ...) _4(arg)   _EXPECT_FOR_EACH_3( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_5( _1, _2, _3, _4, _5, each, arg, ...) _5(arg)   _EXPECT_FOR_EACH_4( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_6( _1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_5( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_7( _1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_6( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_8( _1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_7( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_9( _1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_8( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_10(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_9( _1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_11(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_10(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_12(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_11(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_13(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_12(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_14(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_13(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_15(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_14(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_16(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_15(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_17(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_16(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_18(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_17(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_19(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_18(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_20(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_19(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_21(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_20(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_22(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_21(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_23(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_22(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_24(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_23(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_25(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_24(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_26(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_25(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_27(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_26(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_28(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_27(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_29(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_28(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_30(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_29(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_31(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_30(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_32(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_31(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_33(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_32(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_34(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_33(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_35(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_34(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_36(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_35(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_37(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_36(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_38(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_37(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_39(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_38(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_40(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_39(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_41(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_40(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_42(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_41(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_43(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_42(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_44(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_43(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_45(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_44(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_46(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_45(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_47(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_46(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_48(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_47(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_49(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_48(_1, _2, _3, _4, _5, each, __VA_ARGS__)
#define _EXPECT_FOR_EACH_50(_1, _2, _3, _4, _5, each, arg, ...) each(arg) _EXPECT_FOR_EACH_49(_1, _2, _3, _4, _5, each, __VA_ARGS__)

#define _EXPECT_ITERATE_IMP(_1, _2, _3, _4, _5, each, ...) \
  _EXPECT_CONCAT(_EXPECT_FOR_EACH_, _EXPECT_COUNT(__VA_ARGS__)) \
  (_1, _2, _3, _4, _5, each, __VA_ARGS__)

#define _EXPECT_ITERATE_5(_1, _2, _3, _4, _5, each, ...) \
  _EXPECT_ITERATE_IMP(_1, _2, _3, _4, _5, each, __VA_ARGS__)

#define _EXPECT_ITERATE_4(_1, _2, _3, _4, each, ...) \
  _EXPECT_ITERATE_IMP(_1, _2, _3, _4, each, each, __VA_ARGS__)

#define _EXPECT_ITERATE_3(_1, _2, _3, each, ...) \
  _EXPECT_ITERATE_IMP(_1, _2, _3, each, each, each, __VA_ARGS__)

#define _EXPECT_ITERATE_2(_1, _2, each, ...) \
  _EXPECT_ITERATE_IMP(_1, _2, each, each, each, each, __VA_ARGS__)

#define _EXPECT_ITERATE_1(_1, each, ...) \
  _EXPECT_ITERATE_IMP(_1, each, each, each, each, each, __VA_ARGS__)

#define _EXPECT_ITERATE(each, ...) \
  _EXPECT_ITERATE_IMP(each, each, each, each, each, each, __VA_ARGS__)

#define _EXPECT_ITERATE_PASS(value)
