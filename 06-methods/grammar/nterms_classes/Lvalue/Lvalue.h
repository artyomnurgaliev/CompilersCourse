#pragma once
#include <string>
#include <base_elements/BaseElement.h>
class Lvalue : public BaseElement {
 public:
  virtual bool IsSimple() = 0;
  virtual const std::string &GetIdentifier() const = 0;
  void Accept(Visitor *visitor) override {
    visitor->Visit(this);
  }
};

