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



/// Define the setup for a test suite.
/// \remarks
///   The body of the setup should be terminated by a semicolon.
///   Example:
///   ```
///   SUITE(MyTests) {
///     int someValue;
///     
///     SETUP {
///       someValue = 3;
///     };
///     
///     ...
///   }
///   ```
/// \sa SUITE(name)
#define SETUP \
  this->setup = [&]() -> void



/// Define the teardown for a test suite.
/// \remarks
///   The body of the setup should be terminated by a semicolon.
///   Example:
///   ```
///   SUITE(MyTests) {
///     Foo foo;
///     
///     TEARDOWN {
///       foo.cleanup();
///     };
///     
///     ...
///   }
///   ```
/// \sa SUITE(name)
#define TEARDOWN \
  this->teardown = [&]() -> void
