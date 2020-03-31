
#include "WhileStatement.h"
WhileStatement::WhileStatement(Expression *expression, Statement *statement)
    : expression_(expression), statement_(statement) {}
void WhileStatement::Accept(Visitor *visitor) {visitor->Visit(this);}
Expression *WhileStatement::GetExpression() const { return expression_; }
void WhileStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
Statement *WhileStatement::GetStatement() const { return statement_; }
void WhileStatement::SetStatement(Statement *statement) {
  statement_ = statement;
}
