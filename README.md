# Expect

A small C++ unit testing library that allows for the creation of organized,
readable, and easy-to-write unit test cases for your code.

## Jump to...
- [Features](#Features)
- [Examples](#Examples)
- [Quick Start](#Quick-Start)
- [Documentation](#Documentation)
- [Expect](#Expect)

## Features

- Intuitive syntax
  - Assertions expressions can be written as they normally would be without using a variety of different macros, maintaining readability and ease of writing
- Matchers
  - Form compound statements that can be used to evaluate a value
- A variety of floating-point comparison utilities
- Customizable variable descriptions, comparators, matchers, failure messages, and output handlers
- Fatal and non-fatal assertions
- Micro benchmarking
- Just one header file to include, and one source file to build


## Examples
---

A simple unit test case:
``` C++
SUITE(MyTestSuite) {
  TEST(my test, "Test the `foo(...)` function.") {
    EXPECT foo(3) == 1 * 3;
    EXPECT foo(5) == 1 * 3 * 5;
    EXPECT foo(7) == 1 * 3 * 5 * 7;
    //            ↑
    // No need to use various comparison macros,
    // just write your expression as you normally
    // would and Expect will handle the rest
  };
}
```

Use matchers for compound expectations:
``` C++
SUITE(Matchers) {
  TEST(my test 2, "Test the `faz(...)` function.") {
    EXPECT_THAT faz(1, 3, 5) | hasLength(3) and elements(1, 3, 5);
  };
}
```

Compare floating-point numbers within bounds:
``` C++
SUITE(FloatingPoint) {
  TEST(within, "Check that two numbers are within ε of each other.") {
    EXPECT_WITHIN 1.000001 == 1.00002;
  };
  
  TEST(approx, "Check that two numbers are approximately within 0.001 of each other.") {
    EXPECT_APPROX 1.000001 == 1.00002 | 0.001;
     // Set the desired comparison precision ↖︎
  };
}
```

Share common variables between tests:
``` C++
SUITE(Sharing) {
  SHARE {
    Connection connection;
  };
  
  SETUP {
    SHARED connection = connect("somewhere");
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
  
  TEARDOWN {
    SHARED connection.end();
  };
}
```

A small benchmark:
``` C++
SUITE(SomeBenchmarks) {
  // We can tag the test as a benchmark so it won't be run
  // when we only want to run unit tests      ↓
  TEST(benchmark foo, "Benchmark `foo()`.", benchmark) {
    BENCHMARK foo();
  };
  
  TEST(benchmark, "Benchmark some code.", benchmark) {
    BENCHMARK {
      int y = x();
      int z = foo(y);
    }
  };
}
```

## Quick Start

After cloning the repository include the `Include/Expect` header file in your test file(s).
Build the `Source/Expect.cpp` file if you want to use your own test driver or build the `Source/AutoExpect.cpp` file if you want to use the built-in command-line driver with your unit test files.

Done!
Now you can start writing and executing unit tests and benchmarks.

Entire test suites can be ran by specifying the suite names when running the command line driver, or individual tests can be ran by specifying the test case names.
If you tag any test cases, all test cases corresponding with that tag can be ran by specifying the tag name and prefixing it with a `#`.
For example, if you tag benchmarks with the `benchmark` tag and want to run all benchmarks, include `#benchmark` when running your unit tests using the command line driver.

## Documentation

The [Documentation](Documentation) folder contains thorough documentation for the entire Expect library.

A general reference for the Expect library can be found in [Documentation/Reference](Documentation/Reference).

An overview of building can be found under [Documentation/Building](Documentation/Building.md) and running Expect under [Documentation/Running](Documentation/Running.md).

## Expect

© 2023 Michael Bykov

The Expect library is published under an MIT license that can be found in [LICENSE](LICENSE).

Issues and feature requests can be submitted under the [issues tab](https://github.com/MichaelBykov/Expect/issues) of this repository.

Contributions are welcome, accepted, and encouraged.
