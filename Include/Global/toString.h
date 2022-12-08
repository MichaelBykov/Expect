// ===--- toString.h --------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for string conversion of types.                              //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <string>

START_NAMESPACE_EXPECT



/// Convert a testing value to a string to output for errors.
/// \param[in] value
///   The value to convert.
/// \returns
///   A string representation of the given value.
template<typename T>
std::string toString(const T value) {
  char string[14 + 2 * sizeof(T *)] = "";
  int index;
  uint64_t address;
  if (std::is_pointer<T>::value) {
    // Display the pointer itself
    std::strcpy(string, "<0x");
    index = 3;
    address = (uint64_t)value;
  } else {
    // Display a pointer to the given type
    std::strcpy(string, "<value at 0x");
    index = 12;
    address = (uint64_t)&value;
  }
  for (int i = 2 * sizeof(T *) - 1; i >= 0; i--) {
    int nibble = (address >> 4 * i) & 0b1111;
    if (nibble >= 10)
      string[index++] = 'A' + nibble - 10;
    else
      string[index++] = '0' + nibble;
  }
  string[index++] = '>';
  string[index] = 0;
  return string;
}



END_NAMESPACE_EXPECT



/// Define a stringification of a type used in testing.
/// \param type
///   The type for which to define a string conversion.
/// \param name
///   The name to use for the stringified function.
/// \remarks
///   Example usage:
///   ```
///   TEST_STRINGIFY(int, value) {
///     return std::to_string(value);
///   }
///   ```
///   
///   If you are using a stringification of a type in more than one file, make
///   sure to define the specialization in a shared header, for example,
///   `TEST_STRINGIFY(int, value);` for the above example, to avoid duplicate
///   code errors when compiling.
#define TEST_STRINGIFY(type, name) \
  template<> \
  std::string NAMESPACE_EXPECT toString(const type name)



// Implement the standard types
TEST_STRINGIFY(char     , value);
TEST_STRINGIFY(short    , value);
TEST_STRINGIFY(int      , value);
TEST_STRINGIFY(long     , value);
TEST_STRINGIFY(long long, value);

TEST_STRINGIFY(unsigned char     , value);
TEST_STRINGIFY(unsigned short    , value);
TEST_STRINGIFY(unsigned int      , value);
TEST_STRINGIFY(unsigned long     , value);
TEST_STRINGIFY(unsigned long long, value);

TEST_STRINGIFY(float      , value);
TEST_STRINGIFY(double     , value);
TEST_STRINGIFY(long double, value);

TEST_STRINGIFY(std::string &, value);
TEST_STRINGIFY(char *, value);
