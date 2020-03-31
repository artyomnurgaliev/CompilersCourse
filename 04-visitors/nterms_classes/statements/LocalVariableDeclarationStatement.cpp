//
// Created by artyom on 15.03.2020.
//

#include "LocalVariableDeclarationStatement.h"
LocalVariableDeclarationStatement::LocalVariableDeclarationStatement(
    LocalVariableDeclaration *local_variable_declaration) : local_variable_declaration_(local_variable_declaration) {}
void LocalVariableDeclarationStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
LocalVariableDeclaration *
LocalVariableDeclarationStatement::GetLocalVariableDeclaration() const {
  return local_variable_declaration_;
}
void LocalVariableDeclarationStatement::SetLocalVariableDeclaration(
    LocalVariableDeclaration *local_variable_declaration) {
  local_variable_declaration_ = local_variable_declaration;
}
