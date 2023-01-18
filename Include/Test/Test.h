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
#include <Global/Iterate.h>
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
    /// \param[in] tags
    ///   A set of tags associated with the unit test.
    Add(
      std::vector<Test> *tests      ,
      const char        *name       ,
      const char        *description,
      std::vector<const char *> tags
    );
    
    /// Add a test driver to the unit test case.
    /// \param[in] body
    ///   The body of the unit test case driver.
    void operator, (std::function<void(Environment &)> body);
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
  
  /// The test tags.
  std::vector<const char *> tags;
};



END_NAMESPACE_EXPECT



/// Define a unit test case.
/// \param name
///   The name of the test case.
/// \param description
///   A description of the unit test used when displaying help.
/// \param ...
///   A list of all of the tags associated with the test case.
///   Specially handled tags are `benchmark`, and `skip`.
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
#define TEST(name, description, ...) \
  NAMESPACE_EXPECT Test::Add(&tests, #name, description, \
    { _EXPECT_STRINGIFY_ARGS(__VA_ARGS__) }), \
    [=](NAMESPACE_EXPECT Environment &__environment) -> void
