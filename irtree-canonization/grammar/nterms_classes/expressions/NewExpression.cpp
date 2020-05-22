//
// Created by artyom on 15.03.2020.
//

#include "NewExpression.h"
NewExpression::NewExpression(TypeIdentifier* type_identifier) : type_identifier_(type_identifier){}
void NewExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
TypeIdentifier *NewExpression::GetTypeIdentifier() const {
  return type_identifier_;
}
void NewExpression::SetTypeIdentifier(TypeIdentifier *type_identifier) {
  type_identifier_ = type_identifier;
}
