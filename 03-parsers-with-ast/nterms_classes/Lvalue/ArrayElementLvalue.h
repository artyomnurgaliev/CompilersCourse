#pragma once
#include <string>
#include "Lvalue.h"
#include <nterms_classes/expressions/Expression.h>

class ArrayElementLvalue : public Lvalue {
public:
  explicit ArrayElementLvalue(std::string identifier, Expression* expression);
private:
  std::string identifier_;
  Expression* expression_;;
};

