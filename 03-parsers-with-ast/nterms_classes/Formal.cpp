
#include "Formal.h"

#include <utility>
Formal::Formal(Type *type, std::string identifier)
    : type_(type), identifier_(std::move(identifier)) {}
