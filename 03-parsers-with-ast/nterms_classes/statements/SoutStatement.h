#pragma once

#include "Statement.h"
#include <nterms_classes/expressions/Expression.h>
class SoutStatement : public Statement {
public:
  SoutStatement(Expression* expression);
private:
  Expression* expression_;
};
