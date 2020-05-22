

#include "VariableDeclaration.h"

#include <utility>
VariableDeclaration::VariableDeclaration(Type *type, std::string identifier)
    : type_(type), identifier_(std::move(identifier)) {}
void VariableDeclaration::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Type *VariableDeclaration::GetType() const { return type_; }
void VariableDeclaration::SetType(Type *type) { type_ = type; }
const std::string &VariableDeclaration::GetIdentifier() const {
  return identifier_;
}
void VariableDeclaration::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier;
}
