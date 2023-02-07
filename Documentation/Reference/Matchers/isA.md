# `isA` matcher / `isAn` matcher

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
isA<[base] *, [sub]>()

isAn<[base] *, [sub]>()
```

## Parameters

- `[base]` : The base type that is being checked.
- `[sub]` : The type to check that the pointer points to.

## Usage

Check that a pointer is a specific type.

Typically used to check if the pointer is an instance of a subclass of a
superclass where the pointer is defined as a pointer to the superclass.

## Examples

The below example demonstrates checking a type.
``` C++
class Foo { ... }
class Bar : Foo { ... }

Foo *foo = new Bar();

// Check that foo is actually an instance of Bar
EXPECT_THAT foo | isA<Foo *, Bar>;
```

## See Also

- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.
