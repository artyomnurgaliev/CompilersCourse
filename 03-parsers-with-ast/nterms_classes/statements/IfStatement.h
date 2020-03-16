#pragma once


#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class IfStatement : public Statement {
public:
  IfStatement(Expression* expression, Statement* statement);

private:
  Expression* expression_;
  Statement* statement_;
};


