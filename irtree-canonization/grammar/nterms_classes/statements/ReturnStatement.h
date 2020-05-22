#pragma once

#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class ReturnStatement : public Statement {
public:
  ReturnStatement(Expression* expression);
  void Accept(Visitor* visitor) override;
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  Expression* expression_;
};


