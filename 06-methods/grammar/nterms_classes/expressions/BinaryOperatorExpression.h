#pragma once
#include "Expression.h"
#include <nterms_classes/BinaryOperator.h>

class BinaryOperatorExpression : public Expression {
 public:
    BinaryOperatorExpression(Expression* e1, BinaryOperator* binary_operator, Expression* e2);
    void Accept(Visitor* visitor) override;
    Expression *GetFirst() const;
    void SetFirst(Expression *first);
    Expression *GetSecond() const;
    void SetSecond(Expression *second);
    BinaryOperator *GetBinaryOperator() const;
    void SetBinaryOperator(BinaryOperator *binary_operator);

  private:
    Expression* first_;
    Expression* second_;
    BinaryOperator* binary_operator_;
};