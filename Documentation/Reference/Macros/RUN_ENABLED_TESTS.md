# `RUN_ENABLED_TESTS` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Implementation](#Parameters-and-Implementation)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
RUN_ENABLED_TESTS([environment], [state]) {
  [implementation]
};
```

## Parameters and Implementation
- `[environment]` : The configured test environment.
- `[state]` : A name for the current test state accessed from the
  implementation.
- `[implementation]` : Handle the current test state.

## Usage

Create and invoke a custom test driver for all enabled unit test cases.

The test `state` is a [`RunState`](../Types/RunState.md) object that is passed
to the `implementation` whenever the state of the test run changes.
The following is the order in which a test run executes and the state passed at
each point:
1. `RunningSuite`
    - Called before a test suite begins setup and before running its tests.
      Will only be called if there is at least one enabled test in the test
      suite.
      If no tests are defined for a test suite, it will not be called.
2. `RunningTest`
    - Called before a test case is run.
      Can be followed by either `TestSuccess` (3.) or `TestFailed` (4.)
      depending on the result of the test.
3. `TestSuccess`
    - Called when a test case succeeds.
      Includes information about any benchmarks that were run inside the test
      case.
4. `TestFailed`
    - Called when a test case fails. Includes all the failed assertion in the
      test case.
5. `FinishedSuite`
    - Called after a test suite finishes running all of its enabled tests and
      after it is torn down.
      Includes information about the number of ran and successful tests in the
      test suite.
6. Step 1. is repeated until all test suites with enabled tests have been run.
7. A [`Report`](../Types/Report.h) is returned about the overall success/failure
  of the test run.
  This is not passed to the implementation function, but returned from the
  `RUN_ENABLED_TESTS` run.

If your test cases are linked to the [AutoExpect](../../Tutorials/Building.md)
library, the default command-line driver will be automatically invoked.
Therefore, in order to use a custom test driver, only link to the standard
Expect library and include a `main` function with your test cases that calls
your custom driver.

## Examples

The below example demonstrates creating a custom command-line test driver.
``` C++
using namespace Expect;

Environment environment { };

// ... set up the environment as appropriate

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
    printf("  Running test %s (%zu/%zu) ... ",
      test.test.name, test.index, test.count);
    fflush(stdout);
  } break;
  
  case RunState::State::TestSuccess: {
    TestSuccess &success = (TestSuccess &)state;
    printf("success.\n");
    for (BenchmarkResult &benchmark : success.benchmarks) {
      printf(
        "    Benchmark results on line %d:\n"
        "        Iterations: %zu\n"
        "        Total time: %lld (ns)\n"
        "         Mean time: %lld (ns)\n"
        "      Distribution: min -[Q1 - median - Q3]- max\n"
        "        %lld -[%lld - %lld - %lld]- %lld (ns)\n"
      ,
        benchmark.line,
        benchmark.iterations,
        benchmark.totalTime,
        benchmark.meanTime,
        benchmark.minTime, benchmark.q1Time, benchmark.medianTime,
          benchmark.q3Time, benchmark.maxTime
      );
    }
  } break;
  
  case RunState::State::TestFailed: {
    TestFailed &failed = (TestFailed &)state;
    printf("failure.\n");
    for (Failure &fail : failed.failures)
      printf("    %s\n", fail.message.c_str());
  } break;
};
```

## See Also

- [`RunState` class](../Types/RunState.md)
  - The state of an in-progress test run.
- [`Report` class](../Types/Report.md)
  - A report of all of the evaluated test cases.
- [`Suite` class](../Types/Suite.md)
  - Configure and manage a test suite instance, including accessing all of its
    test cases.
- [`suites` global variable](../Variables/suites.md)
  - Manage all instances instances of test suites in the program.
- [`Test` class](../Types/Test.md)
  - Configure and manage a test case instance, including enabling it to be
    run with a custom test driver.
- [Building Expect Tutorial](../../Tutorials/Building.md)
  - A guide to the various ways of building Expect.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walthrough of creating a custom test driver.
