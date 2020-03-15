

#include "Expression.h"
#include <nterms_classes/type/SimpleType.h>
class ArrayDefenitionExpression : public Expression{
public:
  ArrayDefenitionExpression(SimpleType* simple_type, Expression* expression);

private:
  SimpleType* simple_type_;
  Expression* expression_;
};

