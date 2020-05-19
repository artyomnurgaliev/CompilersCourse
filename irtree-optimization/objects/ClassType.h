#pragma once
#include <nterms_classes/class_declarations/ClassDeclaration.h>
#include "ObjectType.h"
#include "MethodType.h"
#include "PrimitiveType.h"
#include <nterms_classes/type/Type.h>
#include <string>
#include <vector>
#include <symbol_table/Symbol.h>

class ClassType : public ObjectType {
public:
  ClassType(const std::string& extends_identifier, ClassDeclaration* class_declaration);
  void AddMethod(const Symbol& symbol, std::shared_ptr<MethodType> method);
  void AddField(const Symbol& symbol, std::shared_ptr<PrimitiveType> field);
  std::unordered_map<Symbol, std::shared_ptr<MethodType>> GetMethodTypes();
  std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> GetFieldTypes();
  ClassDeclaration* GetClassDeclaration();
  std::string GetTypeName() override;
  //std::string GetObject() override;
private:
  ClassDeclaration* class_declaration_;
  std::unordered_map<Symbol, std::shared_ptr<MethodType>> method_types_;
  std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> field_types_;
  Symbol extends_class_;

};
