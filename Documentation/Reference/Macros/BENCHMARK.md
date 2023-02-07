# `BENCHMARK` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Contents](#Parameters-and-Contents)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
BENCHMARK [contents];

BENCHMARK {
  [contents]
}
```

## Parameters and Contents
- `[contents]` : The statement or code to benchmark.

## Usage

Micro benchmark a section of code.

The benchmarked code will be run up between 16 and 1024 times computing the
total run time, average run time, and every quartile of the run times for the
benchmarked code.

If an assertion in the test case failed prior to the benchmark, the benchmark
won't be run.
This can be utilized to set preconditions for a benchmark.

## Examples

The below example demonstrates a simple benchmark.
``` C++
SUITE(Benchmark) {
  TEST(my benchmark, "Run a small benchmark.", benchmark) {
    // Check that the function returns the correct result,
    // if an incorrect result is produced, the benchmark
    // won't be run and the test will fail
    EXPECT factorialList(100).size() == 100;
    
    // Benchmark the function's execution time
    BENCHMARK factorialList(100);
  };
}
```

## See Also

- [`TEST` macro](TEST.md)
  - Define a test case.
- [`BenchmarkResult` class](../Types/BenchmarkResult.md)
  - Handle the result of a micro benchmark.
- [Creating a micro benchmark tutorial](../../Tutorials/Benchmarking.md)
  - Learn to setup and run a micro benchmark.
