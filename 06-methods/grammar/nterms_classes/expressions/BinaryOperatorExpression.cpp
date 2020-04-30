#include "BinaryOperatorExpression.h"

BinaryOperatorExpression::BinaryOperatorExpression(Expression *e1,BinaryOperator* binary_operator, Expression *e2): first_(e1), binary_operator_(binary_operator), second_(e2) {}
void BinaryOperatorExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Expression *BinaryOperatorExpression::GetFirst() const { return first_; }
void BinaryOperatorExpression::SetFirst(Expression *first) { first_ = first; }
Expression *BinaryOperatorExpression::GetSecond() const { return second_; }
void BinaryOperatorExpression::SetSecond(Expression *second) {
  second_ = second;
}
BinaryOperator *BinaryOperatorExpression::GetBinaryOperator() const {
  return binary_operator_;
}
void BinaryOperatorExpression::SetBinaryOperator(
    BinaryOperator *binary_operator) {
  binary_operator_ = binary_operator;
}
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