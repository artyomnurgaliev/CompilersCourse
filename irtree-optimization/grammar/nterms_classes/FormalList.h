#pragma once
#include "Formal.h"
#include <base_elements/BaseElement.h>
#include <string>
#include <deque>
class FormalList: public BaseElement {
public:
  void AddFormal(Formal* formal);
  void Accept(Visitor* visitor) override;
  const std::deque<Formal*> &GetFormals() const;
  int GetSize();
private:
  std::deque<Formal*> formals_;
};

