#pragma once
#include "ObjectType.h"
#include "ClassType.h"
#include "PrimitiveSimpleType.h"
class PrimitiveArrayType : public PrimitiveType {
 public:
  bool IsArray() override;
  PrimitiveSimpleType* GetSimpleType();
  std::string GetTypeName() override;
  size_t GetSize() override ;
  explicit PrimitiveArrayType(PrimitiveSimpleType* primitive_type);
  explicit PrimitiveArrayType(ArrayType *type);
 private:
  PrimitiveSimpleType* simple_type_;
};

