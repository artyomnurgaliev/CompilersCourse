#pragma once

#include "ObjectType.h"
#include <nterms_classes/type/Type.h>
#include <string>
#include <vector>
class MethodType : public ObjectType {
 public:
   MethodType(Type* type, FormalList* formal_list);
   std::string GetTypeName() override;
   Type* GetType();
 private:
  FormalList* formal_list_;
  Type* return_value_type_;
};



