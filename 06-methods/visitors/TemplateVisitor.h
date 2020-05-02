#pragma once

#include "include/visitors/Visitor.h"
#include <base_elements/BaseElement.h>

template<typename T>
class TemplateVisitor : public Visitor {
 public:
    T Accept(BaseElement* element) {
      element->Accept(this);
      return tos_value_;
    }
 protected:
    T tos_value_;

};