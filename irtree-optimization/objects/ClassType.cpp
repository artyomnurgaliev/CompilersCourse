#include "ClassType.h"

#include <utility>

std::unordered_map<Symbol, std::shared_ptr<MethodType>> ClassType::GetMethodTypes() {
  return method_types_;
}
ClassType::ClassType(const std::string &extends_identifier, ClassDeclaration *class_declaration)
  : class_declaration_(class_declaration), extends_class_(Symbol(extends_identifier)) {
}
void ClassType::AddMethod(const Symbol &symbol, std::shared_ptr<MethodType> method) {
  method_types_[symbol] = std::move(method);
  method_names_.push_back(symbol);
}
ClassDeclaration *ClassType::GetClassDeclaration() {
  return class_declaration_;
}
void ClassType::AddField(const Symbol &symbol, std::shared_ptr<PrimitiveType> field) {
  field_types_[symbol] = std::move(field);
  field_names_.push_back(symbol);
}
std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> ClassType::GetFieldTypes() {
  return field_types_;
}

std::string ClassType::GetTypeName() {
  return "Class";
}
std::vector<Symbol> ClassType::GetFieldNames() {
  return field_names_;
}
std::vector<Symbol> ClassType::GetMethodNames() {
  return method_names_;
}
/*
std::string ClassType::GetObject() {
  return "ClassType";
}
*/