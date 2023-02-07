# Quick Start

A guide to quickly setup and start using Expect.

## Jump to...
- [What is Expect](#What-is-Expect)
- [Installing](#Installing)
- [Setting Up](#Setting-Up)
- [Your First Test Case](#Your-First-Test-Case)
- [Running Your Tests](#Running-Your-Tests)
- [Going Further](#Going-Further)
- [See Also](#See-Also)

## What is Expect

Expect is a unit-testing and micro-benchmarking library.
It allows you to test your code using other code—automating testing and removing
the need to manually test your code whenever you make a change.
It also allows you to test the performance of your code, to see areas of your
codebase that need to be optimized, and to select between different
optimization.

## Installing

If you don't know what project you want to add Expect to, or if you don't have
any, start by creating a new project in the editor of your choice otherwise,
follow this tutorial from your project.

Expect can be installed directly from GitHub as a zip file by clicking the
green button in the top-right corner of the
[front page](https://github.com/MichaelBykov/Expect) or directly through
[https://github.com/MichaelBykov/Expect/archive/refs/heads/expect.zip](https://github.com/MichaelBykov/Expect/archive/refs/heads/expect.zip).
Unzip the folder and move the folder to either a specific place on your machine
where you will use it for all projects (remember the location), or somewhere in
your project, for instance in a `dependencies` folder.

If you have git installed on your machine, you can clone the repository directly
by using the following command in the directory where you want to install
Expect:
``` console
git clone https://github.com/MichaelBykov/Expect.git
```
A good place, as stated above, to clone Expect is to a `dependencies` folder in
your project if you don't have a specific place to put it.

If you are using an automated build system you may be able to have the build
system download Expect directly for you.
For example, the CMake commands below will download Expect for you in the build
folder:
``` CMake
include(FetchContent)
FetchContent_Declare(
  Expect
  GIT_REPOSITORY https://github.com/MichaelBykov/Expect.git
  GIT_TAG 1.0.0 # The version of Expect you want to use
)
FetchContent_MakeAvailable(Expect)
```

Alternatively, if you want to add unit testing to a codebase which is under
git source control, you can add Expect directly as a submodule using the
following git command in the root directory of your project:
``` console
git submodule add https://github.com/MichaelBykov/Expect.git
```
This will allow your project to be directly synced with Expect.

## Setting up

Once you have Expect installed, it's time to build it.
Using the build system of your choice, build Expect from inside your project.

The first step in building Expect requires you to add the main Expect `Include`
directory to your project's include directories.
In CMake, this involves the following command:
``` CMake
include_directories(${EXPECT_DIR}/Include)
```
where `${EXPECT_DIR}` is the location of your Expect installation.

The next step in building Expect requires adding just one file to your build
system as a standalone library, `Source/AutoExpect.cpp` from your Expect
download.
For instance, if you are using CMake, you can write:
``` CMake
add_library(AutoExpect ${EXPECT_DIR}/Source/AutoExpect.cpp)
```
where `${EXPECT_DIR}` is the location of your Expect installation.

If you downloaded Expect directly through CMake using `FetchContent`, you can
skip the all of the above and simply use `Expect::AutoExpect` when linking, as
discussed below.

Now that you have Expect built, you need to create a test executable for the
unit tests that you are going to write.

Create a file named `test.cpp` in a `test` folder in your project.
In your build system, add `test/test.cpp` to a standalone executable called
`MyTests`.
For instance, in CMake, you would have the below:
``` CMake
add_executable(MyTests test/test.cpp)
```
Link the Expect library that you build above to your test executable.
In CMake you would have the below:
``` CMake
add_executable(MyTests test/test.cpp)
target_link_libraries(MyTests AutoExpect)
```
(As mentioned above, if you downloaded Expect through CMake by using
`FetchContent`, you can use `Expect::AutoExpect` instead of `AutoExpect` and
CMake will do the rest for you.)

If you want to test a library you already have, make sure to link it to
`MyTests` too.

Check that your project built successfully and fix any errors that occurred.

## Your First Test Case

Now that you have Expect built, you can start adding test cases to your program!

Start by including the Expect library in your `test.cpp` file:
``` C++
#include <Expect>
```

Before we start testing, we need some code to test.
Add the below simple arithmetic function to your `test.cpp` file:
``` C++
int add(int x, int y) {
  return x + y;
}
```
This is the code you will be testing in this tutorial.

All unit test cases in Expect are organized using test suites.
A test suite is simply a collection of unit test cases and any data that they
all share.
This is discussed further in the [Creating a Test Suite](Test-Suite.md)
tutorial.

Defining a test suite in Expect involves using the `SUITE` macro and giving the
test suite a name.
For this example, we will be naming the test suite `MyFirstTests`.
Add the below code to your `test.cpp` file after your `#include` statement:
``` C++
SUITE(MyFirstTests) {
  
}
```
The above code defines a test suite named `MyFirstTests` and gives it a body.
Your test cases will go inside of the body (curly braces).

Test cases manage a single unit test that tests one specific thing.
Test cases are defined using the `TEST` macro and require a test name,
test description, and optionally a set of tags.
The test name is written without quotes but the test description is written
with quotes.
We want to start by testing the `add` function we defined above.
Add the following test case inside of your test suite as shown:
``` C++
SUITE(MyFirstTests) {
  TEST(add, "Test the add function.") {
    
  };
}
```
The above code defines a test case `add` inside of the test suite `MyFirstTests`
with a description of `"Test the add function."` and an empty body (the inside
set of curly braces).

The test case will be run whenever we want to make sure that `add` works the way
we want it to.

In order to define what behavior you want the `add` function to exhibit,
you can use assertions.
Assertions execute a specific expression that, if it evaluates to false, fails
the test case so that we know that something didn't go as expected.
To define an assertion use the `EXPECT` macro. The `ASSERT` macro can also be
used but it will stop the test case immediately upon failure so we won't be able
to see if we had any other assertions fail.
We want to add assertions that test basic behavior as well as edge cases for our
function.
Add the following code inside of your `add` test case:
``` C++
SUITE(MyFirstTests) {
  TEST(add, "Test the add function.") {
    // Test the basic functionality
    EXPECT add(1, 2) == 3; // 1 + 2 == 3
    EXPECT add(-10, 10) == 0; // -10 + 10 == 0
    EXPECT add(-50, -6) == -56; // -50 + -6 == -56
    
    // Test edge cases
    EXPECT add(100, 0) == 100; // + zero = itself
    EXPECT add(-100, 0) == -100; // + zero = itself
    EXPECT add(2147483647, 1) == -2147483648; // Overflow
    EXPECT add(-2147483648, -1) == 2147483647; // Underflow
  };
}
```
The above code sets expectations for what value the add function will produce
for various inputs by checking if it's equal to the value it should produce.

## Running Your Tests

Now that you have added a test case to your project, build it so that you have
a test executable you can run.
To run the test executable, add the name of the test suite you want to test
to run all of its test cases.
You can also specify individual test cases to run by name or tag if you added
tags to your test case.
If your test executable is in your build folder, you should be able to run the
following command to run your tests.
``` command
build/MyTests MyFirstTests
```
Note that if your command prompt's current directory is in the same folder as
your test executable, you can't call your test executable directly but must
instead prefix it with `./`, so you would have to call `./MyTests` for this
tutorial.

You should have the following output:
```
Running test suite MyFirstTests
  Running test add (1/1) ... success.
Successful: 1/1

All tests passed.
```
This tells us that our `add` function behaves exactly as we expected it to.

We can test how unit testing reports unexpected behavior by replacing our `add`
function with subtraction, as follows:
``` C++
int add(int x, int y) {
  return x - y;
}
```
If we run our unit tests now, we will have the following output:
```
Running test suite MyFirstTests
  Running test add (1/1) ... failure.
    Failure on line 10: `EXPECT add(1, 2) == 3; // 1 + 2 == 3`, -1 is not equal to 3.
    Failure on line 11: `EXPECT add(-10, 10) == 0; // -10 + 10 == 0`, -20 is not equal to 0.
    Failure on line 12: `EXPECT add(-50, -6) == -56; // -50 + -6 == -56`, -44 is not equal to -56.
    Failure on line 17: `EXPECT add(2147483647, 1) == -2147483648; // Overflow`, 2147483646 is not equal to -2147483648.
    Failure on line 18: `EXPECT add(-2147483648, -1) == 2147483647; // Overflow`, -2147483647 is not equal to 2147483647.
Successful: 0/1

1 tests failed.
```
Notice how the unit test run told us exactly where our expectations weren't
fulfilled and what value was actually produced.
We can now use this information to correct our `add` function so that it behaves
the way it needs to.

## Going Further

Now that you know how to create unit tests, you can apply this knowledge to
automate testing for all of your code.
It is generally considered good practice to write a test case for every function
or method you have to ensure that it works as intended and catch any bugs before
they become difficult to pinpoint.

You can create a test suite for every every class you have and a test case for
every method as well as test suites for free-standing functions.

More information about creating and managing test suites can be found in the
[Creating a Test Suite](Test-Suite.md) tutorial.

More information about creating a test case can be found in the
[Creating a Test Case](Test-Case.md) tutorial.

## See Also

- [Building](Building.md)
  - A guide to the various ways of building Expect.
- [Running](Running.md)
  - A guide to the various ways of running Expect.
- [Creating a Test Suite](Test-Suite.md)
  - A walkthrough of creating and configuring a test suite.
- [Creating a Test Case](Test-Case.md)
  - A walkthrough of setting up a test case.
- [Using Assertions](Using-Assertions.md)
  - A guided walkthrough of all the different assertions.
- [Using Matchers](Using-Matchers.md)
  - A guided walkthrough of using matchers.
