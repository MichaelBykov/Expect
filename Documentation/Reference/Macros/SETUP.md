# `SETUP` macro

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
SETUP {
  [contents]
};
```

## Parameters and Contents
- `[contents]` : The setup code for the test suite, including initializing
  shared variables.

## Usage

Setup a test suite.

The `SETUP` block is run once before the test cases of a test suite are ran.
If no tests are selected to be run in a test suite with a `SETUP` block, the
`SETUP` block won't be run.

It is typical, although not required, for a [`TEARDOWN`](TEARDOWN.md) block to
accompany a `SETUP` block to perform any cleanup necessary once the test suite
has finished running.

Note that a `SETUP` block must be accompanied by a [`SHARE`](SHARE.md) block
before it.

Only one `SETUP` block can be declared in a test suite.
Instead of declaring two `SETUP` blocks in a test suite, merge them together.

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
- [`SHARED` macro](SHARED.md)
  - Access a shared variable.
- [`TEARDOWN` macro](TEARDOWN.md)
  - Define teardown code for a test suite.
- [`SUITE` macro](SUITE.md)
  - Define a test suite.
- [Setting up and configuring a test suite tutorial](../../Tutorials/Intro/TestSuite.md)
  - Learn to setup and configure a test suite, including sharing variables.
