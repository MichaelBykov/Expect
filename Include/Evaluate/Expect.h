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



/// An expectation builder for a single value.
template<typename T>
struct ExpectCase {
  /// The value for which to build expectations.
  T value;
  
  /// Set expectations for a value.
  /// \param[in] value
  ///   The value for which to set expectations.
  ExpectCase<T>(T value) : value(value) { }
  
  
  
  /// Expect that the loaded value is exactly equal to another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   An equality expectation.
  Expressions::Equal<T> operator ==(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly not equal to another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A non-equality expectation.
  Expressions::NotEqual<T> operator !=(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly less than another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Expressions::Less<T> operator <(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly less than or equal to another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Expressions::LessEqual<T> operator <=(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly greater than another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Expressions::Greater<T> operator >(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly greater than or equal to another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Expressions::GreaterEqual<T> operator >=(T other) {
    return { value, other };
  }
};



/// The start of an expectation builder.
struct Expect {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  ExpectCase<T> operator << (T other) {
    return other;
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
  ::Testing::Evaluate(__environment, __FILE__, __LINE__, false), \
    ::Testing::Expect() <<

/// Define an assertion expression that aborts upon failure.
/// \remarks
///   Expectations and assertions can be set for any comparison.
///   For example, `ASSERT a == b`, `ASSERT a < b`, or `ASSERT a != b`.
///   Expectations and assertions can also be set for an expression that
///   evaluates to a boolean.
///   For example, `ASSERT isTrue()` or `ASSERT !someValue`.
#define ASSERT \
  ::Testing::Evaluate(__environment, __FILE__, __LINE__, true), \
    ::Testing::Expect() <<
