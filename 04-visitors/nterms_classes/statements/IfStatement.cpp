//
// Created by artyom on 15.03.2020.
//

#include "IfStatement.h"
IfStatement::IfStatement(Expression *expression, Statement *statement)
    : expression_(expression), statement_(statement) {}
void IfStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
Expression *IfStatement::GetExpression() const { return expression_; }
void IfStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
Statement *IfStatement::GetStatement() const { return statement_; }
void IfStatement::SetStatement(Statement *statement) { statement_ = statement; }
