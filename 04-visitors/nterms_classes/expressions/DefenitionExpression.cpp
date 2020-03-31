//
// Created by artyom on 15.03.2020.
//

#include "DefenitionExpression.h"
DefenitionExpression::DefenitionExpression(TypeIdentifier* type_identifier) : type_identifier_(type_identifier){}
void DefenitionExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
TypeIdentifier *DefenitionExpression::GetTypeIdentifier() const {
  return type_identifier_;
}
void DefenitionExpression::SetTypeIdentifier(TypeIdentifier *type_identifier) {
  type_identifier_ = type_identifier;
}
