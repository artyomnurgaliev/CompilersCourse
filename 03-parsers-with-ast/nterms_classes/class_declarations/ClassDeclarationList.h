//
// Created by artyom on 15.03.2020.
//

#ifndef COMPILERS_03_PARSERS_WITH_AST_NTERMS_CLASSES_CLASS_DECLARATIONS_CLASSDECLARATIONLIST_H_
#define COMPILERS_03_PARSERS_WITH_AST_NTERMS_CLASSES_CLASS_DECLARATIONS_CLASSDECLARATIONLIST_H_

#include "ClassDeclaration.h"
#include "ClassExtendsDeclaration.h"
class ClassDeclarationList {
  void AddClassDeclaration(ClassDeclaration* class_declaration);
  void AddClassDeclaration(ClassExtendsDeclaration* class_declaration);
};

#endif // COMPILERS_03_PARSERS_WITH_AST_NTERMS_CLASSES_CLASS_DECLARATIONS_CLASSDECLARATIONLIST_H_
