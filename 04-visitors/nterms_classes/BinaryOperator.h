#pragma once
#include <base_elements/BaseElement.h>
#include <iostream>
#include <string>

class BinaryOperator :public BaseElement{
public:
  explicit BinaryOperator(std::string operator_name);
  std::string GetOperatorName();
  void Accept(Visitor* visitor) override;
private:
  std::string operator_name_;

};

