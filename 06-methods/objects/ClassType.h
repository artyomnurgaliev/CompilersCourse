#pragma once
#include <nterms_classes/class_declarations/ClassDeclaration.h>
#include "ObjectType.h"
#include "MethodType.h"
#include <nterms_classes/type/Type.h>
#include <string>
#include <vector>
#include <symbol_table/Symbol.h>

class ClassType : public ObjectType {
public:
  ClassType(const std::string& extends_identifier);
  void AddMethod(const Symbol& symbol, std::shared_ptr<MethodType> method);
  std::unordered_map<Symbol, std::shared_ptr<MethodType>> GetMethods();
  std::string GetTypeName() override;
private:
  std::unordered_map<Symbol, std::shared_ptr<MethodType>> methods_;
  Symbol extends_class_;
  DeclarationList* declaration_list_{};
};
