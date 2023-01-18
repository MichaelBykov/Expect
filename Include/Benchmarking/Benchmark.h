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
  
  Benchmark(Environment &environment, int line)
    : environment(environment), line(line) { }
  
  bool operator()() {
    if (iterations < 16 || totalTime <= 1000000000 && iterations < 1024) {
      // Continue iterating
      start = std::chrono::steady_clock::now();
      return true;
    } else {
      // Sufficient iterations reached
      std::sort(times.begin(), times.end());
      size_t half = times.size() / 2;
      size_t quarter = times.size() / 4;
      BenchmarkResult result {
        line,
        iterations,
        totalTime,
          .meanTime = totalTime / (long long)iterations,
        .medianTime = times[half],
           .minTime = times[0],
           .maxTime = times[times.size() - 1],
            .q1Time = times[quarter],
            .q3Time = times[times.size() - 1 - quarter],
      };
      environment.benchmarks.push_back(result);
      return false;
    }
  }
  
  void operator++(int) {
    auto end = std::chrono::steady_clock::now();
    auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    long long time = elapsed.count();
    times.push_back(time);
    totalTime += time;
    iterations++;
  }
};



END_NAMESPACE_EXPECT



#define BENCHMARK \
  for (NAMESPACE_EXPECT Benchmark __benchmark { __environment, __LINE__ }; __benchmark(); __benchmark++)
