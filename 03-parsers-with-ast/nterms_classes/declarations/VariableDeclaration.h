#pragma once


#include "DeclarationClass.h"
#include <nterms_classes/type/Type.h>
#include <string>
class VariableDeclaration : public DeclarationClass {
public:
  VariableDeclaration(Type* type, std::string identifier);

private:
  Type* type_;
  std::string identifier_;
};


