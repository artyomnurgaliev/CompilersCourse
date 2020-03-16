#pragma once
#include "Formal.h"
#include <string>
#include <vector>
class FormalList {
public:
  void AddFormal(Type* type, std::string identifier);

private:
  std::vector<Formal> formals_;
};

