
#include "ClassDeclaration.h"

#include <utility>
ClassDeclaration::ClassDeclaration(std::string identifier,
                                   DeclarationList *declaration_list)
    : identifier_(std::move(identifier)), declaration_list_(declaration_list) {}

ClassDeclaration::ClassDeclaration(std::string identifier,
                                   std::string extends_identifier,
                                   DeclarationList *declaration_list)
    : identifier_(std::move(identifier)),
      extends_identifier_(std::move(extends_identifier)),
      declaration_list_(declaration_list) {}
void ClassDeclaration::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::string &ClassDeclaration::GetIdentifier() const {
  return identifier_;
}
void ClassDeclaration::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier;
}
const std::string &ClassDeclaration::GetExtendsIdentifier() const {
  return extends_identifier_;
}
void ClassDeclaration::SetExtendsIdentifier(
    const std::string &extends_identifier) {
  extends_identifier_ = extends_identifier;
}
DeclarationList *ClassDeclaration::GetDeclarationList() const {
  return declaration_list_;
}
void ClassDeclaration::SetDeclarationList(DeclarationList *declaration_list) {
  declaration_list_ = declaration_list;
}
