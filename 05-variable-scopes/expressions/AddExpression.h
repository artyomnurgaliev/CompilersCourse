#pragma once
#include "Expression.h"

class BinaryOperatorExpression : public Expression {
 public:
   BinaryOperatorExpression(Expression* e1, Expression* e2);
    int eval() const override;
    void Accept(Visitor* visitor) override;
    Expression* first;
    Expression* second;
};