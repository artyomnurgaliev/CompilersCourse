//
// Created by artyom on 15.03.2020.
//

#include "SimpleLvalue.h"

#include <utility>
SimpleLvalue::SimpleLvalue(std::string identifier) : identifier_(std::move(identifier)) {}
void SimpleLvalue::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::string &SimpleLvalue::GetIdentifier() const { return identifier_; }
void SimpleLvalue::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier;
}
