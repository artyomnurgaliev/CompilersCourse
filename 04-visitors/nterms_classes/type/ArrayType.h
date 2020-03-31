#pragma once

#include "SimpleType.h"
class ArrayType : public BaseElement {
public:
  explicit ArrayType(SimpleType* simple_type);
  void Accept(Visitor* visitor) override ;
  SimpleType *GetSimpleType() const;
  void SetSimpleType(SimpleType *simple_type);

private:
  SimpleType* simple_type_;
};

