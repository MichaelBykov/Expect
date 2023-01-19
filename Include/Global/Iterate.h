// ===--- Iterate.h ---------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
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

#define _EXPECT_ITERATE_STRINGIFY(value) #value

#define _EXPECT_STRINGIFY_ARGS(...) \
  _EXPECT_ITERATE(_EXPECT_ITERATE_STRINGIFY, __VA_ARGS__)



#define _EXPECT_SWITCH_IMP_1( _1, _2, _3, _4, _5, others, arg, ...) _1(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_2( _1, _2, _3, _4, _5, others, arg, ...) _2(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_3( _1, _2, _3, _4, _5, others, arg, ...) _3(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_4( _1, _2, _3, _4, _5, others, arg, ...) _4(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_5( _1, _2, _3, _4, _5, others, arg, ...) _5(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_6( _1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_7( _1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_8( _1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_9( _1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_10(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_11(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_12(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_13(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_14(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_15(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_16(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_17(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_18(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_19(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_20(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_21(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_22(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_23(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_24(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_25(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_26(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_27(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_28(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_29(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_30(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_31(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_32(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_33(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_34(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_35(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_36(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_37(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_38(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_39(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_40(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_41(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_42(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_43(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_44(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_45(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_46(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_47(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_48(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_49(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)
#define _EXPECT_SWITCH_IMP_50(_1, _2, _3, _4, _5, others, arg, ...) others(__VA_ARGS__)



#define _EXPECT_SWITCH_IMP(_1, _2, _3, _4, _5, others, ...) \
  _EXPECT_CONCAT(_EXPECT_SWITCH_IMP_, _EXPECT_COUNT(__VA_ARGS__)) \
  (_1, _2, _3, _4, _5, others, __VA_ARGS__)

#define _EXPECT_SWITCH_5(_1, _2, _3, _4, _5, others, ...) \
  _EXPECT_SWITCH_IMP(_1, _2, _3, _4, _5, others, __VA_ARGS__)

#define _EXPECT_SWITCH_4(_1, _2, _3, _4, others, ...) \
  _EXPECT_SWITCH_IMP(_1, _2, _3, _4, others, others, __VA_ARGS__)

#define _EXPECT_SWITCH_3(_1, _2, _3, others, ...) \
  _EXPECT_SWITCH_IMP(_1, _2, _3, others, others, others, __VA_ARGS__)

#define _EXPECT_SWITCH_2(_1, _2, others, ...) \
  _EXPECT_SWITCH_IMP(_1, _2, others, others, others, others, __VA_ARGS__)

#define _EXPECT_SWITCH_1(_1, others, ...) \
  _EXPECT_SWITCH_IMP(_1, others, others, others, others, others, __VA_ARGS__)

#define _EXPECT_SWITCH_PASS(...)



