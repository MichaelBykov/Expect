// ===--- Section.cpp -------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Implement test subsections.                                                //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Evaluate/Section.h>
#include <Global/Environment.h>

void NAMESPACE_EXPECT Section::operator << (std::function<void()> body) {
  try {
    body();
  } catch (TestFailedException) { }
}
