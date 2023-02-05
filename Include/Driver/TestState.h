// ===--- TestState.h -------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// A set of reportable test running states.                                   //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Suite/Suite.h>

START_NAMESPACE_EXPECT



/// The state of an in-progress test run.
struct RunState {
  /// The state tag.
  enum class State {
    RunningSuite , //< A test suite is beginning to be run.
    FinishedSuite, //< A test suite has finished running.
    RunningTest  , //< A test case is about to be ran.
    TestSuccess  , //< A test case succeeded.
    TestFailed   , //< A test case failed.
  };
  
  /// The state tag.
  State state;
};

/// A test suite is beginning to be run.
struct RunningSuite : RunState {
  /// The test suite that is being run.
  Suite &suite;
  
  RunningSuite(Suite &suite);
};

/// A test suite has finished running.
struct FinishedSuite : RunState {
  /// The test suite that finished running.
  Suite &suite;
  /// The number of test cases that passed all assertion in the test suite.
  size_t successful;
  /// The total number of test cases that were run in the test suite.
  size_t count;
  
  FinishedSuite(Suite &suite, size_t successful, size_t count);
};

/// A test case is preparing to be run.
struct RunningTest : RunState {
  /// The test suite that the test case is in.
  Suite &suite;
  /// The test case that is going to be run.
  Test &test;
  /// The index of the test within the test suite.
  size_t index;
  /// The total number of test cases that will be run in the test suite.
  size_t count;
  
  RunningTest(Suite &suite, Test &test, size_t index, size_t count);
};

/// A test case succeeded in running.
struct TestSuccess : RunState {
  /// The test case that succeeded in running.
  Test &test;
  
  /// A list of all micro benchmark results that were run in the test case.
  std::vector<BenchmarkResult> &benchmarks;
  
  TestSuccess(Test &test, std::vector<BenchmarkResult> &benchmarks);
};

/// A test case failed in running.
struct TestFailed : RunState {
  /// The test case that failed.
  Test &test;
  
  /// A list of all the assertion failures in the test case.
  std::vector<Failure> &failures;
  
  TestFailed(Test &test, std::vector<Failure> &failures);
};



END_NAMESPACE_EXPECT
