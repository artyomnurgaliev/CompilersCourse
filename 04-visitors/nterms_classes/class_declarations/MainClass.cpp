

#include "MainClass.h"

#include <iostream>
#include <utility>
MainClass::MainClass(std::string identifier, StatementList *statement_list)
    : identifier_(std::move(identifier)), statement_list_(statement_list) {}
void MainClass::Accept(Visitor *visitor) {
  std::cout << "gg!";
  fflush(stdout);
  visitor->Visit(this);
}
const std::string &MainClass::GetIdentifier() const { return identifier_; }
void MainClass::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier;
}
StatementList *MainClass::GetStatementList() const { return statement_list_; }
void MainClass::SetStatementList(StatementList *statement_list) {
  statement_list_ = statement_list;
}
