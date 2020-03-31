#pragma once

#include <base_elements/BaseElement.h>
#include <nterms_classes/class_declarations/ClassDeclarationList.h>
#include <nterms_classes/class_declarations/MainClass.h>

class Program : public BaseElement{
 public:
    void Accept(Visitor* visitor) override ;
    Program(MainClass* main_class, ClassDeclarationList* class_declaration_list);

    MainClass* GetMainClass();
    ClassDeclarationList* GetClassDeclarationList();
  private:
    MainClass* main_class_;
    ClassDeclarationList* class_declaration_list_;
};