// ===--- MiscExpression.cpp ------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The implementation of miscellaneous assertion expressions.                 //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#include <Expression/MiscExpression.h>



template<>
bool NAMESPACE_EXPECT MiscExpressions::
  ExceptionValue<NAMESPACE_EXPECT TestFailedException>::evaluate() {
  try {
    value->expression();
  } catch (TestFailedException) {
    return true;
  } catch (...) {
    // Note that the wrong exception was triggered
    value->wrongTriggeredException = true;
    return false;
  }
  return false;
}

bool NAMESPACE_EXPECT MiscExpressions::AnyExceptionValue::evaluate() {
  try {
    expression();
  } catch (TestFailedException e) {
    // Propagate the test failure
    throw e;
  } catch (...) {
    return true;
  }
  return false;
}

bool NAMESPACE_EXPECT MiscExpressions::NoExceptionValue::evaluate() {
  try {
    expression();
  } catch (TestFailedException e) {
    // Propagate the test failure
    throw e;
  } catch (...) {
    return false;
  }
  return true;
}
