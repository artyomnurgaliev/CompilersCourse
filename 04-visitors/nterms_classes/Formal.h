#pragma once
#include <base_elements/BaseElement.h>
#include <nterms_classes/type/Type.h>
#include <string>
class Formal :public BaseElement{
public:
  Formal(Type* type, std::string identifier);
  void Accept(Visitor* visitor) override;
  Type *GetType() const;
  const std::string &GetIdentifier() const;

private:
  Type* type_;
  std::string identifier_;
};


