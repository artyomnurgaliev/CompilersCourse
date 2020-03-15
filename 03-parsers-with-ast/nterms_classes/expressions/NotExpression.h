//
// Created by artyom on 15.03.2020.
//

#ifndef COMPILERS_03_PARSERS_WITH_AST_CLASSES_EXPRESSIONS_NOTEXPRESSION_H_
#define COMPILERS_03_PARSERS_WITH_AST_CLASSES_EXPRESSIONS_NOTEXPRESSION_H_

#include "Expression.h"
class NotExpression: public Expression {
public:
  explicit NotExpression(Expression* expression);

private:
  Expression* expression_;
};

#endif // COMPILERS_03_PARSERS_WITH_AST_CLASSES_EXPRESSIONS_NOTEXPRESSION_H_
