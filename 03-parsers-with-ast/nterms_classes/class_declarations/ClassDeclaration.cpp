
#include "ClassDeclaration.h"

#include <utility>
ClassDeclaration::ClassDeclaration(std::string identifier,
                                   DeclarationList *declaration_list)
    : identifier_(std::move(identifier)), declaration_list_(declaration_list) {}

ClassDeclaration::ClassDeclaration(std::string identifier,
                                   std::string extends_identifier,
                                   DeclarationList *declaration_list)
    : identifier_(std::move(identifier)),
      extends_identifier_(std::move(extends_identifier)),
      declaration_list_(declaration_list) {}