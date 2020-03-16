#pragma once
#include "TypeClass.h"
#include <nterms_classes/TypeIdentifier.h>
#include <string>
class SimpleType : public TypeClass {
public:
  explicit SimpleType(std::string simple_type_identifier);
  explicit SimpleType(TypeIdentifier* type_identifier);

private:
  std::string simple_type_identifier_;
};


