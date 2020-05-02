#pragma once


#include "Expression.h"
#include <nterms_classes/type/SimpleType.h>
class ArrayNewExpression : public Expression{
public:
  ArrayNewExpression(SimpleType* simple_type, Expression* expression);
  void Accept(Visitor* visitor) override;
  SimpleType *GetSimpleType() const;
  void SetSimpleType(SimpleType *simple_type);
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  SimpleType* simple_type_;
  Expression* expression_;
};

