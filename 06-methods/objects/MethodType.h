#pragma once

#include "ObjectType.h"
#include <nterms_classes/type/Type.h>
#include <string>
#include <vector>
#include <nterms_classes/declarations/MethodDeclaration.h>

class MethodType : public ObjectType {
 public:
   MethodType(MethodDeclaration* method_declaration);
   //std::string GetTypeName() override;
   Type* GetReturnValueType();
   //std::string GetObject() override;
   MethodDeclaration* GetMethodDeclaration();
 private:
  MethodDeclaration *method_declaration_;
  FormalList* formal_list_;
  Type* return_value_type_;
};



