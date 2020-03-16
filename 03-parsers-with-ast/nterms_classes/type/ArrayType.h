#pragma once

#include "SimpleType.h"
class ArrayType : public TypeClass {
public:
  explicit ArrayType(SimpleType* simple_type);

private:
  SimpleType* simple_type_;
};

