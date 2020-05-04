#pragma once
#include "ObjectType.h"

class PrimitiveType : public ObjectType{
 public:
  virtual bool IsArray() = 0;
  virtual std::string GetTypeName() = 0;
};

