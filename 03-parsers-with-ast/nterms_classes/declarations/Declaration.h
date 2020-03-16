#pragma once


#include "DeclarationClass.h"
class Declaration {
public:
  Declaration(DeclarationClass* declaration_class);

private:
  DeclarationClass* declaration_class_;
};
