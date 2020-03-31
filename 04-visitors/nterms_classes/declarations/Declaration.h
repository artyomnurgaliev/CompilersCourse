#pragma once

#include <base_elements/BaseElement.h>
class Declaration :public BaseElement{
public:
  explicit Declaration(MethodDeclaration* method_declaration);
  explicit Declaration(VariableDeclaration* variable_declaration);

  void Accept(Visitor* visitor) override;
  MethodDeclaration *GetMethodDeclaration() const;
  void SetMethodDeclaration(MethodDeclaration *method_declaration);
  VariableDeclaration *GetVariableDeclaration() const;
  void SetVariableDeclaration(VariableDeclaration *variable_declaration);
  bool IsVariable() const;
  void SetIsVariable(bool is_variable);

private:
  MethodDeclaration* method_declaration_ = nullptr;
  VariableDeclaration* variable_declaration_ = nullptr;
  bool is_variable_ = true;
};
