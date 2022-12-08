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



/// A failed assertion exception.
struct TestFailedException {
  
};

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
    if (!expression.evaluate()) {
      // Failure
      environment.failures.push_back(Failure {
        messagePrefix().append(expression.failMessage())
      });
      environment.success = false;
      if (stopOnFailure || environment.stopOnFailure)
        throw TestFailedException();
    }
  }
};



END_NAMESPACE_EXPECT
