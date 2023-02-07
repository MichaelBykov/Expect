# `contains` matcher

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
contains<[type], [element]>([]([element] value) -> bool { [expression] })

contains<[type], [element]>([value])

contains<[string]>([substring])
```

## Parameters

- `[type]` : The collection type.
- `[element]` : The element type in the collection.
- `[expression]` : The expression to match, should return a boolean.
- `[value]` : The value to match.

- `[string]` : The string type.
- `[substring]` : The substring to match in the string.

## Usage

Check that a specific predicate or element matches at least once in a
collection.

If the collection is a string, check that a specific substring exists within
the string.

## Examples

The below example demonstrates checking that at least one element passes a
condition.
``` C++
std::vector<int> vector = foo();

// Check that there is a positive value in a vector
EXPECT_THAT vector | contains<std::vector<int>, int>([](int value) {
  return value >= 0;
});
```

The below example demonstrates checking that a collection has at least one
specific instance of an element.
``` C++
std::vector<int> vector = foo();

// Check that the vector has at least one zero
EXPECT_THAT vector | contains<std::vector<int>, int>([](int value) {
  return value == 0;
});
```

The below example demonstrates checking a string for a substring.
``` C++
const char *string = "Hello, world!";

// Check that the string has the substring "world"
EXPECT_THAT string | contains<const char *>("world");
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
