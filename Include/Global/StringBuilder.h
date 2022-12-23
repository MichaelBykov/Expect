// ===--- StringBuilder.h ---------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
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



struct StringBuilder {
  std::string message;
  
  operator std::string() {
    return message;
  }
  
  StringBuilder &operator << (const char *message) {
    this->message = this->message.append(message);
    return *this;
  }
  
  StringBuilder &operator << (std::string &message) {
    this->message = this->message.append(message);
    return *this;
  }
  
  template<typename T>
  StringBuilder &operator << (T message) {
    this->message = this->message.append(toString(message));
    return *this;
  }
};



END_NAMESPACE_EXPECT



#define MESSAGE \
  ::NAMESPACE_EXPECT StringBuilder() <<
