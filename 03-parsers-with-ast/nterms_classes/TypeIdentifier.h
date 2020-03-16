#pragma once
#include <string>
class TypeIdentifier {
public:
  explicit TypeIdentifier(std::string identifier);
  std::string GetIdentifier();
private:
  std::string identifier_;
};


