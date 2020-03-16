#pragma once


#include "ClassDeclaration.h"
#include <vector>
class ClassDeclarationList {
public:
  void AddClassDeclaration(ClassDeclaration* class_declaration);

private:
  std::vector<ClassDeclaration*> class_declarations_;
};
