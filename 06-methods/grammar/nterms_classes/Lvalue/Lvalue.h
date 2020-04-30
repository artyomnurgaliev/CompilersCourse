#pragma once

#include <base_elements/BaseElement.h>
class Lvalue:public BaseElement{
public:
  void Accept(Visitor* visitor) override{
    visitor->Visit(this);
  }
};

