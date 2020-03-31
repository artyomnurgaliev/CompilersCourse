#pragma once


#include "Expression.h"
class ThisExpression: public Expression {
public:
  void Accept(Visitor* visitor) override;
  ThisExpression();
private:
};


