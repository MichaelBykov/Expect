# `EXPECT` macro / `ASSERT` macro

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
EXPECT [expression];

EXPECT [expression] | [message];

ASSERT [expression];

ASSERT [expression] | [message];
```

## Parameters and Contents
- `[expression]` : The expression to evaluate

## Usage

Define an assertion expression.

`EXPECT` is non-fatal and will not stop the test case from continuing to run.

`ASSERT` is fatal and will stop the test case case from continuing to run.

Expectations can be set for any comparison, for example,
`EXPECT a == b`, `EXPECT a < b`, and `EXPECT a != b` are all valid and.
Expectations can also accept range expressions in the form
`lower < value < upper`, where `lower` is the lower bound, `upper` is the upper
bound, and `value` is the value being tested.
Range expressions can be formed by any combination of `<` and `<=`, for example,
`EXPECT 1 < 2 <= 3`, `EXPECT 0 <= 0 < 1`, or `EXPECT 1 <= 1 <= 1`.
Range expressions can be built for any type that has the appropriate comparison
operators `<`, `<=` as used in the range expression.
Expectations can also be set for an expression that evaluates to a boolean,
for example, `EXPECT isTrue()` or `EXPECT !someValue` are valid.

All arguments in an expression will be extracted and displayed upon an assertion
failure.
For a binary expression (`==`, `!=`, `<`, `>`, `<=`, `>=`), the left-hand-side
and right-hand-side of the expression will be displayed, for instance,
`EXPECT 2 == 3` will produce the error message, `2 is not equal to 3`.
For a range expression, the bounds and the tested value will all be displayed,
for instance, `EXPECT 2 < 0 < 5` will produce the error message
`0 is not in the range of 2, 5 (exclusive).`.

A message can be passed to the assertion that is either a string or a message
builder from the [`MESSAGE`](../Macros/MESSAGE.md) macro.
The message will be displayed when the assertion fails in front of the standard
failure message.
Messages are separated from the main expression by a vertical bar (`|`).
Any amount of separate messages can be chained together after the expression
separated by the vertical bars.
For instance, `EXPECT false | "hello" | MESSAGE " " | "world!";` will display
`hello world! (Result evaluated to false.)`.

## Examples

The below example includes various valid expressions
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
- [Setting up and configuring a test suite tutorial](../../Tutorials/Test-Suite.md)
  - Learn to setup and configure a test suite, including sharing variables.
