# `Suite` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Members](#Members)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Manage an instance of a test suite.

## Members

- `name` - `const char *` : The name of the test suite.
- `tests` - `std::vector<`[`Test`](Test.md)`>` : A list of all test cases
   in the test suite.
- `setup` - `() -> void` : The setup function of the test suite.
  Called before any test cases are run.
  Defaults to `nullptr`.
- `teardown` - `() -> void` : The teardown function of the test suite.
  Called after the test suite finishes running and before cleanup is called.
  Defaults to `nullptr`.
- `cleanup` - `() -> void` : The cleanup function of the test suite.
  Removes allocated shared variables for the test suite.
  Called after the test suite finishes running and after teardown is called.
  Defaults to `nullptr`.

## See Also

- [`SUITE` macro](../Macros/SUITE.md)
  - Define a test suite.
- [`SETUP` macro](../Macros/SETUP.md)
  - Define test suite setup code.
- [`TEARDOWN` macro](../Macros/TEARDOWN.md)
  - Define test suite teardown code.
- [`Test` class](Test.md)
  - Configure and manage a test case instance.
- [`suites` global variable](../Variables/suites.md)
  - Manage all instances instances of test suites in the program.
- [Setting up and configuring a test suite tutorial](../../Tutorials/Test-Suite.md)
  - Learn to setup and configure a test suite.
