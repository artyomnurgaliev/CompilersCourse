#pragma once

#include "assignments/AssignmentList.h"
#include "expressions/Expression.h"

class Program {
 public:
    Program(MainClass* main_class, ClassDeclarationList* class_declaration_list);
 private:
    MainClass* main_class_;
    ClassDeclarationList class_declaration_list_;
};