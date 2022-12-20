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
  std::vector<MatcherExpression<T> *> right = { };
  bool hasRight = false;
  bool lastExpression = true;
  
  MatcherExpressionType type;
  
  union {
    std::function<bool(T)> value;
    MatcherExpression<T> *expression;
    struct {
      MatcherExpression<T> *lhs;
      MatcherExpression<T> *rhs;
    };
  };
  
  MatcherExpressionData<T>(
    std::function<bool(T)> value
  ) : type(MatcherExpressionType::Value), value(value) { }
  
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
  
  std::string &message() {
    return data->message;
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
};

template<typename T>
struct ValueMatcherExpression : MatcherExpression<T> {
  ValueMatcherExpression<T>(std::function<bool(T)> value)
    : MatcherExpression<T>(new MatcherExpressionData<T>(value)) { }
  
  bool evaluate(T value) {
    return this->data->value(value);
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
    return !this->data->expression->evaluate(value);
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
    return this->data->lhs->evaluate(value) && this->data->rhs->evaluate(value);
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
    return this->data->lhs->evaluate(value) || this->data->rhs->evaluate(value);
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
    return this->data->lhs->evaluate(value) ^ this->data->rhs->evaluate(value);
  }
};

template<typename T>
XorMatcherExpression<T> &MatcherExpression<T>::operator ^(MatcherExpression<T> &other) {
  return *new XorMatcherExpression<T>(*this, other);
}



namespace Matchers {



// Numerical matchers
template<typename T>
MatcherExpression<T> &isEven() {
  return *new ValueMatcherExpression<T>([=](T value) -> bool {
    return value % 2 == 0;
  });
};

template<typename T>
MatcherExpression<T> &inRange(T lhs, T rhs) {
  return *new ValueMatcherExpression<T>([=](T value) -> bool {
    return lhs <= value && value <= rhs;
  });
};




} // namespace Matchers
END_NAMESPACE_EXPECT



#define USE_EXPECT_MATCHING \
  using namespace NAMESPACE_EXPECT Matchers;
