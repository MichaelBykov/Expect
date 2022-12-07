// ===--- CommandLineDriver.h ------------------------------------ C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The test driver used when launching tests form the command line.           //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Driver/CommandLineDriver.h>
#include <Driver/Driver.h>
#include <Suite/Suite.h>
#include <stdio.h>

void displayHelp(const char *executable) {
  printf(
    "Usage: %s [flags...] [test-names-or-suites...]\n"
    "\n"
    "Flags:\n"
    "  -h, --help        Display help.\n"
    "  -c, --continue    Continue after failed assertions.\n"
    "  --stop            Stop after failed assertions.\n"
    "\n"
    "Test Suites:\n"
  , executable);
  for (NAMESPACE_EXPECT Suite *suite : NAMESPACE_EXPECT suites()) {
    printf("  %s    Enable all tests in the suite.\n", suite->name);
    for (NAMESPACE_EXPECT Test &test : suite->tests)
      printf("  %s    %s\n", test.name, test.description);
  }
}


int NAMESPACE_EXPECT runCommandLineTests(
  int   argc  ,
  char *argv[]
) {
  Environment environment { };
  
  // Parse the command line arguments
  if (argc == 1) {
    // No arguments provided: display help
    displayHelp(argv[0]);
    return 0;
  }
  for (int i = 1; i < argc; i++)
    // Flags
    if (
      strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0
    ) {
      // Display help
      displayHelp(argv[0]);
      return 0;
    } else if (
      strcmp(argv[i], "--continue") == 0 || strcmp(argv[i], "-c") == 0
    ) {
      environment.stopOnFailure = false;
    } else if (
      strcmp(argv[i], "--stop") == 0
    ) {
      environment.stopOnFailure = true;
    } else {
      // Test suites
      bool found = false;
      for (Suite *suite : suites())
        if (strcmp(argv[i], suite->name) == 0) {
          // Enable all tests in the suite
          for (Test &test : suite->tests)
            test.enabled = true;
          found = true;
          break;
        } else {
          for (Test &test : suite->tests)
            if (strcmp(argv[i], test.name) == 0) {
              // Enable the individual test
              test.enabled = true;
              found = true;
              break;
            }
          if (found)
            break;
        }
      if (!found) {
        printf("Unknown flag or test name '%s'.\nUse '--help' for help.\n", argv[i]);
        return 1;
      }
    }
  
  // Run all tests
  Report report = RUN_ENABLED_TESTS(environment, state) {
    switch (state.state) {
    case RunState::State::RunningSuite: {
      RunningSuite &suite = (RunningSuite &)state;
      printf("\nRunning test suite %s.\n", suite.suite.name);
    } break;
    
    case RunState::State::FinishedSuite: {
      FinishedSuite &suite = (FinishedSuite &)state;
      printf("Successful: %zu/%zu\n", suite.successful, suite.count);
    } break;
    
    case RunState::State::RunningTest: {
      RunningTest &test = (RunningTest &)state;
      printf("  Running test %s (%zu/%zu) ... ", test.test.name, test.index, test.count);
    } break;
    
    case RunState::State::TestSuccess: {
      printf("success.\n");
    } break;
    
    case RunState::State::TestFailed: {
      TestFailed &failed = (TestFailed &)state;
      printf("failure.\n");
      for (Failure &fail : failed.failures)
        printf("    %s\n", fail.message.c_str());
    } break;
    }
  };
  
  // Finish
  if (report.isSuccessful)
    printf("\nAll tests passed.\n");
  else
    printf("\n%zu tests failed.\n", report.totalFailed);
  return 0;
}
