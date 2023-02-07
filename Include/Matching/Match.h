// ===--- Match.h ------------------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The interface for evaluating match asserts.                                //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>
#include <Expression/Expression.h>
#include "Matcher.h"
#include <stack>

START_NAMESPACE_EXPECT



/// An expectation builder for a matcher assertion.
template<typename T>
struct ExpectThatBuilder : Expressions::Expression {
  /// The value to match.
  T value;
  
  /// The matcher expressions.
  std::vector<MatcherExpression<T> *> matchers = { };
  /// The final composed failure message.
  std::string failMessages = "";
  
  /// A flag to check if the builder is currently in an expression.
  /// Used for expression validation.
  bool inExpression = false;
  
  ExpectThatBuilder<T>(T value) : value(value) { }
  
  /// Evaluate the expression with the set values.
  bool evaluate() {
    bool success = true;
    size_t count = 1;
    for (MatcherExpression<T> *matcher : matchers) {
      if (!matcher->evaluate(value)) {
        failMessages.append(" Condition #").append(toString(count))
          .append(" failed: ").append(matcher->failMessage(value));
        success = false;
      }
      count++;
    }
    return success;
  }
  
  /// The message to report if the evaluation failed.
  std::string failMessage() {
    return toString(value)
      .append(" did not match the set conditions.")
      .append(failMessages);
  }
  
  ExpectThatBuilder<T> operator | (MatcherExpression<T> &matcher) {
    this->message = this->message.append(matcher.message());
    this->matchers.push_back(&matcher);
    inExpression = true;
    return *this;
  }
  
  ExpectThatBuilder<T> operator | (MatcherExpression<T> &(*emptyMatcher)()) {
    MatcherExpression<T> &matcher = emptyMatcher();
    this->message = this->message.append(matcher.message());
    this->matchers.push_back(&matcher);
    inExpression = true;
    return *this;
  }
  
  /// Load a message into the builder.
  ExpectThatBuilder<T> operator | (const char *message) {
    this->message = this->message.append(message);
    inExpression = false;
    return *this;
  }
  
  ExpectThatBuilder<T> operator | (std::string &message) {
    this->message = this->message.append(message);
    inExpression = false;
    return *this;
  }
  
  ExpectThatBuilder<T> operator | (StringBuilder &message) {
    this->message = this->message.append(message);
    inExpression = false;
    return *this;
  }
  
