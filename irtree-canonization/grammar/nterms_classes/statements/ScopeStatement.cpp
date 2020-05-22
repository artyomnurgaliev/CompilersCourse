

#include "ScopeStatement.h"
ScopeStatement::ScopeStatement(StatementList *statement_list) : statement_list_(statement_list) {}
void ScopeStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
StatementList *ScopeStatement::GetStatementList() const {
  return statement_list_;
}
void ScopeStatement::SetStatementList(StatementList *statement_list) {
  statement_list_ = statement_list;
}
