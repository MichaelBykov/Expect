// ===--- TestState.h -------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
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
  
  virtual std::string message() = 0;
};

struct RunningSuite : RunState {
  Suite &suite;
  
  RunningSuite(Suite &suite);
  
  std::string message();
};

struct FinishedSuite : RunState {
  Suite &suite;
  size_t successful;
  size_t count;
  
  FinishedSuite(Suite &suite, size_t successful, size_t count);
  
  std::string message();
};

struct RunningTest : RunState {
  Suite &suite;
  Test &test;
  size_t index;
  size_t count;
  
  RunningTest(Suite &suite, Test &test, size_t index, size_t count);
  
  std::string message();
};

struct TestSuccess : RunState {
  Test &test;
  
  TestSuccess(Test &test);
  
  std::string message();
};

struct TestFailed : RunState {
  Test &test;
  
  std::vector<Failure> &failures;
  
  TestFailed(Test &test, std::vector<Failure> &failures);
  
  std::string message();
};



END_NAMESPACE_EXPECT
