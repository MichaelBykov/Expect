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



struct Report {
  bool isSuccessful;
  
  Report(size_t successful, size_t total);
  
  size_t total;
  size_t totalSuccessful;
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
