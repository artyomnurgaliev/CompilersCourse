//
// Created by artyom on 15.03.2020.
//

#include "ArrayElementLvalue.h"

#include <utility>
ArrayElementLvalue::ArrayElementLvalue(std::string identifier,
                                       Expression *expression) : identifier_(std::move(identifier)), expression_(expression) {}
