#pragma once

#include <vector>
#include "Declaration.h"
class DeclarationList :public BaseElement{
public:
  void AddDeclaration(Declaration* declaration);
  void Accept(Visitor* visitor) override;
  const std::vector<Declaration *> &GetDeclarations() const;
  void SetDeclarations(const std::vector<Declaration *> &declarations);

private:
  std::vector<Declaration*> declarations_;
};

