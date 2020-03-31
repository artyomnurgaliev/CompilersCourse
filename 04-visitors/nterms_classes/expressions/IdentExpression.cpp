#include "IdentExpression.h"

#include <utility>

IdentExpression::IdentExpression(std::string identifier): identifier_(std::move(identifier)) {}
void IdentExpression::Accept(Visitor *visitor) { visitor->Visit(this); }
const std::string &IdentExpression::GetIdentifier() const { return identifier_; }
void IdentExpression::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier; }

/*int IdentExpression::eval() const {
    return 0;
}*/