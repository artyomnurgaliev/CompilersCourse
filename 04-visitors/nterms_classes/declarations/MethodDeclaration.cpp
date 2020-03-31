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
void MethodDeclaration::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
Type *MethodDeclaration::GetType() const { return type_; }
void MethodDeclaration::SetType(Type *type) { type_ = type; }
const std::string &MethodDeclaration::GetIdentifier() const {
  return identifier_;
}
void MethodDeclaration::SetIdentifier(const std::string &identifier) {
  identifier_ = identifier;
}
FormalList *MethodDeclaration::GetFormals() const { return formals_; }
void MethodDeclaration::SetFormals(FormalList *formals) { formals_ = formals; }
StatementList *MethodDeclaration::GetStatements() const { return statements_; }
void MethodDeclaration::SetStatements(StatementList *statements) {
  statements_ = statements;
}
