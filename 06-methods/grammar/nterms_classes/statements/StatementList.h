#pragma once
#include <vector>
#include "Statement.h"
class StatementList :public BaseElement{
public:
  void AddStatement(Statement* statement);
  void Accept(Visitor* visitor) override;
  const std::vector<Statement *> &GetStatements() const;
  void SetStatements(const std::vector<Statement *> &statements);

private:
  std::vector<Statement*> statements_;
};


