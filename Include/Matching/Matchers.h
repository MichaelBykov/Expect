// ===--- Matchers.h --------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
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



MATCHER(IsBoolValue, bool, IsBoolValue) {
  bool value;
  
  IsBoolValue(bool value) : value(value) { }
  
  bool evaluate(bool value) {
    return this->value == value;
  }
  
  std::string message(bool value, bool succeeded) {
    if (value) {
      return succeeded ? "Value is true." : "Value is false.";
    } else {
      return succeeded ? "Value is false." : "Value is true.";
    }
  }
};

/// Check that a boolean is true.
static MATCHER_RESULT(bool) isTrue = IsBoolValue(true);

/// Check that a boolean is false.
static MATCHER_RESULT(bool) isFalse = IsBoolValue(false);



template<typename T, typename Type>
MATCHER(IsA, T, IsA<T, Type>) {
  bool evaluate(T value) {
    const std::type_info &lhs = typeid(*value);
    const std::type_info &rhs = typeid(Type);
    return lhs == rhs;
  }
  
  std::string message(T value, bool succeeded) {
    return succeeded ? "Matching types." : "Non-matching types.";
  }
};

/// Check that a pointer to a base type is an instance of a subtype.
/// \tparam T
///   The base type pointer.
/// \tparam Type
///   The subtype (not a pointer).
template<typename T, typename Type>
MATCHER_RESULT(T) isA() {
  return IsA<T, Type>();
}

