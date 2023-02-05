# `Environment` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Members](#Members)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Configure the test environment in which test runs are performed.

## Members

- `stopOnFailure` - `bool` : Whether or not unit test cases should stop after a
  failed assertion.
  Defaults to `true`.
- `success` - `bool` : Whether or not the just ran unit test was successful.
  Managed by the test driver.
- `failures` - `std::vector<`[`Failure`](Failure.md)`>` : A list of all failures
  encountered during a unit test run.
  Managed by the test driver.
- `benchmarks` - `std::vector<`[`BenchmarkResult`](BenchmarkResult.md)`>` -
  A list of all benchmark results for a unit test run.
  Managed by the test driver.

## See Also

- [`RUN_ENABLED_TESTS` macro](../Macros/RUN_ENABLED_TESTS.md)
  - Declare a custom test driver.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
