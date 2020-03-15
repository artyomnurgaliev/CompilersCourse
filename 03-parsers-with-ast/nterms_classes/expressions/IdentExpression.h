#pragma once
#include "Expression.h"

#include <string>

class IdentExpression: public Expression {
 public:
    IdentExpression(std::string  ident);
    int eval() const override;
 private:
    std::string ident_;
};