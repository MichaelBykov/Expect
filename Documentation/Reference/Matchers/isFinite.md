# `isFinite` matcher

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
isFinite<[type]>()
```

## Parameters

- `[type]` : The floating-point type.

## Usage

Check that a floating-point value is finite (not NaN and not infinity).

## Examples

The below example demonstrates checking for finite numbers.
``` C++
double value = calculate();

EXPECT_THAT value | isFinite;
// ^ will pass when value is not NaN and not infinity
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
