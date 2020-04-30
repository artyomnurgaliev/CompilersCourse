#include "ClassType.h"

#include <utility>
ClassType::ClassType(std::string extends_identifier,
                     DeclarationList *declaration_list) : extends_identifier_(std::move(extends_identifier)), declaration_list_(declaration_list){}
