# `isFalse` matcher

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
isFalse
```

## Usage

Check that value is false.

## Examples

The below example demonstrates checking for false.
``` C++
bool value = calculate();

EXPECT_THAT value | isFalse;
// ^ passes when value is false
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
