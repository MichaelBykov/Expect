# `EXPECT_THAT` macro / `ASSERT_THAT` macro

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
EXPECT_THAT [value] | [matchers...];

EXPECT_THAT [value] | [matchers...] | [message];

ASSERT_THAT [value] | [matchers...];

ASSERT_THAT [value] | [matchers...] | [message];
```

## Parameters and Contents

- `[value]` : The value to match.
- `[matchers...]` : The matchers to use for matching.
- `[message]` : An optional custom failure message.

## Usage

Define a matcher assertion expression.

`EXPECT_THAT` is non-fatal and will not stop the test case from continuing to
run.

`ASSERT_THAT` is fatal and will stop the test case case from continuing to run.

Matchers are used to match a value to a set of matcher expressions, allowing for
the composition of more complex assertions, especially for dynamic and
collection types.
For example, checking that a vector has three zeros can be done through
`EXPECT_THAT vector | has<std::vector<int>>(3, 0)`.
This approach also allows for richer failure reporting.
For instance, in the previous expression, if `vector` has the value
`{ 0, 1, 0 }`, the following failure message will be returned:
`{ 0, 1, 0 } did not match the set conditions. Condition #1 failed: 2 (not 3) elements matched.`.

There are a variety of built-in matchers and custom ones can easily be defined
using the [`MATCHER` macro](MATCHER.md).
Some of the common default matchers you can use are listed below:
- [`isTrue`](isTrue.md) - Check that a value is true.
- [`isFalse`](isFalse.md) - Check that a value is false.
- [`isA`](isA.md) / [`isAn`](isAn.md) - Check that a pointer to a value is a
  specific type.
- [`isNull`](isNull.md) - Check that a pointer is null.
- [`isSome`](isSome.md) - Check that a pointer is not null.
- [`isNaN`](isNaN.md) - Check that a floating-point number is not-a-number.
- [`isNonNaN`](isNonNaN.md) - Check that a floating-point number is not
  not-a-number.
- [`isFinite`](isFinite.md) - Check that a floating-point is finite.
- [`isInfinite`](isInfinite.md) - Check that a floating-point is infinite.
- [`each`](each.md) - Check that each element in a collection matches a
  predicate.
- [`has`](has.md) - Check that a collection has a set number of specific items.
- [`contains`](contains.md) - Check that a collection has some specific item.
- [`beginsWith`](beginsWith.md) - Check that a string begins with a given value.
- [`endsWith`](endsWith.md) - Check that a string ends with a given value.

Matcher expressions are separated from the main value using a vertical bar
(`|`).
A matcher assertion can have as many matcher expressions as you want, each
separated by a vertical bar.
A matcher expression is expressed by calling calling a specific matcher and can
be composed using the standard logical operators, `and`, `or`, `xor`, and `not`
(it is preferred to use the name rather than the symbolic form in order to
easily disambiguate between the vertical bars and the expression itself.)
Each matcher expression will be evaluated individually between every set of
vertical bars, for a matcher assertion to pass, all matcher expressions must
evaluate to true.
For example, `EXPECT_THAT true | isTrue | isFalse` will always fail, while
`EXPECT_THAT value | isTrue or isFalse` will always succeed.

Many matchers are generic and can therefore match for a wide variety of types,
but this means that matchers typically have to be called with their generic
arguments.

It is generally possible to omit template arguments and omit the parenthesis
from a matcher with no arguments if the matcher is not prefixed by the `not`
operator, not the left-hand-side of the `xor` operator and if the argument is
not the first in a set of parenthesis.
For instance, `EXPECT_THAT value | isNonNaN and isFinite` is valid and will
work as-intended, while
`EXPECT_THAT value | isNonNan<double>() xor isFinite`,
`EXPECT_THAT value | not isNonNan<double>() and isFinite`, and
`EXPECT_THAT value | (isNonNan<double>() or isFinite)` all require
template arguments and parenthesis for `isNonNan`.

A message can be passed to the assertion that is either a string or a message
builder from the [`MESSAGE`](../Macros/MESSAGE.md) macro.
The message will be displayed when the assertion fails in front of the standard
failure message.
Messages, like the matcher expressions, are separated from the main value by a
vertical bar (`|`).
Any amount of separate messages can be chained together after the expression
separated by the vertical bars and intertwined in any order with the matchers.
For instance, `EXPECT_THAT value | "hello" | isNan | MESSAGE " " | not isFinite<double>() | "world!";`
will display `hello world! (3.0 did not match the set conditions. Condition #1 failed: 3.0 is not not-a-number.)`.

## Examples

The below example includes various matcher assertion expressions.
``` C++
TEST(simple matchers, "Demonstrate some simple matcher expressions.") {
  double x = foo();
  
  ASSERT_THAT x | isNonNaN;
  // ^ will stop the test case if x is not-a-number
  
  EXPECT_THAT x | isInfinite;
  // ^ will continue if x is finite, but will fail the test case
};

TEST(type matchers, "Demonstrate some type matcher expressions.") {
  // class Foo
  // class Bar : Foo
  Foo *foo = compute();
  
  // Check that some value was actually returned
  ASSERT_THAT foo | isSome;
  
  // Check that the given value is of the type Bar
  EXPECT_THAT foo | isA<Bar>;
};
```

The below example demonstrates how to compose matchers using logical operators.
``` C++
TEST(composure, "Demonstrate composing matchers.") {
  std::vector<int> value = foo();
  
  // This assertion will only pass if all of
  // the below expressions are satisfied
  EXPECT_THAT value |
    has<std::vector<int>>(1, 5) |
    // ^ value has exactly 1 `5`
    
    not contains<std::vector<int>>(1) and contains<std::vector<int>>(20) |
    // ^ value doesn't contain 1 but contains 20
    
    each<std::vector<int>>([](int x) { return x >= 0 }) or
    (contains<std::vector<int>>(-1) and contains<std::vector<int>>(0));
    // ^ each element in value is positive or
    //   value contains at least one `-1` and `0`
};
```

## See Also

- [`MATCHER` macro](MATCHER.md)
  - Define a custom matcher.
- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
