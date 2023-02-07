# `isSome` matcher

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
isSome<[type] *>()
```

## Parameters

- `[type]` : The type of the matched value.

## Usage

Check that a pointer is non-null.

## Examples

The below example demonstrates checking for non-null.
``` C++
int *foo = calculate();

// Check that foo is non-null
EXPECT_THAT foo | isSome<int *>;
// Note that the template can be
// omitted in the above expression
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
