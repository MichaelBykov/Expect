// ===--- StringBuilder.h ---------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for a stream-like string builder.                            //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include "toString.h"

START_NAMESPACE_EXPECT



/// A string builder for creating messages from different types.
struct StringBuilder {
  /// The constructed message.
  std::string message;
  
  /// Extract the message contents.
  operator std::string() {
    return message;
  }
  
  /// Append a string to the message builder.
  /// \param[in] message
  ///   The string to append.
  StringBuilder &operator << (const char *message) {
    this->message = this->message.append(message);
    return *this;
  }
  
  /// Append a string to the message builder.
  /// \param[in] message
  ///   The string to append.
  StringBuilder &operator << (std::string &message) {
    this->message = this->message.append(message);
    return *this;
  }
  
  /// Append a generic value to the message builder.
  /// \param[in] message
  ///   The value to append.
  ///   Should have a toString conversion defined for it.
  /// \sa TEST_STRINGIFY
  template<typename T>
  StringBuilder &operator << (T message) {
    this->message = this->message.append(toString(message));
    return *this;
  }
};



END_NAMESPACE_EXPECT



/// Begin a writing a message for output.
/// \remarks
///   A message can be constructed by using additional `<<` operators in order
///   to append values of both non-string and string types.
///   For example, `MESSAGE "The index is " << index << ".";` would construct
///   a string of `"The index is 3"` for an `index` value of `3`.
#define MESSAGE \
  ::NAMESPACE_EXPECT StringBuilder() <<
