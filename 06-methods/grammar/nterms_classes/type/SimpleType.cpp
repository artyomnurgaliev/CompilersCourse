

#include "SimpleType.h"
#include <utility>

SimpleType::SimpleType(std::string simple_type_identifier)
    : simple_type_identifier_(std::move(simple_type_identifier)) {}
SimpleType::SimpleType(TypeIdentifier *type_identifier)
    : simple_type_identifier_(type_identifier->GetIdentifier()) {}
void SimpleType::Accept(Visitor *visitor) { visitor->Visit(this); }
const std::string &SimpleType::GetSimpleTypeIdentifier() const {
  return simple_type_identifier_;
}
void SimpleType::SetSimpleTypeIdentifier(
    const std::string &simple_type_identifier) {
  simple_type_identifier_ = simple_type_identifier;
}
