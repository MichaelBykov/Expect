// ===--- Expect Float.h ----------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for floating-point assertion expectations.                   //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Expression/ApproxExpression.h>
#include <Expression/NearExpression.h>
#include <Expression/WithinExpression.h>

START_NAMESPACE_EXPECT



/// The start of an approximate expectation builder.
struct ExpectApprox {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  ApproxExpressions::Value<T> operator << (T other) {
    return { other };
  }
};

/// The start of an near expectation builder.
struct ExpectNear {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  NearExpressions::Value<T> operator << (T other) {
    return { other };
  }
};

/// The start of an within expectation builder.
struct ExpectWithin {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  WithinExpressions::Value<T> operator << (T other) {
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
#define EXPECT_APPROX \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectApprox() <<

/// Define an assertion expression that stops the test case upon failure.
/// \remarks
///   Expectations and assertions can be set for any comparison.
///   For example, `ASSERT a == b`, `ASSERT a < b`, or `ASSERT a != b`.
///   Expectations and assertions can also be set for an expression that
///   evaluates to a boolean.
///   For example, `ASSERT isTrue()` or `ASSERT !someValue`.
#define ASSERT_APPROX \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectApprox() <<



/// Define an assertion expression.
/// \remarks
///   Expectations can be set for any comparison.
///   For example, `EXPECT a == b`, `EXPECT a < b`, or `EXPECT a != b`.
///   Expectations can also be set for an expression that evaluates to a
///   boolean.
///   For example, `EXPECT isTrue()` or `EXPECT !someValue`.
#define EXPECT_NEAR \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectNear() <<

/// Define an assertion expression that stops the test case upon failure.
/// \remarks
///   Expectations and assertions can be set for any comparison.
///   For example, `ASSERT a == b`, `ASSERT a < b`, or `ASSERT a != b`.
///   Expectations and assertions can also be set for an expression that
///   evaluates to a boolean.
///   For example, `ASSERT isTrue()` or `ASSERT !someValue`.
#define ASSERT_NEAR \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectNear() <<



/// Define an assertion expression.
/// \remarks
///   Expectations can be set for any comparison.
///   For example, `EXPECT a == b`, `EXPECT a < b`, or `EXPECT a != b`.
///   Expectations can also be set for an expression that evaluates to a
///   boolean.
///   For example, `EXPECT isTrue()` or `EXPECT !someValue`.
#define EXPECT_WITHIN \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectWithin() <<

/// Define an assertion expression that stops the test case upon failure.
/// \remarks
///   Expectations and assertions can be set for any comparison.
///   For example, `ASSERT a == b`, `ASSERT a < b`, or `ASSERT a != b`.
///   Expectations and assertions can also be set for an expression that
///   evaluates to a boolean.
///   For example, `ASSERT isTrue()` or `ASSERT !someValue`.
#define ASSERT_WITHIN \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectWithin() <<
