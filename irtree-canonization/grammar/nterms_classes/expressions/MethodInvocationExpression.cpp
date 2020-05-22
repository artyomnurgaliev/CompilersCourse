//
// Created by artyom on 15.03.2020.
//

#include "MethodInvocationExpression.h"
MethodInvocationExpression::MethodInvocationExpression(
    MethodInvocation *method_invocation) : method_invocation_(method_invocation) {}
void MethodInvocationExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
MethodInvocation *MethodInvocationExpression::GetMethodInvocation() const {
  return method_invocation_;
}
void MethodInvocationExpression::SetMethodInvocation(
    MethodInvocation *method_invocation) {
  method_invocation_ = method_invocation;
}
