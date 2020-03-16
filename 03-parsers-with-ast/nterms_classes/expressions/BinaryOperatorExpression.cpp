#include "BinaryOperatorExpression.h"

BinaryOperatorExpression::BinaryOperatorExpression(Expression *e1,BinaryOperator* binary_operator, Expression *e2): first_(e1), binary_operator_(binary_operator), second_(e2) {}
/*
int BinaryOperatorExpression::eval() const {
  std::string operator_name = binary_operator_->GetOperatorName();
  if (operator_name == "$$") {
    return first_ && second_;
  }
  if (operator_name == "||") {
    return first_ && second_;
  }
  if (operator_name == "<") {
    return first_ && second_;
  }
  if (operator_name == ">") {
    return first_ && second_;
  }
  if (operator_name == "==") {
    return first_ && second_;
  }
  if (operator_name == "+") {
    return first_ && second_;
  }
  if (operator_name == "-") {
    return first_ && second_;
  }
  if (operator_name == "*") {
    return first_ && second_;
  }
  if (operator_name == "/") {
    return first_ && second_;
  }
  if (operator_name == "%") {
    return first_ && second_;
  }
  return -1;
}*/