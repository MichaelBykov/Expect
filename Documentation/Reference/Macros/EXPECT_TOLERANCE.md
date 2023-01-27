# `EXPECT_TOLERANCE` macro

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
#define EXPECT_TOLERANCE [tolerance]
#include <Expect>
```

## Parameters and Contents
- `[tolerance]` : The default tolerance to use in Expect.

## Usage

The standard tolerance of approximate comparison operations.

Can be defined to be any value but defaults to `1e-6` if undefined.

## Examples

The below example demonstrates using a custom default tolerance.
``` C++
#define EXPECT_TOLERANCE 1e-3
#include <Expect>

SUITE(Tolerance) {
  TEST(tolerance, "Use the default tolerance.") {
    // Check that foo() returns a number approx within 1e-3 of 0.3
    EXPECT_APPROX foo() == 0.3;
  };
}
```

## See Also

- [Assertions](../Assertions)
  - A list of all the different assertion macros, including approximate
    assertions that utilize tolerance.
- [Using assertions tutorial](../../Tutorials/Using-Assertions.md)
  - Learn how to use the different assertion macros, including those using
    tolerance.
