# `RunningTest` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Types](#Subtypes)
- [Members](#Members)
- [Subtypes](#Subtypes)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Access the state of a test case is preparing to be run.

## Superclass

- [`RunState`](RunState.md) : The general run state.

## Members

- `state` - [`State`](RunState.State.md) : The state tag.
  Will always be set to [`State::RunningTest`](RunState.State.md).

- `suite` - [`Suite &`](Suite.md) : The test suite that the test case is in.
- `test` - [`Test &`](Test.md) : The test case that is going to be run.
- `index` - `size_t` : The index of the test within the test suite.
- `count` - `size_t` : The total number of test cases that will be run in the
  test suite.

## See Also

- [`RunState` class](RunState.md)
  The general run state.
- [`RUN_ENABLED_TESTS` macro](../Macros/RUN_ENABLED_TESTS.md)
  - Declare a custom test driver.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
