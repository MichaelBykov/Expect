# Expect Reference

## Jump to...
- [Categories](#Categories)
- [Suites and Setup](#Suites-and-Setup)
- [Test Cases](#Test-Cases)
- [Assertions](#Assertions)
- [Matchers](#Matchers)
- [Custom Comparison](#Custom-Comparison)
- [Strings and Messages](#Strings-and-Messages)
- [Drivers](#Drivers)

## Categories
- [Macros](Macros)
- [Assertions](Assertions)
- [Matchers](Matchers)
- [Types](Types)
- [Variables](Variables)
- [Functions](Functions)

## Suites and Setup
- [`SUITE` macro](Macros/SUITE.md)
  - Define a test suite.
- [`SHARE` macro](Macros/SHARE.md)
  - Share variables in a test suite.
- [`SHARED` macro](Macros/SHARED.md)
  - Access shared variables.
- [`SETUP` macro](Macros/SETUP.md)
  - Define startup code for a test suite.
- [`TEARDOWN` macro](Macros/TEARDOWN.md)
  - Define teardown code for a test suite.
- [`Suite` class](Types/Suite.md)
  - Configure and manage a test suite instance.
- [`suites` global variable](Variables/suites.md)
  - Manage all instances instances of test suites in the program.

## Test Cases
- [`TEST` macro](Macros/TEST.md)
  - Define a test case.
- [`SECTION` macro](Macros/SECTION.md)
  - Define a subsection of a test case.
- [`BENCHMARK` macro](Macros/BENCHMARK.md)
  - Run a micro benchmark.
- [`Test` class](Types/Test.md)
  - Configure and manage a test case instance.
- [`BenchmarkResult` class](Types/BenchmarkResult.md)
  - The result of a micro benchmark run.

## Assertions
- [`EXPECT` macro](Assertions/EXPECT.md) / [`ASSERT` macro](Assertions/ASSERT.md)
  - Expect a general condition.
- [`EXPECT_APPROX` macro](Assertions/EXPECT_APPROX.md) / [`ASSERT_APPROX` macro](Assertions/ASSERT_APPROX.md)
  - Expect that number(s) are approximately within each epsilon of each other.
- [`EXPECT_NEAR` macro](Assertions/EXPECT_NEAR.md) / [`ASSERT_NEAR` macro](Assertions/ASSERT_NEAR.md)
  - Expect that number(s) are nearly within each epsilon of each other.
- [`EXPECT_WITHIN` macro](Assertions/EXPECT_WITHIN.md) / [`ASSERT_WITHIN` macro](Assertions/ASSERT_WITHIN.md)
  - Expect that number(s) are within each epsilon of each other.
- [`EXPECT_EXCEPTION` macro](Assertions/EXPECT_EXCEPTION.md) / [`ASSERT_EXCEPTION` macro](Assertions/ASSERT_EXCEPTION.md)
  - Expect a specific exception to be thrown.
- [`EXPECT_ANY_EXCEPTION` macro](Assertions/EXPECT_ANY_EXCEPTION.md) / [`ASSERT_ANY_EXCEPTION` macro](Assertions/ASSERT_ANY_EXCEPTION.md)
  - Expect any exception to be thrown.
- [`EXPECT_NO_EXCEPTION` macro](Assertions/EXPECT_NO_EXCEPTION.md) / [`ASSERT_NO_EXCEPTION` macro](Assertions/ASSERT_NO_EXCEPTION.md)
  - Expect that no exception is thrown.

## Matchers
- [`EXPECT_THAT` macro](Matchers/EXPECT_THAT.md) / [`ASSERT_THAT` macro](Matchers/ASSERT_THAT.md)
  - Expect that a value matches a set of matchers.
- [`MATCHER` macro](Matchers/MATCHER.md)
  - Define a custom matcher.
- [`MATCHER_RESULT` macro](Matchers/MATCHER_RESULT.md)
  - Get the result of a custom matcher.
- [`USE_EXPECT_MATCHING` macro](Matchers/USE_EXPECT_MATCHING.md)
  - Use default matchers.
- [`isA` matcher](Matchers/isA.md) / [`isAn` matcher](Matchers/isA.md)
  - The default type-matching matcher.
- [`isNull` matcher](Matchers/isNull.md)
  - The default null matcher.
- [`isSome` matcher](Matchers/isSome.md)
  - The default non-null matcher.
- [`isNaN` matcher](Matchers/isNaN.md)
  - The default not-a-number matcher.
- [`isNonNaN` matcher](Matchers/isNonNaN.md)
  - The default not-not-a-number matcher.
- [`isFinite` matcher](Matchers/isFinite.md)
  - The default finite-number matcher.
- [`isInfinite` matcher](Matchers/isInfinite.md)
  - The default infinite-number matcher.
- [`each` matcher](Matchers/each.md)
  - The default predicate matcher.
- [`has` matcher](Matchers/has.md)
  - The default specific-count predicate matcher.
- [`contains` matcher](Matchers/contains.md)
  - The default any-count predicate matcher.
- [`beginsWith` matcher](Matchers/beginsWith.md)
  - The default string prefix matcher.
- [`endsWith` matcher](Matchers/endsWith.md)
  - The default string suffix matcher.

## Custom Comparison
- [`TEST_CUSTOM_COMPARE` macro](Macros/TEST_CUSTOM_COMPARE.md)
  - Define a custom comparison operation for a type.
- [`EXPECT_TOLERANCE` macro](Macros/EXPECT_TOLERANCE.md)
  - The default floating-point comparison tolerance.

## Strings and Messages
- [`MESSAGE` macro](Macros/MESSAGE.md)
  - Create an output message using a message builder.
- [`TEST_STRINGIFY` macro](Macros/TEST_STRINGIFY.md)
  - Define a custom string conversion for a type.
- [`TEST_STRINGIFY_GENERIC` macro](Macros/TEST_STRINGIFY_GENERIC.md)
  - Define a custom string conversion for a template type.

## Drivers
- [`RUN_COMMAND_LINE_TESTS` macro](Macros/RUN_COMMAND_LINE_TESTS.md)
  - Run the standard command line test driver.
- [`RUN_ENABLED_TESTS` macro](Macros/RUN_ENABLED_TESTS.md)
  - Run all enabled unit test cases.
- [`Environment` class](Types/Environment.md)
  - The test environment in which test runs are performed.
- [`Failure` class](Types/Failure.md)
  - The reported result of an assertion failure.
- [`Report` class](Types/Report.md)
  - A report of all of the evaluated test cases.
- [`RunState` class](Types/RunState.md)
  - The state of an in-progress test run.
- [`RunState::State` enum](Types/RunState.State.md)
  - The state tag of an in-progress test run.
- [`RunningSuite` class](Types/RunningSuite.md)
  - A test suite is beginning to be run.
- [`FinishedSuite` class](Types/FinishedSuite.md)
  - A test suite has finished being run.
- [`RunningTest` class](Types/RunningTest.md)
  - A test case is beginning to be run.
- [`TestSuccess` class](Types/TestSuccess.md)
  - A test case was successfully ran.
- [`TestFailed` class](Types/TestFailed.md)
  - A test case was unsuccessfully ran.
