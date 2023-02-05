# `TEST_STRINGIFY` macro

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
TEST_STRINGIFY([type], [name]);

TEST_STRINGIFY([type], [name]) {
  [implementation]
}
```

## Parameters and Implementation
- `[type]` : The type for which to define a custom string description.
  Should usually be defined as a reference to a type
- `[name]` : The name of the type parameter used in the implementation.
- `[implementation]` : The implementation of the stringification for the given
  type.
  Should return a string description of the passed value, `[type] [name]`.

## Usage

Define a custom string description for a type used in testing.

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

The below example demonstrates creating custom descriptions for some types.
``` C++
struct Point { int x, y; };
struct Size { int width, height; };
struct Rect { Point origin; Size size; };

TEST_STRINGIFY(Point &, point) {
  return MESSAGE "(" << point.x << ", " << point.y << ")";
}

TEST_STRINGIFY(Size &, size) {
  return MESSAGE "[" << size.width << ", " << size.height << "]";
}

TEST_STRINGIFY(Rect &, rect) {
  // Other types' custom descriptions can be used with the MESSAGE macro
  return MESSAGE << rect.origin << " x " << rect.size;
}
```

The below example shows sharing custom descriptions between multiple files.
``` C++
struct Point {
  int x, y;
};

// Description.h
TEST_STRINGIFY(Point &, value);

// Description.cpp
TEST_STRINGIFY(Point &, value) {
  return MESSAGE "(" << value.x << ", " << value.y << ")";
}

// Test Point.cpp
SUITE(Point) {
  TEST(difference) {
    EXPECT Point(1, 2) - Point(3, 4) == Point(13, 24);
      //< (-2, -2) is not equal to (13, 24).
  };
}

// Test Geometry.cpp
SUITE(Geometry) {
  TEST(rotate) {
    EXPECT Geometry::rotatePoint({ 1, 2 }, 90_deg) == Point(-2, 1);
      //< (2, -1) is not equal to (-2, 1).
  };
}
```

## See Also

- [`TEST_STRINGIFY_GENERIC` macro](TEST_STRINGIFY_GENERIC.md)
  - Define a custom string description for template types.
- [`MESSAGE` macro](MESSAGE.md)
  - Compose a custom message from various values, including those for which
    custom description have been defined using the `TEST_STRINGIFY` macro.
- [Custom String Conversion](../../Tutorials/Custom-String-Conversion.md)
  - Learn how to set up custom string conversions for your types in Expect.
