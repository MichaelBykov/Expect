// ===--- Matcher.h ---------------------------------------------- C++ ---=== //
//                                                                            //
// © 2022, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for defining custom and standard matchers.                   //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Global/StringBuilder.h>
#include <functional>
#include <vector>
#include <string>

START_NAMESPACE_EXPECT



template<typename T>
struct NotMatcherExpression;
template<typename T>
struct AndMatcherExpression;
template<typename T>
struct OrMatcherExpression;
template<typename T>
struct XorMatcherExpression;

enum class MatcherExpressionType {
  Value,
  Not  ,
  And  ,
  Or   ,
  Xor  ,
};

template<typename T>
struct MatcherExpression;

template<typename T>
struct MatcherExpressionData {
  size_t references = 1;
  std::string message = "";
  std::string failMessage = "";
  std::vector<MatcherExpression<T> *> right = { };
  bool hasRight = false;
  bool lastExpression = true;
  bool messageAccessed = false;
  
  MatcherExpressionType type;
  
  union {
    struct {
      std::function<bool(T)> value;
      std::function<std::string(T)> explanation;
    };
    MatcherExpression<T> *expression;
    struct {
      MatcherExpression<T> *lhs;
      MatcherExpression<T> *rhs;
    };
  };
  
  MatcherExpressionData<T>(
    std::function<bool(T)> value,
    std::function<std::string(T)> explanation
  ) : type(MatcherExpressionType::Value),
      value(value), explanation(explanation) { }
  
  MatcherExpressionData<T>(
    MatcherExpression<T> *expression
  ) : type(MatcherExpressionType::Not), expression(expression) { }
  
  MatcherExpressionData<T>(
    MatcherExpressionType type,
    MatcherExpression<T> *lhs ,
    MatcherExpression<T> *rhs
  ) : type(type), lhs(lhs), rhs(rhs) { }
  
  ~MatcherExpressionData<T>() {
    switch (type) {
    case MatcherExpressionType::Value:
      value.~function<bool(T)>();
      explanation.~function<std::string(T)>();
      break;
    
    case MatcherExpressionType::Not:
      expression->~MatcherExpression<T>();
      break;
    
    case MatcherExpressionType::And:
    case MatcherExpressionType::Or:
    case MatcherExpressionType::Xor:
      lhs->~MatcherExpression<T>();
      rhs->~MatcherExpression<T>();
      break;
    }
  }
  
  void retain() {
    references++;
  }
  
  void release() {
    if (--references == 0)
      delete this;
  }
};

template<typename T>
struct MatcherExpression {
  MatcherExpressionData<T> *data;
  
protected:
  MatcherExpression<T>(
    MatcherExpressionData<T> *data
  ) : data(data) { }
public:
  
  MatcherExpression<T>() {
    data = nullptr;
  }
  
  MatcherExpression<T>(MatcherExpression<T> &other) {
    data = other.data;
    data->retain();
  }
  
  MatcherExpression<T> &operator =(MatcherExpression<T> &other) {
    if (data != nullptr)
      data->release();
    data = other.data;
    data->retain();
    return *this;
  }
  
  virtual ~MatcherExpression<T>() {
    if (data != nullptr)
      data->release();
    data = nullptr;
  }
  
  virtual bool evaluate(T value) = 0;
  
  std::string message() {
    data->messageAccessed = true;
    switch (data->type) {
    case MatcherExpressionType::Value:
    case MatcherExpressionType::Not:
      return data->message;
    
    case MatcherExpressionType::And:
    case MatcherExpressionType::Or:
    case MatcherExpressionType::Xor:
      return data->lhs->message()
        .append(data->message)
        .append(data->rhs->message());
    }
  }
  
  std::string failMessage() {
    return data->failMessage;
  }
  
  bool messageAccessed() {
    return data->messageAccessed;
  }
  
  std::vector<MatcherExpression<T> *> &right() {
    return data->right;
  }
  
  bool hasRight() {
    return data->hasRight;
  }
  
  bool lastExpression() {
    return data->lastExpression;
  }
  
