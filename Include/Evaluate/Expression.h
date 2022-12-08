// ===--- Expression.h ------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for assertion expressions.                                   //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Global/toString.h>
#include <string>

START_NAMESPACE_EXPECT
namespace Expressions {



/// An expression that can be evaluated for validity.
struct Expression {
  /// An optional message carried by the expression.
  const char *message = nullptr;
  
  /// Evaluate the expression with the set values.
  virtual bool evaluate() = 0;
  
  /// The message to report if the evaluation failed.
  virtual std::string failMessage() = 0;
  
  /// Any cleanup that needs to be performed for the expression.
  virtual void cleanup() { }
};

/// Expect that two values are exactly equal.
template<typename T>
struct Equal : Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// Create a new equal expression.
  Equal(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not equal to ")
      .append(toString(rhs)).append(".");
  }
  
  /// Load a message into the expression.
  Equal<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
};

/// Expect that two values are exactly not equal.
template<typename T>
struct NotEqual : Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// Create a new not-equal expression.
  NotEqual(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is equal to ")
      .append(toString(rhs)).append(".");
  }
  
  /// Load a message into the expression.
  NotEqual<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
};

/// Expect that a value is in an inclusive range.
template<typename T>
struct InclusiveRange : Expression {
  /// The lower-bound of the range.
  T lhs;
  /// The value to check for being within the range.
  T value;
  /// The upper-bound of the range.
  T rhs;
  
  /// Create a new range expression.
  InclusiveRange(T lhs, T value, T rhs) : lhs(lhs), value(value), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(value).append(" is not within the range of ")
      .append(toString(lhs)).append(", ")
      .append(toString(rhs)).append(" (inclusive).");
  }
  
  /// Load a message into the expression.
  InclusiveRange<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
};

/// Expect that a value is in a range.
template<typename T>
struct Range : Expression {
  /// The lower-bound of the range.
  T lhs;
  /// Whether or not the lower bound is included within the range
  /// (lower bound inclusive or exclusive).
  bool lhsIncluded;
  /// The value to check for being within the range.
  T value;
  /// The upper-bound of the range.
  T rhs;
  /// Whether or not the upper bound is included within the range
  /// (upper bound inclusive or exclusive).
  bool rhsIncluded;
  
  /// Create a new range expression.
  Range(T lhs, bool lhsIncluded, T value, T rhs, bool rhsIncluded) :
    lhs(lhs), lhsIncluded(lhsIncluded), value(value),
    rhs(rhs), rhsIncluded(rhsIncluded) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(value).append(" is not within the range of ")
      .append(toString(lhs)).append(", ")
      .append(toString(rhs)).append(" (")
      .append(
        lhsIncluded == rhsIncluded ?
          lhsIncluded ? "inclusive" : "exclusive" :
          lhsIncluded ? "inclusive, exclusive" : "exclusive, inclusive"
      )
      .append(").");
  }
  
  /// Load a message into the expression.
  Range<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
};

/// Expect that a value is in an exclusive range.
template<typename T>
struct ExclusiveRange : Expression {
  /// The lower-bound of the range.
  T lhs;
  /// The value to check for being within the range.
  T value;
  /// The upper-bound of the range.
  T rhs;
  
  /// Create a new range expression.
  ExclusiveRange(T lhs, T value, T rhs) : lhs(lhs), value(value), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(value).append(" is not within the range of ")
      .append(toString(lhs)).append(", ")
      .append(toString(rhs)).append(" (exclusive).");
  }
  
  /// Load a message into the expression.
  ExclusiveRange<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
};

/// Expect that one value is exactly less than another value.
template<typename T>
struct Less : Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// Create a new less-than expression.
  Less(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not less than ")
      .append(toString(rhs)).append(".");
  }
  
  /// Load a message into the expression.
  Less<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
  
  
  
  /// Expect that the loaded value is exactly within an exclusive range of
  /// values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  ExclusiveRange<T> operator <(T other) {
    return { lhs, rhs, other };
  }
  
  /// Expect that the loaded value is exactly within an exclusive, inclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator <=(T other) {
    return { lhs, false, rhs, other, true };
  }
};

/// Expect that one value is exactly less than or equal to another value.
template<typename T>
struct LessEqual : Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// Create a new less-than-or-equal-to expression.
  LessEqual(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not less than or equal to ")
      .append(toString(rhs)).append(".");
  }
  
  /// Load a message into the expression.
  LessEqual<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
  
  
  
  /// Expect that the loaded value is exactly within an inclusive, exclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator <(T other) {
    return { lhs, true, rhs, other, false };
  }
  
  /// Expect that the loaded value is exactly within an inclusive range of
  /// values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  InclusiveRange<T> operator <=(T other) {
    return { lhs, rhs, other };
  }
};

