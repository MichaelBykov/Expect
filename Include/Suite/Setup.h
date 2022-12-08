// ===--- Suite.h ------------------------------------------------ C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
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
  this->setup = [=]() -> void



START_NAMESPACE_EXPECT



/// A set of functions to teardown a test suite.
struct Teardown {
  /// The user-defined teardown function.
  std::function<void()> teardown;
  
  /// The library-defined teardown code to be run after the user defined
  /// teardown function, `teardown`.
  std::function<void()> cleanup;
  
  /// Create a teardown helper by passing the library-defined teardown code.
  Teardown(std::function<void()> cleanup) : cleanup(cleanup) { }
  
  /// Add user-defined teardown code to the teardown helper.
  /// \param[in] teardown
  ///   The user-defined teardown code.
  /// \returns
  ///   A full teardown helper object for storage in a test suite.
  Teardown *operator << (std::function<void()> teardown) {
    this->teardown = teardown;
    return new Teardown(*this);
  }
};



END_NAMESPACE_EXPECT



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
///     TEARDOWN {
///       SHARED foo.cleanup();
///     };
///     
///     ...
///   }
///   ```
/// \sa SUITE(name)
#define TEARDOWN \
  this->teardown = NAMESPACE_EXPECT Teardown([=]() { delete shared; }) << \
    [=]() -> void
