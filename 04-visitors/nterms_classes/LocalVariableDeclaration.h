#pragma once
#include <base_elements/BaseElement.h>
#include <nterms_classes/declarations/VariableDeclaration.h>

class LocalVariableDeclaration: public BaseElement {
public:
  explicit LocalVariableDeclaration(VariableDeclaration* variable_declaration);
  void Accept(Visitor* visitor) override;
  VariableDeclaration *GetVariableDeclaration() const;

private:
  VariableDeclaration* variable_declaration_;
};


