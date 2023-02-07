# `SHARE` macro

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
SHARE {
  [variables]
};
```

## Parameters and Contents
- `[variables]` : A set of all the variables to share throughout the test suite.
  Should be declared as statements.

## Usage

Shares a set of common variables throughout a test suite instance.

Shared variables are accessed by using the [`SHARED`](SHARED.md) macro before
the variable name.
For example, if a variable `std::string message` is shared, it can be accessed
by using `SHARED message`.
Note that parentheses are not required if accessing submembers, so the statement
`SHARED message.length()` is valid.

A `SHARE` block must be accompanied by a [`SETUP`](SETUP.md) block before the
variables can be accessed in the test suite.

It is typical to declare variables in the share block and then initializing them
in the [`SETUP`](SETUP.md) block and de-initializing them in the
[`TEARDOWN`](TEARDOWN.md) block of the test suite, although they can be
initialized directly in the `SHARE` block.
Variables with no default constructor must be initialized in the `SETUP` block.

Note that only one set of variables can be shared in a test suite.
Instead of declaring two `SHARE` blocks in a test suite, merge them together.

## Examples

The below example includes setup and teardown code in addition to a shared
variable.
``` C++
SUITE(Sharing) {
  SHARE {
    // The below variable is shared between all
    // test cases the setup and teardown code
    // over the life of the test suite
    Connection connection;
  };
  
  SETUP {
    // Shared variables are accessed by prefixing
    // `SHARED` before their name
    // (parenthesis are not required)
    SHARED connection = connect("somewhere");
  };
  
  TEARDOWN {
    SHARED connection.end();
  };
  
  // A common constant, note that because it has no managed lifetime, it can
  // be declared without having to set it up or tear it down
  int x = 3;
  
  TEST(response foo, "Test for a `foo` response.") {
    Response r = SHARED connection.get("foo", x);
    EXPECT r.status == Response::Status::foo;
  };
  
  TEST(response baz, "Test for a `baz` response.") {
    Response r = SHARED connection.get("baz", x);
    EXPECT r.status == Response::Status::baz;
  };
}
```

## See Also

- [`SHARED` macro](SHARED.md)
  - Access a shared variable.
- [`SETUP` macro](SETUP.md)
  - Define setup code for a test suite.
- [`TEARDOWN` macro](TEARDOWN.md)
  - Define teardown code for a test suite.
- [`SUITE` macro](SUITE.md)
  - Define a test suite.
- [Setting up and configuring a test suite tutorial](../../Tutorials/Test-Suite.md)
  - Learn to setup and configure a test suite, including sharing variables.
