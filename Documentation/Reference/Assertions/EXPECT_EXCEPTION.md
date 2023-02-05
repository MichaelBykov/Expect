# `EXPECT_EXCEPTION` macro / `ASSERT_EXCEPTION` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Contents](#Parameters-and-Contents)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
EXPECT_EXCEPTION([type]) { [expression...] };

EXPECT_EXCEPTION([type]) { [expression...] } | [message];

ASSERT_EXCEPTION([type]) { [expression...] };

ASSERT_EXCEPTION([type]) { [expression...] } | [message];
```

## Parameters and Contents

- `[type]` : The type of exception that should be produced.
- `[expression...]` : The expression(s) to evaluate for the assertion.
- `[message]` : An optional custom failure message for the assertion.

## Usage

Define an assertion expression for an exception.

`EXPECT_EXCEPTION` is non-fatal and will not stop the test case from continuing
to run.

`ASSERT_EXCEPTION` is fatal and will stop the test case case from continuing to
run.

Behavior and syntax is the same as the `EXPECT` and `ASSERT` macros except that
the expression (enclosed in curly braces and spanning as many statements as
you want) is being checked for a specific exception and fails upon no exception
or if the exception thrown does not match the given type.

## Examples

The below example demonstrates the usage of the assertion.
``` C++
TEST(my assertion test, "Test the EXPECT_EXCEPTION macro.") {
  EXPECT_EXCEPTION(int) { throw 3; }; // Succeeds
  
  EXPECT_EXCEPTION(int) { }; // Fails
  
  EXPECT_EXCEPTION(int) { throw "An exception."; }; // Fails
};
```

## See Also

- [`EXPECT` macro](EXPECT.md)
  - The standard non-fatal assertion macro.
- [`ASSERT` macro](ASSERT.md)
  - The standard fatal assertion macro.
- [Using Assertions](../../Tutorials/Using-Assertions.md)
  - A guided walkthrough of using all the different assertions.
