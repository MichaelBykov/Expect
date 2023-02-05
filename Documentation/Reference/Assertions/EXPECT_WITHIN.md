# `EXPECT_WITHIN` macro / `ASSERT_WITHIN` macro

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
EXPECT_WITHIN [expression];

EXPECT_WITHIN [expression] | [tolerance] | [message];

ASSERT_WITHIN [expression];

ASSERT_WITHIN [expression] | [tolerance] | [message];
```

## Parameters and Contents

- `[expression]` : The expression to evaluate for the assertion.
- `[tolerance]` : An optional custom tolerance to use in comparison.
  Defaults to [`EXPECT_TOLERANCE`](../Macros/EXPECT_TOLERANCE.md).
- `[message]` : An optional custom failure message for the assertion.

## Usage

Define an assertion expression with approximate comparison.

`EXPECT_WITHIN` is non-fatal and will not stop the test case from continuing to
run.

`ASSERT_WITHIN` is fatal and will stop the test case case from continuing to
run.

Behavior and syntax is the same as the `EXPECT` and `ASSERT` macros except that
all comparison uses the following formulas:
- `x == y` : |x - y| ≤ tol
- `x != y` : |x - y| > tol
- `x < y` : x - y < -tol
- `x <= y` : x - y ≤ tol
- `x > y` : x - y > tol
- `x >= y` : x - y ≥ -tol
where `tol` is the set comparison tolerance.

The type which you are comparing should have a conversion from a single double
value to your type, addition, subtraction, multiplication, negation, and exactly
less (the `<` operator) defined in order to be able to be compared using
`EXPECT_WITHIN` or `ASSERT_WITHIN`.

The tolerance, like the message, is set by adding a vertical bar (`|`) after the
expression and including a `double` tolerance value.
Setting tolerance and adding messages can be mixed in any order, for example,
`EXPECT_WITHIN 1 == 3 | "hello" | MESSAGE " " | 0.1 | "world!";` will display
`hello world! (1 is not equal to 3 within 0.1.)`

## Examples

The below example includes various valid assertions.
``` C++
TEST(my assertion test, "Test the EXPECT_WITHIN and ASSERT_WITHIN macros.") {
  double x = foo();
  
  // Expect that x is approx not within zero
  EXPECT_WITHIN x;
  
  // Expect that x is approx equal to 3 with a tolerance of 0.1
  EXPECT_WITHIN x == 3 | 0.1;
  
  // Expect that x is approx between 0 and 10 (inclusive, exclusive)
  EXPECT_WITHIN 0 <= x < 10;
};
```

## See Also

- [`EXPECT` macro](EXPECT.md)
  - The standard non-fatal assertion macro.
- [`ASSERT` macro](ASSERT.md)
  - The standard fatal assertion macro.
- [Using Assertions](../../Tutorials/Using-Assertions.md)
  - A guided walkthrough of using all the different assertions.
