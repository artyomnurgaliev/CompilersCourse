//
// Created by artyom on 15.03.2020.
//

#include "ArrayElementLvalue.h"

#include <utility>
ArrayElementLvalue::ArrayElementLvalue(std::string identifier,
                                       Expression *expression) : identifier_(std::move(identifier)), expression_(expression) {}
void ArrayElementLvalue::Accept(Visitor *visitor) { visitor->Visit(this); }
const std::string &ArrayElementLvalue::GetIdentifier() const {
  return identifier_;
}
void ArrayElementLvalue::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier;
}
Expression *ArrayElementLvalue::GetExpression() const { return expression_; }
void ArrayElementLvalue::SetExpression(Expression *expression) {
  expression_ = expression;
}
bool ArrayElementLvalue::IsSimple() {
  return false;
}