//
// Created by artyom on 15.03.2020.
//

#include "MethodDeclaration.h"

#include <utility>
MethodDeclaration::MethodDeclaration(Type *type, std::string identifier,
                                     FormalList *formals,
                                     StatementList *statements)
    : type_(type), identifier_(std::move(identifier)), formals_(formals),
      statements_(statements) {}
MethodDeclaration::MethodDeclaration(Type *type, std::string identifier,
                                     StatementList *statements)
    : type_(type), identifier_(std::move(identifier)), statements_(statements) {
}
