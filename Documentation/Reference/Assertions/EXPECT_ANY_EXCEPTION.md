# `EXPECT_ANY_EXCEPTION` macro / `ASSERT_ANY_EXCEPTION` macro

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
EXPECT_ANY_EXCEPTION { [expression...] };

EXPECT_ANY_EXCEPTION { [expression...] } | [message];

ASSERT_ANY_EXCEPTION { [expression...] };

ASSERT_ANY_EXCEPTION { [expression...] } | [message];
```

## Parameters and Contents

- `[expression...]` : The expression(s) to evaluate for the assertion.
- `[message]` : An optional custom failure message for the assertion.

## Usage

Define an assertion expression for an exception.

`EXPECT_ANY_EXCEPTION` is non-fatal and will not stop the test case from
continuing to run.

`ASSERT_ANY_EXCEPTION` is fatal and will stop the test case case from continuing
to run.

Behavior and syntax is the same as the `EXPECT` and `ASSERT` macros except that
the expression (enclosed in curly braces and spanning as many statements as
you want) is being checked for some exception and fails upon no exception.

## Examples

The below example demonstrates the usage of the assertion.
``` C++
TEST(my assertion test, "Test the EXPECT_ANY_EXCEPTION macro.") {
  EXPECT_ANY_EXCEPTION { throw 3; }; // Succeeds
  
  EXPECT_ANY_EXCEPTION { throw "An exception."; }; // Succeeds
  
  EXPECT_ANY_EXCEPTION { }; // Fails
};
```

## See Also

- [`EXPECT` macro](EXPECT.md)
  - The standard non-fatal assertion macro.
- [`ASSERT` macro](ASSERT.md)
  - The standard fatal assertion macro.
- [Using Assertions](../../Tutorials/Using-Assertions.md)
  - A guided walkthrough of using all the different assertions.