  ExpectThatBuilder<T> operator ||(MatcherExpression<T> &matcher) {
    if (!matcher.messageAccessed())
      this->message = this->message.append(matcher.message());
    if (!inExpression)
      throw "Improperly formatted match expression.";
    
    // builder | [expression *this] || [expression matcher]
    // X | ... || d && a | b | c && (d || g) | f
    // X | ... || ((d &&0 a | b | c) &&1 (d ||2 g) | f)
    //   stack: { &&1, nullptr }
    //   stack: { ||2, &&1 } { &&0, &&1 }
    //   &&0.rhs.hasRight
    //   
    //   tree: &&0.rhs -rhs> &&0 -lhs> &&1 -> nullptr
    //   take all immediate -rhs>
    //   root: &&0
    //   push:
    // X | ... || d &&0 a | b | c
    //   
    //   go up the stack
    //     &&1: call &&
    // X | [expression *this] && [expression &&1.rhs]
    //     nullptr: done
    
    // Find the first right expression
    struct Stack {
      size_t referenceCount = 1;
      MatcherExpression<T> &matcher;
      Stack *parent;
      bool rhs;
      
      Stack(
        MatcherExpression<T> &matcher,
        Stack *parent,
        bool rhs
      ) : matcher(matcher), parent(parent), rhs(rhs) { }
      
      Stack(
        Stack *other
      ) : matcher(other->matcher), parent(other->parent), rhs(other->rhs) {
        if (parent != nullptr)
          parent->referenceCount++;
      }
      
      void release() {
        referenceCount--;
        if (referenceCount == 0) {
          if (parent != nullptr)
            parent->release();
          delete this;
        }
      }
    };
    std::stack<Stack *> stack { };
    stack.push(new Stack(matcher, nullptr, false));
    while (!stack.empty()) {
      Stack *top = stack.top();
      if (!top->matcher.hasRight()) {
        stack.pop();
        switch (top->matcher.type()) {
        case MatcherExpressionType::And: {
          AndMatcherExpression<T> &matcher = (AndMatcherExpression<T> &)top->matcher;
          stack.push(new Stack(matcher.rhs(), new Stack(top), true ));
          stack.push(new Stack(matcher.lhs(), new Stack(top), false));
        } break;
        
        case MatcherExpressionType::Or: {
          OrMatcherExpression<T> &matcher = (OrMatcherExpression<T> &)top->matcher;
          stack.push(new Stack(matcher.rhs(), new Stack(top), true ));
          stack.push(new Stack(matcher.lhs(), new Stack(top), false));
        } break;
        
        default: break;
        }
        
        top->release();
      } else {
        // Extract the complete expression
        Stack *expression = top;
        while (expression->rhs)
          expression = expression->parent;
        
        MatcherExpression<T> *last = (MatcherExpression<T> *)matchers[matchers.size() - 1];
        if (last->type() == MatcherExpressionType::Or) {
          OrMatcherExpression<T> *lastOr = (OrMatcherExpression<T> *)last;
          while (lastOr->rhs().type() == MatcherExpressionType::Or)
            lastOr = (OrMatcherExpression<T> *)&lastOr->rhs();
          lastOr->rhs() = *new OrMatcherExpression<T>(lastOr->rhs(), expression->matcher);
        } else {
          matchers.pop_back();
          matchers.push_back(new OrMatcherExpression<T>(*last, expression->matcher));
        }
        
        for (MatcherExpression<T> *right : top->matcher.right()) {
          if (!right->messageAccessed())
            message = message.append(right->message());
          matchers.push_back(right);
        }
        inExpression = top->matcher.lastExpression();
        
        expression = expression->parent;
        while (expression != nullptr) {
          // All upper expressions should be lhs only, but just in case check
          if (!expression->rhs)
            switch (expression->matcher.type()) {
            case MatcherExpressionType::And: {
              AndMatcherExpression<T> &matcher = (AndMatcherExpression<T> &)expression->matcher;
              *this && matcher.rhs();
            } break;
            
            case MatcherExpressionType::Or: {
              OrMatcherExpression<T> &matcher = (OrMatcherExpression<T> &)expression->matcher;
              *this || matcher.rhs();
            } break;
            
            default: break;
            }
          
          expression = expression->parent;
        }
        
        while (!stack.empty()) {
          stack.top()->release();
          stack.pop();
        }
        return *this;
      }
    }
    
    // No other divisions: add to hierarchy
    MatcherExpression<T> *last = matchers[matchers.size() - 1];
    if (last->type() == MatcherExpressionType::Or) {
      OrMatcherExpression<T> *lastOr = (OrMatcherExpression<T> *)last;
      while (lastOr->rhs().type() == MatcherExpressionType::Or)
        lastOr = (OrMatcherExpression<T> *)&lastOr->rhs();
      lastOr->rhs() = *new OrMatcherExpression<T>(lastOr->rhs(), matcher);
    } else {
      matchers.pop_back();
      matchers.push_back(new OrMatcherExpression<T>(*last, matcher));
    }
    
    return *this;
  }
  
  ExpectThatBuilder<T> operator ||(MatcherExpression<T> &(*emptyMatcher)()) {
    return *this || emptyMatcher();
  }
  
