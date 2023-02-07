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

NAMESPACE_EXPECT Benchmark::Benchmark(
  Environment &environment,
  const int    line
) : environment(environment), line(line) { }

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
    
    // Record how long each iteration took
    std::vector<long long> iterationTimes = times;
    
    // Sort times for computation
    std::sort(times.begin(), times.end());
    
    // Compute results
    size_t half = times.size() / 2;
    size_t quarter = times.size() / 4;
    BenchmarkResult result {
      line,
      iterations,
      totalTime,
      totalTime / (long long)iterations, // meanTime
      times[half], // medianTime
      times[0], // minTime
      times[times.size() - 1], // maxTime
      times[quarter], // q1Time
      times[times.size() - 1 - quarter], // q3Time
      iterationTimes
    };
    
    // Record results
    environment.benchmarks.push_back(result);
    
    // No need to continue iterating, the benchmarking is done
    return false;
  }
}

void NAMESPACE_EXPECT Benchmark::operator++(int) {
  // Record the time that the iteration took
  auto end = std::chrono::steady_clock::now();
  auto elapsed =
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  long long time = elapsed.count();
  times.push_back(time);
  totalTime += time;
  iterations++;
}
