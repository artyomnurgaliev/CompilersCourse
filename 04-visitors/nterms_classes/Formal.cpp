
#include "Formal.h"

#include <utility>
Formal::Formal(Type *type, std::string identifier)
    : type_(type), identifier_(std::move(identifier)) {}
void Formal::Accept(Visitor *visitor) { visitor->Visit(this);}
Type *Formal::GetType() const { return type_; }
const std::string &Formal::GetIdentifier() const { return identifier_; }
