#pragma once

#include "Expression.h"
class NotExpression: public Expression {
public:
  explicit NotExpression(Expression* expression);
  void Accept(Visitor* visitor) override;
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  Expression* expression_;
};

