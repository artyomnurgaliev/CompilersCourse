#pragma once
#include "Expression.h"

class NumberExpression: public Expression {
public:
    explicit NumberExpression(int value);
    void Accept(Visitor* visitor) override;
    int GetValue() const;
    void SetValue(int value);

  private:
    int value_;
};