// ===--- Test.h ------------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for unit test cases.                                         //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Global/Environment.h>
#include <vector>
#include <functional>

START_NAMESPACE_EXPECT



/// A unit test case.
struct Test {
  /// A helper struct to add unit tests using the `TEST(...)` macro
  struct Add {
    /// A pointer to the created test.
    Test *test;
    
    /// Create a new unit test case.
    /// \param[inout] tests
    ///   The list of tests in which this test case should be recorded.
    /// \param[in] name
    ///   The name of the unit test.
    /// \param[in] description
    ///   A description of the unit test.
    Add(
      std::vector<Test> *tests      ,
      const char        *name       ,
      const char        *description
    );
    
    /// Add a test driver to the unit test case.
    /// \param[in] body
    ///   The body of the unit test case driver.
    void operator, (void (*body)(Environment &));
  };
  
  /// The name of the unit test.
  const char *name;
  
  /// A description of the unit test.
  /// \remarks
  ///   Used in help messages.
  const char *description;
  
  /// The test driver.
  std::function<void(Environment &)> test;
  
  /// Whether or not the unit test should be ran.
  bool enabled;
};



END_NAMESPACE_EXPECT



/// Define a unit test case.
/// \param name
///   The name of the test case.
/// \param description
///   A description of the unit test used when displaying help.
/// \remarks
///   The body of the test case should be terminated by a semicolon.
///   Example:
///   ```
///   TEST(MyTest, "Test the `myTest` function.") {
///     ...
///   };
///   ```
///   All test cases should be enclosed in a test suite.
/// \sa SUITE(name)
#define TEST(name, description) \
  NAMESPACE_EXPECT Test::Add(&tests, #name, description), \
    [&](Environment &__environment) -> void
