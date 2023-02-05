# `RunningSuite` class

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

Access the state of a test suite that is beginning to be run.

## Superclass

- [`RunState`](RunState.md) : The general run state.

## Members

- `state` - `State` : The state tag.
  Will always be set to [`State::RunningSuite`](RunState.State.md).

- `suite` - [`Suite &`](Suite.md) : The test suite that is being run.

## See Also

- [`RunState` class](RunState.md)
  The general run state.
- [`RUN_ENABLED_TESTS` macro](../Macros/RUN_ENABLED_TESTS.md)
  - Declare a custom test driver.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
