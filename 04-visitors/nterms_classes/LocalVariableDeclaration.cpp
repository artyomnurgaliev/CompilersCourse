#include "LocalVariableDeclaration.h"
LocalVariableDeclaration::LocalVariableDeclaration(
    VariableDeclaration *variable_declaration) : variable_declaration_(variable_declaration) {}
void LocalVariableDeclaration::Accept(Visitor *visitor) {visitor->Visit(this);}
VariableDeclaration *LocalVariableDeclaration::GetVariableDeclaration() const {
  return variable_declaration_;
}
