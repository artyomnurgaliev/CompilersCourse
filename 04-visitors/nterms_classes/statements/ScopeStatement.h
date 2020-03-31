#pragma once

#include "StatementList.h"
class ScopeStatement: public Statement {
public:
  ScopeStatement(StatementList* statement_list);
  void Accept(Visitor* visitor) override;
  StatementList *GetStatementList() const;
  void SetStatementList(StatementList *statement_list);

private:
  StatementList* statement_list_;
};


