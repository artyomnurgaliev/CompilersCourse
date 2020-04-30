
#include "BoolExpression.h"
BoolExpression::BoolExpression(bool value) : value_(value) {}
void BoolExpression::Accept(Visitor *visitor) { visitor->Visit(this); }
bool BoolExpression::GetValue() const { return value_; }
void BoolExpression::SetValue(bool value) { value_ = value; }
