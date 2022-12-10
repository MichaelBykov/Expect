// ===--- Environment.h ------------------------------------------ C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for the global test environment.                             //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <vector>
#include <string>

START_NAMESPACE_EXPECT



/// A failed assertion exception.
struct TestFailedException {
  
};

/// A test failure.
struct Failure {
  /// The test failure message.
  std::string message;
};

/// A complete testing environment.
struct Environment {
  /// Whether or not unit test cases should stop after a failed assertion.
  bool stopOnFailure = true;
  
  /// Whether or not the ran unit test was successful.
  bool success = true;
  
  /// A list of all failures encountered during a unit test run.
  std::vector<Failure> failures { };
};



END_NAMESPACE_EXPECT
