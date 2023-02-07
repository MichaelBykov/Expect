# `endsWith` matcher

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
endsWith<[string]>([substring])
```

## Parameters

- `[string]` : The string type.
- `[substring]` : The substring to match at the end of the string.

## Usage

Check that a string ends with a specific substring.

## Examples

The below example demonstrates checking check that a string ends with a
specific substring.
``` C++
const char *string = "Hello, world!";

// Check that the string ends with an exclamation mark
EXPECT_THAT string | endsWith<const char *>("!");
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
