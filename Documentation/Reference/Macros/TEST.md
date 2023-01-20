# `TEST` macro

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
TEST([name], [description], [tags...]) {
  [contents]
};
```

## Parameters and Contents
- `[name]` : The name of the unit test case.
  Can include special characters and whitespace.
- `[description]` : A description of the unit test case.
  Used when displaying help.
- `[tags...]` : Optional.
  A set of tags used to group test cases together and control their execution.
  Notable tags that have special behavior are `skip` and `benchmark` which skip
  test cases from aggregate runs, such as when an entire test suite is specified
  to be run.
- `[contents]` : The contents of the test case including assertions and
  benchmarks.

## Usage

Creates and registers a test case inside of a test suite.

Test cases must be contained within test suites, freestanding test cases won't
compile.

Test case `[contents]` are treated like a normal code block, can contain
variable declaration, conditionals, etc., and are executed linearly.
The following are test control structures that can be used in test cases:
- Assertion macros, including `EXPECT`, `ASSERT`, `EXPECT_THAT`,
  `EXPECT_APPROX`, `EXPECT_EXCEPTION`, etc.
  A complete list of assertion macros can be found in the
  [Assertions article](../Assertions).
- Section macros in the form:
  ``` C++
  SECTION {
    ...
  };
  ```
  More information about test sections can be found under the
  [`SECTION` reference article](SECTION.md).
- Benchmark macros in the form:
  ``` C++
  BENCHMARK ...;
  
  BENCHMARK {
    ...
  }
  ```
  More information about benchmarks can be found under the
  [`BENCHMARK` reference article](BENCHMARK.md).

## Examples

The below example demonstrates a simple test suite with a single test case and
a single assertion ([`EXPECT`](../Assertions/EXPECT.md)).
``` C++
SUITE(MyTestSuite) {
  TEST(a test case, "A description.") {
    EXPECT foo() == x;
  };
}
```

The below example includes a variety of tags for grouping together and
categorizing test cases.
``` C++
SUITE(Tags) {
  TEST(test foo, "Test the `foo` function.", small-test) {
    EXPECT foo() == 3;
  };
  
  TEST(test timeout, "Test the `timeout` function.", big-test, skip, throws) {
    EXPECT_EXCEPTION(TimeoutException) { timeout(1000) };
  };
  
  TEST(benchmark baz, "Benchmark the `baz` function.", benchmark) {
    BENCHMARK baz(23);
  };
}
```

The below example includes sections and a non-linear flow.
``` C++
SUITE(Tests) {
  TEST(my test, "Run a non-straight-forward test.") {
    int n[] { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
    
    // Run an isolated section that doesn't affect the execution of the rest of
    // the test case
    SECTION {
      std::vector<int> fibList = fibonacciList(10);
      // If the below assertion fails, only the section will stop executing,
      // not the whole test case
      ASSERT fibList.size() == 10;
      for (int i = 0; i < 10; i++)
        EXPECT fibList[i] == n[i];
    };
    
    // Run a loop to test a variety of values
    for (int i = 0; i < 10; i++)
      EXPECT fibonacci(i) == n[i]
        | MESSAGE "fib(" << i << ") != " << n[i] << ".";
        // The actual failure message itself (including the contents of the two
        // tested values) will be printed after the above message, it just
        // provides context
    
  };
}
```

## See Also

- [`SUITE` macro](SUITE.md)
  - Declare a test suite in which test cases can be declared.
- [Assertions](../Assertions)
  - A list of all the different assertion macros that can be used inside of test
    cases.
- [`SECTION` macro](SECTION.md)
  - Define subsections of a test case.
- [`BENCHMARK` macro](BENCHMARK.md)
  - Run a micro benchmark inside a test case.
- [`Test` class](../Types/Test.md)
  - Configure and manage a test case instance.
- [Creating a test case tutorial](../../Tutorials/Intro/TestCase.md)
  - Learn to setup and run a test case.
