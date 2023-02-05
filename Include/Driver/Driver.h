// ===--- Driver.h ----------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The test driver used when launching tests from code.                       //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include "TestState.h"
#include <Global/Environment.h>
#include <Suite/Suite.h>
#include <functional>

START_NAMESPACE_EXPECT



/// The result of a test run.
struct Report {
  /// Whether or not the test run was successful.
  bool isSuccessful;
  
  /// Create a report from the number of successful tests out of total tests.
  /// \param[in] successful
  ///   The number of successful test cases in the test run.
  /// \param[in] total
  ///   The number of total test cases in the test run.
  Report(size_t successful, size_t total);
  
  /// The total number of test cases in the test run.
  size_t total;
  /// The number of test cases in the test run that passed all assertion checks.
  size_t totalSuccessful;
  /// The number of test cases in the test run that failed at least one
  /// assertion check.
  size_t totalFailed;
};

Report runTests(
  Environment                    &environment,
  std::function<void(RunState &)> state
);

struct RunTests {
  Environment &environment;
  
  RunTests(Environment &environment);
  
  Report operator << (std::function<void(RunState &)> state);
};



END_NAMESPACE_EXPECT



/// Run all enabled test cases.
/// \param report
///   The name of the generated report variable.
/// \sa Expect::Report
#define RUN_ENABLED_TESTS(environment, state) \
  ::NAMESPACE_EXPECT RunTests(environment) << \
    [&](::NAMESPACE_EXPECT RunState &state) -> void
