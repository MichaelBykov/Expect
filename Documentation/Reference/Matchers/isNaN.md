# `isNaN` matcher

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
isNaN<[type]>()
```

## Parameters

- `[type]` : The floating-point type.

## Usage

Check that a floating-point value is not-a-number.

## Examples

The below example demonstrates checking for NaN.
``` C++
double value = calculate();

EXPECT_THAT value | isNaN;
// ^ will pass when value is NaN
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
