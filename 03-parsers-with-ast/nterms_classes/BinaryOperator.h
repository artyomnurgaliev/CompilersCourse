#pragma once
#include <string>
#include <iostream>

class BinaryOperator {
public:
  explicit BinaryOperator(std::string operator_name);
  std::string GetOperatorName();
private:
  std::string operator_name_;

};

