#pragma once

#include "StatementList.h"
class ScopeStatement: public Statement {
public:
  ScopeStatement(StatementList* statement_list);

private:
  StatementList* statement_list_;
};


