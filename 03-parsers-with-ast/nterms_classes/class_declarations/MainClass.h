#pragma once

#include <nterms_classes/statements/StatementList.h>
#include <string>
class MainClass {
public:
  MainClass(std::string identifier, StatementList* statement_list);
private:
  std::string identifier_;
  StatementList* statement_list_;
};


