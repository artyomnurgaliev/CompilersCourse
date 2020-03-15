

#include "Expression.h"
class ArrayLengthExpression: public Expression {
public:
  explicit ArrayLengthExpression(Expression* expression);

private:
  Expression* expression_;
};
