//
// Created by artyom on 15.03.2020.
//

#include "ArrayNewExpression.h"
ArrayNewExpression::ArrayNewExpression(SimpleType *simple_type,
                                       Expression *expression): simple_type_(simple_type), expression_(expression) {}
void ArrayNewExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
SimpleType *ArrayNewExpression::GetSimpleType() const {
  return simple_type_;
}
void ArrayNewExpression::SetSimpleType(SimpleType *simple_type) {
  simple_type_ = simple_type;
}
Expression *ArrayNewExpression::GetExpression() const {
  return expression_;
}
void ArrayNewExpression::SetExpression(Expression *expression) {
  expression_ = expression;
}
