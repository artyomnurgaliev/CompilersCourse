#include "Program.h"

Program::Program(MainClass *main_class,
                 ClassDeclarationList *class_declaration_list)
    : main_class_(main_class), class_declaration_list_(class_declaration_list) {
}
void Program::Accept(Visitor *visitor) { visitor->Visit(this); }
MainClass *Program::GetMainClass() { return main_class_; }
ClassDeclarationList *Program::GetClassDeclarationList() {
  return class_declaration_list_;
}
