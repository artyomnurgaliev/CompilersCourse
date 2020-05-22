#pragma once

#include "Expression.h"
class AccessToArrayElementExpression : public Expression{
public:
  AccessToArrayElementExpression(Expression* first, Expression* second);
  void Accept(Visitor* visitor) override;
  Expression *GetFirst() const;
  void SetFirst(Expression *first);
  Expression *GetSecond() const;
  void SetSecond(Expression *second);

private:
  Expression* first_;
  Expression* second_;
};


