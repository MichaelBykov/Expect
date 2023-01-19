// ===--- Benchmark.cpp ------------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The implementation for benchmarking snippets of code.                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Benchmarking/Benchmark.h>

NAMESPACE_EXPECT Benchmark::Benchmark(Environment &environment, int line)
    : environment(environment), line(line) { }

bool NAMESPACE_EXPECT Benchmark::operator()() {
  if (iterations == 0 && !environment.success)
    // Preconditions failed: do not benchmark
    return false;
  
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

void NAMESPACE_EXPECT Benchmark::operator++(int) {
  auto end = std::chrono::steady_clock::now();
  auto elapsed =
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  long long time = elapsed.count();
  times.push_back(time);
  totalTime += time;
  iterations++;
}
