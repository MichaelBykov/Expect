# `Test` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Members](#Members)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Manage an instance of a test case.

## Members

- `name` - `const char *` : The name of the test case.
- `description` - `const char *` : A description of the test case.
- `tags` - `std::vector<const char *>` : A list of all of the test case's tags.
- `enabled` - `bool` : Whether or not the test case is enabled for running in
  the next test run.
  Defaults to `false`.
- `test` - `(`[`Environment`](Environment.md)` &) -> void` : The driver for the
  test case.

## See Also

- [`TEST` macro](../Macros/TEST.md)
  - Define a test case.
- [Creating a test case tutorial](../../Tutorials/Test-Case.md)
  - Learn to setup and run a test case.
