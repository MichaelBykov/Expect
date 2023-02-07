# Building Expect

A guide to the various ways of building Expect.

## Jump to...
- [Overview](#Overview)
- [Building](#Building)
- [See Also](#See-Also)

## Overview

Expect, like many C++ programs, is composed of a collection of C++ header and
source files.

There is a single amalgamated header file that can be conveniently included in
any of your testing code located at `Include/Expect` (no extension).
It is typically sufficient to just add the `Include` directory in the include
paths for your test library.
Doing so allows your testing code to simply reference `#include <Expect>` to
include the Expect testing library.

Similar to the header files, the C++ source files come in two amalgamated
versions, `Source/Expect.cpp` and `Source/AutoExpect.cpp`.
`Expect.cpp` includes all the source files necessary in order to be able to
build and use the Expect unit testing library.
`AutoExpect.cpp` is the same as `Expect.cpp` but also includes a default
command-line test driver, meaning you do not need to add a `main` function in
your testing code, Expect handles it for you.

## Building

Building the Expect library requires taking the appropriate amalgamated source
file and building it as a dynamic library using your existing build system.
For example, if you are using CMake, the following build commands would suffice.
``` CMake
# Build the standalone Expect library
add_library(Expect ${EXPECT_DIR}/Source/Expect.cpp)

# Build the Expect library with the default test driver
add_library(AutoExpect ${EXPECT_DIR}/Source/AutoExpect.cpp)
```
Where `${EXPECT_DIR}` is the location where you cloned the Expect repository.
Expect requires support for the C++11 standard when being built and used.
It is also a good idea to add the Expect `Include` path to your C++ include
directories.
For example, if you are using CMake, the following would work.
``` CMake
include_directories(${EXPECT_DIR}/Include)
```

Once the library has been built by your build system, all you have to do is link
it to any of your testing executables that use the Expect library.
For example, if you are using CMake, the below example demonstrates linking the
AutoExpect library to a test executable called NumberTests.
``` CMake
# The test executable - contains all your test code
add_executable(NumberTests
  Tests/Number/Add.cpp
  Tests/Number/Subtract.cpp
  Tests/Number/Multiply.cpp)

# Link your executable to AutoExpect
target_link_libraries(NumberTests AutoExpect)
```
If you link your test executable to the standard Expect library
(not AutoExpect), make sure to also include a test driver with your executable.

## See Also

- [Quick Start](Quick-Start.md)
  - A guide to quickly setup and start using Expect.
- [Running](Running.md)
  - A guide to the various ways of running Expect.
