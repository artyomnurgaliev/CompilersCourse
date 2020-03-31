#pragma once
#include "Expression.h"

#include <string>

class IdentExpression: public Expression {
 public:
  IdentExpression(std::string identifier);
  void Accept(Visitor* visitor) override;
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);

private:
    std::string identifier_;
};