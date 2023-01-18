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
  const char        *description,
  std::vector<const char *> tags
) {
  tags.erase(std::remove_if(tags.begin(), tags.end(), [](const char *element) {
    return *element == '\0';
  }), tags.end());
  Test test { name, description, nullptr, false, tags };
  tests->push_back(test);
  this->test = &tests->at(tests->size() - 1);
}

void NAMESPACE_EXPECT Test::Add::operator, (
  std::function<void(Environment &)> body
) {
  test->test = body;
}
