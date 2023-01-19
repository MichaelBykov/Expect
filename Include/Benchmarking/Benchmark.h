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



struct Benchmark {
  Environment &environment;
  std::vector<long long> times { };
  long long totalTime = 0;
  size_t iterations = 0;
  std::chrono::steady_clock::time_point start;
  int line;
  
  Benchmark(Environment &environment, int line);
  
  bool operator()();
  
  void operator++(int);
};



END_NAMESPACE_EXPECT



#define BENCHMARK \
  for (NAMESPACE_EXPECT Benchmark __benchmark { __environment, __LINE__ }; __benchmark(); __benchmark++)
