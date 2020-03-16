#pragma once


#include "Statement.h"
#include <nterms_classes/Lvalue/Lvalue.h>
#include <nterms_classes/expressions/Expression.h>
class AssignmentStatement : public Statement {
public:
  AssignmentStatement(Lvalue* lvalue, Expression* expression);
private:
  Lvalue* lvalue_;
  Expression* expression_;
};
