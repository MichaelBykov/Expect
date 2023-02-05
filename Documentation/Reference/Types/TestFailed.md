# `TestFailed` class

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

Access the state of a test case succeeded in running.

## Superclass

- [`RunState`](RunState.md) : The general run state.

## Members

- `state` - [`State`](RunState.State.md) : The state tag.
  Will always be set to [`State::TestFailed`](RunState.State.md).

- `test` - [`Test &`](Test.md) : The test case that failed.
- `failures` - `std::vector<`[`Failure`](Failure.md)`> &` : A list of all the
  assertion failures in the test case.

## See Also

- [`RunState` class](RunState.md)
  The general run state.
- [`RUN_ENABLED_TESTS` macro](../Macros/RUN_ENABLED_TESTS.md)
  - Declare a custom test driver.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
