#pragma once


#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class AssertStatement : public Statement {
public:
  AssertStatement(Expression* expression);

private:
  Expression* expression_;
};

