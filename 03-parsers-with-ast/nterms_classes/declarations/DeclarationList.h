#pragma once

#include <vector>
#include "Declaration.h"
class DeclarationList {
public:
  void AddDeclaration(Declaration* declaration);

private:
  std::vector<Declaration*> declarations_;
};

