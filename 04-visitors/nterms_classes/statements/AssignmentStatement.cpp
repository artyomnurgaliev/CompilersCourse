

#include "AssignmentStatement.h"
AssignmentStatement::AssignmentStatement(Lvalue *lvalue, Expression *expression)
    : lvalue_(lvalue), expression_(expression) {}
void AssignmentStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Lvalue *AssignmentStatement::GetLvalue() const { return lvalue_; }
void AssignmentStatement::SetLvalue(Lvalue *lvalue) { lvalue_ = lvalue; }
Expression *AssignmentStatement::GetExpression() const { return expression_; }
void AssignmentStatement::SetExpression(Expression *expression) {
  expression_ = expression;
}
