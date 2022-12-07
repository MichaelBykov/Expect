// ===--- Test.cpp ----------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Implementation of the unit test case interface.                            //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Test/Test.h>

NAMESPACE_EXPECT Test::Add::Add(
  std::vector<Test> *tests      ,
  const char        *name       ,
  const char        *description
) {
  Test test { name, description, nullptr, false };
  tests->push_back(test);
  this->test = &tests->at(tests->size() - 1);
}

void NAMESPACE_EXPECT Test::Add::operator, (void (*body)(Environment &)) {
  test->test = body;
}
