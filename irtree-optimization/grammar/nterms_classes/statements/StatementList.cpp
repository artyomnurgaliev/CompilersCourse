

#include "StatementList.h"
void StatementList::AddStatement(Statement *statement) {
  statements_.push_back(statement);
}
void StatementList::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::vector<Statement *> &StatementList::GetStatements() const {
  return statements_;
}
void StatementList::SetStatements(const std::vector<Statement *> &statements) {
  statements_ = statements;
}
