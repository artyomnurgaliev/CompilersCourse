
#include "IfElseStatement.h"
IfElseStatement::IfElseStatement(Expression *expression, Statement *statement,
                                 Statement *else_statement)
    : expression_(expression), statement_(statement),
      else_statement_(else_statement) {}
void IfElseStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
Expression *IfElseStatement::GetExpression() const { return expression_; }
void IfElseStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
Statement *IfElseStatement::GetStatement() const { return statement_; }
void IfElseStatement::SetStatement(Statement *statement) {
  statement_ = statement;
}
Statement *IfElseStatement::GetElseStatement() const { return else_statement_; }
void IfElseStatement::SetElseStatement(Statement *else_statement) {
  else_statement_ = else_statement;
}
