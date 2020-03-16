#pragma once

#include <nterms_classes/class_declarations/ClassDeclarationList.h>
#include <nterms_classes/class_declarations/MainClass.h>

class Program {
 public:
    Program(MainClass* main_class, ClassDeclarationList* class_declaration_list);
 private:
    MainClass* main_class_;
    ClassDeclarationList* class_declaration_list_;
};