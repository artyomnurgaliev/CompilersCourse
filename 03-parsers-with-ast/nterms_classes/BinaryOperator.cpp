//
// Created by artyom on 15.03.2020.
//

#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(std::string operator_name) : operator_name_(std::move(operator_name)) {}

std::string BinaryOperator::GetOperatorName() { return operator_name_;}