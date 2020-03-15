//
// Created by artyom on 15.03.2020.
//

#include "SimpleLvalue.h"

#include <utility>
SimpleLvalue::SimpleLvalue(std::string identifier) : identifier_(std::move(identifier)) {}
