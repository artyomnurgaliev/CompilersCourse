#pragma once
#include "Expression.h"

class NumberExpression: public Expression {
public:
    explicit NumberExpression(int value);
private:
    int value_;
};