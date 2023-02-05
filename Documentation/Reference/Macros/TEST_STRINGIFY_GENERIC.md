# `TEST_STRINGIFY_GENERIC` macro

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
template< [template] >
TEST_STRINGIFY_GENERIC([type], [name]) {
  [implementation]
} TEST_STRINGIFY_GENERIC_END
```

## Parameters and Implementation
- `[template]` : The template used in defining the described type.
- `[type]` : The type for which to define a custom string description, including
  template arguments.
  Should usually be defined as a reference to a type
- `[name]` : The name of the type parameter used in the implementation.
- `[implementation]` : The implementation of the stringification for the given
  type.
  Should return a string description of the passed value, `[type] [name]`.

## Usage

Define a custom string description for a template type used in testing.

The implementation has a single parameter of the type `[type]` and named
`[name]`.
It should be converted to string and a description of it should be returned from
the implementation.

Types that don't define custom descriptions will be described using their
address.

If you are using a custom description of a type in more than one file, make
sure to define the specialization in a shared header file instead to avoid
duplicate code errors when compiling.

## Examples

The below example demonstrates creating a custom description for a template
type.
``` C++
template<typename T>
TEST_STRINGIFY_GENERIC(std::vector<T> &, vector) {
  if (vector.empty()) {
    // Empty vector
    return "(0) { }";
  }
  else if (vector.size() > 5) {
    // Vector of more than 5 elements,
    // only describe the first five
    std::string description =
      MESSAGE "(" << vector.size() << ") { " << vector[0];
    for (int i = 1; i < 5; i++)
      description += MESSAGE ", " << vector[i];
    description += MESSAGE ", ... }";
    return description + ", ... }";
  }
  else {
    // Vector of 1-5 elements
    std::string description =
      MESSAGE "(" << vector.size() << ") { " << vector[0];
    for (int i = 1; i < vector.size(); i++)
      description += MESSAGE ", " << vector[i];
    return description + " }";
  }
} TEST_STRINGIFY_GENERIC_END

// ... inside some test
std::vector<int> x = { 1, 2, 3 };
std::vector<int> y = { };
EXPECT x == y;
  //< (3) { 1, 2, 3 } is not equal to (0) { }.
```

## See Also

- [`TEST_STRINGIFY` macro](TEST_STRINGIFY.md)
  - Define a custom string description for non-template types.
- [`MESSAGE` macro](MESSAGE.md)
  - Compose a custom message from various values, including those for which
    custom description have been defined using the `TEST_STRINGIFY` or
    `TEST_STRINGIFY_GENERIC` macros.
- [Custom String Conversion](../../Tutorials/Custom-String-Conversion.md)
  - Learn how to set up custom string conversions for your types in Expect.
