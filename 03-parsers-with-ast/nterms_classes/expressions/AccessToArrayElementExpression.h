#pragma once

#include "Expression.h"
class AccessToArrayElementExpression : public Expression{
public:
  AccessToArrayElementExpression(Expression* first, Expression* second);

private:
  Expression* first_;
  Expression* second_;
};


