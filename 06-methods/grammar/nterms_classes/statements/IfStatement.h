#pragma once


#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class IfStatement : public Statement {
public:
  IfStatement(Expression* expression, Statement* statement);
  void Accept(Visitor* visitor) override;
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);
  Statement *GetStatement() const;
  void SetStatement(Statement *statement);

private:
  Expression* expression_;
  Statement* statement_;
};


