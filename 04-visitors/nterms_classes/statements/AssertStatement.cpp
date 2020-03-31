//
// Created by artyom on 15.03.2020.
//

#include "AssertStatement.h"
AssertStatement::AssertStatement(Expression *expression)
    : expression_(expression) {}
void AssertStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
Expression *AssertStatement::GetExpression() const { return expression_; }
void AssertStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
