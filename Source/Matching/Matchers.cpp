// ===--- Matchers.cpp ------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The implementations of default matchers.                                   //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Matching/Matchers.h>
USE_EXPECT_MATCHING

template<>
bool BeginsWith<const char *>::evaluate(const char *value) {
  const char *lhs = substring, *rhs = value;
  while (*lhs == *rhs && *lhs != '\0') lhs++, rhs++;
  return *lhs == '\0';
}

template<>
bool BeginsWith<std::string>::evaluate(std::string value) {
  const char *lhs = substring.c_str(), *rhs = value.c_str();
  while (*lhs == *rhs && *lhs != '\0') lhs++, rhs++;
  return *lhs == '\0';
}

template<>
bool EndsWith<const char *>::evaluate(const char *value) {
  size_t length = strlen(value);
  size_t endLength = strlen(substring);
  if (length < endLength)
    return false;
  const char *lhs = value + length - 1, *rhs = substring + endLength - 1;
  for (size_t i = 0; i < endLength; i++)
    if (*lhs-- != *rhs--)
      return false;
  return true;
}

template<>
bool EndsWith<std::string>::evaluate(std::string value) {
  size_t length = value.length();
  size_t endLength = substring.length();
  if (length < endLength)
    return false;
  const char *lhs = value.c_str() + length - 1;
  const char *rhs = substring.c_str() + endLength - 1;
  for (size_t i = 0; i < endLength; i++)
    if (*lhs-- != *rhs--)
      return false;
  return true;
}

template<>
struct Contains<const char *, const char *> : ::NAMESPACE_EXPECT Matcher<const char *, Contains<const char *, const char *>> {
  const char *substring;
  
  Contains<const char *, const char *>(const char *substring)
    : substring(substring) { }
  
  bool evaluate(const char *value) {
    for (size_t i = 0; value[i] != '\0'; i++) {
      const char *lhs = substring, *rhs = value + i;
      while (*lhs == *rhs && *lhs != '\0') lhs++, rhs++;
      if (*lhs == '\0')
        return true;
    }
    return false;
  }
  
  std::string message(const char *value, bool succeeded) {
    if (succeeded)
      return MESSAGE "Contains " << substring << ".";
    else
      return MESSAGE "Doesn't contain " << substring << ".";
  }
};

template<>
MATCHER_RESULT(const char *) ::NAMESPACE_EXPECT Matchers::contains<const char *, const char *>(const char *substring) {
  return Contains<const char *, const char *>(substring);
}

template<>
struct Contains<std::string, std::string> : ::NAMESPACE_EXPECT Matcher<std::string, Contains<std::string, std::string>> {
  std::string substring;
  
  Contains<std::string, std::string>(std::string substring)
    : substring(substring) { }
  
  bool evaluate(std::string value) {
    for (size_t i = 0; value[i] != '\0'; i++) {
      const char *lhs = substring.c_str(), *rhs = value.c_str() + i;
      while (*lhs == *rhs && *lhs != '\0') lhs++, rhs++;
      if (*lhs == '\0')
        return true;
    }
    return false;
  }
  
  std::string message(std::string value, bool succeeded) {
    if (succeeded)
      return MESSAGE "Contains " << substring << ".";
    else
      return MESSAGE "Doesn't contain " << substring << ".";
  }
};

template<>
MATCHER_RESULT(std::string) ::NAMESPACE_EXPECT Matchers::contains<std::string, std::string>(std::string substring) {
  return Contains<std::string, std::string>(substring);
}
