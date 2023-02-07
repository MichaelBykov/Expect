# `beginsWith` matcher

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
beginsWith<[string]>([substring])
```

## Parameters

- `[string]` : The string type.
- `[substring]` : The substring to match at the beginning of the string.

## Usage

Check that a string starts with a specific substring.

## Examples

The below example demonstrates checking check that a string starts with a
specific substring.
``` C++
const char *string = "Hello, world!";

// Check that the string starts with "Hello"
EXPECT_THAT string | beginsWith<const char *>("Hello");
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
