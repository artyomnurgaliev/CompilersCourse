#pragma once
#include <nterms_classes/declarations/VariableDeclaration.h>
class LocalVariableDeclaration {
public:
  LocalVariableDeclaration(VariableDeclaration* variable_declaration);
private:
  VariableDeclaration* variable_declaration_;
};


