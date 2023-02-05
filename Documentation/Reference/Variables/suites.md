# `suites` global variable

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

A list of all of the registered test suites used to manage or configure the
test suites and their test cases.

## Examples

The below example demonstrates enabling all tests with the name `my test`.
``` C++
for (Suite *suite : Expect::suites) {
  for (Test &test : suite->tests) {
    if (test.name == "my test") {
      test.enabled = true;
    }
  }
}
```

## See Also

- [`SUITE` macro](../Macros/SUITE.md)
  - Define a test suite.
- [`Suite` class](../Types/Suite.md)
  - Configure and manage a test suite instance.
- [Setting up and configuring a test suite tutorial](../../Tutorials/Test-Suite.md)
  - Learn to setup and configure a test suite.