/// Expect that one value is exactly greater than another value.
template<typename T>
struct Greater : Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// Create a new greater-than expression.
  Greater(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not greater than ")
      .append(toString(rhs)).append(".");
  }
  
  /// Load a message into the expression.
  Greater<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
  
  
  
  /// Expect that the loaded value is exactly within an exclusive range of
  /// values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  ExclusiveRange<T> operator >(T other) {
    return { other, rhs, lhs };
  }
  
  /// Expect that the loaded value is exactly within an exclusive, inclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator >=(T other) {
    return { other, true, rhs, lhs, false };
  }
};

/// Expect that one value is exactly greater than or equal to another value.
template<typename T>
struct GreaterEqual : Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// Create a new greater-than-or-equal-to expression.
  GreaterEqual(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not greater than or equal to ")
      .append(toString(rhs)).append(".");
  }
  
  /// Load a message into the expression.
  GreaterEqual<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
  
  
  
  /// Expect that the loaded value is exactly within an inclusive, exclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator >(T other) {
    return { other, false, rhs, lhs, true };
  }
  
  /// Expect that the loaded value is exactly within an inclusive range of
  /// values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  InclusiveRange<T> operator >=(T other) {
    return { other, rhs, lhs };
  }
};

/// Expect that a value is true.
template<typename T>
struct Value : Expression {
  /// The value to test for truthiness.
  T value;
  
