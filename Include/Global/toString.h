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
#include <Global/Iterate.h>
#include <string>

START_NAMESPACE_EXPECT



template<typename T>
struct ToString {
  static std::string convert(const T value) {
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
};


/// Convert a testing value to a string to output for errors.
/// \param[in] value
///   The value to convert.
/// \returns
///   A string representation of the given value.
template<typename T>
std::string toString(const T value) {
  return ToString<T>::convert(value);
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



#define _TEST_STRINGIFY_GET_TYPE_2(type) type
#define _TEST_STRINGIFY_GET_TYPE_EACH(type) type,
#define _TEST_STRINGIFY_GENERIC_TYPE(...) _EXPECT_ITERATE_2( \
  _EXPECT_ITERATE_PASS, \
  _TEST_STRINGIFY_GET_TYPE_2, _TEST_STRINGIFY_EACH, __VA_ARGS__)

#define _TEST_STRINGIFY_GET_VALUE_1(value) value
#define _TEST_STRINGIFY_GENERIC_VALUE(...) _EXPECT_ITERATE_1( \
  _TEST_STRINGIFY_GET_VALUE_1, _EXPECT_ITERATE_PASS, __VA_ARGS__)

#define TEST_STRINGIFY_GENERIC(...) \
  struct NAMESPACE_EXPECT \
    ToString<_TEST_STRINGIFY_GENERIC_TYPE(__VA_ARGS__)> { \
    static std::string convert( \
      const _TEST_STRINGIFY_GENERIC_TYPE (__VA_ARGS__) \
            _TEST_STRINGIFY_GENERIC_VALUE(__VA_ARGS__) \
    )
#define TEST_STRINGIFY_GENERIC_END \
  };





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



/// Implement the standard template types
template<typename T>
TEST_STRINGIFY_GENERIC(std::vector<T>, vector) {
  if (vector.empty())
    return "{ }";
  else if (vector.size() < 10) {
    std::string string = "{ ";
    bool first = true;
    for (T element : vector) {
      if (first)
        first = false;
      else
        string += ", ";
      string += toString(element);
    }
    return string + " }";
  } else {
    std::string string = "{ ";
    size_t index = 0, start = 5, end = vector.size() - 3;
    for (T element : vector) {
      if (index < start) {
        if (index > 0)
          string += ", ";
        string += toString(element);
      } else if (index == start)
        string += " ... ";
      else if (index >= end) {
        if (index > end)
          string += ", ";
        string += toString(element);
      }
      index++;
    }
    return string + " }";
  }
} TEST_STRINGIFY_GENERIC_END
