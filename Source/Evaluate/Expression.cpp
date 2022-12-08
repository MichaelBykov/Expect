// ===--- Expression.cpp ----------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Specializations for assertion expressions.                                 //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Evaluate/Expression.h>



TEST_CUSTOM_COMPARE(char *, Equal) {
  return strcmp(lhs, rhs) == 0;
}

TEST_CUSTOM_COMPARE(char *, NotEqual) {
  return strcmp(lhs, rhs) != 0;
}

TEST_CUSTOM_COMPARE(char *, Less) {
  return strcmp(lhs, rhs) < 0;
}

TEST_CUSTOM_COMPARE(char *, LessEqual) {
  return strcmp(lhs, rhs) <= 0;
}

TEST_CUSTOM_COMPARE(char *, Greater) {
  return strcmp(lhs, rhs) > 0;
}

TEST_CUSTOM_COMPARE(char *, GreaterEqual) {
  return strcmp(lhs, rhs) >= 0;
}



TEST_CUSTOM_COMPARE(const char *, Equal) {
  return strcmp(lhs, rhs) == 0;
}

TEST_CUSTOM_COMPARE(const char *, NotEqual) {
  return strcmp(lhs, rhs) != 0;
}

TEST_CUSTOM_COMPARE(const char *, Less) {
  return strcmp(lhs, rhs) < 0;
}

TEST_CUSTOM_COMPARE(const char *, LessEqual) {
  return strcmp(lhs, rhs) <= 0;
}

TEST_CUSTOM_COMPARE(const char *, Greater) {
  return strcmp(lhs, rhs) > 0;
}

TEST_CUSTOM_COMPARE(const char *, GreaterEqual) {
  return strcmp(lhs, rhs) >= 0;
}