  MatcherExpressionType type() {
    return data->type;
  }
  
  NotMatcherExpression<T> &operator ! ();
  AndMatcherExpression<T> &operator &&(MatcherExpression<T> &other);
   OrMatcherExpression<T> &operator ||(MatcherExpression<T> &other);
  XorMatcherExpression<T> &operator ^ (MatcherExpression<T> &other);
  
  MatcherExpression<T> &operator | (MatcherExpression<T> &other) {
    data->right.push_back(&other);
    data->lastExpression = true;
    data->hasRight = true;
    return *this;
  }
  
  MatcherExpression<T> &operator | (const char *message) {
    data->message = data->message.append(message);
    data->lastExpression = false;
    data->hasRight = true;
    return *this;
  }
  
  MatcherExpression<T> &operator | (std::string &message) {
    data->message = data->message.append(message);
    data->lastExpression = false;
    data->hasRight = true;
    return *this;
  }
  
  MatcherExpression<T> &operator | (StringBuilder &message) {
    data->message = data->message.append(message);
    data->lastExpression = false;
    data->hasRight = true;
    return *this;
  }
};

template<typename T>
struct ValueMatcherExpression : MatcherExpression<T> {
  ValueMatcherExpression<T>(
    std::function<bool(T)> value,
    std::function<std::string(T)> explanation
  ) : MatcherExpression<T>(new MatcherExpressionData<T>(value, explanation)) { }
  
  bool evaluate(T value) {
    bool success = this->data->value(value);
    if (!success)
      this->data->failMessage = this->data->explanation(value);
    return success;
  }
};

template<typename T>
struct NotMatcherExpression : MatcherExpression<T> {
  NotMatcherExpression<T>(MatcherExpression<T> &expression)
    : MatcherExpression<T>(new MatcherExpressionData<T>(&expression)) { }
  
  MatcherExpression<T> &expression() {
    return *this->data->expression;
  }
  
  bool evaluate(T value) {
    bool success = !this->data->expression->evaluate(value);
    if (!success)
      this->data->failMessage =
        std::string("(NOT: result true.)");
    return success;
  }
};

template<typename T>
NotMatcherExpression<T> &MatcherExpression<T>::operator !() {
  return *new NotMatcherExpression<T>(*this);
}

template<typename T>
struct AndMatcherExpression : MatcherExpression<T> {
  AndMatcherExpression<T>(MatcherExpression<T> &lhs, MatcherExpression<T> &rhs)
    : MatcherExpression<T>(new MatcherExpressionData<T>(
      MatcherExpressionType::And, &lhs, &rhs
    )) { }
  
  MatcherExpression<T> &lhs() {
    return *this->data->lhs;
  }
  
  MatcherExpression<T> &rhs() {
    return *this->data->rhs;
  }
  
  bool evaluate(T value) {
    bool _lhs = this->data->lhs->evaluate(value);
    if (!_lhs) {
      this->data->failMessage =
        this->data->lhs->failMessage().append(" (AND) ...");
      return false;
    }
    bool _rhs = this->data->rhs->evaluate(value);
    if (!_rhs) {
      this->data->failMessage =
        std::string("... (AND) ").append(this->data->rhs->failMessage());
      return false;
    }
    return true;
  }
};

template<typename T>
AndMatcherExpression<T> &MatcherExpression<T>::operator &&(MatcherExpression<T> &other) {
  return *new AndMatcherExpression<T>(*this, other);
}

template<typename T>
struct OrMatcherExpression : MatcherExpression<T> {
  OrMatcherExpression<T>(MatcherExpression<T> &lhs, MatcherExpression<T> &rhs)
    : MatcherExpression<T>(new MatcherExpressionData<T>(
      MatcherExpressionType::Or, &lhs, &rhs
    )) { }
  
  MatcherExpression<T> &lhs() {
    return *this->data->lhs;
  }
  
  MatcherExpression<T> &rhs() {
    return *this->data->rhs;
  }
  