#define _EXPECT_ARG_1( arg, ...) arg
#define _EXPECT_ARG_2( arg, ...) _EXPECT_ARG_1( __VA_ARGS__)
#define _EXPECT_ARG_3( arg, ...) _EXPECT_ARG_2( __VA_ARGS__)
#define _EXPECT_ARG_4( arg, ...) _EXPECT_ARG_3( __VA_ARGS__)
#define _EXPECT_ARG_5( arg, ...) _EXPECT_ARG_4( __VA_ARGS__)
#define _EXPECT_ARG_6( arg, ...) _EXPECT_ARG_5( __VA_ARGS__)
#define _EXPECT_ARG_7( arg, ...) _EXPECT_ARG_6( __VA_ARGS__)
#define _EXPECT_ARG_8( arg, ...) _EXPECT_ARG_7( __VA_ARGS__)
#define _EXPECT_ARG_9( arg, ...) _EXPECT_ARG_8( __VA_ARGS__)
#define _EXPECT_ARG_10(arg, ...) _EXPECT_ARG_9( __VA_ARGS__)
#define _EXPECT_ARG_11(arg, ...) _EXPECT_ARG_10(__VA_ARGS__)
#define _EXPECT_ARG_12(arg, ...) _EXPECT_ARG_11(__VA_ARGS__)
#define _EXPECT_ARG_13(arg, ...) _EXPECT_ARG_12(__VA_ARGS__)
#define _EXPECT_ARG_14(arg, ...) _EXPECT_ARG_13(__VA_ARGS__)
#define _EXPECT_ARG_15(arg, ...) _EXPECT_ARG_14(__VA_ARGS__)
#define _EXPECT_ARG_16(arg, ...) _EXPECT_ARG_15(__VA_ARGS__)
#define _EXPECT_ARG_17(arg, ...) _EXPECT_ARG_16(__VA_ARGS__)
#define _EXPECT_ARG_18(arg, ...) _EXPECT_ARG_17(__VA_ARGS__)
#define _EXPECT_ARG_19(arg, ...) _EXPECT_ARG_18(__VA_ARGS__)
#define _EXPECT_ARG_20(arg, ...) _EXPECT_ARG_19(__VA_ARGS__)
#define _EXPECT_ARG_21(arg, ...) _EXPECT_ARG_20(__VA_ARGS__)
#define _EXPECT_ARG_22(arg, ...) _EXPECT_ARG_21(__VA_ARGS__)
#define _EXPECT_ARG_23(arg, ...) _EXPECT_ARG_22(__VA_ARGS__)
#define _EXPECT_ARG_24(arg, ...) _EXPECT_ARG_23(__VA_ARGS__)
#define _EXPECT_ARG_25(arg, ...) _EXPECT_ARG_24(__VA_ARGS__)
#define _EXPECT_ARG_26(arg, ...) _EXPECT_ARG_25(__VA_ARGS__)
#define _EXPECT_ARG_27(arg, ...) _EXPECT_ARG_26(__VA_ARGS__)
#define _EXPECT_ARG_28(arg, ...) _EXPECT_ARG_27(__VA_ARGS__)
#define _EXPECT_ARG_29(arg, ...) _EXPECT_ARG_28(__VA_ARGS__)
#define _EXPECT_ARG_30(arg, ...) _EXPECT_ARG_29(__VA_ARGS__)
#define _EXPECT_ARG_31(arg, ...) _EXPECT_ARG_30(__VA_ARGS__)
#define _EXPECT_ARG_32(arg, ...) _EXPECT_ARG_31(__VA_ARGS__)
#define _EXPECT_ARG_33(arg, ...) _EXPECT_ARG_32(__VA_ARGS__)
#define _EXPECT_ARG_34(arg, ...) _EXPECT_ARG_33(__VA_ARGS__)
#define _EXPECT_ARG_35(arg, ...) _EXPECT_ARG_34(__VA_ARGS__)
#define _EXPECT_ARG_36(arg, ...) _EXPECT_ARG_35(__VA_ARGS__)
#define _EXPECT_ARG_37(arg, ...) _EXPECT_ARG_36(__VA_ARGS__)
#define _EXPECT_ARG_38(arg, ...) _EXPECT_ARG_37(__VA_ARGS__)
#define _EXPECT_ARG_39(arg, ...) _EXPECT_ARG_38(__VA_ARGS__)
#define _EXPECT_ARG_40(arg, ...) _EXPECT_ARG_39(__VA_ARGS__)
#define _EXPECT_ARG_41(arg, ...) _EXPECT_ARG_40(__VA_ARGS__)
#define _EXPECT_ARG_42(arg, ...) _EXPECT_ARG_41(__VA_ARGS__)
#define _EXPECT_ARG_43(arg, ...) _EXPECT_ARG_42(__VA_ARGS__)
#define _EXPECT_ARG_44(arg, ...) _EXPECT_ARG_43(__VA_ARGS__)
#define _EXPECT_ARG_45(arg, ...) _EXPECT_ARG_44(__VA_ARGS__)
#define _EXPECT_ARG_46(arg, ...) _EXPECT_ARG_45(__VA_ARGS__)
#define _EXPECT_ARG_47(arg, ...) _EXPECT_ARG_46(__VA_ARGS__)
#define _EXPECT_ARG_48(arg, ...) _EXPECT_ARG_47(__VA_ARGS__)
#define _EXPECT_ARG_49(arg, ...) _EXPECT_ARG_48(__VA_ARGS__)
#define _EXPECT_ARG_50(arg, ...) _EXPECT_ARG_49(__VA_ARGS__)
