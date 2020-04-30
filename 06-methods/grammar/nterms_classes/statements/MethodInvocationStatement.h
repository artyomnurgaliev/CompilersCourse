#pragma once


#include "Statement.h"
#include <nterms_classes/MethodInvocation.h>
class MethodInvocationStatement : public Statement{
public:
  explicit MethodInvocationStatement(MethodInvocation* method_invocation);
  void Accept(Visitor* visitor) override;
  MethodInvocation *GetMethodInvocation() const;
  void SetMethodInvocation(MethodInvocation *method_invocation);

private:
  MethodInvocation* method_invocation_;
};


