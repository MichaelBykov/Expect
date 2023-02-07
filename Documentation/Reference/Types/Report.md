# `Report` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Members](#Members)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Access the final results of a test run.

## Members

- `isSuccessful` - `bool` : Whether or not the test run was successful, i.e. all
  tests passed all assertion checks.
- `total` - `size_t` : The total number of test cases in the test run.
- `totalSuccessful` - `size_t` : The number of test cases in the test run that
  passed all assertion checks.
- `totalFailed` - `size_t` : The number of test cases in the test run that
  failed at least one assertion check.

## See Also

- [`RUN_ENABLED_TESTS` macro](../Macros/RUN_ENABLED_TESTS.md)
  - Declare a custom test driver.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
