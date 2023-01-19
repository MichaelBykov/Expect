// ===--- Expect.h ----------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for assertion expectations.                                  //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Expression/Expression.h>
#include <Expression/ExactExpression.h>
#include <Expression/MiscExpression.h>

START_NAMESPACE_EXPECT



/// The start of an expectation builder.
struct Expect {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  ExactExpressions::Value<T> operator << (T other) {
    return { other };
  }
};

/// The start of an exception expectation builder.
template<typename T>
struct ExpectException {
  /// The name of the exception type.
  const char *exception;
  
  /// Create an exception expectation builder through the exception type name.
  /// \param[in] exception
  ///   The name of the exception type to expect.
  ExpectException<T>(
    const char *exception
  ) : exception(exception) { }
  
  /// Load an expression from which to expect an exception.
  /// \param[in] other
  ///   The expression for which to build expectations.
  /// \returns
  ///   An expectation builder for the given expression.
  MiscExpressions::ExceptionValue<T> operator << (
    std::function<void()> expression
  ) {
    return MiscExpressions::ExceptionValue<T> { exception, expression };
  }
};

/// The start of an exception expectation builder for any exception.
struct ExpectAnyException {
  /// Load an expression from which to expect any exception.
  /// \param[in] other
  ///   The expression for which to build expectations.
  /// \returns
  ///   An expectation builder for the given expression.
  MiscExpressions::AnyExceptionValue operator << (
    std::function<void()> expression
  ) {
    return { expression };
  }
};

/// The start of an exception expectation builder for no exceptions.
struct ExpectNoException {
  /// Load an expression from which to expect no exceptions.
  /// \param[in] other
  ///   The expression for which to build expectations.
  /// \returns
  ///   An expectation builder for the given expression.
  MiscExpressions::NoExceptionValue operator << (
    std::function<void()> expression
  ) {
    return { expression };
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

/// Define an assertion expression that stops the test case upon failure.
/// \remarks
///   Expectations and assertions can be set for any comparison.
///   For example, `ASSERT a == b`, `ASSERT a < b`, or `ASSERT a != b`.
///   Expectations and assertions can also be set for an expression that
///   evaluates to a boolean.
///   For example, `ASSERT isTrue()` or `ASSERT !someValue`.
#define ASSERT \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT Expect() <<



/// Define an assertion expression for an exception.
/// \param exception
///   The type of exception to expect.
/// \remarks
///   The exception expression should be enclosed in curly braces.
///   For example, `EXPECT_EXCEPTION(int) { throw 3 };`
#define EXPECT_EXCEPTION(exception) \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectException<exception>(#exception) << [&]() -> void

/// Define an assertion expression for an exception that stops the test case
/// upon failure.
/// \param exception
///   The type of exception to expect.
/// \remarks
///   The exception expression should be enclosed in curly braces.
///   For example, `ASSERT_EXCEPTION(int) { throw 3 };`
#define ASSERT_EXCEPTION(exception) \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectException<exception>(#exception) << [&]() -> void



/// Define an assertion expression for any exception.
/// \remarks
///   The exception expression should be enclosed in curly braces.
///   For example, `EXPECT_ANY_EXCEPTION { throw 3 };`
#define EXPECT_ANY_EXCEPTION \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectAnyException() << [&]() -> void

/// Define an assertion expression for any exception that stops the test case
/// upon failure.
/// \remarks
///   The exception expression should be enclosed in curly braces.
///   For example, `EXPECT_ANY_EXCEPTION { throw 3 };`
#define ASSERT_ANY_EXCEPTION \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectAnyException() << [&]() -> void



/// Define an assertion expression for no exceptions.
/// \remarks
///   The exception expression should be enclosed in curly braces.
///   For example, `EXPECT_NO_EXCEPTION { throw 3 };`
#define EXPECT_NO_EXCEPTION \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectNoException() << [&]() -> void

/// Define an assertion expression for no exceptions that stops the test case
/// upon failure.
/// \remarks
///   The exception expression should be enclosed in curly braces.
///   For example, `EXPECT_NO_EXCEPTION { throw 3 };`
#define ASSERT_NO_EXCEPTION \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectNoException() << [&]() -> void
