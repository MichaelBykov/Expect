# `SUITE` macro

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
SUITE([name]) {
  [contents]
}
```

## Parameters and Contents
- `[name]` : The unique name of the suite that should be in the form a standard
  type name. Suite names do not support special characters, literals, or
  anything other than a single identifier. Note that unlike identifiers, a suite
  name can start with an integer.
- `[contents]` : The contents of the test suite which includes unit test cases,
  shared constants, shared variables, setup, and teardown code, or any
  combination of the aforementioned.

## Usage

Creates and registers a test suite to run test cases.

Test suites can include any of the following in their `[contents]` area:
- Unit test cases in the form:
  ``` C++
  TEST(...) {
    ...
  };
  ```
  More information about test cases can be found under the
  [`TEST` reference article](TEST.md).
- Shared constants can be declared inside a test suite by simply declaring them
  as a variable before using them inside test cases, setup, tear down, or shared
  variables.
- Shared variables can be declared by using the `SHARED` macro,
  ``` C++
  SHARED {
    /* shared variables are declared here */
  };
  ```
  More information about shared variables can be found under the
  [`SHARED` reference article](SHARED.md).
- setup or teardown code by using the `SETUP` and `TEARDOWN` macros,
  respectively,
  ``` C++
  SETUP {
    ...
  };
  TEARDOWN {
    ...
  };
  ```
  More information about setup and teardown code can be found under the
  [`SETUP` reference article](SETUP.md) and
  [`TEARDOWN` reference article](TEARDOWN.md).

The contents of a test suite is executed as a standard code block meaning that
arbitrary statements can be used inside of it including, for example,
conditionally including tests by placing them inside conditionals or replicating
a test by placing it inside a loop.
Note that the contents of a test suite are ran immediately upon application
startup.

## Examples

The below example demonstrates a simple test suite with a single test case.
``` C++
SUITE(MyTestSuite) {
  // Constants can be declared and used immediately
  int x = 3;
  
  TEST(a test case, "A description.") {
    EXPECT foo() == x;
  };
}
```

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
  
  // A common constant
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

- [`TEST` macro](TEST.md)
  - Define unit test cases inside a test suite.
- [`SHARE` macro](SHARE.md)
  - Share common variables throughout a test suite.
- [`SETUP` macro](SETUP.md)
  - Define setup code for a test suite.
- [`TEARDOWN` macro](TEARDOWN.md)
  - Define teardown code for a test suite.
- [`Suite` class](../Types/Suite.md)
  - Configure and manage a test suite instance.
- [`suites` global variable](../Variables/suites.md)
  - Manage all instances instances of test suites in the program.
- [Setting up and configuring a test suite tutorial](../../Tutorials/Test-Suite.md)
  - Learn to setup and configure a test suite.
