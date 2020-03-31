#pragma once

#include <nterms_classes/statements/StatementList.h>
#include <string>
class MainClass:public BaseElement {
public:
  MainClass(std::string identifier, StatementList* statement_list);
  void Accept(Visitor* visitor) override;
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);
  StatementList *GetStatementList() const;
  void SetStatementList(StatementList *statement_list);

private:
  std::string identifier_;
  StatementList* statement_list_;
};


