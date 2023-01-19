// ===--- Suite.cpp ---------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Implementation of the test suite interface.                                //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Suite/Suite.h>

std::vector<NAMESPACE_EXPECT Suite *> &NAMESPACE_EXPECT suites() {
  static std::vector<NAMESPACE_EXPECT Suite *> suites = { };
  return suites;
}

NAMESPACE_EXPECT Suite::Suite(
  const char *name ,
  Suite      *suite
) : name(name) {
  suites().push_back(suite);
}
