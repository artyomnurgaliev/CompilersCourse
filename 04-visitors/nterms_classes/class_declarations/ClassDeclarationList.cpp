
#include "ClassDeclarationList.h"
void ClassDeclarationList::AddClassDeclaration(
    ClassDeclaration *class_declaration) {
  class_declarations_.push_back(class_declaration);
}
void ClassDeclarationList::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::vector<ClassDeclaration *> &
ClassDeclarationList::GetClassDeclarations() const {
  return class_declarations_;
}
void ClassDeclarationList::SetClassDeclarations(
    const std::vector<ClassDeclaration *> &class_declarations) {
  class_declarations_ = class_declarations;
}
