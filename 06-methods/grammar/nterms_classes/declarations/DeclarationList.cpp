

#include "DeclarationList.h"
void DeclarationList::AddDeclaration(Declaration *declaration) {
  declarations_.push_back(declaration);
}
void DeclarationList::Accept(Visitor *visitor) {visitor->Visit(this);}
const std::vector<Declaration *> &DeclarationList::GetDeclarations() const {
  return declarations_;
}
void DeclarationList::SetDeclarations(
    const std::vector<Declaration *> &declarations) {
  declarations_ = declarations;
}
