#pragma once

#include "Expression.h"
class NotExpression: public Expression {
public:
  explicit NotExpression(Expression* expression);

private:
  Expression* expression_;
};

