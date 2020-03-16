#pragma once

#include "Statement.h"
#include <nterms_classes/LocalVariableDeclaration.h>
class LocalVariableDeclarationStatement : public Statement{
public:
  LocalVariableDeclarationStatement(LocalVariableDeclaration* local_variable_declaration);

private:
  LocalVariableDeclaration* local_variable_declaration_;
};
