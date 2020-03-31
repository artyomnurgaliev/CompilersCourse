//
// Created by artyom on 15.03.2020.
//

#include "ParenthesisExpression.h"
ParenthesisExpression::ParenthesisExpression(Expression *expression) : expression_(expression) {}
void ParenthesisExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Expression *ParenthesisExpression::GetExpression() const { return expression_; }
void ParenthesisExpression::SetExpression(Expression *expression) {
  expression_ = expression;
}
