// ===--- Evaluate.h --------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for assertion expression evaluation.                         //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Global/Environment.h>
#include <Global/toString.h>
#include "Expect.h"

START_NAMESPACE_EXPECT



/// An assertion evaluator.
struct Evaluate {
  /// The test environment.
  Environment &environment;
  
  /// The file in which the assertion exists.
  const char *file;
  
  /// The line in the file on which the assertion exists.
  int line;
  
  /// Whether or not to abort upon assertion failure.
  bool stopOnFailure;
  
  /// Create an assertion evaluator.
  /// \param[inout] environment
  ///   The test environment.
  /// \param[in] file
  ///   The file in which the assertion exists.
  /// \param[in] line
  ///   The line in the file on which the assertion begins.
  /// \param[in] stop
  ///   Whether or not to abort upon assertion failure.
  Evaluate(
    Environment &environment,
    const char  *file       ,
    const int    line       ,
    const bool   stop
  ) : environment(environment), file(file), line(line), stopOnFailure(stop) { }
  
  
  
  /// Generate an error message prefix applicable to the assertion.
  std::string messagePrefix();
  
  
  
  /// Load an expression into the assertion evaluator.
  /// \param[in] expression
  ///   The expression to evaluate.
  template<typename Expression>
  void operator, (Expression expression) {
    bool lastSuccess = environment.success;
    size_t lastErrorCount = environment.failures.size();
    if (!expression.evaluate()) {
      // Failure
      std::string message = messagePrefix().append(expression.failMessage());
      if (expression.message != nullptr)
        message = message.append(" ").append(expression.message);
      environment.failures.push_back(Failure { message });
      expression.cleanup();
      environment.success = false;
      if (stopOnFailure || environment.stopOnFailure)
        throw TestFailedException();
    } else {
      // Reset the state in case it was messed up
      environment.success = lastSuccess;
      while (environment.failures.size() > lastErrorCount)
        environment.failures.pop_back();
      expression.cleanup();
    }
  }
};



END_NAMESPACE_EXPECT
