#pragma once
#include <string>
#include <nterms_classes/declarations/DeclarationList.h>
class ClassDeclaration {
public:
  ClassDeclaration(std::string identifier, DeclarationList* declaration_list);
  ClassDeclaration(std::string identifier, std::string extends_identifier, DeclarationList* declaration_list);
private:
  std::string identifier_;
  std::string extends_identifier_;
  DeclarationList* declaration_list_;
};

