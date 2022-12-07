// ===--- Suite.h ------------------------------------------------ C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for test suites.                                             //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Test/Test.h>
#include <vector>

START_NAMESPACE_EXPECT



/// A testing suite.
struct Suite {
  /// A list of all tests in the test suite.
  std::vector<Test> tests = { };
  
  /// The test suite setup function
  std::function<void()> setup = nullptr;
  
  /// The test suite teardown function
  std::function<void()> teardown = nullptr;
  
  /// The name of the test suite.
  const char *name;
  
  
  
  /// Create and register a new test suite instance.
  /// \param[in] name
  ///   The name of the test suite.
  /// \param[in] suite
  ///   A pointer to the test suite instance.
  Suite(
    const char *name ,
    Suite      *suite
  );
};



/// Get a list of all registered test suites.
std::vector<Suite *> &suites();



END_NAMESPACE_EXPECT



/// Define a test suite.
/// \param name
///   The name of the test suite.
/// \remarks
///   A test suite should have a body with its test cases.
///   Example:
///   ```
///   SUITE(MySuite) {
///     TEST(MyTest, "Example.") {
///       ...
///     };
///   }
///   ```
#define SUITE(name) \
  START_NAMESPACE_EXPECT namespace Suites { \
  struct TestSuite##name : NAMESPACE_EXPECT Suite { \
    TestSuite##name(); \
  }; \
  static TestSuite##name testSuite##name = { }; \
  } END_NAMESPACE_EXPECT \
  Expect::Suites::TestSuite##name::TestSuite##name() : \
    NAMESPACE_EXPECT Suite(#name, &Expect::Suites::testSuite##name)
