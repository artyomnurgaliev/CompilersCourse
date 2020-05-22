//
// Created by akhtyamovpavel on 4/7/20.
//


#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"


namespace IRT {

class ExpStatement : public Statement {
 public:
  bool IsExp() override;
  explicit ExpStatement(Expression* expression);
  Expression* GetExpression();
  ~ExpStatement() override = default;
  void Accept(Visitor *visitor) override;

 private:
  Expression* expression_;
};

}

