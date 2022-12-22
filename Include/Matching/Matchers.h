// ===--- Matchers.h --------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// A definition of default matchers.                                          //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include "Matcher.h"
#include <vector>

START_NAMESPACE_EXPECT
namespace Matchers {


template<typename T>
MATCHER(InRange, T, InRange<T>) {
  T lhs, rhs;
  
  InRange<T>(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  bool evaluate(T value) {
    return lhs <= value && value <= rhs;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE
        value << " is in the range of " << lhs << ", " << rhs << ".";
    else
      return MESSAGE
        value << " is not in the range of " << lhs << ", " << rhs << ".";
  }
};

template<typename T>
MATCHER_RESULT(T) inRange(T lhs, T rhs) {
  return InRange<T> { lhs, rhs };
}

template<typename T>
MATCHER(IsEven, T, IsEven<T>) {
  bool evaluate(T value) {
    return value % 2 == 0;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE value << " is even.";
    else
      return MESSAGE value << " is not even.";
  }
};

template<typename T>
MATCHER_RESULT(T) isEven() {
  return IsEven<T>();
}

template<typename T>
MATCHER(IsNull, T, IsNull<T>) {
  bool evaluate(T value) {
    return value == nullptr;
  }
  
  std::string message(T value, bool succeeded) {
    return MESSAGE "Address " << value <<
      (succeeded ? " is null." : " is not null.");
  }
};

template<typename T>
MATCHER_RESULT(T) isNull() {
  return IsNull<T>();
}

template<typename T>
MATCHER(IsSome, T, IsSome<T>) {
  bool evaluate(T value) {
    return value != nullptr;
  }
  
  std::string message(T value, bool succeeded) {
    return MESSAGE "Address " << value <<
      (succeeded ? " is some." : " is not some (is null).");
  }
};

template<typename T>
MATCHER_RESULT(T) isSome() {
  return IsSome<T>();
}

template<typename Collection, typename Element>
MATCHER(Each, Collection, Each<Collection, Element>) {
  std::function<bool(Element)> predicate;
  
  Each<Collection, Element>(std::function<bool(Element)> predicate)
    : predicate(predicate) { }
  
  bool evaluate(Collection value) {
    for (Element element : value)
      if (!predicate(element))
        return false;
    return true;
  }
  
  std::string message(Collection value, bool succeeded) {
    if (succeeded)
      return "All elements matched.";
    else {
      StringBuilder builder { };
      builder << "Element(s) ";
      size_t index = 0, count = 0;
      for (Element element : value) {
        if (!predicate(element)) {
          if (count > 10) {
            builder << " ...";
            break;
          } else if (count > 0)
            builder << ", ";
          builder << index;
          count++;
        }
        index++;
      }
      return builder << " did not match.";
    }
  }
};

template<typename T, typename Element>
MATCHER_RESULT(T) each(std::function<bool(Element)> predicate) {
  return Each<T, Element> { predicate };
}

template<typename T, typename Element>
MATCHER_RESULT(T) each(Element element) {
  return Each<T, Element> { [element](Element other) {
    return element == other;
  } };
}



} // namespace Matchers
END_NAMESPACE_EXPECT



#define USE_EXPECT_MATCHING \
  using namespace NAMESPACE_EXPECT Matchers;