  ExpectThatBuilder<T> operator &&(MatcherExpression<T> &matcher) {
    if (!matcher.messageAccessed())
      this->message = this->message.append(matcher.message());
    if (!inExpression)
      throw "Improperly formatted match expression.";
    
    // Find the first right expression
    struct Stack {
      size_t referenceCount = 1;
      MatcherExpression<T> &matcher;
      Stack *parent;
      bool rhs;
      
      Stack(
        MatcherExpression<T> &matcher,
        Stack *parent,
        bool rhs
      ) : matcher(matcher), parent(parent), rhs(rhs) { }
      
      Stack(
        Stack *other
      ) : matcher(other->matcher), parent(other->parent), rhs(other->rhs) {
        if (parent != nullptr)
          parent->referenceCount++;
      }
      
      void release() {
        referenceCount--;
        if (referenceCount == 0) {
          if (parent != nullptr)
            parent->release();
          delete this;
        }
      }
    };
    std::stack<Stack *> stack { };
    stack.push(new Stack(matcher, nullptr, false));
    while (!stack.empty()) {
      Stack *top = stack.top();
      if (!top->matcher.hasRight()) {
        stack.pop();
        if (top->matcher.type() == MatcherExpressionType::And) {
          AndMatcherExpression<T> &matcher = (AndMatcherExpression<T> &)top->matcher;
          stack.push(new Stack(matcher.rhs(), new Stack(top), true ));
          stack.push(new Stack(matcher.lhs(), new Stack(top), false));
        }
        top->release();
      } else {
        // Extract the complete expression
        Stack *expression = top;
        while (expression->rhs)
          expression = expression->parent;
        
        MatcherExpression<T> *last = (MatcherExpression<T> *)matchers[matchers.size() - 1];
        if (last->type() == MatcherExpressionType::And) {
          AndMatcherExpression<T> *lastAnd = (AndMatcherExpression<T> *)last;
          while (lastAnd->rhs().type() == MatcherExpressionType::And)
            lastAnd = (AndMatcherExpression<T> *)&lastAnd->rhs();
          lastAnd->rhs() = *new AndMatcherExpression<T>(lastAnd->rhs(), expression->matcher);
        } else {
          matchers.pop_back();
          matchers.push_back(new AndMatcherExpression<T>(*last, expression->matcher));
        }
        
        for (MatcherExpression<T> *right : top->matcher.right()) {
          if (!right->messageAccessed())
            message = message.append(right->message());
          matchers.push_back(right);
        }
        inExpression = top->matcher.lastExpression();
        
        expression = expression->parent;
        while (expression != nullptr) {
          // All upper expressions should be lhs only, but just in case check
          if (!expression->rhs) {
            AndMatcherExpression<T> &matcher = (AndMatcherExpression<T> &)expression->matcher;
            *this && matcher.rhs();
          }
          
          expression = expression->parent;
        }
        
        while (!stack.empty()) {
          stack.top()->release();
          stack.pop();
        }
        return *this;
      }
    }
    
    // No other divisions: add to hierarchy
    MatcherExpression<T> *last = matchers[matchers.size() - 1];
    if (last->type() == MatcherExpressionType::And) {
      AndMatcherExpression<T> *lastAnd = (AndMatcherExpression<T> *)last;
      while (lastAnd->rhs().type() == MatcherExpressionType::And)
        lastAnd = (AndMatcherExpression<T> *)&lastAnd->rhs();
      lastAnd->rhs() = *new AndMatcherExpression<T>(lastAnd->rhs(), matcher);
    } else {
      matchers.pop_back();
      matchers.push_back(new AndMatcherExpression<T>(*last, matcher));
    }
    
    return *this;
  }
  
  ExpectThatBuilder<T> operator &&(MatcherExpression<T> &(*emptyMatcher)()) {
    return *this && emptyMatcher();
  }
};

/// The start of a matching expectation builder.
struct ExpectThat {
  /// Load a value for which to build expectations.
  /// \param[in] other
  ///   The value for which to build expectations.
  /// \returns
  ///   An expectation builder for the given value.
  template<typename T>
  ExpectThatBuilder<T> operator << (T other) {
    return { other };
  }
};



END_NAMESPACE_EXPECT



/// Match a value to a set of expectations.
/// \remarks
///   Only a single value should be used for matching, all other expressions
///   passed to the expectation, using vertical bars (`|`), should be matchers.
#define EXPECT_THAT \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, false), \
    NAMESPACE_EXPECT ExpectThat() <<

/// Match a value to a set of expectations, stopping the test case upon failure.
/// \remarks
///   Only a single value should be used for matching, all other expressions
///   passed to the expectation, using vertical bars (`|`), should be matchers.
#define ASSERT_THAT \
  NAMESPACE_EXPECT Evaluate(__environment, __FILE__, __LINE__, true), \
    NAMESPACE_EXPECT ExpectThat() <<
