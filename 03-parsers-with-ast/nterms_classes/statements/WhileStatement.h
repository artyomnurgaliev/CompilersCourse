#pragma once


#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class WhileStatement : public Statement {
public:
  WhileStatement(Expression* expression, Statement* statement);

private:
  Expression* expression_;
  Statement* statement_;
};
