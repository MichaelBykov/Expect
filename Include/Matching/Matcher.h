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
struct MatcherExpression {
  std::string message = "";
  std::vector<MatcherExpression<T> *> right = { };
  bool hasRight = false;
  bool lastExpression = true;
  
  MatcherExpressionType type;
  
  virtual ~MatcherExpression<T>() = default;
  
  virtual bool evaluate(T value) = 0;
  
  virtual MatcherExpression<T> &copy() = 0;
  
  NotMatcherExpression<T> &operator ! ();
  AndMatcherExpression<T> &operator &&(MatcherExpression<T> &other);
   OrMatcherExpression<T> &operator ||(MatcherExpression<T> &other);
  XorMatcherExpression<T> &operator ^ (MatcherExpression<T> &other);
  
  MatcherExpression<T> &operator | (MatcherExpression<T> &other) {
    right.push_back(&other);
    lastExpression = true;
    hasRight = true;
    return *this;
  }
  
  MatcherExpression<T> &operator | (const char *message) {
    this->message = this->message.append(message);
    lastExpression = false;
    hasRight = true;
    return *this;
  }
};

template<typename T>
struct ValueMatcherExpression : MatcherExpression<T> {
  std::function<bool(T)> value;
  
  ValueMatcherExpression<T>(std::function<bool(T)> value) : value(value) {
    this->type = MatcherExpressionType::Value;
  }
  
  bool evaluate(T value) {
    return this->value(value);
  }
  
  MatcherExpression<T> &copy() {
    return *(MatcherExpression<T> *)new ValueMatcherExpression<T>(value);
  }
};

template<typename T>
struct NotMatcherExpression : MatcherExpression<T> {
  MatcherExpression<T> &value;
  
  NotMatcherExpression<T>(MatcherExpression<T> &value) : value(value) {
    this->type = MatcherExpressionType::Not;
    this->message = this->message.append(value.message);
    this->right = value.right;
  }
  
  ~NotMatcherExpression<T>() {
    delete &value;
  }
  
  bool evaluate(T value) {
    return !this->value.evaluate(value);
  }
  
  MatcherExpression<T> &copy() {
    return *(MatcherExpression<T> *)new NotMatcherExpression<T>(value.copy());
  }
};

template<typename T>
NotMatcherExpression<T> &MatcherExpression<T>::operator !() {
  return *new NotMatcherExpression<T>(*this);
}

template<typename T>
struct AndMatcherExpression : MatcherExpression<T> {
  MatcherExpression<T> &lhs;
  MatcherExpression<T> &rhs;
  
  AndMatcherExpression<T>(MatcherExpression<T> &lhs, MatcherExpression<T> &rhs)
    : lhs(lhs), rhs(rhs) {
    this->type = MatcherExpressionType::And;
    this->message = this->message.append(lhs.message).append(rhs.message);
  }
  
  ~AndMatcherExpression<T>() {
    delete &lhs;
    delete &rhs;
  }
  
  bool evaluate(T value) {
    return lhs.evaluate(value) && rhs.evaluate(value);
  }
  
  MatcherExpression<T> &copy() {
    return *(MatcherExpression<T> *)new AndMatcherExpression<T>(lhs.copy(), rhs.copy());
  }
};

template<typename T>
AndMatcherExpression<T> &MatcherExpression<T>::operator &&(MatcherExpression<T> &other) {
  return *new AndMatcherExpression<T>(*this, other);
}

template<typename T>
struct OrMatcherExpression : MatcherExpression<T> {
  MatcherExpression<T> &lhs;
  MatcherExpression<T> &rhs;
  
  OrMatcherExpression<T>(MatcherExpression<T> &lhs, MatcherExpression<T> &rhs)
    : lhs(lhs), rhs(rhs) {
    this->type = MatcherExpressionType::Or;
    this->message = this->message.append(lhs.message).append(rhs.message);
  }
  
  ~OrMatcherExpression<T>() {
    delete &lhs;
    delete &rhs;
  }
  
  bool evaluate(T value) {
    return lhs.evaluate(value) || rhs.evaluate(value);
  }
  
  MatcherExpression<T> &copy() {
    return *(MatcherExpression<T> *)new OrMatcherExpression<T>(lhs.copy(), rhs.copy());
  }
};

template<typename T>
OrMatcherExpression<T> &MatcherExpression<T>::operator ||(MatcherExpression<T> &other) {
  return *new OrMatcherExpression<T>(*this, other);
}

template<typename T>
struct XorMatcherExpression : MatcherExpression<T> {
  MatcherExpression<T> &lhs;
  MatcherExpression<T> &rhs;
  
  XorMatcherExpression<T>(MatcherExpression<T> &lhs, MatcherExpression<T> &rhs)
    : lhs(lhs), rhs(rhs) {
    this->type = MatcherExpressionType::Xor;
    this->message = this->message.append(lhs.message).append(rhs.message);
  }
  
  ~XorMatcherExpression<T>() {
    delete &lhs;
    delete &rhs;
  }
  
  bool evaluate(T value) {
    return lhs.evaluate(value) ^ rhs.evaluate(value);
  }
  
  MatcherExpression<T> &copy() {
    return *(MatcherExpression<T> *)new XorMatcherExpression<T>(lhs.copy(), rhs.copy());
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
