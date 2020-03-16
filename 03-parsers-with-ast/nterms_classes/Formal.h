#pragma once
#include <string>
#include <nterms_classes/type/Type.h>
class Formal {
public:
  Formal(Type* type, std::string identifier);

private:
  Type* type_;
  std::string identifier_;
};


