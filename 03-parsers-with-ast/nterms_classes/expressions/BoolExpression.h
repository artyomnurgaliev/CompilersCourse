

#include "Expression.h"
class BoolExpression : public Expression {
public:
  explicit BoolExpression(bool value);

private:
  bool value_;
};

