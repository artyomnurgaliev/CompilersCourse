#pragma once

#include <vector>
#include "Expression.h"
class ExpressionList:public BaseElement {
public:
  void AddExpression(Expression* expression);
  void Accept(Visitor* visitor) override;
  const std::vector<Expression *> &GetExpressions() const;
  void SetExpressions(const std::vector<Expression *> &expressions);

private:
  std::vector<Expression*> expressions;
};

