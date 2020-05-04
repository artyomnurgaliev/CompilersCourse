#pragma once
#include <string>
#include "Lvalue.h"
#include <nterms_classes/expressions/Expression.h>

class ArrayElementLvalue : public Lvalue {
public:
  bool IsSimple() override;
  explicit ArrayElementLvalue(std::string identifier, Expression* expression);
  void Accept(Visitor* visitor) override;
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);
  Expression *GetExpression() const;
  void SetExpression(Expression *expression);

private:
  std::string identifier_;
  Expression* expression_;;
};

