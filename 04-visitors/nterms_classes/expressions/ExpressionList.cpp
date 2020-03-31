
#include "ExpressionList.h"
void ExpressionList::AddExpression(Expression *expression) {
  expressions.push_back(expression);
}
void ExpressionList::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::vector<Expression *> &ExpressionList::GetExpressions() const {
  return expressions;
}
void ExpressionList::SetExpressions(
    const std::vector<Expression *> &expressions) {
  ExpressionList::expressions = expressions;
}
