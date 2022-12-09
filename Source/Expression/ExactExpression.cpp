// ===--- ExactExpression.cpp ------------------------------------ C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Specializations for assertion expressions.                                 //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Expression/ExactExpression.h>



TEST_CUSTOM_COMPARE(char *, Exact, Equal) {
  return strcmp(lhs, rhs) == 0;
}

TEST_CUSTOM_COMPARE(char *, Exact, NotEqual) {
  return strcmp(lhs, rhs) != 0;
}

TEST_CUSTOM_COMPARE(char *, Exact, Less) {
  return strcmp(lhs, rhs) < 0;
}

TEST_CUSTOM_COMPARE(char *, Exact, LessEqual) {
  return strcmp(lhs, rhs) <= 0;
}

TEST_CUSTOM_COMPARE(char *, Exact, Greater) {
  return strcmp(lhs, rhs) > 0;
}

TEST_CUSTOM_COMPARE(char *, Exact, GreaterEqual) {
  return strcmp(lhs, rhs) >= 0;
}



TEST_CUSTOM_COMPARE(const char *, Exact, Equal) {
  return strcmp(lhs, rhs) == 0;
}

TEST_CUSTOM_COMPARE(const char *, Exact, NotEqual) {
  return strcmp(lhs, rhs) != 0;
}

TEST_CUSTOM_COMPARE(const char *, Exact, Less) {
  return strcmp(lhs, rhs) < 0;
}

TEST_CUSTOM_COMPARE(const char *, Exact, LessEqual) {
  return strcmp(lhs, rhs) <= 0;
}

TEST_CUSTOM_COMPARE(const char *, Exact, Greater) {
  return strcmp(lhs, rhs) > 0;
}

TEST_CUSTOM_COMPARE(const char *, Exact, GreaterEqual) {
  return strcmp(lhs, rhs) >= 0;
}
