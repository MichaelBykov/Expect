// ===--- Matcher.h ---------------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
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
  bool messageAccessed = false;
  
  MatcherExpressionType type;
  
  union {
    struct {
      std::function<bool(T)> value;
      std::function<std::string(T, bool)> explanation;
      std::function<void()> cleanup;
      bool success;
    };
    struct {
      MatcherExpression<T> *expression;
      bool expressionSuccess;
    };
    struct {
      MatcherExpression<T> *lhs;
      MatcherExpression<T> *rhs;
      bool lhsSuccess;
      bool rhsSuccess;
    };
  };
  
  MatcherExpressionData<T>(
    std::function<bool(T)> value,
    std::function<std::string(T, bool)> explanation,
    std::function<void()> cleanup
  ) : type(MatcherExpressionType::Value),
      value(value), explanation(explanation), cleanup(cleanup) { }
  
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
      cleanup();
      value.~function<bool(T)>();
      explanation.~function<std::string(T, bool)>();
      cleanup.~function<void()>();
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
  
  virtual std::string failMessage(T value) = 0;
  
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
  
  AndMatcherExpression<T> &operator &&(MatcherExpression<T> &(*emptyMatcher)());
   OrMatcherExpression<T> &operator ||(MatcherExpression<T> &(*emptyMatcher)());
  XorMatcherExpression<T> &operator ^ (MatcherExpression<T> &(*emptyMatcher)());
  
  MatcherExpression<T> &operator | (MatcherExpression<T> &other) {
    data->right.push_back(&other);
    data->lastExpression = true;
    data->hasRight = true;
    return *this;
  }
  
  MatcherExpression<T> &operator | (MatcherExpression<T> &(*emptyMatcher)()) {
    MatcherExpression<T> &matcher = emptyMatcher();
    data->right.push_back(&matcher);
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
    std::function<std::string(T, bool)> explanation,
    std::function<void()> cleanup
  ) : MatcherExpression<T>(new MatcherExpressionData<T>(
        value, explanation, cleanup
      )) { }
  
  bool evaluate(T value) {
    return this->data->success = this->data->value(value);
  }
  
  std::string failMessage(T value) {
    return this->data->explanation(value, this->data->success);
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
    return
      this->data->expressionSuccess = !this->data->expression->evaluate(value);
  }
  
  std::string failMessage(T value) {
    return std::string("(NOT) ")
      .append(this->data->expression->failMessage(value));
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
    this->data->lhsSuccess = this->data->lhs->evaluate(value);
    if (!this->data->lhsSuccess)
      return false;
    this->data->rhsSuccess = this->data->rhs->evaluate(value);
    if (!this->data->rhsSuccess)
      return false;
    return true;
  }
  
  std::string failMessage(T value) {
    if (!this->data->lhsSuccess)
      return this->data->lhs->failMessage(value).append(" (AND) ...");
    else if (!this->data->rhsSuccess)
      return std::string("... (AND) ")
        .append(this->data->rhs->failMessage(value));
    else
      // NOT case
    return this->data->lhs->failMessage(value)
      .append(" (AND) ")
      .append(this->data->rhs->failMessage(value));
  }
};

template<typename T>
AndMatcherExpression<T> &MatcherExpression<T>::operator &&(MatcherExpression<T> &other) {
  return *new AndMatcherExpression<T>(*this, other);
}

template<typename T>
AndMatcherExpression<T> &MatcherExpression<T>::operator &&(MatcherExpression<T> &(*emptyMatcher)()) {
  return *new AndMatcherExpression<T>(*this, emptyMatcher());
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
    this->data->lhsSuccess = this->data->lhs->evaluate(value);
    if (this->data->lhsSuccess)
      return true;
    this->data->rhsSuccess = this->data->rhs->evaluate(value);
    if (this->data->rhsSuccess)
      return true;
    return false;
  }
  
  std::string failMessage(T value) {
    if (this->data->lhsSuccess)
      // NOT case
      return this->data->lhs->failMessage(value).append(" (OR) ...");
    else if (this->data->rhsSuccess)
      // NOT case
      return std::string("... (OR) ")
        .append(this->data->rhs->failMessage(value));
    else
      return this->data->lhs->failMessage(value)
        .append(" (OR) ")
        .append(this->data->rhs->failMessage(value));
  }
};

template<typename T>
OrMatcherExpression<T> &MatcherExpression<T>::operator ||(MatcherExpression<T> &other) {
  return *new OrMatcherExpression<T>(*this, other);
}

