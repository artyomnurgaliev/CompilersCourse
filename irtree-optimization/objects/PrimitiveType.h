#pragma once
#include "ObjectType.h"

class PrimitiveType : public ObjectType{
 public:
  virtual size_t GetSize() = 0;
  virtual bool IsArray() = 0;
  std::string GetTypeName() override;
};