  bool evaluate(T value) {
    bool _lhs = this->data->lhs->evaluate(value);
    if (_lhs)
      return true;
    bool _rhs = this->data->rhs->evaluate(value);
    if (!_rhs) {
      if (!_lhs)
        this->data->failMessage = this->data->lhs->failMessage()
          .append(" (OR) ").append(this->data->rhs->failMessage());
      else
        this->data->failMessage =
          std::string("... (OR) ").append(this->data->rhs->failMessage());
      return false;
    } else if (!_lhs) {
      this->data->failMessage =
        this->data->lhs->failMessage().append(" (OR) ...");
      return false;
    }
    return true;
  }
};

template<typename T>
OrMatcherExpression<T> &MatcherExpression<T>::operator ||(MatcherExpression<T> &other) {
  return *new OrMatcherExpression<T>(*this, other);
}

template<typename T>
struct XorMatcherExpression : MatcherExpression<T> {
  XorMatcherExpression<T>(MatcherExpression<T> &lhs, MatcherExpression<T> &rhs)
    : MatcherExpression<T>(new MatcherExpressionData<T>(
      MatcherExpressionType::Xor, &lhs, &rhs
    )) { }
  
  MatcherExpression<T> &lhs() {
    return *this->data->lhs;
  }
  
  MatcherExpression<T> &rhs() {
    return *this->data->rhs;
  }
  
  bool evaluate(T value) {
    bool _lhs = this->data->lhs->evaluate(value);
    bool _rhs = this->data->rhs->evaluate(value);
    if (!_lhs && !_rhs) {
      this->data->failMessage = this->data->lhs->failMessage()
        .append(" (XOR) ").append(this->data->rhs->failMessage());
      return false;
    } else if (_lhs && _rhs) {
      this->data->failMessage = std::string("(XOR: both failed.)");
      return false;
    }
    return true;
  }
};

template<typename T>
XorMatcherExpression<T> &MatcherExpression<T>::operator ^(MatcherExpression<T> &other) {
  return *new XorMatcherExpression<T>(*this, other);
}



template<typename T>
struct Matcher {
  operator ValueMatcherExpression<T> &() {
    return *new ValueMatcherExpression<T>(
      [this](T value) { return this->evaluate(value); },
      [this](T value) { return this->message(value, this->evaluate(value)); }
    );
  }
  
  virtual bool evaluate(T value) = 0;
  
  virtual std::string message(T value, bool succeeded) {
    return "Failed.";
  }
};



namespace Matchers {



#define MATCHER_MEMBERS_CONCAT_(lhs, rhs) lhs##rhs
#define MATCHER_MEMBERS_CONCAT(lhs, rhs) MATCHER_MEMBERS_CONCAT_(lhs, rhs)

#define MATCHER_MEMBERS_COUNT_( \
  __1, __2, __3, __4, __5, __6, __7, __8, __9, _10, \
  _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
  _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
  _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
  _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
  N, ... \
) N
#define MATCHER_MEMBERS_COUNT(...) \
  MATCHER_MEMBERS_COUNT_(__VA_ARGS__, \
    50, 49, 48, 47, 46, 45, 44, 43, 42, 41, \
    40, 39, 38, 37, 36, 35, 34, 33, 32, 31, \
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21, \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11, \
    10,  9,  8,  7,  6,  5,  4,  3,  2,  1 \
  )

#define IMPLEMENT_MATCHER_MEMBERS_1(...)
#define IMPLEMENT_MATCHER_MEMBERS_2( type, name     ) type name;
#define IMPLEMENT_MATCHER_MEMBERS_4( type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_2( __VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_6( type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_4( __VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_8( type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_6( __VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_10(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_8( __VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_12(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_10(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_14(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_12(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_16(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_14(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_18(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_16(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_20(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_18(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_22(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_20(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_24(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_22(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_26(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_24(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_28(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_26(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_30(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_28(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_32(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_30(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_34(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_32(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_36(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_34(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_38(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_36(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_40(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_38(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_42(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_40(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_44(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_42(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_46(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_44(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_48(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_46(__VA_ARGS__)
#define IMPLEMENT_MATCHER_MEMBERS_50(type, name, ...) type name; IMPLEMENT_MATCHER_MEMBERS_48(__VA_ARGS__)

