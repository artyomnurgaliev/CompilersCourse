#pragma once

#include <grammar/nterms_classes/type/Type.h>
#include "ObjectType.h"
#include "ClassType.h"
class PrimitiveSimpleType : public PrimitiveType {
 public:
  bool IsClass();
  bool IsArray() override ;
  std::string GetTypeName() override ;
  size_t GetSize() override ;
  explicit PrimitiveSimpleType(SimpleType* type);
  bool is_class_ = false;
  SimpleType* type_{};
};


