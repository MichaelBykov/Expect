# `isInfinite` matcher

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters](#Parameters)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
isInfinite<[type]>()
```

## Parameters

- `[type]` : The floating-point type.

## Usage

Check that a floating-point value is infinite.

## Examples

The below example demonstrates checking for infinity.
``` C++
double value = calculate();

EXPECT_THAT value | isInfinite;
// ^ will pass when value is positive or negative infinity
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