#define IMPLEMENT_MATCHER_UNPACK_1(...)
#define IMPLEMENT_MATCHER_UNPACK_2( type, name     ) type name
#define IMPLEMENT_MATCHER_UNPACK_4( type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_2( __VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_6( type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_4( __VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_8( type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_6( __VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_10(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_8( __VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_12(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_10(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_14(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_12(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_16(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_14(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_18(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_16(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_20(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_18(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_22(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_20(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_24(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_22(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_26(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_24(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_28(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_26(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_30(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_28(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_32(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_30(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_34(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_32(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_36(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_34(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_38(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_36(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_40(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_38(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_42(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_40(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_44(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_42(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_46(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_44(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_48(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_46(__VA_ARGS__)
#define IMPLEMENT_MATCHER_UNPACK_50(type, name, ...) type name, IMPLEMENT_MATCHER_UNPACK_48(__VA_ARGS__)

#define IMPLEMENT_MATCHER_NAMES_1(...)
#define IMPLEMENT_MATCHER_NAMES_2( type, name     ) name
#define IMPLEMENT_MATCHER_NAMES_4( type, name, ...) name, IMPLEMENT_MATCHER_NAMES_2( __VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_6( type, name, ...) name, IMPLEMENT_MATCHER_NAMES_4( __VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_8( type, name, ...) name, IMPLEMENT_MATCHER_NAMES_6( __VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_10(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_8( __VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_12(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_10(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_14(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_12(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_16(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_14(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_18(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_16(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_20(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_18(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_22(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_20(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_24(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_22(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_26(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_24(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_28(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_26(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_30(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_28(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_32(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_30(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_34(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_32(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_36(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_34(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_38(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_36(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_40(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_38(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_42(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_40(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_44(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_42(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_46(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_44(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_48(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_46(__VA_ARGS__)
#define IMPLEMENT_MATCHER_NAMES_50(type, name, ...) name, IMPLEMENT_MATCHER_NAMES_48(__VA_ARGS__)

#define IMPLEMENT_MATCHER_MEMBERS(...) \
  MATCHER_MEMBERS_CONCAT(IMPLEMENT_MATCHER_MEMBERS_, \
    MATCHER_MEMBERS_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define IMPLEMENT_MATCHER_UNPACK(...) \
  MATCHER_MEMBERS_CONCAT(IMPLEMENT_MATCHER_UNPACK_, \
    MATCHER_MEMBERS_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define IMPLEMENT_MATCHER_NAMES(...) \
  MATCHER_MEMBERS_CONCAT(IMPLEMENT_MATCHER_NAMES_, \
    MATCHER_MEMBERS_COUNT(__VA_ARGS__))(__VA_ARGS__)



#define DEFINE_MATCHER(name, ...) \
  template<typename Any> \
  struct _##name { \
    IMPLEMENT_MATCHER_MEMBERS(__VA_ARGS__) \
    bool __evaluate__(Any value); \
    std::string __message__(Any value); \
  }; \
  template<typename Any> \
  ::NAMESPACE_EXPECT ValueMatcherExpression<Any> &name( \
    IMPLEMENT_MATCHER_UNPACK(__VA_ARGS__) \
  ) { \
    return *new ::NAMESPACE_EXPECT ValueMatcherExpression<Any>( \
      [=](Any value) -> bool { \
        _##name<Any> match = { IMPLEMENT_MATCHER_NAMES(__VA_ARGS__) }; \
        return match.__evaluate__(value); \
      }, \
      [=](Any value) -> std::string { \
        _##name<Any> match = { IMPLEMENT_MATCHER_NAMES(__VA_ARGS__) }; \
        return match.__message__(value); \
      } \
    ); \
  }

#define IMPLEMENT_MATCHER(name, value, message) \
  template<typename Any> \
  std::string _##name<Any>::__message__(Any value) { \
    return ::NAMESPACE_EXPECT StringBuilder() << message; \
  } \
  template<typename Any> \
  bool _##name<Any>::__evaluate__(Any value)

