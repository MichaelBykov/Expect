# `BenchmarkResult` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Members](#Members)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Access the results of a micro benchmark run in a test case.

## Members

- `line` - `int` : The line number of the benchmark that was run.
- `iterations` - `size_t` : The total number of iterations that occurred.
- `totalTime` - `long long` : The total elapsed time of the benchmark.
- `meanTime` - `long long` : The mean time that a benchmark cycle took,
  in nanoseconds.
- `medianTime` - `long long` : The median time that a benchmark cycle took,
  in nanoseconds.
- `minTime` - `long long` : The minimum time that a benchmark cycle took,
  in nanoseconds.
- `maxTime` - `long long` : The maximum time that a benchmark cycle took,
  in nanoseconds.
- `q1Time` - `long long` : The first quartile of the time that a benchmark cycle
  took, in nanoseconds.
- `q3Time` - `long long` : The third quartile of the time that a benchmark cycle
  took, in nanoseconds.
- `times` - `std::vector<long long>` : The execution times of each iteration,
  in nanoseconds.

## See Also

- [`BENCHMARK` macro](../Macros/BENCHMARK.md)
  - Run a micro benchmark.
- [`TEST` macro](../Macros/TEST.md)
  - Define a test case.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
