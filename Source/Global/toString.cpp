// ===--- toString.cpp ------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// Implementation of the string conversions of a set of standard types.       //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Global/toString.h>



TEST_STRINGIFY(char, value) {
  char string[2] { value, 0 };
  return string;
}

TEST_STRINGIFY(short, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(int, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(long, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(long long, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(unsigned char, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(unsigned short, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(unsigned int, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(unsigned long, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(unsigned long long, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(float, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(double, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(long double, value) {
  return std::to_string(value);
}

TEST_STRINGIFY(std::string, string) {
  return std::string("\"").append(string).append("\"");
}

TEST_STRINGIFY(std::string &, string) {
  return std::string("\"").append(string).append("\"");
}

TEST_STRINGIFY(char *, string) {
  return std::string("\"").append(string).append("\"");
}

TEST_STRINGIFY(bool, value) {
  return value ? "true" : "false";
}

TEST_STRINGIFY(nullptr_t, value) {
  return "<null>";
}
