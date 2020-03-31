#pragma once


#include "Expression.h"
class ArrayLengthExpression: public Expression {
public:
  explicit ArrayLengthExpression(Expression* expression);
  void Accept(Visitor* visitor) override;
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  Expression* expression_;
};
