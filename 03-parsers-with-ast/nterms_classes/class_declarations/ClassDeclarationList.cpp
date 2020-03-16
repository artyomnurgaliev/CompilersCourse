
#include "ClassDeclarationList.h"
void ClassDeclarationList::AddClassDeclaration(
    ClassDeclaration *class_declaration) {
  class_declarations_.push_back(class_declaration);
}
