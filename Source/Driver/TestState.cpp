// ===--- TestState.cpp ------------------------------------------ C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// A set of reportable test running states.                                   //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Driver/TestState.h>



NAMESPACE_EXPECT RunningSuite::RunningSuite(
  Suite &suite
) : suite(suite) {
  state = State::RunningSuite;
}

std::string NAMESPACE_EXPECT RunningSuite::message() {
  // TODO: Finish
  return "";
}



NAMESPACE_EXPECT FinishedSuite::FinishedSuite(
  Suite &suite     ,
  size_t successful,
  size_t count
) : suite(suite), successful(successful), count(count) {
  state = State::FinishedSuite;
}

std::string NAMESPACE_EXPECT FinishedSuite::message() {
  // TODO: Finish
  return "";
}



NAMESPACE_EXPECT RunningTest::RunningTest(
  Suite &suite,
  Test  &test ,
  size_t index,
  size_t count
) : suite(suite), test(test), index(index), count(count) {
  state = State::RunningTest;
}

std::string NAMESPACE_EXPECT RunningTest::message() {
  // TODO: Finish
  return "";
}



NAMESPACE_EXPECT TestSuccess::TestSuccess(
  Test &test
) : test(test) {
  state = State::TestSuccess;
}

std::string NAMESPACE_EXPECT TestSuccess::message() {
  // TODO: Finish
  return "";
}



NAMESPACE_EXPECT TestFailed::TestFailed(
  Test                 &test    ,
  std::vector<Failure> &failures
) : test(test), failures(failures) {
  state = State::TestFailed;
}

std::string NAMESPACE_EXPECT TestFailed::message() {
  // TODO: Finish
  return "";
}
