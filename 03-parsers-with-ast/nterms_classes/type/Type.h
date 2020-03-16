#pragma once
#include "TypeClass.h"
class Type {
public:
  Type(TypeClass* type_class);

private:
  TypeClass* type_class_;
};

