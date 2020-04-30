#pragma once
#include <nterms_classes/class_declarations/ClassDeclaration.h>
#include "ObjectType.h"
#include <nterms_classes/type/Type.h>
#include <string>
#include <vector>

class ClassType : public ObjectType {
public:
  ClassType(std::string  extends_identifier, DeclarationList* declaration_list);

private:
  std::string extends_identifier_;
  DeclarationList* declaration_list_;
};
