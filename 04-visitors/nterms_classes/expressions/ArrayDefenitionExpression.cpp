//
// Created by artyom on 15.03.2020.
//

#include "ArrayDefenitionExpression.h"
ArrayDefenitionExpression::ArrayDefenitionExpression(SimpleType *simple_type,
                                                     Expression *expression): simple_type_(simple_type), expression_(expression) {}
void ArrayDefenitionExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
SimpleType *ArrayDefenitionExpression::GetSimpleType() const {
  return simple_type_;
}
void ArrayDefenitionExpression::SetSimpleType(SimpleType *simple_type) {
  simple_type_ = simple_type;
}
Expression *ArrayDefenitionExpression::GetExpression() const {
  return expression_;
}
void ArrayDefenitionExpression::SetExpression(Expression *expression) {
  expression_ = expression;
}
