

#include "Expression.h"
class ParenthesisExpression: public Expression {
public:
  explicit ParenthesisExpression(Expression* expression);
private:
  Expression* expression_;
};

