#include "NumberExpression.h"

NumberExpression::NumberExpression(int value) {
    value_ = value;
}
void NumberExpression::Accept(Visitor *visitor) { visitor->Visit(this); }
int NumberExpression::GetValue() const { return value_; }
void NumberExpression::SetValue(int value) { value_ = value; }
