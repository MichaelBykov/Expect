# `MATCHER` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Implementation](#Parameters-and-Implementation)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
MATCHER([name], [type], [full-name]) {
  [implementation]
};
```

## Parameters and Implementation

- `[name]` : The name of the custom matcher type.
- `[type]` : The type that the matcher matches.
  Can come from a template.
- `[full-name]` : The full name of the custom matcher, including all template
  arguments, if applicable.
- `[implementation]` : The implementation of the custom matcher.
  Should, at a minimum, have a `bool evaluate([type] value)` method.

## Usage

Define a custom matcher.

A matcher should have its matcher arguments, constructor (if there are matcher
arguments), a `bool evaluate([type] value)` method, and optionally a
`std::string message([type] value, bool succeeded)` method inside of it its
`[implementation]`.

The evaluate method will be invoked when the matcher is used to match a value.

The message method will be invoked if the matcher assertion that the matcher
was used in fails, and an error message needs to be produced.
Separate messages for match success and failure should be produced because the
matcher may be used with a, for instance, `not` operator.

A matcher should also have an instantiation function or variable for easier use.
An instantiation function typically follows the form
``` C++
template<typename T>
MATCHER_RESULT(T) myMatcher() {
  return MyMatcher<T>();
}
```
Where `MyMatcher` is the name of your custom matcher and
[`MATCHER_RESULT`](Matcher_RESULT.md) declares the result type of a matcher.
For matchers without a template and with no custom arguments, a variable may
be more appropriate, in the form
``` C++
static MATCHER_RESULT(int) isZero = IsZero();
```
Where `IsZero` is the name of your custom matcher.
Defining a separate instantiation function or variable for your matcher allows
the matcher to be used with omitted template arguments and/or parenthesis when
possible.

## Examples

The below example demonstrates creating a simple range matcher.
``` C++
template<typename T>
MATCHER(InRange, T, InRange<T>) {
  // Custom matcher arguments
  T lhs, rhs;
  
  // Populate the custom matcher arguments
  InRange(T lhs, T rhs)
    : lhs(lhs), rhs(rhs) { }
  
  // Check if a given value matches
  // the set matcher conditions
  bool evaluate(T value) {
    return lhs <= value && value <= rhs;
  }
  
  // Custom failure message
  std::string message(T value, bool succeeded) {
    return MESSAGE
      value << " is " << (succeeded ? "in" : "not in") <<
      " the range of [" << lhs << ", " << rhs "]."
    ;
  }
};

// Instantiation for the matcher
template<typename T>
MATCHER_RESULT(T) inRange(T lhs, T, rhs) {
  return InRange<T>(lhs, rhs);
}
```

## See Also

- [`MATCHER_RESULT` macro](MATCHER_RESULT.md)
  - The result type of a custom matcher.
- [Custom Matchers Tutorial](../../Tutorials/Custom-Matchers.md)
  - A guided walkthrough of creating your own matchers and using them.
