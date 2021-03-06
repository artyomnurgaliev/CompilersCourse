#pragma once


#include "Statement.h"
#include <nterms_classes/Lvalue/Lvalue.h>
#include <nterms_classes/expressions/Expression.h>
class AssignmentStatement : public Statement {
public:
  AssignmentStatement(Lvalue* lvalue, Expression* expression);
  void Accept(Visitor* visitor) override;
  Lvalue *GetLvalue() const;
  void SetLvalue(Lvalue *lvalue);
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  Lvalue* lvalue_;
  Expression* expression_;
};
