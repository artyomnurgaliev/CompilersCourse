//
// Created by artyom on 15.03.2020.
//

#include "AccessToArrayElementExpression.h"
AccessToArrayElementExpression::AccessToArrayElementExpression(
    Expression *first, Expression *second): first_(first), second_(second) {}
void AccessToArrayElementExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Expression *AccessToArrayElementExpression::GetFirst() const { return first_; }
void AccessToArrayElementExpression::SetFirst(Expression *first) {
  first_ = first;
}
Expression *AccessToArrayElementExpression::GetSecond() const {
  return second_;
}
void AccessToArrayElementExpression::SetSecond(Expression *second) {
  second_ = second;
}
