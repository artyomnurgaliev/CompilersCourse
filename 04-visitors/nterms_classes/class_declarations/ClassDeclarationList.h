#pragma once


#include "ClassDeclaration.h"
#include <vector>
class ClassDeclarationList :public BaseElement {
public:
  void AddClassDeclaration(ClassDeclaration* class_declaration);
  void Accept(Visitor* visitor) override;
  const std::vector<ClassDeclaration *> &GetClassDeclarations() const;
  void SetClassDeclarations(
      const std::vector<ClassDeclaration *> &class_declarations);

private:
  std::vector<ClassDeclaration*> class_declarations_;
};
