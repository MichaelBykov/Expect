# `each` matcher

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
each<[type], [element]>([]([element] value) -> bool { [expression] })

each<[type], [element]>([value])
```

## Parameters

- `[type]` : The collection type.
- `[element]` : The element type in the collection.
- `[expression]` : The expression to match, should return a boolean.
- `[value]` : The value to match.

## Usage

Check that a each element in a collection matches a set condition or a set
element.

## Examples

The below example demonstrates checking every element for a condition.
``` C++
std::vector<int> vector = foo();

// Check that every element in a vector is positive
EXPECT_THAT vector | each<std::vector<int>, int>([](int value) {
  return value >= 0;
});
```

The below example demonstrates checking that a collection consists of a single
instance of an element.
``` C++
std::vector<int> vector = foo();

// Check that every element in a vector is zero
EXPECT_THAT vector | each<std::vector<int>, int>([](int value) {
  return value == 0;
});
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
