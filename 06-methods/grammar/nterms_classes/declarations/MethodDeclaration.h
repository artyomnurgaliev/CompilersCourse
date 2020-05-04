#pragma once

#include <nterms_classes/FormalList.h>
#include <nterms_classes/statements/StatementList.h>
class MethodDeclaration : public BaseElement {
public:
  MethodDeclaration(StatementList* statement_list);
  MethodDeclaration(Type* type, std::string identifier, FormalList* formals, StatementList* statements);
  MethodDeclaration(Type* type, std::string identifier, StatementList* statements);
  void Accept(Visitor* visitor) override;
  Type *GetType() const;
  void SetType(Type *type);
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);
  FormalList *GetFormals() const;
  void SetFormals(FormalList *formals);
  StatementList *GetStatements() const;
  void SetStatements(StatementList *statements);

private:
  Type* type_;
  std::string identifier_ = "main";
  FormalList* formals_{};
  StatementList* statements_;
};

