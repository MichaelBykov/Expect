# `MESSAGE` macro

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
MESSAGE [contents]

MESSAGE [item1] << [item2] << [...] << [itemN]
```

## Parameters and Contents
- `[contents]` : The message to construct.
  Can consist of both string and non string values separated by `<<`.

## Usage

The message macro is used to compose custom error messages for assertion macros.

It is composed of string and/or non-string items separated by the stream
insertion operator `<<`.
For non-standard types the default stringification that will be provided is the
address of the given object.
Custom string  descriptions can be specified for custom objects using the
[`TEST_STRINGIFY`](TEST_STRINGIFY.md) and
[`TEST_STRINGIFY_GENERIC`](TEST_STRINGIFY_GENERIC.md) macros.

Most assertion macros accept custom messages using a pipe (`|`) operator,
for instance for the standard `EXPECT` macro, a custom message can be provided
as such: `EXPECT [expression] | MESSAGE [contents];`.

## Examples

The below example demonstrates using a message macro to show an index for an
assertion in a loop.
``` C++
TEST(messages, "Demonstrate the MESSAGE macro through a loop.") {
  int *x = fibonacci(10);
  int expected[] { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
  for (int i = 0; i < 10; i++)
    EXPECT x[i] == expected[i] | MESSAGE "Unsatisfied at index " << i << ".";
      //> Unsatisfied at index 3. (1 was not equal to 2.)
};
```

## See Also

- [`TEST_STRINGIFY` macro](TEST_STRINGIFY.md)
  - Share a set of variables in a test suite.
- [`TEST_STRINGIFY_GENERIC` macro](TEST_STRINGIFY_GENERIC.md)
  - Access a shared variable.
- [Assertions](../Assertions)
  - A list of all the different assertion macros, all of which accept custom
    messages.
- [Custom String Conversion](../../Tutorials/Custom-String-Conversion.md)
  - Learn to define and use custom string conversions for your types in the
    Expect library.
