//
// Created by artyom on 15.03.2020.
//

#include "NotExpression.h"
NotExpression::NotExpression(Expression *expression) :expression_(expression) {}
void NotExpression::Accept(Visitor *visitor) { visitor->Visit(this); }
Expression *NotExpression::GetExpression() const { return expression_; }
void NotExpression::SetExpression(Expression *expression) {
  expression_ = expression;
}
