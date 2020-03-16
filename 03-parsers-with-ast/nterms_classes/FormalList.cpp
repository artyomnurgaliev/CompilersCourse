//
// Created by artyom on 15.03.2020.
//

#include "FormalList.h"

#include <utility>
void FormalList::AddFormal(Type *type, std::string identifier) {
  formals_.emplace_back(type, std::move(identifier));
}

