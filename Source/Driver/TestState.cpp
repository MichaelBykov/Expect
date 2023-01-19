// ===--- TestState.cpp ------------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
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



NAMESPACE_EXPECT FinishedSuite::FinishedSuite(
  Suite &suite     ,
  size_t successful,
  size_t count
) : suite(suite), successful(successful), count(count) {
  state = State::FinishedSuite;
}



NAMESPACE_EXPECT RunningTest::RunningTest(
  Suite &suite,
  Test  &test ,
  size_t index,
  size_t count
) : suite(suite), test(test), index(index), count(count) {
  state = State::RunningTest;
}



NAMESPACE_EXPECT TestSuccess::TestSuccess(
  Test                         &test      ,
  std::vector<BenchmarkResult> &benchmarks
) : test(test), benchmarks(benchmarks) {
  state = State::TestSuccess;
}



NAMESPACE_EXPECT TestFailed::TestFailed(
  Test                 &test    ,
  std::vector<Failure> &failures
) : test(test), failures(failures) {
  state = State::TestFailed;
}
