#pragma once

#include "Expression.h"
#include <nterms_classes/MethodInvocation.h>
class MethodInvocationExpression : public Expression {
public:
  explicit MethodInvocationExpression(MethodInvocation* method_invocation);
  void Accept(Visitor* visitor) override;
  MethodInvocation *GetMethodInvocation() const;
  void SetMethodInvocation(MethodInvocation *method_invocation);

private:
  MethodInvocation* method_invocation_;
};


