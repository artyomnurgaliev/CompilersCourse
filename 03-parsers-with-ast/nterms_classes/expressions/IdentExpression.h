#pragma once
#include "Expression.h"

#include <string>

class IdentExpression: public Expression {
 public:
    IdentExpression(std::string  ident);
 private:
    std::string ident_;
};