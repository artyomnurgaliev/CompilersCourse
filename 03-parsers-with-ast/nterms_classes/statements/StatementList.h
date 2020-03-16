#pragma once
#include <vector>
#include "Statement.h"
class StatementList {
public:
  void AddStatement(Statement* statement);

private:
  std::vector<Statement*> statements_;
};


