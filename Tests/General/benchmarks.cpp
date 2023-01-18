#include <Expect>
#include <thread>

SUITE(Benchmarks) {
  TEST(test benchmarking, "A description.", benchmark) {
    BENCHMARK std::this_thread::sleep_for(std::chrono::nanoseconds(10000000));
  };
  
  TEST(test benchmarking 2, "A description.", benchmark) {
    int x = 0;
    BENCHMARK x += 3;
  };
}
