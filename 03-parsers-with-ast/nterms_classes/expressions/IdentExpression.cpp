#include "IdentExpression.h"

#include <utility>

IdentExpression::IdentExpression(std::string  ident): ident_(std::move(ident)) {}

int IdentExpression::eval() const {
    return 0;
}