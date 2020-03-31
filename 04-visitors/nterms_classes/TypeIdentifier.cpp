#include "TypeIdentifier.h"

#include <utility>
TypeIdentifier::TypeIdentifier(std::string identifier)
    : identifier_(std::move(identifier)) {}
std::string TypeIdentifier::GetIdentifier() { return identifier_; }
void TypeIdentifier::Accept(Visitor *visitor) {visitor->Visit(this);}
