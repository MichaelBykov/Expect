# `SHARED` macro

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
SHARED [variable];
```

## Parameters and Contents
- `[variable]` : The shared variable to access.

## Usage

Access a shared variable first defined in a [`SHARE`](SHARE.md) block.

Note that parentheses are not required for accessing submembers, so the
statement `SHARED message.length()` is valid if `std::string message` was
shared, for instance.

## Examples

The below example demonstrates how to access a shared variable throughout a test
suite.
``` C++
SUITE(Sharing) {
  SHARE {
    // The below variable is shared between all
    // test cases the setup and teardown code
    // over the life of the test suite
    Connection connection;
  };
  
  SETUP {
    SHARED connection = connect("somewhere");
  };
  
  TEARDOWN {
    SHARED connection.end();
  };
  
  TEST(response foo, "Test for a `foo` response.") {
    Response r = SHARED connection.get("foo");
    EXPECT r.status == Response::Status::foo;
  };
  
  TEST(response baz, "Test for a `baz` response.") {
    Response r = SHARED connection.get("baz");
    EXPECT r.status == Response::Status::baz;
  };
}
```

## See Also

- [`SHARE` macro](SHARE.md)
  - Share a set of variables in a test suite.
- [`SUITE` macro](SUITE.md)
  - Define a test suite.
- [Setting up and configuring a test suite tutorial](../../Tutorials/Test-Suite.md)
  - Learn to setup and configure a test suite, including sharing variables.
