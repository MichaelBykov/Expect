# `TEST_CUSTOM_COMPARE` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Implementation](#Parameters-and-Implementation)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
TEST_CUSTOM_COMPARE([type], [mode], [comparison]);

TEST_CUSTOM_COMPARE([type], [mode], [comparison]) {
  [contents]
}
```

## Parameters and Implementation
- `[type]` : The type for which to define a custom comparison.
- `[mode]` : The comparison mode.
  Should be one of the following: `Exact`, `Approx`, `Near`, `Within`.
- `[comparison]` : The comparison type to define.
  Should be one of the following options: `Value`, `Equal`, `NotEqual`, `Less`,
  `LessEqual`, `Greater`, `GreaterEqual`, `Range`, `InclusiveRange`,
  `ExclusiveRange`.
- `[implementation]` : The implementation of the comparison function.
  Should return a boolean indicating the result of the comparison.
  See the usage notes below for variables that can be accessed in the
  implementation for comparison.

## Usage

Define a custom comparison used in testing.

For the `Value` comparison, there is one member to compare, `value`.

For the `Equal`, `NotEqual`, `Less`, `LessEqual`, `Greater`, and
`GreaterEqual` comparisons, there are two members to compare, `lhs` and
`rhs`.

For the `InclusiveRange` and `ExclusiveRange` comparisons, there are three
members to compare, `lhs`, `value`, and `rhs`, where `lhs` and `rhs` are
the left and right bounds of the range, respectively, and `value` is the
value being tested for being within the range.

The `Range` comparison has five members to compare, the three mentioned
for the range comparisons above in addition to `lhsIncluded` and
`rhsIncluded` which are booleans that indicate whether or not the left
and right ends of the range are included in the comparison.

Note that all three of the range specializations automatically adapt to
comparison specializations made in `Less`, `LessEqual`, `Greater`, and
`GreaterEqual`, therefore making a custom range comparison specialization
shouldn't be necessary oftentimes.

If the comparison mode is `Approx`, `Near`, or `Within`, there is a
further member `tolerance` that indicates the tolerance in comparing two
values.

The `Exact` comparison mode tests whether the value(s) are exactly within
their bounds.
For example, in exact comparison the expression `1.0 == 1.0000000001`
would evaluate to false.

The `Approx` comparison mode tests whether the value(s) are relatively
within their bounds with relative equality at zero failing for all
non-zero values.
For example, in approximate comparison the expression `0.0 == 1e-50` with
a tolerance of `1e-6` would fail.
The expressions `1.0 == 1.02` and `1.0 == 1.03` with a tolerance of `0.01`
would succeed and fail, respectively.
The equation for approximate equality is `|x - y| ≤ tol * |x + y|` and for
approximately less is `x - y < -tol * |x + y|` where `x` and `y` are the
left-hand-side and right-hand-side comparison arguments, respectively,
and `tol` is the approximate comparison tolerance.

The `Near` comparison mode tests whether the value(s) are relatively
within their bounds with relative equality at zero to be within the set
tolerance.
For example, in near comparison the expression `0.0 == 1.05` with a
tolerance of `0.1` would succeed while `0.0 == 1.15` would fail.
The expressions `1.0 == 1.02` and `1.0 == 1.03` with a tolerance of `0.01`
would succeed and fail, respectively.
The equation for near equality is `|x - y| ≤ tol * max(1, |x + y|)` and
for nearly less is `x - y < -tol * max(1, |x + y|)` where `x` and `y` are
the left-hand-side and right-hand-side comparison arguments, respectively,
and `tol` is the near comparison tolerance.

The `Within` comparison mode tests whether the value(s) are within a fixed
tolerance.
For example, in within comparison the expression `0.0 == 1.05` with a
tolerance of `0.1` would succeed while `0.0 == 1.15` would fail.
The expressions `1.0 == 1.05` and `1.0 == 1.15` with a tolerance of `0.1`
would succeed and fail, respectively.
The equation for within equality is `|x - y| ≤ tol` and for within less is
`x - y < -tol` where `x` and `y` are the left-hand-side and
right-hand-side comparison arguments, respectively, and `tol` is the
comparison tolerance.

If you are using a custom comparison of a type in more than one file, make
sure to define the specialization in a shared header, for example,
`TEST_CUSTOM_COMPARE(int, Exact, Value);` for the first specialization in
the above example, to avoid duplicate code errors when compiling.

## Examples

The below example demonstrates several implementations of custom comparison.
``` C++
TEST_CUSTOM_COMPARE(int, Exact, Value) {
  // Convert the integer to a boolean value
  return value != 0;
}

TEST_CUSTOM_COMPARE(double, Within, Equal) {
  // Check that `lhs` is within `tolerance` of `rhs`
  double x = lhs - rhs;
  return x * x <= tolerance * tolerance;
}

TEST_CUSTOM_COMPARE(int, Exact, InclusiveRange) {
  // Check that `lhs <= value <= rhs`
  return lhs <= value && value <= rhs;
}

TEST_CUSTOM_COMPARE(int, Exact, Range) {
  // Check that `value` is within the specified range
  if (lhsIncluded && rhsIncluded)
    return lhs <= value && value <= rhs;
  else if (lhsIncluded)
    return lhs <= value && value < rhs;
  else if (rhsIncluded)
    return lhs < value && value <= rhs;
  else
    return lhs < value && value < rhs;
}
```

## See Also

- [Assertions](../Assertions)
  - A list of all the different assertion macros, including those utilizing
    custom comparison.
- [Custom comparison tutorial](../../Tutorials/Custom-Comparison.md)
  - Learn how to implement custom comparison for your types in Expect.
