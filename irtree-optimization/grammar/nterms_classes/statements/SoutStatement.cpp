

#include "SoutStatement.h"
SoutStatement::SoutStatement(Expression *expression)
    : expression_(expression) {}
void SoutStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
Expression *SoutStatement::GetExpression() const { return expression_; }
void SoutStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
