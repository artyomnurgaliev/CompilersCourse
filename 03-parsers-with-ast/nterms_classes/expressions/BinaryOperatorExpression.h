#pragma once
#include "Expression.h"
#include <nterms_classes/BinaryOperator.h>

class BinaryOperatorExpression : public Expression {
 public:
   BinaryOperatorExpression(Expression* e1, BinaryOperator* binary_operator, Expression* e2);
 private:
    Expression* first_;
    Expression* second_;
    BinaryOperator* binary_operator_;
};