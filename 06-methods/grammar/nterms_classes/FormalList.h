#pragma once
#include "Formal.h"
#include <base_elements/BaseElement.h>
#include <string>
#include <vector>
class FormalList:public BaseElement {
public:
  void AddFormal(Formal* formal);
  void Accept(Visitor* visitor) override;
  const std::vector<Formal*> &GetFormals() const;

private:
  std::vector<Formal*> formals_;
};