/// Check that a pointer to a base type is an instance of a subtype.
/// \tparam T
///   The base type pointer.
/// \tparam Type
///   The subtype (not a pointer).
template<typename T, typename Type>
MATCHER_RESULT(T) isAn() {
  return IsA<T, Type>();
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

/// Check that a pointer is null.
/// \tparam T
///   The type of the pointer.
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

/// Check that a pointer is non-null.
/// \tparam T
///   The type of the pointer.
template<typename T>
MATCHER_RESULT(T) isSome() {
  return IsSome<T>();
}



template<typename T>
MATCHER(IsNaN, T, IsNaN<T>) {
  bool evaluate(T value) {
    return value != value;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return "Is not-a-number.";
    else
      return MESSAGE value << " is not not-a-number.";
  }
};

/// Check that a floating-point is not-a-number.
/// \tparam T
///   The type of the floating-point.
template<typename T>
MATCHER_RESULT(T) isNaN() {
  return IsNaN<T>();
}

template<typename T>
MATCHER(IsNonNaN, T, IsNonNaN<T>) {
  bool evaluate(T value) {
    return value == value;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE value << " is a number.";
    else
      return "Is not-a-number.";
  }
};

/// Check that a floating-point is not not-a-number.
/// \tparam T
///   The type of the floating-point.
template<typename T>
MATCHER_RESULT(T) isNonNaN() {
  return IsNonNaN<T>();
}

template<typename T>
MATCHER(IsFinite, T, IsFinite<T>) {
  bool evaluate(T value) {
    return value == value && value / value == value / value;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE value << " is finite.";
    else
      return MESSAGE value << " is not finite.";
  }
};

/// Check that a floating-point is finite.
/// \tparam T
///   The type of the floating-point.
template<typename T>
MATCHER_RESULT(T) isFinite() {
  return IsFinite<T>();
}

template<typename T>
MATCHER(IsInfinite, T, IsInfinite<T>) {
  bool evaluate(T value) {
    return value == value && value / value != value / value;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return "Is infinite.";
    else
      return MESSAGE value << " is not infinite.";
  }
};

/// Check that a floating-point is infinite.
/// \tparam T
///   The type of the floating-point.
template<typename T>
MATCHER_RESULT(T) isInfinite() {
  return IsInfinite<T>();
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

/// Check that each element of a collection matches a predicate.
/// \tparam T
///   The type of the collection.
/// \tparam Element
///   The type of the element in the collection.
/// \param predicate
///   The predicate for which every element in the given collection should
///   match.
template<typename T, typename Element>
MATCHER_RESULT(T) each(std::function<bool(Element)> predicate) {
  return Each<T, Element> { predicate };
}

/// Check that each element of a collection matches a set value.
/// \tparam T
///   The type of the collection.
/// \tparam Element
///   The type of the element in the collection.
/// \param element
///   The value that should match every element in the collection.
template<typename T, typename Element>
MATCHER_RESULT(T) each(Element element) {
  return Each<T, Element> { [element](Element other) {
    return element == other;
  } };
}



template<typename Collection, typename Element>
MATCHER(Has, Collection, Has<Collection, Element>) {
  std::function<bool(Element)> predicate;
  size_t count;
  
  Has<Collection, Element>(
    std::function<bool(Element)> predicate,
    size_t count
  ) : predicate(predicate), count(count) { }
  
  bool evaluate(Collection value) {
    size_t count = 0;
    for (Element element : value)
      if (predicate(element))
        count++;
    return count == this->count;
  }
  
  std::string message(Collection value, bool succeeded) {
    if (succeeded)
      return MESSAGE this->count << " elements matched.";
    else {
      size_t count = 0;
      for (Element element : value)
        if (predicate(element))
          count++;
      return MESSAGE count << " (not " << this->count << ") elements matched.";
    }
  }
};

/// Check that a collection matches a predicate a specific number of times.
/// \tparam T
///   The type of the collection.
/// \tparam Element
///   The type of the element in the collection.
/// \param predicate
///   The predicate that should be matched `count` times in the collection.
/// \param count
///   The number of times the predicate should match in the collection.
template<typename T, typename Element>
MATCHER_RESULT(T) has(std::function<bool(Element)> predicate, size_t count) {
  return Has<T, Element> { predicate, count };
}

/// Check that a collection has a specific number of a specific element.
/// \tparam T
///   The type of the collection.
/// \tparam Element
///   The type of the element in the collection.
/// \param element
///   The element that should be matched `count` times in the collection.
/// \param count
///   The number of times the element should be found in the collection.
template<typename T, typename Element>
MATCHER_RESULT(T) has(Element element, size_t count) {
  return Has<T, Element> { [element](Element other) {
    return element == other;
  }, count };
}



template<typename Collection, typename Element>
MATCHER(Contains, Collection, Contains<Collection, Element>) {
  std::function<bool(Element)> predicate;
  
  Contains<Collection, Element>(std::function<bool(Element)> predicate)
    : predicate(predicate) { }
  
  MATCHER_RESULT(Collection) times(size_t count) {
    return Has<Collection, Element> { predicate, count };
  }
  
  bool evaluate(Collection value) {
    for (Element element : value)
      if (predicate(element))
        return true;
    return false;
  }
  
  std::string message(Collection value, bool succeeded) {
    if (succeeded) {
      size_t index = 0;
      for (Element element : value) {
        if (predicate(element))
          return MESSAGE "Element " << index << " matched.";
        index++;
      }
    }
    return "No elements matched.";
  }
};

/// Check that a collection matches a predicate at least once.
/// \tparam T
///   The type of the collection.
/// \tparam Element
///   The type of the element in the collection.
/// \param predicate
///   The predicate that should be matched at least once in the collection.
template<typename T, typename Element>
MATCHER_RESULT(T) contains(std::function<bool(Element)> predicate) {
  return Contains<T, Element> { predicate };
}

/// Check that a collection has at least one of the given element.
/// \tparam T
///   The type of the collection.
/// \tparam Element
///   The type of the element in the collection.
/// \param element
///   The element that should be matched at least once in the collection.
template<typename T, typename Element>
MATCHER_RESULT(T) contains(Element element) {
  return Contains<T, Element> { [element](Element other) {
    return element == other;
  } };
}



template<typename T>
MATCHER(BeginsWith, T, BeginsWith<T>) {
  T substring;
  
  BeginsWith<T>(T substring) : substring(substring) { }
  
  bool evaluate(T value);
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE "Begins with " << substring << ".";
    else
      return MESSAGE "Doesn't begin with " << substring << ".";
  }
};

template<>
bool BeginsWith<const char *>::evaluate(const char *value);

template<>
bool BeginsWith<std::string>::evaluate(std::string value);

/// Check that a string begins with a given substring.
/// \tparam T
///   The type of the string.
/// \param substring
///   The substring that should be matched at the beginning of the string.
template<typename T>
MATCHER_RESULT(T) beginsWith(T substring) {
  return BeginsWith<T>(substring);
}

template<typename T>
MATCHER(EndsWith, T, EndsWith<T>) {
  T substring;
  
  EndsWith<T>(T substring) : substring(substring) { }
  
  bool evaluate(T value);
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE "Ends with " << substring << ".";
    else
      return MESSAGE "Doesn't end with " << substring << ".";
  }
};

template<>
bool EndsWith<const char *>::evaluate(const char *value);

template<>
bool EndsWith<std::string>::evaluate(std::string value);

/// Check that a string ends with a given substring.
/// \tparam T
///   The type of the string.
/// \param substring
///   The substring that should be matched at the end of the string.
template<typename T>
MATCHER_RESULT(T) endsWith(T substring) {
  return EndsWith<T>(substring);
}

template<>
struct Contains<const char *, const char *>;

/// Check that a string contains a given substring.
/// \param substring
///   The substring to check for in the string.
template<>
MATCHER_RESULT(const char *) contains<const char *, const char *>(const char *substring);

template<>
struct Contains<std::string, std::string>;

/// Check that a string contains a given substring.
/// \param substring
///   The substring to check for in the string.
template<>
MATCHER_RESULT(std::string) contains<std::string, std::string>(std::string substring);



} // namespace Matchers
END_NAMESPACE_EXPECT



/// Use the standard Expect matchers.
#define USE_EXPECT_MATCHING \
  using namespace NAMESPACE_EXPECT Matchers;