#define SPECIALIZE_MATCHER(name, type, value) \
  template<> \
  bool _##name<type>::__evaluate__(type value)



DEFINE_MATCHER(isEven)
IMPLEMENT_MATCHER(isEven, value, value << " is odd.") {
  return value % 2 == 0;
}

DEFINE_MATCHER(inRange, Any, lhs, Any, rhs)
IMPLEMENT_MATCHER(inRange, value, value << " is not in the range of " << lhs << ", " << rhs << ".") {
  return lhs <= value && value <= rhs;
}

DEFINE_MATCHER(isNull)
IMPLEMENT_MATCHER(isNull, value, "Address " << value << " is not null.") {
  return value == nullptr;
}

DEFINE_MATCHER(isSome)
IMPLEMENT_MATCHER(isSome, value, "Address " << value << " is null.") {
  return value != nullptr;
}

// TODO: Implement custom templated macro matchers and better stringification (including for NOT cases)

// DEFINE_MATCHER(each, std::function<bool(Any)>, predicate)
// IMPLEMENT_MATCHER(each, value, "A value did not match.") {
//   for ()
// }

// template<typename Vector, typename Element>
// struct each : ::NAMESPACE_EXPECT Matcher<T> {
//   std::function<bool(Element)> predicate;
  
//   bool __evaluate__(Vector value, ::NAMESPACE_EXPECT StringBuilder &message) {
    
//   }
// };

// template<typename T>
// struct inRange : ::NAMESPACE_EXPECT Matcher<T> {
//   T lhs, rhs;
  
//   bool __evaluate__(T value, ::NAMESPACE_EXPECT StringBuilder &message) {
//     if (lhs <= value && value <= rhs) {
//       message << value << " is in the range of " << lhs << ", " << rhs << ".";
//       return true;
//     } else {
//       message << value << " is not in the range of " << lhs << ", " << rhs << ".";
//       return true;
//     }
//   }
// };

#define MATCHER(name, type) \
  struct name : ::NAMESPACE_EXPECT Matcher<type>

#define MATCHER_EVALUATE(value, message) \
  bool __evaluate__(value, ::NAMESPACE_EXPECT StringBuilder &message)

#define MATCHER_IMPLEMENT_EVALUATE(matcher, value, message) \
  bool matcher::__evaluate__(value, ::NAMESPACE_EXPECT StringBuilder &message)

#define IMPLEMENT_MATCHER3(name, type, matcher, ...) \
  ::NAMESPACE_EXPECT ValueMatcherExpression<type> &name( \
    IMPLEMENT_MATCHER_UNPACK(__VA_ARGS__) \
  ) { \
    return *new ::NAMESPACE_EXPECT ValueMatcherExpression<type>( \
      [=](type __value__, std::string &__message__) -> bool { \
        auto __match__ = (matcher) { IMPLEMENT_MATCHER_NAMES(__VA_ARGS__) }; \
        return __match__.__evaluate__(__value__, __message__); \
      } \
    ); \
  }

template<typename T>
MATCHER(inRange3, T) {
  T lhs, rhs;
  
  inRange3<T>(T lhs, T rhs) : lhs(lhs), rhs(rhs) { }
  
  bool evaluate(T value) {
    return lhs <= value && value <= rhs;
  }
  
  std::string message(T value, bool succeeded) {
    if (succeeded)
      return MESSAGE value << " is in the range of " << lhs << ", " << rhs << ".";
    else
      return MESSAGE value << " is not in the range of " << lhs << ", " << rhs << ".";
  }
};

template<typename T>
MATCHER(isEven3, T) {
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

template<typename Collection, typename Element>
MATCHER(each, Collection) {
  std::function<bool(Element)> predicate;
  
  each<Collection, Element>(
    std::function<bool(Element)> predicate
  ) : predicate(predicate) { }
  
  bool evaluate(Collection value) {
    for (Element &element : value)
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
      for (Element &element : value) {
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



} // namespace Matchers
END_NAMESPACE_EXPECT



#define USE_EXPECT_MATCHING \
  using namespace NAMESPACE_EXPECT Matchers;
