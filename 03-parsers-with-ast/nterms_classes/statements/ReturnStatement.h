#pragma once

#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class ReturnStatement : public Statement {
public:
  ReturnStatement(Expression* expression);

private:
  Expression* expression_;
};


