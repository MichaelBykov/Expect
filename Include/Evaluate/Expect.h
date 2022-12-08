// ===--- Expect.h ----------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for assertion expectations.                                  //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include "Expression.h"

START_NAMESPACE_EXPECT



/// The start of an expectation builder.
struct Expect {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  Expressions::Value<T> operator << (T other) {
    return { other };
  }
};



END_NAMESPACE_EXPECT



/// Define an assertion expression.
/// \remarks
///   Expectations can be set for any comparison.
///   For example, `EXPECT a == b`, `EXPECT a < b`, or `EXPECT a != b`.
///   Expectations can also be set for an expression that evaluates to a
///   boolean.
///   For example, `EXPECT isTrue()` or `EXPECT !someValue`.
#define EXPECT \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT Expect() <<

/// Define an assertion expression that aborts upon failure.
/// \remarks
///   Expectations and assertions can be set for any comparison.
///   For example, `ASSERT a == b`, `ASSERT a < b`, or `ASSERT a != b`.
///   Expectations and assertions can also be set for an expression that
///   evaluates to a boolean.
///   For example, `ASSERT isTrue()` or `ASSERT !someValue`.
#define ASSERT \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT Expect() <<
