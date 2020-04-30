#include "Declaration.h"

Declaration::Declaration(MethodDeclaration *method_declaration) : is_variable_(false), method_declaration_(method_declaration) {}
Declaration::Declaration(VariableDeclaration *variable_declaration) : is_variable_(true), variable_declaration_(variable_declaration){}
void Declaration::Accept(Visitor *visitor) { visitor->Visit(this); }
MethodDeclaration *Declaration::GetMethodDeclaration() const {
  return method_declaration_;
}
void Declaration::SetMethodDeclaration(MethodDeclaration *method_declaration) {
  method_declaration_ = method_declaration;
}
VariableDeclaration *Declaration::GetVariableDeclaration() const {
  return variable_declaration_;
}
void Declaration::SetVariableDeclaration(
    VariableDeclaration *variable_declaration) {
  variable_declaration_ = variable_declaration;
}
bool Declaration::IsVariable() const { return is_variable_; }
void Declaration::SetIsVariable(bool is_variable) {
  is_variable_ = is_variable;
}
