// ===--- Benchmark.h -------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for benchmarking snippets of code.                           //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Global/Environment.h>
#include <vector>
#include <chrono>
#include <algorithm>

START_NAMESPACE_EXPECT



/// A micro benchmark handler.
struct Benchmark {
  /// The test environment that the benchmark operates in.
  Environment &environment;
  /// The times (in nanoseconds) of each iteration.
  std::vector<long long> times { };
  /// The total time (in nanoseconds) that the benchmark has run.
  long long totalTime = 0;
  /// The number of iterations that the benchmark has run.
  size_t iterations = 0;
  /// The start time of the current iteration.
  std::chrono::steady_clock::time_point start;
  /// The line number on which the benchmark occurs.
  int line;
  
  /// Create a new benchmark handler.
  /// \param[inout] environment
  ///   The benchmark's test environemnt.
  /// \param[in] line
  ///   The line number on which the benchmark occurs.
  Benchmark(
    Environment &environment,
    const int    line
  );
  
  /// Check whether to continue running benchmarks, and begin the next benchmark
  /// iteration, if applicable.
  /// \returns
  ///   Whether or not to run another benchmark iteration.
  bool operator()();
  
  /// End a benchmark iteration.
  void operator++(int);
};



END_NAMESPACE_EXPECT



/// Benchmark a snippet of code.
/// \remarks
///   A benchmark should be placed inside of a test case and can execute either
///   a single statement or block of code.
///   If an expectation or assertion in the test case before the benchmark
///   fails, the benchmark and its associated code snippet won't be run.
///   A `benchmark` tag can be added to test cases that employ benchmarks to
///   prevent them from being run in aggregate unit tests, such as when an
///   entire test suite is specified to be tested.
///   Example:
///   ```
///   TEST(my benchmark, "A description.", benchmark) {
///     EXPECT precondition == true;
///     BENCHMARK foo();
///     BENCHMARK {
///       int y = x();
///       int z = fn(y);
///     }
///   };
///   ```
#define BENCHMARK \
  for (NAMESPACE_EXPECT Benchmark __benchmark { __environment, __LINE__ }; \
    __benchmark(); __benchmark++)
