#pragma once
#include "expressions/Expression.h"
#include <nterms_classes/expressions/ExpressionList.h>
#include <string>
class MethodInvocation {
public:
  MethodInvocation(Expression* expression, std::string identifier);
  MethodInvocation(Expression* expression, std::string identifier, Expression* first, ExpressionList* expression_list);

private:
  Expression* expression_;
  std::string identifier_;
  Expression* first_{};
  ExpressionList* expression_list_{};
};


