# `isTrue` matcher

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
isTrue
```

## Usage

Check that value is true.

## Examples

The below example demonstrates checking for true.
``` C++
bool value = calculate();

EXPECT_THAT value | isTrue;
// ^ passes when value is true
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
