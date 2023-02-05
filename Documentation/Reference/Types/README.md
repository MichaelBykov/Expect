# Types - Reference

## Jump to...
- [Suites and Setup](#Suites-and-Setup)
- [Test Cases](#Test-Cases)
- [Drivers](#Drivers)

## Suites and Setup
- [`Suite` class](Suite.md)
  - Configure and manage a test suite instance.

## Test Cases
- [`Test` class](Test.md)
  - Configure and manage a test case instance.
- [`BenchmarkResult` class](BenchmarkResult.md)
  - The result of a micro benchmark run.

## Drivers
- [`Environment` class](Environment.md)
  - The test environment in which test runs are performed.
- [`Report` class](Report.md)
  - A report of all of the evaluated test cases.
- [`RunState` class](RunState.md)
  - The state of an in-progress test run.
- [`RunState::State` enum](RunState.State.md)
  - The state tag of an in-progress test run.
- [`RunningSuite` class](RunningSuite.md)
  - A test suite is beginning to be run.
- [`FinishedSuite` class](FinishedSuite.md)
  - A test suite has finished being run.
- [`RunningTest` class](RunningTest.md)
  - A test case is beginning to be run.
- [`TestSuccess` class](TestSuccess.md)
  - A test case was successfully ran.
- [`TestFailed` class](TestFailed.md)
  - A test case was unsuccessfully ran.
