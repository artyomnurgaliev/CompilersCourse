
#include "ReturnStatement.h"
ReturnStatement::ReturnStatement(Expression *expression)
    : expression_(expression) {}
void ReturnStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
Expression *ReturnStatement::GetExpression() const { return expression_; }
void ReturnStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
