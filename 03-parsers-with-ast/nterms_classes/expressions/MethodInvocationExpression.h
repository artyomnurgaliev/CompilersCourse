
#include "Expression.h"
#include <nterms_classes/MethodInvocation.h>
class MethodInvocationExpression : public Expression {
public:
  explicit MethodInvocationExpression(MethodInvocation* method_invocation);
private:
  MethodInvocation* method_invocation_;
};


