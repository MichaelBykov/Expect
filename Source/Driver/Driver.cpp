// ===--- Driver.h ----------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The test driver used when launching tests from code.                       //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Driver/Driver.h>
#include <Suite/Suite.h>
#include <Suite/Setup.h>
#include <Evaluate/Evaluate.h>
#include <stddef.h>

NAMESPACE_EXPECT Report::Report(
  size_t successful,
  size_t total
) : isSuccessful(successful == total), total(total),
    totalSuccessful(successful), totalFailed(total - successful) {
  
}



NAMESPACE_EXPECT RunTests::RunTests(
  Environment &environment
) : environment(environment) {
  
}

NAMESPACE_EXPECT Report NAMESPACE_EXPECT RunTests::operator << (
  std::function<void(RunState &)> state
) {
  return runTests(environment, state);
}

NAMESPACE_EXPECT Report NAMESPACE_EXPECT runTests(
  Environment                    &environment,
  std::function<void(RunState &)> state
) {
  // Run all of the tests
  size_t totalCount = 0, totalSuccessful = 0;
  for (Suite *suite : suites()) {
    // Check that at least one test needs to be run
    size_t count = 0;
    for (Test &test : suite->tests)
      if (test.enabled)
        count++;
    
    if (count > 0) {
      // Report
      if (state != nullptr) {
        RunningSuite _state(*suite);
        state(_state);
      }
      
      // Setup the suite
      if (suite->setup != nullptr)
        suite->setup();
      
      size_t successful = 0, index = 0;
      for (Test &test : suite->tests)
        if (test.enabled) {
          index++;
          if (state != nullptr) {
            RunningTest _state(*suite, test, index, count);
            state(_state);
          }
          try {
            test.test(environment);
          } catch (TestFailedException) { }
          if (environment.success) {
            if (state != nullptr) {
              TestSuccess _state(test, environment.benchmarks);
              state(_state);
            }
            successful++;
          } else {
            if (state != nullptr) {
              TestFailed _state(test, environment.failures);
              state(_state);
            }
          }
          environment.success = true;
          environment.failures.clear();
          environment.benchmarks.clear();
        }
      totalCount += count;
      totalSuccessful += successful;
      
      // Teardown the suite
      if (suite->teardown != nullptr) {
        suite->teardown->teardown();
        suite->teardown->cleanup();
      }
      
      // Report
      if (state != nullptr) {
        FinishedSuite _state(*suite, successful, count);
        state(_state);
      }
    }
  }
  
  return Report(totalSuccessful, totalCount);
}
