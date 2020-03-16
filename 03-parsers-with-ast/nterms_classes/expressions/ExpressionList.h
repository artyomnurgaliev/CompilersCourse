#pragma once

#include <vector>
#include "Expression.h"
class ExpressionList {
public:
  void AddExpression(Expression* expression);

private:
  std::vector<Expression*> expressions;
};

