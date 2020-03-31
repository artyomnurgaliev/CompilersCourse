//
// Created by artyom on 15.03.2020.
//

#include "ArrayLengthExpression.h"
ArrayLengthExpression::ArrayLengthExpression(Expression *expression): expression_(expression) {}
void ArrayLengthExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Expression *ArrayLengthExpression::GetExpression() const { return expression_; }
void ArrayLengthExpression::SetExpression(Expression *expression) {
  expression_ = expression;
}
