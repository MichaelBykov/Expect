// ===--- WithinExpression.h ------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for within assertion expressions.                            //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include "Expression.h"

START_NAMESPACE_EXPECT
namespace WithinExpressions {



/// Expect that two values are within-approximately equal.
template<typename T>
struct Equal : Expressions::Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new equal expression.
  Equal(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not equal to ")
      .append(toString(rhs))
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  Equal<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  Equal<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
};

/// Expect that two values are within-approximately not equal.
template<typename T>
struct NotEqual : Expressions::Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new not-equal expression.
  NotEqual(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is equal to ")
      .append(toString(rhs))
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  NotEqual<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  NotEqual<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
};

/// Expect that a value is in an inclusive range.
template<typename T>
struct InclusiveRange : Expressions::Expression {
  /// The lower-bound of the range.
  T lhs;
  /// The value to check for being within the range.
  T value;
  /// The upper-bound of the range.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new range expression.
  InclusiveRange(T lhs, T value, T rhs) : lhs(lhs), value(value), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(value).append(" is not within the range of ")
      .append(toString(lhs)).append(", ")
      .append(toString(rhs)).append(" (inclusive)")
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  InclusiveRange<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  InclusiveRange<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
};

/// Expect that a value is in a range.
template<typename T>
struct Range : Expressions::Expression {
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
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
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
      .append(")")
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  Range<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  Range<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
};

/// Expect that a value is in an exclusive range.
template<typename T>
struct ExclusiveRange : Expressions::Expression {
  /// The lower-bound of the range.
  T lhs;
  /// The value to check for being within the range.
  T value;
  /// The upper-bound of the range.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new range expression.
  ExclusiveRange(T lhs, T value, T rhs) : lhs(lhs), value(value), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(value).append(" is not within the range of ")
      .append(toString(lhs)).append(", ")
      .append(toString(rhs)).append(" (exclusive)")
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  ExclusiveRange<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  ExclusiveRange<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
};

/// Expect that one value is within-approximately less than another value.
template<typename T>
struct Less : Expressions::Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new less-than expression.
  Less(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not less than ")
      .append(toString(rhs))
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  Less<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  Less<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
  
  
  
  /// Expect that the loaded value is within-approximately within an exclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  ExclusiveRange<T> operator <(T other) {
    return { lhs, rhs, other };
  }
  
  /// Expect that the loaded value is within-approximately within an exclusive,
  /// inclusive range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator <=(T other) {
    return { lhs, false, rhs, other, true };
  }
};

/// Expect that one value is within-approximately less than or equal to another
/// value.
template<typename T>
struct LessEqual : Expressions::Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new less-than-or-equal-to expression.
  LessEqual(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not less than or equal to ")
      .append(toString(rhs))
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  LessEqual<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  LessEqual<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
  
  
  
  /// Expect that the loaded value is within-approximately within an inclusive,
  /// exclusive range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator <(T other) {
    return { lhs, true, rhs, other, false };
  }
  
  /// Expect that the loaded value is within-approximately within an inclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  InclusiveRange<T> operator <=(T other) {
    return { lhs, rhs, other };
  }
};

/// Expect that one value is within-approximately greater than another value.
template<typename T>
struct Greater : Expressions::Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new greater-than expression.
  Greater(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not greater than ")
      .append(toString(rhs))
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  Greater<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  Greater<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
  
  
  
  /// Expect that the loaded value is within-approximately within an exclusive
  /// range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  ExclusiveRange<T> operator >(T other) {
    return { other, rhs, lhs };
  }
  
  /// Expect that the loaded value is within-approximately within an exclusive,
  /// inclusive range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator >=(T other) {
    return { other, true, rhs, lhs, false };
  }
};

/// Expect that one value is within-approximately greater than or equal to
/// another value.
template<typename T>
struct GreaterEqual : Expressions::Expression {
  /// The value of the left-hand-side of the comparison.
  T lhs;
  /// The value of the right-hand-side of the comparison.
  T rhs;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new greater-than-or-equal-to expression.
  GreaterEqual(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(lhs).append(" is not greater than or equal to ")
      .append(toString(rhs))
      .append(" within ").append(toString(tolerance)).append(".");
  }
  
  /// Load a tolerance into the expression.
  GreaterEqual<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  GreaterEqual<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
  
  
  
  /// Expect that the loaded value is within-approximately within an inclusive,
  /// exclusive range of values.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A range expectation.
  Range<T> operator >(T other) {
    return { other, false, rhs, lhs, true };
  }
  
  /// Expect that the loaded value is within-approximately within an inclusive
  /// range of values.
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
struct Value : Expressions::Expression {
  /// The value to test for truthiness.
  T value;
  
  /// The tolerance of the expression.
  Expressions::Tolerance tolerance = EXPECT_TOLERANCE;
  
  /// Create a new value expression.
  Value(T value) : value(value) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate();
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return std::string("Result is within ")
      .append(toString(tolerance)).append(" of zero.");
  }
  
  /// Load a tolerance into the expression.
  Value<T> operator | (Expressions::Tolerance tolerance) {
    this->tolerance = tolerance;
    return *this;
  };
  
  /// Load a message into the expression.
  Value<T> operator | (const char *message) {
    this->message = this->message.append(message);
    return *this;
  };
  
  
  
  /// Expect that the loaded value is within-approximately equal to another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   An equality expectation.
  Equal<T> operator ==(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is within-approximately not equal to another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A non-equality expectation.
  NotEqual<T> operator !=(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is within-approximately less than another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Less<T> operator <(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is within-approximately less than or equal to
  /// another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  LessEqual<T> operator <=(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is within-approximately greater than another
  /// value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  Greater<T> operator >(T other) {
    return { value, other };
  }
  
  /// Expect that the loaded value is within-approximately greater than or equal
  /// to another value.
  /// \param[in] other
  ///   The value to compare the loaded value to.
  /// \returns
  ///   A comparison expectation.
  GreaterEqual<T> operator >=(T other) {
    return { value, other };
  }
};



// Implement all of the default comparisons
template<typename T>
bool Value<T>::evaluate() {
  return NotEqual<T>(value, T(0.0)).evaluate();
}

template<typename T>
bool Equal<T>::evaluate() {
  T x = lhs - rhs; if (x < 0) x = -x;
  return x <= tolerance;
}

template<typename T>
bool NotEqual<T>::evaluate() {
  T x = lhs - rhs; if (x < 0) x = -x;
  return x > tolerance;
}

template<typename T>
bool Less<T>::evaluate() {
  return lhs - rhs < -tolerance;
}

template<typename T>
bool LessEqual<T>::evaluate() {
  return lhs - rhs <= tolerance;
}

template<typename T>
bool Greater<T>::evaluate() {
  return lhs - rhs > tolerance;
}

template<typename T>
bool GreaterEqual<T>::evaluate() {
  return lhs - rhs >= -tolerance;
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



} // namespace Expressions
END_NAMESPACE_EXPECT
