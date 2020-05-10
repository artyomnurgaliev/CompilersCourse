#pragma once


#include "Expression.h"
class ParenthesisExpression: public Expression {
public:
  explicit ParenthesisExpression(Expression* expression);
  void Accept(Visitor* visitor) override;
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  Expression* expression_;
};

