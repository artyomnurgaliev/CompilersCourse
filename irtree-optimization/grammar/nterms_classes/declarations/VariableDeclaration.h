#pragma once

#include <nterms_classes/type/Type.h>
#include <string>
class VariableDeclaration : public BaseElement {
public:
  VariableDeclaration(Type* type, std::string identifier);
  void Accept(Visitor* visitor) override;
  Type *GetType() const;
  void SetType(Type *type);
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);

private:
  Type* type_;
  std::string identifier_;
};


