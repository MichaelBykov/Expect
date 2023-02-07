// ===--- Suite.h ------------------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for test suites setup/teardown.                              //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include "Suite.h"
#include <functional>



/// Share a set of mutable values in a test suite.
/// \remarks
///   The body of the shared block should be terminated by a semicolon.
///   Example:
///   ```
///   SUITE(MyTests) {
///     SHARED {
///       int someValue;
///     };
///     
///     SETUP {
///       someValue = 3;
///     };
///     
///     TEST(example, "An example test case.") {
///       int foo = SHARED someValue * 10;
///       ...
///     };
///   }
///   ```
#define SHARE \
  struct __Shared

/// Access a shared value in a test suite.
#define SHARED shared->



/// Define the setup for a test suite.
/// \remarks
///   The body of the setup should be terminated by a semicolon.
///   Any shared setup values should first be defined in a `SHARED` block.
///   Example:
///   ```
///   SUITE(MyTests) {
///     SHARED {
///       int someValue;
///     };
///     
///     SETUP {
///       SHARED someValue = 3;
///     };
///     
///     ...
///   }
///   ```
/// \sa SUITE(name)
/// \sa SHARED
#define SETUP \
  __Shared *shared = new __Shared(); \
  this->cleanup = [=]() { delete shared; }; \
  this->setup = [=]() -> void



/// Define the teardown for a test suite.
/// \remarks
///   The body of the teardown should be terminated by a semicolon.
///   Any shared teardown values should first be defined in a `SHARED` block.
///   Example:
///   ```
///   SUITE(MyTests) {
///     SHARED {
///       Foo foo;
///     };
///     
///     SHARED ...
///     
///     TEARDOWN {
///       SHARED foo.cleanup();
///     };
///     
///     ...
///   }
///   ```
/// \sa SUITE(name)
#define TEARDOWN \
  this->teardown = [=]() -> void
