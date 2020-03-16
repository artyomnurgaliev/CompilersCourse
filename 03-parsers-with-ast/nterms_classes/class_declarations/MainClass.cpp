

#include "MainClass.h"

#include <utility>
MainClass::MainClass(std::string identifier, StatementList *statement_list)
    : identifier_(std::move(identifier)), statement_list_(statement_list) {}
