# `isNonNaN` matcher

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
isNonNaN<[type]>()
```

## Parameters

- `[type]` : The floating-point type.

## Usage

Check that a floating-point value is not not-a-number.

## Examples

The below example demonstrates checking for non-NaN numbers.
``` C++
double value = calculate();

EXPECT_THAT value | isNonNaN;
// ^ will pass when value is not NaN
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
