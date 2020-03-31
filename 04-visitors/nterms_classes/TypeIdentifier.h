#pragma once
#include <base_elements/BaseElement.h>
#include <string>
class TypeIdentifier : public BaseElement {
public:
  void Accept(Visitor* visitor) override ;
  explicit TypeIdentifier(std::string identifier);
  std::string GetIdentifier();
private:
  std::string identifier_;
};


