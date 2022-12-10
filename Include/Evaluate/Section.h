// ===--- Section.h ---------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for test subsections.                                        //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <functional>

START_NAMESPACE_EXPECT



/// The driver for a subsection of a test case.
struct Section {
  /// Load and execute the body of a subsection.
  /// \param[in] body
  ///   The body of the subsection to execute.
  void operator << (std::function<void()> body);
};



END_NAMESPACE_EXPECT



/// Define an isolated subsection of a test case.
/// \remarks
///   Subsections allow for containing a set of related assertions that rely on
///   certain preconditions in order to be evaluated, for instance, when
///   checking thee elements of a list.
///   The contents of a section should be enclosed in curly braces.
///   Example:
///   ```
///   SECTION {
///     ASSERT count == 3;
///     for (int i = 0; i < 3; i++)
///       EXPECT list[i] == i;
///   };
///   ```
#define SECTION \
  NAMESPACE_EXPECT Section() << [&]() -> void
