#pragma once
#include <nterms_classes/TypeIdentifier.h>
#include <string>
class SimpleType : public BaseElement {
public:
  explicit SimpleType(std::string simple_type_identifier);
  explicit SimpleType(TypeIdentifier* type_identifier);
  void Accept(Visitor* visitor) override ;
  const std::string &GetSimpleTypeIdentifier() const;
  void SetSimpleTypeIdentifier(const std::string &simple_type_identifier);

private:
  std::string simple_type_identifier_;
};


