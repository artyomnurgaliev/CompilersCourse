#pragma once


#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class IfElseStatement : public Statement{
public:
  IfElseStatement(Expression* expression, Statement* statement, Statement* else_statement);
private:
  Expression* expression_;
  Statement* statement_;
  Statement* else_statement_;
};
