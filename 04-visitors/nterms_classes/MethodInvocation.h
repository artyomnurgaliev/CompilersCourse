#pragma once
#include "expressions/Expression.h"
#include <base_elements/BaseElement.h>
#include <nterms_classes/expressions/ExpressionList.h>
#include <string>
class MethodInvocation :public BaseElement{
public:
  MethodInvocation(Expression* expression, std::string identifier);
  MethodInvocation(Expression* expression, std::string identifier, Expression* first, ExpressionList* expression_list);
  void Accept(Visitor* visitor) override;
  Expression *GetExpression() const;
  const std::string &GetIdentifier() const;
  Expression *GetFirst() const;
  ExpressionList *GetExpressionList() const;

private:
  Expression* expression_;
  std::string identifier_;
  Expression* first_{};
  ExpressionList* expression_list_{};
};


