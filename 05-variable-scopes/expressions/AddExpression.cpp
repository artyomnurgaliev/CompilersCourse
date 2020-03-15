#include "AddExpression.h"

BinaryOperatorExpression::BinaryOperatorExpression(Expression *e1, Expression *e2): first(e1), second(e2) {}

int BinaryOperatorExpression::eval() const {
    return first->eval() + second->eval();
}

void BinaryOperatorExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}