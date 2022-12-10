// ===--- MiscExpression.h --------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for miscellaneous assertion expressions.                     //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include "Expression.h"

START_NAMESPACE_EXPECT
namespace MiscExpressions {



/// Expect that a an expression produces an exception.
template<typename T>
struct ExceptionValue : Expressions::Expression {
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



// Implement the default exception handler
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
