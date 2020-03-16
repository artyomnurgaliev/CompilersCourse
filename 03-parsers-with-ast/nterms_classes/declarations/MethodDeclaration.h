#pragma once


#include "DeclarationClass.h"
#include <nterms_classes/FormalList.h>
#include <nterms_classes/statements/StatementList.h>
class MethodDeclaration :public DeclarationClass {
public:
  MethodDeclaration(Type* type, std::string identifier, FormalList* formals, StatementList* statements);
  MethodDeclaration(Type* type, std::string identifier, StatementList* statements);

private:
  Type* type_;
  std::string identifier_;
  FormalList* formals_{};
  StatementList* statements_;
};

