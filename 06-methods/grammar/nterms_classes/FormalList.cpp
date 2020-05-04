//
// Created by artyom on 15.03.2020.
//

#include "FormalList.h"

#include <utility>
void FormalList::AddFormal(Formal* formal) {
  formals_.push_back(formal);
}
void FormalList::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::vector<Formal*> &FormalList::GetFormals() const { return formals_; }
int FormalList::GetSize() {
  return formals_.size();
}
