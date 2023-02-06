// ===--- Environment.h ------------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for the global test environment.                             //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <vector>
#include <string>

START_NAMESPACE_EXPECT



/// A failed assertion exception.
struct TestFailedException {
  
};

/// An assertion failure.
struct Failure {
  /// The assertion failure message.
  std::string message;
};

/// The result of a benchmarking run.
struct BenchmarkResult {
  /// The line number of the benchmark that was run.
  int line;
  /// The total number of iterations that occurred.
  size_t iterations;
  /// The total elapsed time of the benchmark.
  long long totalTime;
  /// The mean time that a benchmark cycle took, in nanoseconds.
  long long meanTime;
  /// The median time that a benchmark cycle took, in nanoseconds.
  long long medianTime;
  /// The minimum time that a benchmark cycle took, in nanoseconds.
  long long minTime;
  /// The maximum time that a benchmark cycle took, in nanoseconds.
  long long maxTime;
  /// The first quartile of the time that a benchmark cycle took,
  /// in nanoseconds.
  long long q1Time;
  /// The third quartile of the time that a benchmark cycle took,
  /// in nanoseconds.
  long long q3Time;
  /// The execution times of each iteration, in nanoseconds.
  std::vector<long long> times;
};

/// A complete testing environment.
struct Environment {
  /// Whether or not unit test cases should stop after any failed assertion.
  bool stopOnFailure = false;
  
  /// Whether or not the ran unit test was successful.
  bool success = true;
  
  /// A list of all failures encountered during a unit test run.
  std::vector<Failure> failures { };
  
  /// A list of all benchmark results for a unit test run.
  std::vector<BenchmarkResult> benchmarks { };
};



END_NAMESPACE_EXPECT
