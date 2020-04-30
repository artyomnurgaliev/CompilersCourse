
#include "MethodInvocationStatement.h"
MethodInvocationStatement::MethodInvocationStatement(
    MethodInvocation *method_invocation)
    : method_invocation_(method_invocation) {}
void MethodInvocationStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
MethodInvocation *MethodInvocationStatement::GetMethodInvocation() const {
  return method_invocation_;
}
void MethodInvocationStatement::SetMethodInvocation(
    MethodInvocation *method_invocation) {
  method_invocation_ = method_invocation;
}
