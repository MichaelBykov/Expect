# `has` matcher

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
has<[type], [element]>([]([element] value) -> bool { [expression] }, [count])

has<[type], [element]>([value], [count])
```

## Parameters

- `[type]` : The collection type.
- `[element]` : The element type in the collection.
- `[expression]` : The expression to match, should return a boolean.
- `[value]` : The value to match.
- `[count]` : The number of elements to match.

## Usage

Check that a specific predicate or element matches `[count]` times in a
collection.

## Examples

The below example demonstrates checking that 3 elements pass a condition.
``` C++
std::vector<int> vector = foo();

// Check that exactly 3 elements in a vector are positive
EXPECT_THAT vector | has<std::vector<int>, int>([](int value) {
  return value >= 0;
}, 3);
```

The below example demonstrates checking that a collection consists of exactly 3
specific instance of an element.
``` C++
std::vector<int> vector = foo();

// Check that the vector has exactly 3 zeros
EXPECT_THAT vector | has<std::vector<int>, int>([](int value) {
  return value == 0;
}, 3);
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
