#pragma once


#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class AssertStatement : public Statement {
public:
  explicit AssertStatement(Expression* expression);

private:
  Expression* expression_;
};

