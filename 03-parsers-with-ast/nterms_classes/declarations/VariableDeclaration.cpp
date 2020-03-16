

#include "VariableDeclaration.h"

#include <utility>
VariableDeclaration::VariableDeclaration(Type *type, std::string identifier)
    : type_(type), identifier_(std::move(identifier)) {}
