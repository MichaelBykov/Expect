# `RunState` class

## Jump to...
- [Availability](#Availability)
- [Usage](#Usage)
- [Superclass](#Superclass)
- [Members](#Members)
- [Subtypes](#Subtypes)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Usage

Access the state of an in-progress test run.

## Types

- [`State`](RunState.State.md) : A description of the state tag.

## Members

- `state` - `State` : The state tag.

## Subtypes

- [`RunningSuite`](RunningSuite.md) : A test suite is beginning to be run.
- [`FinishedSuite`](FinishedSuite.md) : A test suite has finished running.
- [`RunningTest`](RunningTest.md) : A test case is preparing to be run.
- [`TestSuccess`](TestSuccess.md) : A test case succeeded in running.
- [`TestFailed`](TestFailed.md) : A test case failed in running.

## See Also

- [`RUN_ENABLED_TESTS` macro](../Macros/RUN_ENABLED_TESTS.md)
  - Declare a custom test driver.
- [Custom Drivers Tutorial](../../Tutorials/Custom-Drivers.md)
  - A guided walkthrough of creating a custom test driver.
