//
// Created by artyom on 15.03.2020.
//

#include "MethodInvocation.h"

#include <utility>
MethodInvocation::MethodInvocation(Expression *expression,
                                   std::string identifier)
    : expression_(expression), identifier_(std::move(identifier)) {}
MethodInvocation::MethodInvocation(Expression *expression,
                                   std::string identifier, Expression *first,
                                   ExpressionList *expression_list)
    : expression_(expression), identifier_(std::move(identifier)),
      first_(first), expression_list_(expression_list) {}
void MethodInvocation::Accept(Visitor *visitor) {visitor->Visit(this);}
Expression *MethodInvocation::GetExpression() const { return expression_; }
const std::string &MethodInvocation::GetIdentifier() const {
  return identifier_;
}
Expression *MethodInvocation::GetFirst() const { return first_; }
ExpressionList *MethodInvocation::GetExpressionList() const {
  return expression_list_;
}
