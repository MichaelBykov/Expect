// ===--- ExactExpression.cpp ------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Specializations for assertion expressions.                                 //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Expression/ExactExpression.h>



TEST_CUSTOM_COMPARE(bool          , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(char          , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(short         , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(int           , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(long          , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(unsigned char , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(unsigned short, Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(unsigned int  , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(unsigned long , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(float         , Exact, Value) { return value; }
TEST_CUSTOM_COMPARE(double        , Exact, Value) { return value; }



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
