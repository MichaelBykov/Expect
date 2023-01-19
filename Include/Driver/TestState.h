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



struct RunState {
  enum class State {
    RunningSuite ,
    FinishedSuite,
    RunningTest  ,
    TestSuccess  ,
    TestFailed   ,
  };
  
  State state;
};

struct RunningSuite : RunState {
  Suite &suite;
  
  RunningSuite(Suite &suite);
};

struct FinishedSuite : RunState {
  Suite &suite;
  size_t successful;
  size_t count;
  
  FinishedSuite(Suite &suite, size_t successful, size_t count);
};

struct RunningTest : RunState {
  Suite &suite;
  Test &test;
  size_t index;
  size_t count;
  
  RunningTest(Suite &suite, Test &test, size_t index, size_t count);
};

struct TestSuccess : RunState {
  Test &test;
  
  std::vector<BenchmarkResult> &benchmarks;
  
  TestSuccess(Test &test, std::vector<BenchmarkResult> &benchmarks);
};

struct TestFailed : RunState {
  Test &test;
  
  std::vector<Failure> &failures;
  
  TestFailed(Test &test, std::vector<Failure> &failures);
};



END_NAMESPACE_EXPECT