template<typename T>
OrMatcherExpression<T> &MatcherExpression<T>::operator ||(MatcherExpression<T> &(*emptyMatcher)()) {
  return *new OrMatcherExpression<T>(*this, emptyMatcher());
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
    this->data->lhsSuccess = this->data->lhs->evaluate(value);
    this->data->rhsSuccess = this->data->rhs->evaluate(value);
    return this->data->lhsSuccess ^ this->data->rhsSuccess;
  }
  
  std::string failMessage(T value) {
    return this->data->lhs->failMessage(value)
      .append(" (XOR) ")
      .append(this->data->rhs->failMessage(value));
  }
};

template<typename T>
XorMatcherExpression<T> &MatcherExpression<T>::operator ^(MatcherExpression<T> &other) {
  return *new XorMatcherExpression<T>(*this, other);
}

template<typename T>
XorMatcherExpression<T> &MatcherExpression<T>::operator ^(MatcherExpression<T> &(*emptyMatcher)()) {
  return *new XorMatcherExpression<T>(*this, emptyMatcher());
}



template<typename T, typename Implementation>
struct Matcher {
  virtual bool evaluate(T value) = 0;
  
  virtual std::string message(T value, bool succeeded) {
    return succeeded ? "Failed." : "Succeeded.";
  }
  
  
  
  operator ValueMatcherExpression<T> &() {
    Implementation *self = new Implementation(*(Implementation *)this);
    return *new ValueMatcherExpression<T>(
      [self](T value) { return self->evaluate(value); },
      [self](T value, bool success) { return self->message(value, success); },
      [self]() { delete self; }
    );
  }
  
  NotMatcherExpression<T> &operator ! () {
    return !(ValueMatcherExpression<T> &)*this;
  }
  
  AndMatcherExpression<T> &operator &&(MatcherExpression<T> &other) {
    return (ValueMatcherExpression<T> &)*this && other;
  }
  
  OrMatcherExpression<T> &operator ||(MatcherExpression<T> &other) {
    return (ValueMatcherExpression<T> &)*this || other;
  }
  
  XorMatcherExpression<T> &operator ^ (MatcherExpression<T> &other) {
    return (ValueMatcherExpression<T> &)*this ^ other;
  }
  
  MatcherExpression<T> &operator | (MatcherExpression<T> &other) {
    ValueMatcherExpression<T> &expression = *this;
    expression.data->right.push_back(&other);
    expression.data->lastExpression = true;
    expression.data->hasRight = true;
    return expression;
  }
  
  MatcherExpression<T> &operator | (MatcherExpression<T> &(*emptyMatcher)()) {
    MatcherExpression<T> &matcher = emptyMatcher();
    ValueMatcherExpression<T> &expression = *this;
    expression.data->right.push_back(&matcher);
    expression.data->lastExpression = true;
    expression.data->hasRight = true;
    return expression;
  }
  
  MatcherExpression<T> &operator | (const char *message) {
    ValueMatcherExpression<T> &expression = *this;
    expression.data->message = expression.data->message.append(message);
    expression.data->lastExpression = false;
    expression.data->hasRight = true;
    return expression;
  }
  
  MatcherExpression<T> &operator | (std::string &message) {
    ValueMatcherExpression<T> &expression = *this;
    expression.data->message = expression.data->message.append(message);
    expression.data->lastExpression = false;
    expression.data->hasRight = true;
    return expression;
  }
  
  MatcherExpression<T> &operator | (StringBuilder &message) {
    ValueMatcherExpression<T> &expression = *this;
    expression.data->message = expression.data->message.append(message);
    expression.data->lastExpression = false;
    expression.data->hasRight = true;
    return expression;
  }
};



END_NAMESPACE_EXPECT



/// Create a custom matcher.
/// \param name
///   The name of the matcher.
/// \param type
///   The type that the matcher matches for.
/// \param ...
///   The full type of the custom matcher, including template arguments.
/// \remarks
///   A custom matcher should have a `bool evaluate(type value)` method and
///   can optionally define a custom
///   `std::string message(type value, bool succeeded)` method.
#define MATCHER(name, type, ...) \
  struct name : ::NAMESPACE_EXPECT Matcher<type, __VA_ARGS__>

/// The result of a matcher type.
/// \param type
///   The type that the matcher matches for.
/// \remarks
///   Should be used to instantiate a matcher.
///   For example,
///   ```
///   template<typename T>
///   MATCHER_RESULT(T) isZero() {
///     return IsZero<T>();
///   }
///   ```
#define MATCHER_RESULT(type) \
  ::NAMESPACE_EXPECT MatcherExpression<type> &



/// Use the standard Expect matchers.
#define USE_EXPECT_MATCHING \
  using namespace NAMESPACE_EXPECT Matchers;