  /// Create a new value expression.
  Value(T value) : value(value) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return "Result evaluated to false.";
  }
  
  /// Load a message into the expression.
  Value<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
  
  
  
  /// Expect that the loaded value is exactly equal to another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   An equality expectation.
  Equal<T> operator ==(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly not equal to another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A non-equality expectation.
  NotEqual<T> operator !=(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly less than another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Less<T> operator <(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly less than or equal to another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  LessEqual<T> operator <=(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly greater than another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Greater<T> operator >(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is exactly greater than or equal to another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  GreaterEqual<T> operator >=(T other) {
    return { value, other };
  }
};

/// Expect that a an expression produces an exception.
template<typename T>
struct ExceptionValue : Expression {
  /// An exception expectation's value.
  struct Value {
    /// The name of the exception to expect.
    const char *exception;
    /// The expression to evaluate for an expression.
    std::function<void()> expression;
    /// Whether or not the wrong exception was triggered.
    bool wrongTriggeredException = false;
    
    /// Create a new exception value.
    /// \param[in] exception
    ///   The name of the exception to expect.
    /// \param[in] expression
    ///   The expression from which to expect an exception.
    Value(
      const char           *exception ,
      std::function<void()> expression
    ) : exception(exception), expression(expression) { }
  };
  
  /// The exception's stored value.
  Value *value;
  
  /// Create a new exception expression.
  ExceptionValue(const char *exception, std::function<void()> expression) :
    value(new Value(exception, expression)) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    if (value->wrongTriggeredException)
      return std::string(
        "The expression produced an exception that was not a(n) "
      ).append(value->exception).append(" exception.");
    else
      return std::string("The expression did not produce any exception.");
  }
  
  /// Any cleanup that needs to be performed for the expression.
  void cleanup() {
    delete value;
  }
  
  /// Load a message into the expression.
  ExceptionValue<T> operator | (const char *message) {
    this->message = message;
    return *this;
  };
};



// Implement all of the default comparisons
template<typename T>
bool Value<T>::evaluate() {
  return value;
}

template<typename T>
bool Equal<T>::evaluate() {
  return lhs == rhs;
}

template<typename T>
bool NotEqual<T>::evaluate() {
  return lhs != rhs;
}

template<typename T>
bool Less<T>::evaluate() {
  return lhs < rhs;
}

template<typename T>
bool LessEqual<T>::evaluate() {
  return lhs <= rhs;
}

template<typename T>
bool Greater<T>::evaluate() {
  return lhs > rhs;
}

template<typename T>
bool GreaterEqual<T>::evaluate() {
  return lhs >= rhs;
}

template<typename T>
bool InclusiveRange<T>::evaluate() {
  return LessEqual<T>(lhs, value).evaluate() &&
         LessEqual<T>(value, rhs).evaluate() ;
}

template<typename T>
bool Range<T>::evaluate() {
  if (lhsIncluded && rhsIncluded)
    return LessEqual<T>(lhs, value).evaluate() &&
           LessEqual<T>(value, rhs).evaluate() ;
  else if (lhsIncluded)
    return LessEqual<T>(lhs, value).evaluate() &&
           Less     <T>(value, rhs).evaluate() ;
  else if (rhsIncluded)
    return Less     <T>(lhs, value).evaluate() &&
           LessEqual<T>(value, rhs).evaluate() ;
  else
    return Less<T>(lhs, value).evaluate() &&
           Less<T>(value, rhs).evaluate() ;
}

template<typename T>
bool ExclusiveRange<T>::evaluate() {
  return Less<T>(lhs, value).evaluate() &&
         Less<T>(value, rhs).evaluate() ;
}

template<typename T>
bool ExceptionValue<T>::evaluate() {
  try {
    value->expression();
  } catch (T) {
    return true;
  } catch (...) {
    // Note that the wrong exception was triggered
    value->wrongTriggeredException = true;
    return false;
  }
  return false;
}



} // namespace Expressions
END_NAMESPACE_EXPECT



/// Define a custom comparison used in testing.
/// \param type
///   The type for which to define a custom comparison.
/// \param comparison
///   The comparison type to define.
///   Should be one of the following options:
///   `Value`, `Equal`, `NotEqual`, `Less`, `LessEqual`, `Greater`,
///    `GreaterEqual`, `Range`, `InclusiveRange`, `ExclusiveRange`.
/// \remarks
///   Example usage:
///   ```
///   TEST_CUSTOM_COMPARE(int, Value) {
///     return value != 0;
///   }
///   
///   TEST_CUSTOM_COMPARE(int, Equal) {
///     return lhs == rhs;
///   }
///   
///   TEST_CUSTOM_COMPARE(int, InclusiveRange) {
///     return lhs <= value && value <= rhs;
///   }
///   
///   TEST_CUSTOM_COMPARE(int, Range) {
///     if (lhsIncluded && rhsIncluded)
///       return lhs <= value && value <= rhs;
///     else if (lhsIncluded)
///       return lhs <= value && value < rhs;
///     else if (rhsIncluded)
///       return lhs < value && value <= rhs;
///     else
///       return lhs < value && value < rhs;
///   }
///   ```
///   
///   For the `Value` comparison, there is one member to compare, `value`.
///   For the `Equal`, `NotEqual`, `Less`, `LessEqual`, `Greater`, and
///   `GreaterEqual` comparisons, there are two members to compare, `lhs` and
///   `rhs`.
///   For the `InclusiveRange` and `ExclusiveRange` comparisons, there are three
///   members to compare, `lhs`, `value`, and `rhs`, where `lhs` and `rhs` are
///   the left and right bounds of the range, respectively, and `value` is the
///   value being tested for being within the range.
///   The `Range` comparison has five members to compare, the three mentioned
///   for the range comparisons above in addition to `lhsIncluded` and
///   `rhsIncluded` which are booleans that indicate whether or not the left
///   and right ends of the range are included in the comparison.
///   Note that all three of the range specializations automatically adapt to
///   comparison specializations made in `Less`, `LessEqual`, `Greater`, and
///   `GreaterEqual`, therefore making a custom range comparison specialization
///   shouldn't be necessary oftentimes.
///   
///   If you are using a custom comparison of a type in more than one file, make
///   sure to define the specialization in a shared header, for example,
///   `TEST_CUSTOM_COMPARE(int, Value);` for the first specialization in the
///   above example, to avoid duplicate code errors when compiling.
#define TEST_CUSTOM_COMPARE(type, comparison) \
  template<> \
  bool NAMESPACE_EXPECT Expressions::comparison<type>::evaluate()



// Implement custom comparison of C strings
TEST_CUSTOM_COMPARE(char *, Equal);
TEST_CUSTOM_COMPARE(char *, NotEqual);
TEST_CUSTOM_COMPARE(char *, Less);
TEST_CUSTOM_COMPARE(char *, LessEqual);
TEST_CUSTOM_COMPARE(char *, Greater);
TEST_CUSTOM_COMPARE(char *, GreaterEqual);

TEST_CUSTOM_COMPARE(const char *, Equal);
TEST_CUSTOM_COMPARE(const char *, NotEqual);
TEST_CUSTOM_COMPARE(const char *, Less);
TEST_CUSTOM_COMPARE(const char *, LessEqual);
TEST_CUSTOM_COMPARE(const char *, Greater);
TEST_CUSTOM_COMPARE(const char *, GreaterEqual);
