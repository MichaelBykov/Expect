# `MATCHER_RESULT` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Contents](#Parameters-and-Contents)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
MATCHER_RESULT([type])
```

## Parameters and Contents

- `[type]` : The type that the matcher matches.
  Can come from a template.

## Usage

Get the result type of a matcher.

Typically used to instantiate a matcher.

## Examples

The below example demonstrates creating a simple range matcher.
``` C++
template<typename T>
MATCHER(InRange, T, InRange<T>) { ... }

// Instantiation for the matcher
template<typename T>
MATCHER_RESULT(T) inRange(T lhs, T, rhs) {
  return InRange<T>(lhs, rhs);
}
```

## See Also

- [`MATCHER` macro](MATCHER.md)
  - Define a custom matcher.
- [Custom Matchers Tutorial](../../Tutorials/Custom-Matchers.md)
  - A guided walkthrough of creating your own matchers and using them.
