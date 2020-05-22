#pragma once
#include <string>
#include <nterms_classes/declarations/DeclarationList.h>
class ClassDeclaration :public BaseElement{
public:
  ClassDeclaration() = default;
  ClassDeclaration(std::string identifier, DeclarationList* declaration_list);
  ClassDeclaration(std::string identifier, std::string extends_identifier, DeclarationList* declaration_list);
  void Accept(Visitor* visitor) override;
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);
  const std::string &GetExtendsIdentifier() const;
  void SetExtendsIdentifier(const std::string &extends_identifier);
  DeclarationList *GetDeclarationList() const;
  void SetDeclarationList(DeclarationList *declaration_list);

private:
  std::string identifier_ = "";
  std::string extends_identifier_ = "";
  DeclarationList* declaration_list_ = nullptr;
};

